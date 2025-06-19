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
	ELogin_NeedPay=5, // ��Ҫ֧�����·���
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
	printf("�пͻ����������� id=%u\n", getID());

	// ֪ͨ�ͻ���
	LoginCmd::stClientID cmd;
	cmd.id = getID();
	this->sendCmd(&cmd, sizeof(cmd));

	return true;
}

bool LoginTask::OnClose()
{
	printf("�ͻ��� %d �ر�����\n", getID());

	// ���û���������ɾ��
	LoginedUserManager& loginedUserMgr = LoginedUserManager::getSingleton();
	User* pUser = loginedUserMgr.getUser(m_account.c_str());
	if (pUser != NULL && pUser->getLoginTask() == this) {
		loginedUserMgr.removeEntity(pUser);
		SAFE_DELETE(pUser);
	}

	// �ӹ�������ɾ��
	ServerManager& serverMgr = ServerManager::getSingleton();
	Server* pServer = serverMgr.getServerByTempID(getID());
	if (pServer) {
		if (pServer->getType() == GameServer) {
			printf("��Ϸ�������Ͽ����� id=%d, name=%s\n", pServer->getID(), pServer->getName());
			InGameUserManager::getSingleton().deleteAllUserForGameServer(pServer->getID());
		} else if (pServer->getType() == GatewayServer) {
			printf("���ط������Ͽ����� id=%d, name=%s\n", pServer->getID(), pServer->getName());
			InGameUserManager::getSingleton().deleteAllUserForGatewayServer(pServer->getID());
		} else {
			printf("δ֪���͵ķ������Ͽ����� id=%d, name=%s\n", pServer->getID(), pServer->getName());
		}
		serverMgr.removeServer(pServer);
		SAFE_DELETE(pServer);
	}

	return true;
}


