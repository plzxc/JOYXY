#include "StdAfx.h"
#include "LoginTask.h"
#include "LoginedUserManager.h"
#include "InGameUserManager.h"
#include "ServerManager.h"
#include "Global.h"
#include "LoginCommand.h"
#include "LoginTaskManager.h"
#include "md5.h"

using namespace LoginCmd;


enum LoinError 
{ 
	ELogin_Success=0,
	ELogin_Success2=1,
	ELogin_AlreadyExistAccount=2,
	ELogin_InvalidePassWord=3,
	ELogin_AlreadyLogIn=4,
	ELogin_NeedPay=5, // 需要支付包月费用
};



LoginTask::LoginTask(WORD id, TCPServer* pTcpServer)
: AppieTCPTask(id,pTcpServer)
{
	m_account = "";
	m_state = LS_VERIFY_VERSION;
}

LoginTask::~LoginTask(void)
{
}

void LoginTask::setState(LoginState state)
{
	m_state = state;
}

LoginState LoginTask::getState()
{
	return m_state;
}

bool LoginTask::OnAccept()
{
	printf("有客户端请求连接 id=%u\n", getID());

	// 通知客户端
	LoginCmd::stClientID cmd;
	cmd.id = getID();
	this->sendCmd(&cmd, sizeof(cmd));

	return true;
}

bool LoginTask::OnClose()
{
	printf("客户端 %d 关闭连接\n", getID());

	// 从用户管理器里删除
	LoginedUserManager& loginedUserMgr = LoginedUserManager::getSingleton();
	User* pUser = loginedUserMgr.getUser(m_account.c_str());
	if (pUser != NULL && pUser->getLoginTask() == this) {
		loginedUserMgr.removeEntity(pUser);
		SAFE_DELETE(pUser);
	}

	// 从管理器里删除
	ServerManager& serverMgr = ServerManager::getSingleton();
	Server* pServer = serverMgr.getServerByTempID(getID());
	if (pServer) {
		if (pServer->getType() == GameServer) {
			printf("游戏服务器断开链接 id=%d, name=%s\n", pServer->getID(), pServer->getName());
			InGameUserManager::getSingleton().deleteAllUserForGameServer(pServer->getID());
		} else if (pServer->getType() == GatewayServer) {
			printf("网关服务器断开链接 id=%d, name=%s\n", pServer->getID(), pServer->getName());
			InGameUserManager::getSingleton().deleteAllUserForGatewayServer(pServer->getID());
		} else {
			printf("未知类型的服务器断开链接 id=%d, name=%s\n", pServer->getID(), pServer->getName());
		}
		serverMgr.removeServer(pServer);
		SAFE_DELETE(pServer);
	}

	return true;
}


