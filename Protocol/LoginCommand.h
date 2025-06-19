#ifndef __LOGINCOMMAND_H__
#define __LOGINCOMMAND_H__

#include "BaseCommand.h"
#include "types.h"

#pragma pack(1)

namespace LoginCmd
{

	//////////////////////////////////////////////////////////////////////////
	//             �ͻ��˺͵�¼������֮�����Ϣ		��ʼ
	//////////////////////////////////////////////////////////////////////////

	// ��¼���������ͻ��˷����ID��
	const byte LOGIN_CMD_CLIENT_ID = 0;		// server -> client
	struct stClientID : stBaseCommand
	{
		stClientID() : stBaseCommand(LOGIN_CMD_CLIENT_ID)
		{
		}
	};


	// �ͻ��˺͵�¼������֮��İ汾��֤
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


	// �ͻ���ʹ���û����������½������
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

	// ���������ص�½���
	const byte LOGIN_CMD_LOGIN_RESULT = 2;	// server -> client
	struct stLoginResult : stBaseCommand 
	{
		char account[MAX_ACCOUNT_SIZE+1];

		BYTE unk1;		// 1
		BYTE unk2;		// ??
		BYTE status;	// �˺�״̬
		BYTE unk3;		// ??

		char key[13];	// ��Կ
		WORD result;	// ����ֵ

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

	// ����Э��
	const byte LOGIN_CMD_KEEPALIVE = 12;	// client -> server. server -> client
	struct stKeepAlive : stBaseCommand
	{
		char account[MAX_ACCOUNT_SIZE+1];
		byte unk1;	// 1
		WORD result;
	};

	// ��֤��Կ
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
		unsigned int id;			// id��
		char name[50];				// ����
		//char IP[50];				// IP
		//WORD port;					// �˿�
		unsigned int onlinecount;	// ��������
		unsigned int maxonlinecount;// �����������
		byte state;					// 0 δ������1 �ѿ���
		byte isNewServer;			// �Ƿ����¿�������

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

	// �������б�
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

	// ������������
	const byte LOGIN_CMD_ENTER_GAMESERVER = 16;	// client -> server, server -> client
	struct stEnterGameServer : stBaseCommand 
	{
		char account[MAX_ACCOUNT_SIZE+1];
		char key[13];
		BYTE gameServerID;
		char IP[50];				// IP
		WORD port;					// �˿�
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
	//			�ͻ��˺͵�¼������֮�����Ϣ	����
	//////////////////////////////////////////////////////////////////////////



	enum CmdLogin
	{
		LOGIN_GAME_CMD = 181,		// ��½������Ϸ��֮�����Ϣ
		LOGIN_GATEWAY_CMD = 183,	// ��½�������ط�֮�����Ϣ
	};




	//////////////////////////////////////////////////////////////////////////
	//			��Ϸ�������͵�¼������֮�����Ϣ		��ʼ
	//////////////////////////////////////////////////////////////////////////

	// ��Ϸ����������ע�ᵽ��½������
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

	// ��½������������֤���
	const byte REGISTER_GAMESERVER_RESULT = 2;		// loginserver -> gameserver
	struct stRegisterGameServerResult : stServerBaseCommand
	{
		BYTE result;	// 0 �ɹ���1 ʧ��

		stRegisterGameServerResult() : stServerBaseCommand(LOGIN_GAME_CMD, REGISTER_GAMESERVER_RESULT)
		{
			result = 0;
		}
	};


	// ���������͵�ǰ״̬����½������
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

	// ��Ϸ�����������û���Ϸ����ʱ��
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


	// ���½�����������˺ŵ���Ϸ����
	const byte GAMESERVER_GET_USER_CASHINFO = 5;		// gameserver -> loginserver
	struct stGameServerGetUserCashInfo : stServerBaseCommand
	{
		UINT charid;
		char account[MAX_ACCOUNT_SIZE+1];
		UINT cashpoint;	// ��Ϸ����
		UINT hongli;	// ���ֵ�

		stGameServerGetUserCashInfo() : stServerBaseCommand(LOGIN_GAME_CMD, GAMESERVER_GET_USER_CASHINFO)
		{
			ZeroMemory(account,sizeof(account));
			charid = 0;
			cashpoint = 0;
			hongli = 0;
		}
	};


	// ���½��������������˺ŵ���Ϸ����
	// gameserver -> loginserver   ���������Ҫ�۳��ĵ����ͻ���
	// loginserver -> gameserver   ���ص�ʣ��ĵ����ͻ���
	const byte GAMESERVER_UPDATE_USER_CASHINFO = 6;		// gameserver -> loginserver
	struct stGameServerUpdateUserCashInfo : stServerBaseCommand
	{
		UINT charid;
		char account[MAX_ACCOUNT_SIZE+1];
		UINT cashpoint;	// ��Ϸ����(��Ҫ�۳�����ֵ)
		UINT hongli;	// ���ֵ�(��Ҫ�۳�����ֵ)
		BYTE result;	// 0 - �ɹ�, ���� - ������

		stGameServerUpdateUserCashInfo() : stServerBaseCommand(LOGIN_GAME_CMD, GAMESERVER_UPDATE_USER_CASHINFO)
		{
			ZeroMemory(account,sizeof(account));
			charid = 0;
			cashpoint = 0;
			hongli = 0;
			result = 0;
		}
	};


	// ������
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


	// ��Ϸ������ping��¼������
	const byte GAMESERVER_PING = 100;		// gameserver -> loginserver
	struct stGameServerPing : stServerBaseCommand
	{
		stGameServerPing() : stServerBaseCommand(LOGIN_GAME_CMD, GAMESERVER_PING)
		{
		}
	};


	/*
	// ��½������ͬ����ҵĵ�½��Կ����Ϸ������
	const byte USER_LOGIN = 4;		// loginserver -> gameserver, gameserver -> loginserver
	struct stUserLogin : stServerBaseCommand
	{
		UINT id;
		UINT gameServerID;
		UINT accId;							// �˺�ID
		char account[MAX_ACCOUNT_SIZE+1];	// �˺���
		char key[13];						// ��Կ
		byte result;						// ����ֵ 0 - �ɹ�, 1 - ʧ��

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
		UINT accId;							// �˺�ID

		stUserLogout() : stServerBaseCommand(LOGIN_GAME_CMD, USER_LOGOUT)
		{
			accId = 0;
		}
	};
	*/


	//////////////////////////////////////////////////////////////////////////
	//			��Ϸ�������͵�¼������֮�����Ϣ		����
	//////////////////////////////////////////////////////////////////////////




	//////////////////////////////////////////////////////////////////////////
	//			���ط������͵�¼������֮�����Ϣ		��ʼ
	//////////////////////////////////////////////////////////////////////////

	// ���ط���������ע�ᵽ��½������
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

	// ��½������������֤���
	const byte REGISTER_GATEWAYSERVER_RESULT = 2;		// loginserver -> gatewayserver
	struct stRegisterGatewayServerResult : stServerBaseCommand
	{
		BYTE result;	// 0 �ɹ���1 ʧ��

		stRegisterGatewayServerResult() : stServerBaseCommand(LOGIN_GATEWAY_CMD, REGISTER_GATEWAYSERVER_RESULT)
		{
			result = 0;
		}
	};

	// ��½������ͬ����ҵĵ�½��Կ�����ط�����
	const byte REG_USER_TO_GATEWAY = 3;		// loginserver -> gatewayserver, gatewayserver -> loginserver
	struct stRegUserToGateway : stServerBaseCommand
	{
		UINT zoneId;						// ����ID
		UINT gatewayId;						// ����
		char account[MAX_ACCOUNT_SIZE+1];	// �˺���
		char key[13];						// ��Կ
		byte result;						// ����ֵ 0 - �ɹ�, 1 - ʧ��

		stRegUserToGateway() : stServerBaseCommand(LOGIN_GATEWAY_CMD, REG_USER_TO_GATEWAY)
		{
			zoneId = 0;
			gatewayId = 0;
			ZeroMemory(account,sizeof(account));
			ZeroMemory(key,sizeof(key));
			result = 0;
		}
	};

	// ����֪ͨ��½������ע���û�	gateway -> login
	const byte UNREG_USER = 4;
	struct stUnregUser : stServerBaseCommand 
	{
		char account[MAX_ACCOUNT_SIZE+1];	// �˺���
		char key[13];						// ��Կ

		stUnregUser() : stServerBaseCommand(LOGIN_GATEWAY_CMD, UNREG_USER)
		{
			ZeroMemory(account,sizeof(account));
			ZeroMemory(key,sizeof(key));
		}
	};


	// ��½������֪ͨ����ע���û�	login -> gateway
	const byte UNREG_GATEWAYUSER = 5;
	struct stUnregGatewayUser : stServerBaseCommand 
	{
		char account[MAX_ACCOUNT_SIZE+1];	// �˺���
		char key[13];						// ��Կ

		stUnregGatewayUser() : stServerBaseCommand(LOGIN_GATEWAY_CMD, UNREG_GATEWAYUSER)
		{
			ZeroMemory(account,sizeof(account));
			ZeroMemory(key,sizeof(key));
		}
	};


	// ��Ϸ������ping��¼������
	const byte GATEWAYSERVER_PING = 100;		// gatewayserver -> loginserver
	struct stGatewayServerPing : stServerBaseCommand
	{
		stGatewayServerPing() : stServerBaseCommand(LOGIN_GATEWAY_CMD, GATEWAYSERVER_PING)
		{
		}
	};

	//////////////////////////////////////////////////////////////////////////
	//			���ط������͵�¼������֮�����Ϣ		����
	//////////////////////////////////////////////////////////////////////////


};

#pragma pack()

#endif