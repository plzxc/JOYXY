#ifndef __LOGINCOMMAND_H__
#define __LOGINCOMMAND_H__

#include "BaseCommand.h"
#include "types.h"

#pragma pack(1)

namespace LoginCmd
{

	//////////////////////////////////////////////////////////////////////////
	//             客户端和登录服务器之间的消息		开始
	//////////////////////////////////////////////////////////////////////////

	// 登录服务器给客户端分配的ID号
	const byte LOGIN_CMD_CLIENT_ID = 0;		// server -> client
	struct stClientID : stBaseCommand
	{
		stClientID() : stBaseCommand(LOGIN_CMD_CLIENT_ID)
		{
		}
	};


	// 客户端和登录服务器之间的版本验证
	const byte LOGIN_CMD_CHECK_VERSION = 4;			// client -> server
	const byte LOGIN_CMD_CHECK_VERSION_RESULT = 5;	// server -> client
	struct stCheckVersion : stBaseCommand
	{
		DWORD version;
		WORD result;

		stCheckVersion() : stBaseCommand(LOGIN_CMD_CHECK_VERSION)
		{
			version = 0;
			result = 0;
		}
	};


	// 客户端使用用户名和密码登陆服务器
	const byte LOGIN_CMD_LOGIN = 1;	// client -> server
	struct stLogin : stBaseCommand 
	{
		char account[MAX_ACCOUNT_SIZE+1];
		char password[MAX_PASSWORD_SIZE+1];
		char clientip[MAX_IP_SIZE+1];
		char email[MAX_EMAIL_SIZE+1];
		char birthday[MAX_BIRTHDAY_SIZE+1];
		byte unk;	// ??

		stLogin() : stBaseCommand(LOGIN_CMD_LOGIN)
		{

		}
	};

	// 服务器返回登陆结果
	const byte LOGIN_CMD_LOGIN_RESULT = 2;	// server -> client
	struct stLoginResult : stBaseCommand 
	{
		char account[MAX_ACCOUNT_SIZE+1];

		BYTE unk1;		// 1
		BYTE unk2;		// ??
		BYTE status;	// 账号状态
		BYTE unk3;		// ??

		char key[13];	// 密钥
		WORD result;	// 返回值

		stLoginResult() : stBaseCommand(LOGIN_CMD_LOGIN_RESULT)
		{
			ZeroMemory(account,sizeof(account));
			unk1 = 1;
			unk2 = 0;
			status = 0;
			unk3 = 0;
			ZeroMemory(key,sizeof(key));
			result = 0;
		}
	};

	// 心跳协议
	const byte LOGIN_CMD_KEEPALIVE = 12;	// client -> server. server -> client
	struct stKeepAlive : stBaseCommand
	{
		char account[MAX_ACCOUNT_SIZE+1];
		byte unk1;	// 1
		WORD result;
	};

	// 验证密钥
	const byte LOGIN_CMD_VERIFY_KEY = 13;	// client -> server
	struct stVerifyKey : stBaseCommand 
	{
		char account[MAX_ACCOUNT_SIZE+1];
		char key[13];
		byte unk1;	// 1
		WORD result;

		stVerifyKey() : stBaseCommand(LOGIN_CMD_VERIFY_KEY)
		{
		}
	};


	struct GameServerInfo 
	{
		unsigned int id;			// id号
		char name[50];				// 名字
		//char IP[50];				// IP
		//WORD port;					// 端口
		unsigned int onlinecount;	// 在线人数
		unsigned int maxonlinecount;// 最大在线人数
		byte state;					// 0 未开启，1 已开启
		byte isNewServer;			// 是否是新开服务器

		GameServerInfo()
		{
			id = 0;
			ZeroMemory(name,sizeof(name));
			//ZeroMemory(IP,sizeof(IP));
			//port = 0;
			onlinecount = 0;
			maxonlinecount = 0;
			state = 0;
			isNewServer = 0;
		}
	};

	// 服务器列表
	const byte LOGIN_CMD_SERVER_LIST = 15;	// server -> client
	struct stServerList : stBaseCommand 
	{
		WORD num;
		GameServerInfo serverInfo[0];

		stServerList() : stBaseCommand(LOGIN_CMD_SERVER_LIST)
		{
			num = 0;
		}

		unsigned int getSize() { return sizeof(stServerList) + num * sizeof(GameServerInfo); }
	};

	// 请求进入服务器
	const byte LOGIN_CMD_ENTER_GAMESERVER = 16;	// client -> server, server -> client
	struct stEnterGameServer : stBaseCommand 
	{
		char account[MAX_ACCOUNT_SIZE+1];
		char key[13];
		BYTE gameServerID;
		char IP[50];				// IP
		WORD port;					// 端口
		WORD result;

		stEnterGameServer() : stBaseCommand(LOGIN_CMD_ENTER_GAMESERVER)
		{
			ZeroMemory(account,sizeof(account));
			ZeroMemory(key,sizeof(key));
			ZeroMemory(IP,sizeof(IP));
			gameServerID = 0;
			port = 0;
			result = 0;
		}
	};