// 处理登陆和客户端之间的消息
bool LoginTask::procClientCmd(stBaseCommand* pCmd, DWORD cmdLen)
{
#ifdef LIMIT_LOCAL
	if ( strcmp(getIP(), "127.0.0.1") != 0 ) {
		disconnect();
		return true;
	}
#endif

	using namespace LoginCmd;
	bool isDisconnect = false;
	byte message = pCmd->message;
	WORD nClient = getID();
	switch(message)
	{
	case LOGIN_CMD_CHECK_VERSION:	// 检查版本号
		{
			if (getState() != LS_VERIFY_VERSION) {
				printf("检查版本号出现异常，状态不正确，断开连接\n");
				isDisconnect = true;
				break;
			}

			stCheckVersion* rev = (stCheckVersion*)pCmd;
			if (rev->version == SERVER_VERSION){
				setState(LS_VERIFY_ACCOUNT);
				rev->result = TRUE;
			} else {
				rev->result = FALSE;
			}
			pCmd->message = LOGIN_CMD_CHECK_VERSION_RESULT;
			sendCmd(pCmd, sizeof(stCheckVersion));
		}
		break;
	case LOGIN_CMD_LOGIN:	// 登陆服务器
		{
			if (getState() != LS_VERIFY_ACCOUNT) {
				printf("登陆服务器出现异常，状态不正确，断开连接\n");
				isDisconnect = true;
				break;
			}

			stLogin* rev = (stLogin*)pCmd;

			// 解密消息
			XorCommand(rev,cmdLen,message);

			stLoginResult cmd;
			strncpy(cmd.account, rev->account, MAX_ACCOUNT_SIZE);

			// check account and password
			bool success = VerifyAccount(rev->account, rev->password, cmd.result);
			if (!success) {
				// 验证失败
				sendCmd(&cmd, sizeof(cmd));
				break;
			}

			// 已经登录过，不能登录
			User* pInGameUser = InGameUserManager::getSingleton().getUser(rev->account);
			if (pInGameUser != NULL) {
				UINT times = pInGameUser->getLoginTimes();
				if (times < 2) {
					// 小于2次，不让登陆
					pInGameUser->setLoginTimes(times+1);
					cmd.result = ELogin_AlreadyLogIn;
					sendCmd(&cmd, sizeof(cmd));
					break;
				} else {
					// 把网关的玩家一起踢下线
					Server* pGatewaySvr = ServerManager::getSingleton().getServer(pInGameUser->getGatewayId());
					if (pGatewaySvr != NULL && pGatewaySvr->getType() == GatewayServer) {
						LoginTask* task = LoginTaskManager::getSingleton().getTask((UINT)pGatewaySvr->getLongID());
						if (task != NULL) {
							stUnregGatewayUser cmdUnreg;
							strncpy(cmdUnreg.account, rev->account, MAX_ACCOUNT_SIZE);
							task->sendCmd(&cmdUnreg, sizeof(cmdUnreg));
						}
					}

					// 大于3次，把在线的踢下去
					InGameUserManager::getSingleton().removeEntity(pInGameUser);
					printf("玩家强行下线, accname=%s\n", rev->account);
					SAFE_DELETE(pInGameUser);
				}
			}

			User* pLoginedUser = LoginedUserManager::getSingleton().getUser(rev->account);
			if (pLoginedUser != NULL) {
				LoginTask* task = pLoginedUser->getLoginTask();
				if (task != NULL) {
					// 把登陆服中在线的踢下线
					printf("把在登录状态的玩家踢下线, accname=%s\n", rev->account);
					task->disconnect();
					LoginedUserManager::getSingleton().removeEntity(pLoginedUser);
					SAFE_DELETE(pLoginedUser);
				}
			}

			// success
			// 加入LoginedUserManager
			User* pUser = new User(this);
			pUser->GenerateKey();
			pUser->setName(rev->account);
			pUser->setIP(this->getIP());
			if ( !LoginedUserManager::getSingleton().addEntity(pUser) ) {
				printf("加入LoginedUserManager失败 account=%s\n", rev->account);
				cmd.result = ELogin_AlreadyLogIn;
				sendCmd(&cmd, sizeof(cmd));
				break;
			}

			// 真的成功了
			m_account = rev->account;
			setState(LS_VERIFY_KEY);

			strncpy(cmd.key,pUser->getKey(),sizeof(cmd.key)-1);
			cmd.result = 0;
			sendCmd(&cmd, sizeof(cmd));
		}
		break;
	case LOGIN_CMD_KEEPALIVE:	// 心跳协议
		{
			//User* pUser = UserManager::getSingleton().getUser(nClient);
			//if (pUser == NULL || !pUser->getLoginOK()) {
			//	isDisconnect = true;
			//	break;
			//}

			stKeepAlive* rev = (stKeepAlive*)pCmd;

			// 解密消息
			XorCommand(rev,cmdLen,message);

			//if (strncmp(pUser->getAccount(),rev->account,MAX_ACCOUNT_SIZE) != 0) {
			//	isDisconnect = true;
			//	break;
			//}
		}
		break;
	case LOGIN_CMD_VERIFY_KEY:	// 验证key
		{
			stVerifyKey* rev = (stVerifyKey*)pCmd;

			// 解密消息
			XorCommand(rev,cmdLen, message);

			if (getState() != LS_VERIFY_KEY) {
				printf("验证Key出现异常，状态不正确，断开连接\n");
				isDisconnect = true;
				break;
			}

			User* pUser = LoginedUserManager::getSingleton().getUser(rev->account);
			if (pUser == NULL) {
				printf("验证Key出现异常，用户不存在，断开连接\n");
				isDisconnect = true;
				break;
			}

			// verify key
			if (strncmp(rev->key,pUser->getKey(),sizeof(rev->key)) != 0) {
				// key 验证失败，断开客户端
				printf("验证Key出现不一致，断开连接\n");
				isDisconnect = true;
				break;
			}

			// 通过了版本验证，用户名和密码验证，密钥验证，
			// 登录服务器返回游戏服务器列表给客户端
			// 登陆服务器需要把密钥同步到游戏服务器
			// 客户端在连接游戏服的时候需要用密钥做验证
			// to do ....
			stServerList* serverList = NULL;
			BUFF_CMD(serverList, stServerList);
			serverList->num = (WORD)ServerManager::getSingleton().size();
			if (serverList->getSize() >= MAX_USER_PACK_SIZE) {
				// 游戏服务器数据过多
				printf("游戏服务器数据过多\n");
				isDisconnect = true;
				break;
			}

			struct stAllServer : public stCallBack<Server> 
			{
				int count;
				stServerList* pServerList;

				stAllServer(stServerList* serverlist2) : count(0), pServerList(serverlist2)
				{ }

				virtual bool exec(Server* entity) 
				{
					if (entity->getType() != GameServer)
						return true;

					pServerList->serverInfo[count].id = entity->getID();
					strncpy(pServerList->serverInfo[count].name,entity->getName(),49);
					/*strncpy(pServerList->serverInfo[count].IP,entity->getIP(),49);
					pServerList->serverInfo[count].port = entity->getPort();*/
					pServerList->serverInfo[count].state = entity->getState() == SS_Close ? 0 : 1;
					pServerList->serverInfo[count].isNewServer = entity->isNew();
					pServerList->serverInfo[count].onlinecount = entity->getOnlineNum();
					pServerList->serverInfo[count].maxonlinecount = entity->getMaxNum();
					count++;
					return true; 
				}
			};

			stAllServer cb(serverList);
			ServerManager::getSingleton().exec(cb);
			serverList->num = cb.count;

			setState(LS_SERVERLIST);
			sendCmd(serverList,serverList->getSize());
		}
		break;
	case LOGIN_CMD_ENTER_GAMESERVER:	// 进入游戏服务器
		{
			stEnterGameServer* rev = (stEnterGameServer*)pCmd;

			// 解密消息
			XorCommand(rev,cmdLen,message);

			if (getState() != LS_SERVERLIST) {
				printf("进入游戏服出现异常，状态不正确，断开连接\n");
				isDisconnect = true;
				break;
			}

			User* pUser = LoginedUserManager::getSingleton().getUser(rev->account);
			if (pUser == NULL) {
				printf("验证Key出现异常，用户不存在，断开连接\n");
				isDisconnect = true;
				break;
			}

			// verify key
			if (strncmp(rev->key,pUser->getKey(),sizeof(rev->key)) != 0) {
				// key 验证失败，断开客户端
				printf("进入游戏服出现Key不一致，断开连接\n");
				isDisconnect = true;
				break;
			}

			// 同步密钥到分配的网关
			Server* pServer = ServerManager::getSingleton().findGatewayServer(rev->gameServerID);
			if (pServer == NULL || pServer->getType() != GatewayServer) {
				// 请求的服务器不存在，或未开启，断开客户端
				printf("请求的服务器不存在，或未开启\n");
				rev->result = 1;
				sendCmd(rev, cmdLen);
				break;
			}

			setState(LS_SYNC_KEY);

			logger.info("IP是(%s)的账号(%s)上线，当前在线人数(%d)", 
				this->getIP(), pUser->getName(), InGameUserManager::getSingleton().size());

			// 先同步密钥到网关服务器, 等网关服务器返回后，再通知客户端，并断开连接
			stRegUserToGateway cmd;
			strncpy(cmd.account, pUser->getName(), MAX_ACCOUNT_SIZE);
			cmd.zoneId = rev->gameServerID;
			cmd.gatewayId = pServer->getID();
			strncpy(cmd.key, pUser->getKey(), sizeof(cmd.key)-1);
			LoginTask* task = LoginTaskManager::getSingleton().getTask((UINT)pServer->getLongID());
			if (task) task->sendCmd(&cmd, sizeof(cmd));
		}
		break;
	case 3:
		{
			// 客户端退出登录服务器
		}
		break;
	default:
		{
#ifdef _DEBUG
			printf("LoginForClient未处理消息 %d\n", message);
#endif
			return false;
		}
		break;
	}

	if (isDisconnect) {
		printf("LoginTask 非法的客户端，服务器主动断开连接 id=%d, message=%d, ip=%s\n", nClient, message, getIP());
		//disconnect();
	}

//#ifdef _DEBUG
//	printf("已处理消息 %d\n", message);
//#endif
	return true;
}

