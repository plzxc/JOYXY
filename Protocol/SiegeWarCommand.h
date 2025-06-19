#ifndef __SIEGEWARCOMMAND_H__
#define __SIEGEWARCOMMAND_H__

// ����ս��ص���Ϣ

#include "BaseCommand.h"
#include "types.h"


#pragma pack(1)

namespace GameCmd
{
	// 170 - ��ʼ����ս
	// 171 - ���빥��ս(���)
	// 172 - δ��
	// 173 - ����սʣ��ʱ��
	// 174 - ��������ս
	// 176 - ����Կ�� (PickupKey)
	// 177 - δ��
	// 178 - ����˰�� (SetTaxRate)
	// 179 - δ��

	// ��ʼ����ս
	const byte GAME_CMD_BEGIN_SIEGEWAR = 170;			// s -> c
	struct stBeginSiegeWar : stBaseCommand
	{
		stBeginSiegeWar() : stBaseCommand(GAME_CMD_BEGIN_SIEGEWAR)
		{
		}
	};

	// ���빥��ս
	const byte GAME_CMD_JOIN_SIEGEWAR = 171;			// c->s, s -> c
	struct stJoinSiegeWar : stBaseCommand
	{
		char guildName[MAX_NAME_SIZE+1];
		stJoinSiegeWar() : stBaseCommand(GAME_CMD_JOIN_SIEGEWAR)
		{
			ZeroMemory(guildName,sizeof(guildName));
		}
	};

	// ����սʣ��ʱ��
	const byte GAME_CMD_SIEGEWAR_REMAINTIME = 173;			// s -> c
	struct stSiegeWarRemainTime : stBaseCommand
	{
		BYTE remainTime;
		stSiegeWarRemainTime() : stBaseCommand(GAME_CMD_SIEGEWAR_REMAINTIME)
		{
			remainTime = 0;
		}
	};

	// ��������ս
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


	// ����Կ��
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


	// ����˰��
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

	// ��ѯ������
	const byte GAME_CMD_GUILDSAFEMONEY = 180;			// c -> s, s -> c
	struct stGuildSafeMoney : stBaseCommand
	{
		DWORD money[3];	//���˹���,����˹���,����˹���
		WORD result;

		stGuildSafeMoney() : stBaseCommand(GAME_CMD_GUILDSAFEMONEY)
		{
			ZeroMemory(money,sizeof(money));
			result = 0;
		}
	};

	// ���ҵ�����
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

	// �ӹ���ȡ���
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