	//////////////////////////////////////////////////////////////////////////
	//			客户端和登录服务器之间的消息	结束
	//////////////////////////////////////////////////////////////////////////



	enum CmdLogin
	{
		LOGIN_GAME_CMD = 181,		// 登陆服和游戏服之间的消息
		LOGIN_GATEWAY_CMD = 183,	// 登陆服和网关服之间的消息
	};




	//////////////////////////////////////////////////////////////////////////
	//			游戏服务器和登录服务器之间的消息		开始
	//////////////////////////////////////////////////////////////////////////

	// 游戏服务器请求注册到登陆服务器
	const byte REGISTER_GAMESERVER = 1;		// gameserver -> loginserver
	struct stRegisterGameServer : stServerBaseCommand
	{
		DWORD id;	// zonieid
		char name[50];
		WORD port;
		BOOL isNew;

		stRegisterGameServer() : stServerBaseCommand(LOGIN_GAME_CMD, REGISTER_GAMESERVER)
		{
			id = 0;
			port = 0;
			ZeroMemory(name,sizeof(name));
			isNew = FALSE;
		}
	};

	// 登陆服务器返回验证结果
	const byte REGISTER_GAMESERVER_RESULT = 2;		// loginserver -> gameserver
	struct stRegisterGameServerResult : stServerBaseCommand
	{
		BYTE result;	// 0 成功，1 失败

		stRegisterGameServerResult() : stServerBaseCommand(LOGIN_GAME_CMD, REGISTER_GAMESERVER_RESULT)
		{
			result = 0;
		}
	};


	// 服务器发送当前状态给登陆服务器
	const byte UPDATE_GAMESERVER_INFO = 3;		// gameserver -> loginserver
	struct stUpdateGameServerInfo : stServerBaseCommand
	{
		UINT serverId;
		DWORD onlineNum;
		DWORD maxNum;
		BYTE state;	// enum ServerState

		stUpdateGameServerInfo() : stServerBaseCommand(LOGIN_GAME_CMD, UPDATE_GAMESERVER_INFO)
		{
			serverId = 0;
			onlineNum = 0;
			maxNum = 0;
			state = 0;
		}
	};

	// 游戏服务器请求用户游戏结束时间
	const byte GAMESERVER_USERENDTIME = 4;		// gameserver -> loginserver
	struct stGameServerUserEndTime : stServerBaseCommand
	{
		UINT charid;
		char account[MAX_ACCOUNT_SIZE+1];
		time_t endtime;

		stGameServerUserEndTime() : stServerBaseCommand(LOGIN_GAME_CMD, GAMESERVER_USERENDTIME)
		{
			charid = 0;
			endtime = 0;
		}
	};


	// 向登陆服务器请求账号的游戏点数
	const byte GAMESERVER_GET_USER_CASHINFO = 5;		// gameserver -> loginserver
	struct stGameServerGetUserCashInfo : stServerBaseCommand
	{
		UINT charid;
		char account[MAX_ACCOUNT_SIZE+1];
		UINT cashpoint;	// 游戏点数
		UINT hongli;	// 积分点

		stGameServerGetUserCashInfo() : stServerBaseCommand(LOGIN_GAME_CMD, GAMESERVER_GET_USER_CASHINFO)
		{
			ZeroMemory(account,sizeof(account));
			charid = 0;
			cashpoint = 0;
			hongli = 0;
		}
	};


	// 向登陆服务器请求更新账号的游戏点数
	// gameserver -> loginserver   填入的是需要扣除的点数和积分
	// loginserver -> gameserver   返回的剩余的点数和积分
	const byte GAMESERVER_UPDATE_USER_CASHINFO = 6;		// gameserver -> loginserver
	struct stGameServerUpdateUserCashInfo : stServerBaseCommand
	{
		UINT charid;
		char account[MAX_ACCOUNT_SIZE+1];
		UINT cashpoint;	// 游戏点数(需要扣除的数值)
		UINT hongli;	// 积分点(需要扣除的数值)
		BYTE result;	// 0 - 成功, 其他 - 错误编号

		stGameServerUpdateUserCashInfo() : stServerBaseCommand(LOGIN_GAME_CMD, GAMESERVER_UPDATE_USER_CASHINFO)
		{
			ZeroMemory(account,sizeof(account));
			charid = 0;
			cashpoint = 0;
			hongli = 0;
			result = 0;
		}
	};


	// 请求封号
	const byte GAMESERVER_STOP_ACCOUNT = 7;		// gameserver -> loginserver
	struct stGameServerStopAccount : stServerBaseCommand
	{
		char charname[MAX_NAME_SIZE+1];
		char account[MAX_ACCOUNT_SIZE+1];

		stGameServerStopAccount() : stServerBaseCommand(LOGIN_GAME_CMD, GAMESERVER_STOP_ACCOUNT)
		{
			ZeroMemory(charname,sizeof(charname));
			ZeroMemory(account,sizeof(account));
		}
	};


	// 游戏服务器ping登录服务器
	const byte GAMESERVER_PING = 100;		// gameserver -> loginserver
	struct stGameServerPing : stServerBaseCommand
	{
		stGameServerPing() : stServerBaseCommand(LOGIN_GAME_CMD, GAMESERVER_PING)
		{
		}
	};