// 处理登陆和游戏服务器之间的消息
bool LoginTask::procGameServerCmd(stServerBaseCommand* pCmd, DWORD cmdLen)
{
	WORD nClient = getID();
	bool isDisconnect = false;
	switch(pCmd->para)
	{
	case REGISTER_GAMESERVER:	// 游戏服务器请求注册
		{
			stRegisterGameServer* rev = (stRegisterGameServer*)pCmd;

			Server* pServer = ServerManager::getSingleton().getServer(rev->id);
			if (pServer != NULL) {
				isDisconnect = true;
				printf("该游戏服务器已经注册过了 id=%d\n", rev->id);
				break;
			}

			pServer = ServerManager::getSingleton().getServerByTempID(nClient);
			if (pServer != NULL) {
				isDisconnect = true;
				printf("该游戏服务器已经注册过了 nClient=%d\n", nClient);
				break;
			}

			// 和数据库中的数据进行比较，判断此服务器是否合法
			if (!VerifyServer(rev->id, this->getIP(), rev->port, rev->name, rev->isNew)) {
				isDisconnect = true;
				printf("注册游戏服务器失败 nClient=%d, id=%d, ip=%s, port=%d \n",
					nClient, rev->id,this->getIP(),rev->port);
				break;
			}

			// 验证成功, 加入管理器
			Server* pNewServer = new Server;
			pNewServer->setID(rev->id);
			pNewServer->setZoneId(rev->id);
			pNewServer->setType(GameServer);
			pNewServer->setLongID(nClient);
			pNewServer->setName(rev->name);
			pNewServer->setIsNew(rev->isNew);
			pNewServer->setIP(this->getIP());
			pNewServer->setPort(rev->port);
			pNewServer->setOnlineNum(0);
			pNewServer->setMaxNum(1000);
			if (!ServerManager::getSingleton().addServer(pNewServer)) {
				SAFE_DELETE(pNewServer);
				isDisconnect = true;
				printf("服务器加入管理器失败 nClient=%d\n", nClient);
				break;
			}
			printf("注册游戏服务器成功 id=%d, name=%s, isnew=%d ip=%s, port=%d, online=%d, maxuser=%d\n\n", 
				rev->id, rev->name, rev->isNew, this->getIP(), rev->port, 0, 1000);

			// 通知客户端
			stRegisterGameServerResult cmd;
			cmd.result = 0;
			sendCmd(&cmd, sizeof(stRegisterGameServerResult));
		}
		break;
	case GAMESERVER_USERENDTIME:	// 查询玩家的游戏结束时间
		{
			
			stGameServerUserEndTime* rev = (stGameServerUserEndTime*)pCmd;
			rev->endtime = GetUserEndTime(rev->account);
            sendCmd(rev, cmdLen);
		}
		break;
	case GAMESERVER_GET_USER_CASHINFO:	// 查询余额等信息
		{
			stGameServerGetUserCashInfo* rev = (stGameServerGetUserCashInfo*)pCmd;
			GetUserCashInfo(rev->account, rev->cashpoint, rev->hongli);
            sendCmd(rev, cmdLen);
		}
		break;
	case GAMESERVER_UPDATE_USER_CASHINFO:	// 扣除点数和积分
		{
			stGameServerUpdateUserCashInfo* rev = (stGameServerUpdateUserCashInfo*)pCmd;
			bool success = SubUserCashInfo(rev->account, rev->cashpoint, rev->hongli);
			GetUserCashInfo(rev->account, rev->cashpoint, rev->hongli);
			rev->result = success ? 0 : 1;
			sendCmd(rev, cmdLen);
		}
		break;
	case GAMESERVER_STOP_ACCOUNT:			// 封号
		{
			stGameServerStopAccount* rev = (stGameServerStopAccount*)pCmd;
            ChangeAccountStatus(rev->account, "S");
			sendCmd(rev, cmdLen);
		}
		break;
	case UPDATE_GAMESERVER_INFO:	// 游戏服务器更新在线信息
		{
			stUpdateGameServerInfo* rev = (stUpdateGameServerInfo*)pCmd;
			printf("服务器状态: id=%u, online=%u, max=%u, state=%u\n",
				rev->serverId, rev->onlineNum, rev->maxNum, rev->state);
		}
		break;
	case GAMESERVER_PING:			// 游戏服务器ping登陆服务器
		{
			stGameServerPing* rev = (stGameServerPing*)pCmd;
		}
		break;
		/*
		case REG_USER_TO_GATEWAY:		// 登陆服务器同步密钥到游戏服务器
		{
		stRegUserToGateway* rev = (stRegUserToGateway*)pCmd;

		User* pUser = LoginedUserManager::getSingleton().getUser(rev->accId);
		if (!pUser) 
		break;

		stEnterGameServer cmd;
		cmd.id = rev->id;
		cmd.gameServerID = rev->gameServerID;
		strncpy(cmd.account, rev->account,MAX_ACCOUNT_SIZE);
		strncpy(cmd.key, rev->key, sizeof(cmd.key)-1);

		if (rev->result != 0) {
		printf("同步密钥失败\n");
		cmd.result = 1;
		} else {
		cmd.result = 0;
		}

		// 通知客户端进入服务器的结果
		pUser->sendCmd(&cmd, sizeof(cmd));

		pUser->setServerId(rev->gameServerID);
		if (cmd.result == 0) {
		// 进入游戏成功，回收的时候，不会删除user对象，而是移入LoginedUserManager
		pUser->setEnterGame(true);
		} else {
		// 进入游戏失败，回收的时候，删除user对象，不进入LoginedUserManager
		pUser->setEnterGame(false);
		}
		LoginedUserManager::getSingleton().removeEntity(pUser);
		RecycleUserManager::getSingleton().addRecycleUser(pUser, 2000);
		}
		break;
		*/
		/*case USER_LOGOUT:
		{
		stUserLogout* rev = (stUserLogout*)pCmd;
		User* pUser = InGameUserManager::getSingleton().getUser(rev->accId);
		if (pUser == NULL) {
		printf("注销用户失败, 此账号不存在, accid=%u\n", rev->accId);
		break;
		}
		InGameUserManager::getSingleton().removeEntity(pUser);
		printf("用户注销, accid=%u, accname=%s\n", rev->accId, pUser->getName());
		SAFE_DELETE(pUser);
		}
		break;*/
	default:
		{
#ifdef _DEBUG
			printf("LoginForServer未处理消息 %d\n", pCmd->cmd);
#endif
			return false;
		}
		break;
	}

	if (isDisconnect) {
		disconnect();
		printf("TaskForServer 非法的客户端，服务器主动断开连接 id=%d, message=%d\n", nClient, pCmd->cmd);
	}

	//#ifdef _DEBUG
	//	printf("已处理消息 %d\n", pCmd->cmd);
	//#endif

	return true;
}