// �����½�Ϳͻ���֮�����Ϣ
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
	case LOGIN_CMD_CHECK_VERSION:	// ���汾��
		{
			if (getState() != LS_VERIFY_VERSION) {
				printf("���汾�ų����쳣��״̬����ȷ���Ͽ�����\n");
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
	case LOGIN_CMD_LOGIN:	// ��½������
		{
			if (getState() != LS_VERIFY_ACCOUNT) {
				printf("��½�����������쳣��״̬����ȷ���Ͽ�����\n");
				isDisconnect = true;
				break;
			}

			stLogin* rev = (stLogin*)pCmd;

			// ������Ϣ
			XorCommand(rev,cmdLen,message);

			stLoginResult cmd;
			strncpy(cmd.account, rev->account, MAX_ACCOUNT_SIZE);

			// check account and password
			bool success = VerifyAccount(rev->account, rev->password, cmd.result);
			if (!success) {
				// ��֤ʧ��
				sendCmd(&cmd, sizeof(cmd));
				break;
			}

			// �Ѿ���¼�������ܵ�¼
			User* pInGameUser = InGameUserManager::getSingleton().getUser(rev->account);
			if (pInGameUser != NULL) {
				UINT times = pInGameUser->getLoginTimes();
				if (times < 2) {
					// С��2�Σ����õ�½
					pInGameUser->setLoginTimes(times+1);
					cmd.result = ELogin_AlreadyLogIn;
					sendCmd(&cmd, sizeof(cmd));
					break;
				} else {
					// �����ص����һ��������
					Server* pGatewaySvr = ServerManager::getSingleton().getServer(pInGameUser->getGatewayId());
					if (pGatewaySvr != NULL && pGatewaySvr->getType() == GatewayServer) {
						LoginTask* task = LoginTaskManager::getSingleton().getTask((UINT)pGatewaySvr->getLongID());
						if (task != NULL) {
							stUnregGatewayUser cmdUnreg;
							strncpy(cmdUnreg.account, rev->account, MAX_ACCOUNT_SIZE);
							task->sendCmd(&cmdUnreg, sizeof(cmdUnreg));
						}
					}

					// ����3�Σ������ߵ�����ȥ
					InGameUserManager::getSingleton().removeEntity(pInGameUser);
					printf("���ǿ������, accname=%s\n", rev->account);
					SAFE_DELETE(pInGameUser);
				}
			}

			User* pLoginedUser = LoginedUserManager::getSingleton().getUser(rev->account);
			if (pLoginedUser != NULL) {
				LoginTask* task = pLoginedUser->getLoginTask();
				if (task != NULL) {
					// �ѵ�½�������ߵ�������
					printf("���ڵ�¼״̬�����������, accname=%s\n", rev->account);
					task->disconnect();
					LoginedUserManager::getSingleton().removeEntity(pLoginedUser);
					SAFE_DELETE(pLoginedUser);
				}
			}

			// success
			// ����LoginedUserManager
			User* pUser = new User(this);
			pUser->GenerateKey();
			pUser->setName(rev->account);
			pUser->setIP(this->getIP());
			if ( !LoginedUserManager::getSingleton().addEntity(pUser) ) {
				printf("����LoginedUserManagerʧ�� account=%s\n", rev->account);
				cmd.result = ELogin_AlreadyLogIn;
				sendCmd(&cmd, sizeof(cmd));
				break;
			}

			// ��ĳɹ���
			m_account = rev->account;
			setState(LS_VERIFY_KEY);

			strncpy(cmd.key,pUser->getKey(),sizeof(cmd.key)-1);
			cmd.result = 0;
			sendCmd(&cmd, sizeof(cmd));
		}
		break;
	case LOGIN_CMD_KEEPALIVE:	// ����Э��
		{
			//User* pUser = UserManager::getSingleton().getUser(nClient);
			//if (pUser == NULL || !pUser->getLoginOK()) {
			//	isDisconnect = true;
			//	break;
			//}

			stKeepAlive* rev = (stKeepAlive*)pCmd;

			// ������Ϣ
			XorCommand(rev,cmdLen,message);

			//if (strncmp(pUser->getAccount(),rev->account,MAX_ACCOUNT_SIZE) != 0) {
			//	isDisconnect = true;
			//	break;
			//}
		}
		break;
	case LOGIN_CMD_VERIFY_KEY:	// ��֤key
		{
			stVerifyKey* rev = (stVerifyKey*)pCmd;

			// ������Ϣ
			XorCommand(rev,cmdLen, message);

			if (getState() != LS_VERIFY_KEY) {
				printf("��֤Key�����쳣��״̬����ȷ���Ͽ�����\n");
				isDisconnect = true;
				break;
			}

			User* pUser = LoginedUserManager::getSingleton().getUser(rev->account);
			if (pUser == NULL) {
				printf("��֤Key�����쳣���û������ڣ��Ͽ�����\n");
				isDisconnect = true;
				break;
			}

			// verify key
			if (strncmp(rev->key,pUser->getKey(),sizeof(rev->key)) != 0) {
				// key ��֤ʧ�ܣ��Ͽ��ͻ���
				printf("��֤Key���ֲ�һ�£��Ͽ�����\n");
				isDisconnect = true;
				break;
			}

			// ͨ���˰汾��֤���û�����������֤����Կ��֤��
			// ��¼������������Ϸ�������б���ͻ���
			// ��½��������Ҫ����Կͬ������Ϸ������
			// �ͻ�����������Ϸ����ʱ����Ҫ����Կ����֤
			// to do ....
			stServerList* serverList = NULL;
			BUFF_CMD(serverList, stServerList);
			serverList->num = (WORD)ServerManager::getSingleton().size();
			if (serverList->getSize() >= MAX_USER_PACK_SIZE) {
				// ��Ϸ���������ݹ���
				printf("��Ϸ���������ݹ���\n");
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
	case LOGIN_CMD_ENTER_GAMESERVER:	// ������Ϸ������
		{
			stEnterGameServer* rev = (stEnterGameServer*)pCmd;

			// ������Ϣ
			XorCommand(rev,cmdLen,message);

			if (getState() != LS_SERVERLIST) {
				printf("������Ϸ�������쳣��״̬����ȷ���Ͽ�����\n");
				isDisconnect = true;
				break;
			}

			User* pUser = LoginedUserManager::getSingleton().getUser(rev->account);
			if (pUser == NULL) {
				printf("��֤Key�����쳣���û������ڣ��Ͽ�����\n");
				isDisconnect = true;
				break;
			}

			// verify key
			if (strncmp(rev->key,pUser->getKey(),sizeof(rev->key)) != 0) {
				// key ��֤ʧ�ܣ��Ͽ��ͻ���
				printf("������Ϸ������Key��һ�£��Ͽ�����\n");
				isDisconnect = true;
				break;
			}

			// ͬ����Կ�����������
			Server* pServer = ServerManager::getSingleton().findGatewayServer(rev->gameServerID);
			if (pServer == NULL || pServer->getType() != GatewayServer) {
				// ����ķ����������ڣ���δ�������Ͽ��ͻ���
				printf("����ķ����������ڣ���δ����\n");
				rev->result = 1;
				sendCmd(rev, cmdLen);
				break;
			}

			setState(LS_SYNC_KEY);

			logger.info("IP��(%s)���˺�(%s)���ߣ���ǰ��������(%d)", 
				this->getIP(), pUser->getName(), InGameUserManager::getSingleton().size());

			// ��ͬ����Կ�����ط�����, �����ط��������غ���֪ͨ�ͻ��ˣ����Ͽ�����
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
			// �ͻ����˳���¼������
		}
		break;
	default:
		{
#ifdef _DEBUG
			printf("LoginForClientδ������Ϣ %d\n", message);
#endif
			return false;
		}
		break;
	}

	if (isDisconnect) {
		printf("LoginTask �Ƿ��Ŀͻ��ˣ������������Ͽ����� id=%d, message=%d, ip=%s\n", nClient, message, getIP());
		//disconnect();
	}

//#ifdef _DEBUG
//	printf("�Ѵ�����Ϣ %d\n", message);
//#endif
	return true;
}

// �����½����Ϸ������֮�����Ϣ
bool LoginTask::procGameServerCmd(stServerBaseCommand* pCmd, DWORD cmdLen)
{
	WORD nClient = getID();
	bool isDisconnect = false;
	switch(pCmd->para)
	{
	case REGISTER_GAMESERVER:	// ��Ϸ����������ע��
		{
			stRegisterGameServer* rev = (stRegisterGameServer*)pCmd;

			Server* pServer = ServerManager::getSingleton().getServer(rev->id);
			if (pServer != NULL) {
				isDisconnect = true;
				printf("����Ϸ�������Ѿ�ע����� id=%d\n", rev->id);
				break;
			}

			pServer = ServerManager::getSingleton().getServerByTempID(nClient);
			if (pServer != NULL) {
				isDisconnect = true;
				printf("����Ϸ�������Ѿ�ע����� nClient=%d\n", nClient);
				break;
			}

			// �����ݿ��е����ݽ��бȽϣ��жϴ˷������Ƿ�Ϸ�
			if (!VerifyServer(rev->id, this->getIP(), rev->port, rev->name, rev->isNew)) {
				isDisconnect = true;
				printf("ע����Ϸ������ʧ�� nClient=%d, id=%d, ip=%s, port=%d \n",
					nClient, rev->id,this->getIP(),rev->port);
				break;
			}

			// ��֤�ɹ�, ���������
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
				printf("���������������ʧ�� nClient=%d\n", nClient);
				break;
			}
			printf("ע����Ϸ�������ɹ� id=%d, name=%s, isnew=%d ip=%s, port=%d, online=%d, maxuser=%d\n\n", 
				rev->id, rev->name, rev->isNew, this->getIP(), rev->port, 0, 1000);

			// ֪ͨ�ͻ���
			stRegisterGameServerResult cmd;
			cmd.result = 0;
			sendCmd(&cmd, sizeof(stRegisterGameServerResult));
		}
		break;
	case GAMESERVER_USERENDTIME:	// ��ѯ��ҵ���Ϸ����ʱ��
		{
			
			stGameServerUserEndTime* rev = (stGameServerUserEndTime*)pCmd;
			rev->endtime = GetUserEndTime(rev->account);
            sendCmd(rev, cmdLen);
		}
		break;
	case GAMESERVER_GET_USER_CASHINFO:	// ��ѯ������Ϣ
		{
			stGameServerGetUserCashInfo* rev = (stGameServerGetUserCashInfo*)pCmd;
			GetUserCashInfo(rev->account, rev->cashpoint, rev->hongli);
            sendCmd(rev, cmdLen);
		}
		break;
	case GAMESERVER_UPDATE_USER_CASHINFO:	// �۳������ͻ���
		{
			stGameServerUpdateUserCashInfo* rev = (stGameServerUpdateUserCashInfo*)pCmd;
			bool success = SubUserCashInfo(rev->account, rev->cashpoint, rev->hongli);
			GetUserCashInfo(rev->account, rev->cashpoint, rev->hongli);
			rev->result = success ? 0 : 1;
			sendCmd(rev, cmdLen);
		}
		break;
	case GAMESERVER_STOP_ACCOUNT:			// ���
		{
			stGameServerStopAccount* rev = (stGameServerStopAccount*)pCmd;
            ChangeAccountStatus(rev->account, "S");
			sendCmd(rev, cmdLen);
		}
		break;
	case UPDATE_GAMESERVER_INFO:	// ��Ϸ����������������Ϣ
		{
			stUpdateGameServerInfo* rev = (stUpdateGameServerInfo*)pCmd;
			printf("������״̬: id=%u, online=%u, max=%u, state=%u\n",
				rev->serverId, rev->onlineNum, rev->maxNum, rev->state);
		}
		break;
	case GAMESERVER_PING:			// ��Ϸ������ping��½������
		{
			stGameServerPing* rev = (stGameServerPing*)pCmd;
		}
		break;
		/*
		case REG_USER_TO_GATEWAY:		// ��½������ͬ����Կ����Ϸ������
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
		printf("ͬ����Կʧ��\n");
		cmd.result = 1;
		} else {
		cmd.result = 0;
		}

		// ֪ͨ�ͻ��˽���������Ľ��
		pUser->sendCmd(&cmd, sizeof(cmd));

		pUser->setServerId(rev->gameServerID);
		if (cmd.result == 0) {
		// ������Ϸ�ɹ������յ�ʱ�򣬲���ɾ��user���󣬶�������LoginedUserManager
		pUser->setEnterGame(true);
		} else {
		// ������Ϸʧ�ܣ����յ�ʱ��ɾ��user���󣬲�����LoginedUserManager
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
		printf("ע���û�ʧ��, ���˺Ų�����, accid=%u\n", rev->accId);
		break;
		}
		InGameUserManager::getSingleton().removeEntity(pUser);
		printf("�û�ע��, accid=%u, accname=%s\n", rev->accId, pUser->getName());
		SAFE_DELETE(pUser);
		}
		break;*/
	default:
		{
#ifdef _DEBUG
			printf("LoginForServerδ������Ϣ %d\n", pCmd->cmd);
#endif
			return false;
		}
		break;
	}

	if (isDisconnect) {
		disconnect();
		printf("TaskForServer �Ƿ��Ŀͻ��ˣ������������Ͽ����� id=%d, message=%d\n", nClient, pCmd->cmd);
	}

	//#ifdef _DEBUG
	//	printf("�Ѵ�����Ϣ %d\n", pCmd->cmd);
	//#endif

	return true;
}

// �����½�����ط�����֮�����Ϣ
bool LoginTask::procGatewayServerCmd(stServerBaseCommand* pCmd, DWORD cmdLen)
{
	WORD nClient = getID();
	bool isDisconnect = false;
	switch(pCmd->para)
	{
	case REGISTER_GATEWAYSERVER:	// ���ط���������ע��
		{
			stRegisterGatewayServer* rev = (stRegisterGatewayServer*)pCmd;

			Server* pServer = ServerManager::getSingleton().getServer(rev->id);
			if (pServer != NULL) {
				isDisconnect = true;
				printf("�����ط������Ѿ�ע����� id=%d\n", rev->id);
				break;
			}

			pServer = ServerManager::getSingleton().getServerByTempID(nClient);
			if (pServer != NULL) {
				isDisconnect = true;
				printf("�����ط������Ѿ�ע����� nClient=%d\n", nClient);
				break;
			}

			//// �����ݿ��е����ݽ��бȽϣ��жϴ˷������Ƿ�Ϸ�
			//if (!VerifyServer(rev->id, rev->ip, rev->port, rev->name, rev->isNew)) {
			//	isDisconnect = true;
			//	printf("ע����Ϸ������ʧ�� nClient=%d, id=%d, ip=%s, port=%d \n",
			//		nClient, rev->id,rev->ip,rev->port);
			//	break;
			//}

			// ��֤�ɹ�, ���������
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
				printf("���������������ʧ�� nClient=%d\n", nClient);
				break;
			}

			printf("ע�����ط������ɹ� id=%d, name=%s, isnew=%d ip=%s, port=%d, online=%d, maxuser=%d\n\n", 
				rev->id, rev->name, rev->isNew, this->getIP(), rev->port, 0, 1000);

			// ֪ͨ�ͻ���
			stRegisterGatewayServerResult cmd;
			cmd.result = 0;
			sendCmd(&cmd, sizeof(stRegisterGatewayServerResult));
		}
		break;
		//case UPDATE_GAMESERVER_INFO:	// ��Ϸ����������������Ϣ
		//	{
		//		stUpdateGameServerInfo* rev = (stUpdateGameServerInfo*)pCmd;
		//		printf("������״̬: id=%u, online=%u, max=%u, state=%u\n",
		//			rev->serverId, rev->onlineNum, rev->maxNum, rev->state);
		//	}
		//	break;
	case REG_USER_TO_GATEWAY:		// ��½������ͬ���ͻ��˵���Կ����Ϸ������
		{
			stRegUserToGateway* rev = (stRegUserToGateway*)pCmd;

			User* pUser = LoginedUserManager::getSingleton().getUser(rev->account);
			if (pUser == NULL) {
				printf("����ͬ����Կ���ʱ��û���ҵ�ָ���û� account=%s\n", rev->account);
				break;
			}

			LoginTask* loginTask = pUser->getLoginTask();
			if (loginTask == NULL || loginTask->getState() != LS_SYNC_KEY) {
				printf("����ͬ����Կ���ʱ��״̬����ȷ account=%s\n", rev->account);
				break;
			}

			stEnterGameServer cmd;
			cmd.gameServerID = rev->zoneId;
			strncpy(cmd.account, rev->account,MAX_ACCOUNT_SIZE);
			strncpy(cmd.key, rev->key, sizeof(cmd.key)-1);

			// ��������
			Server* pGateway = ServerManager::getSingleton().getServer(rev->gatewayId);
			if (pGateway == NULL || pGateway->getType() != GatewayServer) {
				printf("û���ҵ�ָ��������\n");
				rev->result = 1;
				pUser->sendCmd(&cmd, sizeof(cmd));
				break;
			}

			strncpy(cmd.IP, pGateway->getIP(), sizeof(cmd.IP)-1);
			cmd.port = pGateway->getPort();

			if (rev->result != 0) {
				printf("ͬ����Կʧ�� account=%s, key=%s\n", rev->account, rev->key);
				cmd.result = 1;
			} else {
				printf("ͬ����Կ�ɹ� account=%s key=%s\n", rev->account, rev->key);
				cmd.result = 0;
			}

			// ֪ͨ�ͻ��˽���������Ľ��
			pUser->sendCmd(&cmd, sizeof(cmd));

			LoginedUserManager::getSingleton().removeEntity(pUser);

			if (cmd.result == 0) {
				// ����InGameUserManager������
				pUser->setZoneId(pGateway->getZoneId());
				pUser->setGatewayId(pGateway->getID());
				InGameUserManager::getSingleton().addEntity(pUser);
			} else {
				// ɾ��User����
				SAFE_DELETE(pUser);
			}

			// 10���Ͽ��ͻ���
			if (pUser) pUser->disconnect(10);
		}
		break;
	case UNREG_USER:
		{
			// ע����Ϸ�е����
			stUnregUser* rev = (stUnregUser*)pCmd;
			User* pUser = InGameUserManager::getSingleton().getUser(rev->account);
			if (pUser == NULL) {
				printf("ע���˺�ʧ��, ���˺Ų�����, account=%s\n", rev->account);
				break;
			}

			if (strcmp(pUser->getKey(),rev->key) != 0) {
				printf("ע���˺�ʧ��, ��Կ����ȷ, account=%s\n", rev->account);
				break;
			}

			InGameUserManager::getSingleton().removeEntity(pUser);
			logger.info("IP��(%s)���˺�(%s)ע������ǰ��������(%d)", 
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
			printf("LoginForServerδ������Ϣ %d\n", pCmd->para);
#endif
			return false;
		}
		break;
	}

	if (isDisconnect) {
		//disconnect();
		printf("TaskForServer �Ƿ��Ŀͻ��ˣ������������Ͽ����� id=%d, message=%d\n", nClient, pCmd->cmd);
	}

	//#ifdef _DEBUG
	//	printf("�Ѵ�����Ϣ %d\n", pCmd->cmd);
	//#endif

	return true;
}


bool LoginTask::processMessage(void *data, DWORD cmdLen)
{
	stServerBaseCommand* pCmd = (stServerBaseCommand*)data;
	byte cmd = pCmd->cmd;
	if (cmd == LOGIN_GAME_CMD) {
		// ��Ϸ�������͵�¼������֮�����Ϣ
		procGameServerCmd((stServerBaseCommand*)data, cmdLen);
	} else if (cmd == LOGIN_GATEWAY_CMD) {
		// ���غ͵�¼������֮�����Ϣ
		procGatewayServerCmd((stServerBaseCommand*)data, cmdLen);
	} else {
		// �������Ϊ�ͻ��˺͵�¼������֮�����Ϣ
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