	/*
	// 登陆服务器同步玩家的登陆密钥到游戏服务器
	const byte USER_LOGIN = 4;		// loginserver -> gameserver, gameserver -> loginserver
	struct stUserLogin : stServerBaseCommand
	{
		UINT id;
		UINT gameServerID;
		UINT accId;							// 账号ID
		char account[MAX_ACCOUNT_SIZE+1];	// 账号名
		char key[13];						// 密钥
		byte result;						// 返回值 0 - 成功, 1 - 失败

		stUserLogin() : stServerBaseCommand(LOGIN_GAME_CMD, USER_LOGIN)
		{
			id = 0;
			gameServerID = 0;
			accId = 0;
			ZeroMemory(account,sizeof(account));
			ZeroMemory(key,sizeof(key));
			result = 0;
		}
	};

	const byte USER_LOGOUT = 5;
	struct stUserLogout : stServerBaseCommand 
	{
		UINT accId;							// 账号ID

		stUserLogout() : stServerBaseCommand(LOGIN_GAME_CMD, USER_LOGOUT)
		{
			accId = 0;
		}
	};
	*/


	//////////////////////////////////////////////////////////////////////////
	//			游戏服务器和登录服务器之间的消息		结束
	//////////////////////////////////////////////////////////////////////////




	//////////////////////////////////////////////////////////////////////////
	//			网关服务器和登录服务器之间的消息		开始
	//////////////////////////////////////////////////////////////////////////

	// 网关服务器请求注册到登陆服务器
	const byte REGISTER_GATEWAYSERVER = 1;		// gatewayserver -> loginserver
	struct stRegisterGatewayServer : stServerBaseCommand
	{
		UINT zoneid;
		DWORD id;
		char name[50];
		WORD port;
		BOOL isNew;

		stRegisterGatewayServer() : stServerBaseCommand(LOGIN_GATEWAY_CMD, REGISTER_GATEWAYSERVER)
		{
			zoneid = 0;
			id = 0;
			port = 0;
			ZeroMemory(name,sizeof(name));
			isNew = FALSE;
		}
	};

	// 登陆服务器返回验证结果
	const byte REGISTER_GATEWAYSERVER_RESULT = 2;		// loginserver -> gatewayserver
	struct stRegisterGatewayServerResult : stServerBaseCommand
	{
		BYTE result;	// 0 成功，1 失败

		stRegisterGatewayServerResult() : stServerBaseCommand(LOGIN_GATEWAY_CMD, REGISTER_GATEWAYSERVER_RESULT)
		{
			result = 0;
		}
	};

	// 登陆服务器同步玩家的登陆密钥到网关服务器
	const byte REG_USER_TO_GATEWAY = 3;		// loginserver -> gatewayserver, gatewayserver -> loginserver
	struct stRegUserToGateway : stServerBaseCommand
	{
		UINT zoneId;						// 大区ID
		UINT gatewayId;						// 网关
		char account[MAX_ACCOUNT_SIZE+1];	// 账号名
		char key[13];						// 密钥
		byte result;						// 返回值 0 - 成功, 1 - 失败

		stRegUserToGateway() : stServerBaseCommand(LOGIN_GATEWAY_CMD, REG_USER_TO_GATEWAY)
		{
			zoneId = 0;
			gatewayId = 0;
			ZeroMemory(account,sizeof(account));
			ZeroMemory(key,sizeof(key));
			result = 0;
		}
	};

	// 网关通知登陆服务器注销用户	gateway -> login
	const byte UNREG_USER = 4;
	struct stUnregUser : stServerBaseCommand 
	{
		char account[MAX_ACCOUNT_SIZE+1];	// 账号名
		char key[13];						// 密钥

		stUnregUser() : stServerBaseCommand(LOGIN_GATEWAY_CMD, UNREG_USER)
		{
			ZeroMemory(account,sizeof(account));
			ZeroMemory(key,sizeof(key));
		}
	};


	// 登陆服务器通知网关注销用户	login -> gateway
	const byte UNREG_GATEWAYUSER = 5;
	struct stUnregGatewayUser : stServerBaseCommand 
	{
		char account[MAX_ACCOUNT_SIZE+1];	// 账号名
		char key[13];						// 密钥

		stUnregGatewayUser() : stServerBaseCommand(LOGIN_GATEWAY_CMD, UNREG_GATEWAYUSER)
		{
			ZeroMemory(account,sizeof(account));
			ZeroMemory(key,sizeof(key));
		}
	};


	// 游戏服务器ping登录服务器
	const byte GATEWAYSERVER_PING = 100;		// gatewayserver -> loginserver
	struct stGatewayServerPing : stServerBaseCommand
	{
		stGatewayServerPing() : stServerBaseCommand(LOGIN_GATEWAY_CMD, GATEWAYSERVER_PING)
		{
		}
	};

	//////////////////////////////////////////////////////////////////////////
	//			网关服务器和登录服务器之间的消息		结束
	//////////////////////////////////////////////////////////////////////////


};

#pragma pack()

#endif