// 处理登陆和网关服务器之间的消息
bool LoginTask::procGatewayServerCmd(stServerBaseCommand* pCmd, DWORD cmdLen)
{
	WORD nClient = getID();
	bool isDisconnect = false;
	switch(pCmd->para)
	{
	case REGISTER_GATEWAYSERVER:	// 网关服务器请求注册
		{
			stRegisterGatewayServer* rev = (stRegisterGatewayServer*)pCmd;

			Server* pServer = ServerManager::getSingleton().getServer(rev->id);
			if (pServer != NULL) {
				isDisconnect = true;
				printf("该网关服务器已经注册过了 id=%d\n", rev->id);
				break;
			}

			pServer = ServerManager::getSingleton().getServerByTempID(nClient);
			if (pServer != NULL) {
				isDisconnect = true;
				printf("该网关服务器已经注册过了 nClient=%d\n", nClient);
				break;
			}

			//// 和数据库中的数据进行比较，判断此服务器是否合法
			//if (!VerifyServer(rev->id, rev->ip, rev->port, rev->name, rev->isNew)) {
			//	isDisconnect = true;
			//	printf("注册游戏服务器失败 nClient=%d, id=%d, ip=%s, port=%d \n",
			//		nClient, rev->id,rev->ip,rev->port);
			//	break;
			//}

			// 验证成功, 加入管理器
			Server* pNewServer = new Server;
			pNewServer->setID(rev->id);
			pNewServer->setZoneId(rev->zoneid);
			pNewServer->setType(GatewayServer);
			pNewServer->setLongID(nClient);
			pNewServer->setName(rev->name);
			pNewServer->setIsNew(rev->isNew);
			pNewServer->setIP(this->getIP());
			pNewServer->setPort(rev->port);
			pNewServer->setOnlineNum(0);
			pNewServer->setMaxNum(1000);
			if (!ServerManager::getSingleton().addServer(pNewServer)) {
				SAFE_DELETE(pNewServer);
				isDisconnect = true;
				printf("服务器加入管理器失败 nClient=%d\n", nClient);
				break;
			}

			printf("注册网关服务器成功 id=%d, name=%s, isnew=%d ip=%s, port=%d, online=%d, maxuser=%d\n\n", 
				rev->id, rev->name, rev->isNew, this->getIP(), rev->port, 0, 1000);

			// 通知客户端
			stRegisterGatewayServerResult cmd;
			cmd.result = 0;
			sendCmd(&cmd, sizeof(stRegisterGatewayServerResult));
		}
		break;
		//case UPDATE_GAMESERVER_INFO:	// 游戏服务器更新在线信息
		//	{
		//		stUpdateGameServerInfo* rev = (stUpdateGameServerInfo*)pCmd;
		//		printf("服务器状态: id=%u, online=%u, max=%u, state=%u\n",
		//			rev->serverId, rev->onlineNum, rev->maxNum, rev->state);
		//	}
		//	break;
	case REG_USER_TO_GATEWAY:		// 登陆服务器同步客户端的密钥到游戏服务器
		{
			stRegUserToGateway* rev = (stRegUserToGateway*)pCmd;

			User* pUser = LoginedUserManager::getSingleton().getUser(rev->account);
			if (pUser == NULL) {
				printf("返回同步密钥结果时，没有找到指定用户 account=%s\n", rev->account);
				break;
			}

			LoginTask* loginTask = pUser->getLoginTask();
			if (loginTask == NULL || loginTask->getState() != LS_SYNC_KEY) {
				printf("返回同步密钥结果时，状态不正确 account=%s\n", rev->account);
				break;
			}

			stEnterGameServer cmd;
			cmd.gameServerID = rev->zoneId;
			strncpy(cmd.account, rev->account,MAX_ACCOUNT_SIZE);
			strncpy(cmd.key, rev->key, sizeof(cmd.key)-1);

			// 查找网关
			Server* pGateway = ServerManager::getSingleton().getServer(rev->gatewayId);
			if (pGateway == NULL || pGateway->getType() != GatewayServer) {
				printf("没有找到指定的网关\n");
				rev->result = 1;
				pUser->sendCmd(&cmd, sizeof(cmd));
				break;
			}

			strncpy(cmd.IP, pGateway->getIP(), sizeof(cmd.IP)-1);
			cmd.port = pGateway->getPort();

			if (rev->result != 0) {
				printf("同步密钥失败 account=%s, key=%s\n", rev->account, rev->key);
				cmd.result = 1;
			} else {
				printf("同步密钥成功 account=%s key=%s\n", rev->account, rev->key);
				cmd.result = 0;
			}

			// 通知客户端进入服务器的结果
			pUser->sendCmd(&cmd, sizeof(cmd));

			LoginedUserManager::getSingleton().removeEntity(pUser);

			if (cmd.result == 0) {
				// 加入InGameUserManager管理器
				pUser->setZoneId(pGateway->getZoneId());
				pUser->setGatewayId(pGateway->getID());
				InGameUserManager::getSingleton().addEntity(pUser);
			} else {
				// 删除User对象
				SAFE_DELETE(pUser);
			}

			// 10秒后断开客户端
			if (pUser) pUser->disconnect(10);
		}
		break;
	case UNREG_USER:
		{
			// 注销游戏中的玩家
			stUnregUser* rev = (stUnregUser*)pCmd;
			User* pUser = InGameUserManager::getSingleton().getUser(rev->account);
			if (pUser == NULL) {
				printf("注销账号失败, 此账号不存在, account=%s\n", rev->account);
				break;
			}

			if (strcmp(pUser->getKey(),rev->key) != 0) {
				printf("注销账号失败, 密钥不正确, account=%s\n", rev->account);
				break;
			}

			InGameUserManager::getSingleton().removeEntity(pUser);
			logger.info("IP是(%s)的账号(%s)注销，当前在线人数(%d)", 
				pUser->getIP(), pUser->getName(), InGameUserManager::getSingleton().size());
			SAFE_DELETE(pUser);
		}
		break;
	case GATEWAYSERVER_PING:
		{ }
		break;
	default:
		{
#ifdef _DEBUG
			printf("LoginForServer未处理消息 %d\n", pCmd->para);
#endif
			return false;
		}
		break;
	}

	if (isDisconnect) {
		//disconnect();
		printf("TaskForServer 非法的客户端，服务器主动断开连接 id=%d, message=%d\n", nClient, pCmd->cmd);
	}

	//#ifdef _DEBUG
	//	printf("已处理消息 %d\n", pCmd->cmd);
	//#endif

	return true;
}


