#ifndef __SIEGEWARCOMMAND_H__
#define __SIEGEWARCOMMAND_H__

// 攻城战相关的消息

#include "BaseCommand.h"
#include "types.h"


#pragma pack(1)

namespace GameCmd
{
	// 170 - 开始攻城战
	// 171 - 加入攻城战(结果)
	// 172 - 未用
	// 173 - 攻城战剩余时间
	// 174 - 结束攻城战
	// 176 - 捡起钥匙 (PickupKey)
	// 177 - 未用
	// 178 - 设置税率 (SetTaxRate)
	// 179 - 未用

	// 开始攻城战
	const byte GAME_CMD_BEGIN_SIEGEWAR = 170;			// s -> c
	struct stBeginSiegeWar : stBaseCommand
	{
		stBeginSiegeWar() : stBaseCommand(GAME_CMD_BEGIN_SIEGEWAR)
		{
		}
	};

	// 加入攻城战
	const byte GAME_CMD_JOIN_SIEGEWAR = 171;			// c->s, s -> c
	struct stJoinSiegeWar : stBaseCommand
	{
		char guildName[MAX_NAME_SIZE+1];
		stJoinSiegeWar() : stBaseCommand(GAME_CMD_JOIN_SIEGEWAR)
		{
			ZeroMemory(guildName,sizeof(guildName));
		}
	};

	// 攻城战剩余时间
	const byte GAME_CMD_SIEGEWAR_REMAINTIME = 173;			// s -> c
	struct stSiegeWarRemainTime : stBaseCommand
	{
		BYTE remainTime;
		stSiegeWarRemainTime() : stBaseCommand(GAME_CMD_SIEGEWAR_REMAINTIME)
		{
			remainTime = 0;
		}
	};

	// 结束攻城战
	const byte GAME_CMD_END_SIEGEWAR = 174;			// s -> c
	struct stEndSiegeWar : stBaseCommand
	{
		BYTE winner;
		char guildName[MAX_NAME_SIZE+1];
		stEndSiegeWar() : stBaseCommand(GAME_CMD_END_SIEGEWAR)
		{
			winner = 0;
			ZeroMemory(guildName,sizeof(guildName));
		}
	};


	// 捡起钥匙
	const byte GAME_CMD_PICKUP_KEY = 176;			// c -> s, s -> c
	struct stPickupKey : stBaseCommand
	{
		BYTE mapId;
		WORD x;
		WORD y;
		WORD itemId;
		WORD result;
		
		stPickupKey() : stBaseCommand(GAME_CMD_PICKUP_KEY)
		{
			mapId = 0;
			x = 0;
			y = 0;
			itemId = 0;
			result = 0;
		}
	};


	// 设置税率
	const byte GAME_CMD_SET_TAXRATE = 178;			// c -> s, s -> c
	struct stSetTaxRate : stBaseCommand
	{
		BYTE taxRate;
		WORD result;

		stSetTaxRate() : stBaseCommand(GAME_CMD_SET_TAXRATE)
		{
			taxRate = 0;
			result = 0;
		}
	};

	// 查询国库金额
	const byte GAME_CMD_GUILDSAFEMONEY = 180;			// c -> s, s -> c
	struct stGuildSafeMoney : stBaseCommand
	{
		DWORD money[3];	//玛尔斯金币,艾伯斯金币,伊格斯金币
		WORD result;

		stGuildSafeMoney() : stBaseCommand(GAME_CMD_GUILDSAFEMONEY)
		{
			ZeroMemory(money,sizeof(money));
			result = 0;
		}
	};

	// 存金币到国库
	const byte GAME_CMD_GUILDDEPOSITMONEY = 182;			// c -> s, s -> c
	struct stGuildDepositMoney : stBaseCommand
	{
		DWORD money;
		WORD result;

		stGuildDepositMoney() : stBaseCommand(GAME_CMD_GUILDDEPOSITMONEY)
		{
			money = 0;
			result = 0;
		}
	};

	// 从国库取金币
	const byte GAME_CMD_GUILDWIDTHDRAWMONEY = 186;			// c -> s, s -> c
	struct stGuildWidthdrawMoney : stBaseCommand
	{
		DWORD money;
		WORD result;

		stGuildWidthdrawMoney() : stBaseCommand(GAME_CMD_GUILDWIDTHDRAWMONEY)
		{
			money = 0;
			result = 0;
		}
	};
};

#pragma pack()




#endif