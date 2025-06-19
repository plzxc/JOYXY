#ifndef __TRADECOMMAND_H__
#define __TRADECOMMAND_H__

// 交易相关的消息

#include "BaseCommand.h"
#include "types.h"
#include "PackageManager.h"

#pragma pack(1)

namespace GameCmd
{

	// 玩家请求交易(C->S, S->C)
	const byte GAME_CMD_REQUEST_TRADE = 66;
	struct stRequestTrade : stBaseCommand 
	{
		WORD targetId;
		WORD result;

		stRequestTrade() : stBaseCommand(GAME_CMD_REQUEST_TRADE)
		{
			targetId = 0;
			result = 0;
		}
	};

	const byte GAME_CMD_REQUEST_TRADE_RESULT = 67;
	struct stRequestTradeResult : stBaseCommand 
	{
		WORD targetId;
		WORD result;

		stRequestTradeResult() : stBaseCommand(GAME_CMD_REQUEST_TRADE_RESULT)
		{
			targetId = 0;
			result = 0;
		}
	};

	// 取消交易(C->S, S->C)
	const byte GAME_CMD_CANCEL_TRADE = 68;
	struct stCancelTrade : stBaseCommand 
	{
		WORD targetId;
		WORD result;

		stCancelTrade() : stBaseCommand(GAME_CMD_CANCEL_TRADE)
		{
			targetId = 0;
			result = 0;
		}
	};

	const byte GAME_CMD_CANCEL_TRADE_RESULT = 69;
	struct stCancelTradeResult : stBaseCommand 
	{
		WORD targetId;
		WORD result;

		stCancelTradeResult() : stBaseCommand(GAME_CMD_CANCEL_TRADE_RESULT)
		{
			targetId = 0;
			result = 0;
		}
	};

	// 交易确认(C->S, S->C)
	const byte GAME_CMD_TRADE_OK = 70;
	struct stTradeOK : stBaseCommand 
	{
		WORD targetId;
		WORD result;

		stTradeOK() : stBaseCommand(GAME_CMD_TRADE_OK)
		{
			targetId = 0;
			result = 0;
		}
	};

	const byte GAME_CMD_TRADE_OK_RESULT = 71;
	struct stTradeOKResult : stBaseCommand 
	{
		WORD targetId;
		WORD result;

		stTradeOKResult() : stBaseCommand(GAME_CMD_TRADE_OK_RESULT)
		{
			targetId = 0;
			result = 0;
		}
	};


	// 放入物品
	const byte GAME_CMD_TRADE_PUT_ITEM = 72;
	struct stTradePutItem : stBaseCommand 
	{
		WORD targetId;
		stPkgPos pos;
		stItemData itemData;
		WORD index;
		WORD result;

		stTradePutItem() : stBaseCommand(GAME_CMD_TRADE_PUT_ITEM)
		{
			targetId = 0;
			index = 0;
			result = 0;
		}
	};

	const byte GAME_CMD_TRADE_PUT_ITEM_RESULT = 73;
	struct stTradePutItemResult : stBaseCommand 
	{
		WORD targetId;
		stPkgPos pos;
		stItemData itemData;
		WORD index;
		WORD result;

		stTradePutItemResult() : stBaseCommand(GAME_CMD_TRADE_PUT_ITEM_RESULT)
		{
			targetId = 0;
			index = 0;
			result = 0;
		}
	};


	// 取消放入物品
	const byte GAME_CMD_TRADE_PUT_CANCEL = 74;
	struct stTradePutCancel : stBaseCommand 
	{
		WORD targetId;
		stPkgPos pos;
		stItemData itemData;
		WORD index;
		WORD result;

		stTradePutCancel() : stBaseCommand(GAME_CMD_TRADE_PUT_CANCEL)
		{
			targetId = 0;
			index = 0;
			result = 0;
		}
	};

	const byte GAME_CMD_TRADE_PUT_CANCEL_RESULT = 75;
	struct stTradePutCancelResult : stBaseCommand 
	{
		WORD targetId;
		stPkgPos pos;
		stItemData itemData;
		WORD index;
		WORD result;

		stTradePutCancelResult() : stBaseCommand(GAME_CMD_TRADE_PUT_CANCEL_RESULT)
		{
			targetId = 0;
			index = 0;
			result = 0;
		}
	};


	// 交易栏放入金币
	const byte GAME_CMD_TRADE_PUT_MONEY = 76;
	struct stTradePutMoney : stBaseCommand 
	{
		WORD targetId;
		DWORD money;
		WORD result;

		stTradePutMoney() : stBaseCommand(GAME_CMD_TRADE_PUT_MONEY)
		{
			targetId = 0;
			money = 0;
			result = 0;
		}
	};
	const byte GAME_CMD_TRADE_PUT_MONEY_RESULT = 77;
	struct stTradePutMoneyResult : stBaseCommand 
	{
		WORD targetId;
		DWORD money;
		WORD result;

		stTradePutMoneyResult() : stBaseCommand(GAME_CMD_TRADE_PUT_MONEY_RESULT)
		{
			targetId = 0;
			money = 0;
			result = 0;
		}
	};


	// 交易完成
	const byte GAME_CMD_TRADE_END = 146;
	struct stTradeEnd : stBaseCommand 
	{
		WORD targetId;
		DWORD money1;
		DWORD money2;
		stAddItemData addItem1[3];
		stAddItemData addItem2[3];
		stRemoveItemData removeItem1[3];
		stRemoveItemData removeItem2[3];
		WORD result;

		stTradeEnd() : stBaseCommand(GAME_CMD_TRADE_END)
		{
			targetId = 0;
			money1 = money2 = 0;
			result = 0;
		}
	};

	const byte GAME_CMD_TRADE_END_RESULT = 147;
	struct stTradeEndResult : stBaseCommand 
	{
		WORD targetId;
		DWORD money1;
		DWORD money2;
		stAddItemData addItem1[3];
		stAddItemData addItem2[3];
		stRemoveItemData removeItem1[3];
		stRemoveItemData removeItem2[3];
		WORD result;

		stTradeEndResult() : stBaseCommand(GAME_CMD_TRADE_END_RESULT)
		{
			targetId = 0;
			money1 = money2 = 0;
			result = 0;
		}
	};


};

#pragma pack()




#endif