bool LoginTask::processMessage(void *data, DWORD cmdLen)
{
	stServerBaseCommand* pCmd = (stServerBaseCommand*)data;
	byte cmd = pCmd->cmd;
	if (cmd == LOGIN_GAME_CMD) {
		// 游戏服务器和登录服务器之间的消息
		procGameServerCmd((stServerBaseCommand*)data, cmdLen);
	} else if (cmd == LOGIN_GATEWAY_CMD) {
		// 网关和登录服务器之间的消息
		procGatewayServerCmd((stServerBaseCommand*)data, cmdLen);
	} else {
		// 其他情况为客户端和登录服务器之间的消息
		procClientCmd((stBaseCommand*)data, cmdLen);
	}

	return true;
}



bool LoginTask::GetUserCashInfo(const char* account, UINT& cashpoint, UINT& hongli)
{
	cashpoint = 0;
	hongli = 0;

	AutoDBHandle autoHandle(g_dbPool);
	DBHandle* handle = autoHandle.handle();
	if (handle == NULL) return false;

	if ( !handle->queryF("SELECT cashpoint,hongli FROM account WHERE name='%s'", account) )
		return false;

	UINT row = handle->getRowNum();
	if (row != 1) return false;

	handle->fetchRow();
	cashpoint = handle->getIntField(0);
	hongli = handle->getIntField(1);

	return true;
}

