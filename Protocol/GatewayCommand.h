#ifndef __GATEWAYCOMMAND_H__
#define __GATEWAYCOMMAND_H__

#include "BaseCommand.h"
#include "types.h"

#pragma pack(1)

namespace GatewayCmd
{
	enum CmdGateway
	{
		GATEWAY_GAME_CMD = 1,		// 网关服和游戏服之间的消息
	};

	//////////////////////////////////////////////////////////////////////////
	//			网关服务器和游戏服务器之间的消息		开始
	//////////////////////////////////////////////////////////////////////////

	// 网关服务器转发消息到游戏服务器
	const byte GATEWAY_GAME_TRANSCMD = 1;		// gatewayserver -> gameserver, gameserver -> gatewayserver
	struct stGatewayGameTransCmd : stServerBaseCommand
	{
		UINT clientId;	// 每个玩家的网络ID号
		UINT charid;	// 每个玩家的角色ID号
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

	// 网关通知游戏服务器删除玩家
	const byte GATEWAY_GAME_UNREG_USER = 2;
	struct stGatewayGameUnregUser : stServerBaseCommand 
	{
		UINT clientId;	// 每个玩家的网络ID号
		UINT charid;	// 每个玩家的角色ID号

		stGatewayGameUnregUser() : stServerBaseCommand(GATEWAY_GAME_CMD, GATEWAY_GAME_UNREG_USER)
		{
			clientId = 0;
			charid = 0;
		}
	};

	// 踢人下线
	const byte GATEWAY_GAME_KICK_USER = 3;
	struct stGatewayGameKickUser : stServerBaseCommand 
	{
		UINT clientId;	// 每个玩家的网络ID号
		UINT charid;	// 每个玩家的角色ID号

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
	//			网关服务器和游戏服务器之间的消息		结束
	//////////////////////////////////////////////////////////////////////////
	
};

#pragma pack()

#endif