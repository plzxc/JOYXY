#ifndef __GATEWAYCOMMAND_H__
#define __GATEWAYCOMMAND_H__

#include "BaseCommand.h"
#include "types.h"

#pragma pack(1)

namespace GatewayCmd
{
	enum CmdGateway
	{
		GATEWAY_GAME_CMD = 1,		// ���ط�����Ϸ��֮�����Ϣ
	};

	//////////////////////////////////////////////////////////////////////////
	//			���ط���������Ϸ������֮�����Ϣ		��ʼ
	//////////////////////////////////////////////////////////////////////////

	// ���ط�����ת����Ϣ����Ϸ������
	const byte GATEWAY_GAME_TRANSCMD = 1;		// gatewayserver -> gameserver, gameserver -> gatewayserver
	struct stGatewayGameTransCmd : stServerBaseCommand
	{
		UINT clientId;	// ÿ����ҵ�����ID��
		UINT charid;	// ÿ����ҵĽ�ɫID��
		UINT count;		
		BYTE data[0];

		stGatewayGameTransCmd() : stServerBaseCommand(GATEWAY_GAME_CMD, GATEWAY_GAME_TRANSCMD)
		{
			clientId = 0;
			charid = 0;
			count = 0;
		}

		unsigned int getSize() { return sizeof(stGatewayGameTransCmd) + count * sizeof(data[0]); }
	};

	// ����֪ͨ��Ϸ������ɾ�����
	const byte GATEWAY_GAME_UNREG_USER = 2;
	struct stGatewayGameUnregUser : stServerBaseCommand 
	{
		UINT clientId;	// ÿ����ҵ�����ID��
		UINT charid;	// ÿ����ҵĽ�ɫID��

		stGatewayGameUnregUser() : stServerBaseCommand(GATEWAY_GAME_CMD, GATEWAY_GAME_UNREG_USER)
		{
			clientId = 0;
			charid = 0;
		}
	};

	// ��������
	const byte GATEWAY_GAME_KICK_USER = 3;
	struct stGatewayGameKickUser : stServerBaseCommand 
	{
		UINT clientId;	// ÿ����ҵ�����ID��
		UINT charid;	// ÿ����ҵĽ�ɫID��

		stGatewayGameKickUser() : stServerBaseCommand(GATEWAY_GAME_CMD, GATEWAY_GAME_KICK_USER)
		{
			clientId = 0;
			charid = 0;
		}
	};


	const byte GATEWAY_GAME_PING = 100;
	struct stGatewayGamePing : stServerBaseCommand 
	{
		stGatewayGamePing() : stServerBaseCommand(GATEWAY_GAME_CMD, GATEWAY_GAME_PING)
		{
		}
	};

	//////////////////////////////////////////////////////////////////////////
	//			���ط���������Ϸ������֮�����Ϣ		����
	//////////////////////////////////////////////////////////////////////////
	
};

#pragma pack()

#endif