bool LoginTask::SubUserCashInfo(const char* account, UINT cashpoint, UINT hongli)
{
	AutoDBHandle autoHandle(g_dbPool);
	DBHandle* handle = autoHandle.handle();
	if (handle == NULL) return false;

	if ( !handle->queryF("UPDATE account SET cashpoint=cashpoint-%u , hongli=hongli-%u WHERE name='%s' AND cashpoint >= %u AND hongli >= %u",
		cashpoint, hongli, account, cashpoint, hongli) ) 
	{
		return false;
	}	

	UINT row = handle->getRowNum();
	if (row != 1) return false;

	return true;
}

bool LoginTask::ChangeAccountStatus(const char* account, const char* status)
{
	AutoDBHandle autoHandle(g_dbPool);
	DBHandle* handle = autoHandle.handle();
	if (handle == NULL) return false;

	if ( !handle->queryF("UPDATE account SET status='%s' WHERE name='%s'", status, account) ) 
	{
		return false;
	}	

	UINT row = handle->getRowNum();
	if (row != 1) return false;

	return true;
}

time_t LoginTask::GetUserEndTime(const char* account)
{
	AutoDBHandle autoHandle(g_dbPool);
	DBHandle* handle = autoHandle.handle();
	if (handle == NULL) return 0;

	if ( !handle->queryF("SELECT UNIX_TIMESTAMP(endtime) FROM account WHERE name='%s' AND status='A'", account) )
		return 0;

	UINT row = handle->getRowNum();
	if (row != 1) return 0;

	handle->fetchRow();
	time_t endTime = handle->getIntField(0);
	return endTime;
}

bool LoginTask::VerifyAccount(const char* account, const char* password, WORD& error)
{
	AutoDBHandle autoHandle(g_dbPool);
	DBHandle* handle = autoHandle.handle();
	if (handle == NULL) return false;

	string md5Pswd = MD5(password).toString();
	if (!handle->queryF("SELECT UNIX_TIMESTAMP(endtime) FROM account WHERE name='%s' AND password='%s' AND status='A'", account, md5Pswd.c_str()))
		return false;

	UINT row = handle->getRowNum();

	if (row == -1)
		return false;

	if (row == 0) {
#ifdef AUTO_REGISTER
		if (!handle->queryF("INSERT INTO account(name,password) VALUES('%s','%s')", account, password))
			return false;
		return true;
#else
		error = ELogin_InvalidePassWord;
		return false;
#endif
	}

	if (row != 1)
		return false;

// 	time_t endTime = GetUserEndTime(account);
// 	time_t curTime = ::time(NULL);
// 	if (endTime < curTime) {
// 		error = ELogin_NeedPay;
// 		return false;
// 	}

	return true;
}


bool LoginTask::VerifyServer(DWORD id, const char* ip, WORD port, char* name, BOOL& isNew)
{
	AutoDBHandle autoHandle(g_dbPool);
	DBHandle* handle = autoHandle.handle();
	if (handle == NULL)
		return false;

	if (!handle->queryF("SELECT name,isnew FROM servers WHERE id=%d AND ip='%s' AND port=%d", id,ip,port))
		return false;

	if (handle->getRowNum() != 1)
		return false;

	if (handle->fetchRow()) {
		strncpy(name,handle->getStrField(0).c_str(),MAX_NAME_SIZE);
		isNew = handle->getIntField(1);
		return true;
	}

	return false;
}



