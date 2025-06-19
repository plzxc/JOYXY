#ifndef __ITEMCOMMAND_H__
#define __ITEMCOMMAND_H__

// 物品相关的消息

#include "BaseCommand.h"
#include "types.h"
#include "PackageManager.h"

#pragma pack(1)

namespace GameCmd
{
	struct stAddItemData 
	{
		WORD pkg;
		stItemData itemData;
		WORD x;
		WORD y;

		stAddItemData()
		{
			pkg = (WORD)-1;
			x = (WORD)-1;
			y = (WORD)-1;
		}
	};
	typedef stAddItemData stRemoveItemData;


	// 使用物品
	const byte GAME_CMD_USE_ITEM = 6;			// c -> s
	struct stUseItem : stBaseCommand
	{
		WORD srcPkg;
		WORD srcX;
		WORD srcY;
		WORD count;
		WORD itemId;

		stUseItem() : stBaseCommand(GAME_CMD_USE_ITEM)
		{
			srcPkg = srcX = srcY = (WORD)-1;
			count = 0;
			itemId= 0;
		}
	};

	// 使用物品的返回值
	const byte GAME_CMD_USE_ITEM_RESULT = 7;			// s -> c
	struct stUseItemResult : stBaseCommand
	{
		WORD srcPkg;
		WORD srcX;
		WORD srcY;
		WORD count;
		WORD itemId;

		stUseItemResult() : stBaseCommand(GAME_CMD_USE_ITEM_RESULT)
		{
			srcPkg = srcX = srcY = (WORD)-1;
			count = 0;
			itemId= 0;
		}
	};


	// 鉴定(解除封印)
	const byte GAME_CMD_CHECKUP_ITEM = 11;
	struct stCheckupItem : stBaseCommand 
	{
		stPkgPos destPos;	// 装备坐标
		stPkgPos srcPos;	// 宝石坐标
		stItemData data;	// 解封后的数据
		WORD result;		// 返回值

		stCheckupItem() : stBaseCommand(GAME_CMD_CHECKUP_ITEM)
		{

		}
	};



	// 移动物品
	const byte GAME_CMD_MOVE_ITEM = 12;			// c -> s
	struct stMoveItem : stBaseCommand
	{
		WORD srcPkg;	// 源包裹
		WORD srcX;		// 原坐标
		WORD srcY;
		WORD destPkg;	// 目标包裹
		WORD destX;		// 目标坐标
		WORD destY;
		WORD result;	// 返回值
	
		stMoveItem() : stBaseCommand(GAME_CMD_MOVE_ITEM)
		{
			srcPkg = (WORD)-1;
			srcX = (WORD)-1;
			srcY = (WORD)-1;
			destPkg = (WORD)-1;
			destX = (WORD)-1;
			destY = (WORD)-1;
			result = 0;
		}
	};


	// 移动物品
	const byte GAME_CMD_MOVE_ITEM_RESULT = 13;			// s -> c
	struct stMoveItemResult : stBaseCommand
	{
		WORD srcPkg;	// 源包裹
		WORD srcX;		// 原坐标
		WORD srcY;
		WORD destPkg;	// 目标包裹
		WORD destX;		// 目标坐标
		WORD destY;
		WORD result;	// 返回值

		stMoveItemResult() : stBaseCommand(GAME_CMD_MOVE_ITEM_RESULT)
		{
			srcPkg = 0;
			srcX = 0;
			srcY = 0;
			destPkg = 0;
			destX = 0;
			destY = 0;
			result = 0;
		}
	};


	// 装备物品
	const byte GAME_CMD_EQUIP_ITEM = 37;
	struct stEquipItem : stBaseCommand
	{
		WORD srcPkg;	// 源界面
		WORD srcX;
		WORD srcY;

		WORD destPkg;	// 目标界面
		WORD destX;
		WORD destY;

		WORD itemId;	// 物品id
		BYTE petLevel;	// 宠物等级
		stEquipItem() : stBaseCommand(GAME_CMD_EQUIP_ITEM)
		{
		}
	};



	// 服务器主动给玩家发送道具
	const byte GAME_CMD_ADDITEM = 159;	// server -> client
	struct stAddItem : stBaseCommand
	{
		stPkgPos pos;
		stItemData itemData;

		stAddItem() : stBaseCommand(GAME_CMD_ADDITEM)
		{
		}
	};


	// 通知客户端更新物品耐久
	const byte GAME_CMD_SET_ITEMDUR = 107;		// s -> c
	struct stSetItemDur : stBaseCommand
	{
		WORD index;	// 装备界面上的位置
		WORD dur;	// 耐久值
		stSetItemDur() : stBaseCommand(GAME_CMD_SET_ITEMDUR)
		{
			index = 0;
			dur = 0;
		}
	};


	// 客户端请求捡物品
	const byte GAME_CMD_PICKUP_ITEM = 8;			// c -> s
	struct stPickupItem : stBaseCommand
	{
		WORD destPkg;
		WORD mapX;
		WORD mapY;
		BYTE mapId;
		WORD destX;
		WORD destY;
		stItemData Item;
		BYTE result;

		stPickupItem() : stBaseCommand(GAME_CMD_PICKUP_ITEM)
		{
			destPkg = 0;
			destX = destY = 0;
			mapId = 0;
			mapX = mapY = 0;
			ZeroMemory(&Item,sizeof(Item));
			result = 0;
		}
	};


	// 客户端请求捡物品返回值
	const byte GAME_CMD_PICKUP_ITEM_RESULT = 9;			// c -> s
	struct stPickupItemResult : stBaseCommand
	{
		WORD destPkg;
		WORD mapX;
		WORD mapY;
		BYTE mapId;
		WORD destX;
		WORD destY;
		stItemData Item;
		BYTE result;

		stPickupItemResult() : stBaseCommand(GAME_CMD_PICKUP_ITEM_RESULT)
		{
			destPkg = 0;
			destX = destY = 0;
			mapId = 0;
			mapX = mapY = 0;
			ZeroMemory(&Item,sizeof(Item));
			result = 0;
		}
	};


	// 客户端请求丢弃物品到地图
	const byte GAME_CMD_DROP_ITEM = 10;			// c -> s
	struct stDropItemCmd : stBaseCommand
	{
		WORD srcPkg;
		WORD srcX;
		WORD srcY;
		BYTE mapId;
		WORD mapX;
		WORD mapY;
		WORD itemId;
		BYTE dice;		// 骰子数值
		UINT color;

		stDropItemCmd() : stBaseCommand(GAME_CMD_DROP_ITEM)
		{
			srcPkg = 0;
			srcX = srcY = 0;
			mapId = 0;
			mapX = mapY = 0;
			itemId = 0;
			dice = 0;
			color = WHITE;
		}
	};


	// 通知客户端删除地图上的物品
	const byte GAME_CMD_REMOVE_ITEM_FROM_MAP = 201;		// s -> c
	struct stRemoveItemFromMap : stBaseCommand
	{
		BYTE mapId;
		WORD x;
		WORD y;
		stRemoveItemFromMap() : stBaseCommand(GAME_CMD_REMOVE_ITEM_FROM_MAP)
		{
			mapId = 0;
			x = y = 0;
		}
	};


	// 客户端请求打开NPC商店
	const byte GAME_CMD_OPEN_NPC_STORE = 38;		// c -> s
	struct stOpenNpcStore : stBaseCommand
	{
		WORD npcId;
		BYTE type;	// 0 - 购买， 1 - 出售
		stOpenNpcStore() : stBaseCommand(GAME_CMD_OPEN_NPC_STORE)
		{
			npcId = 0;
			type = 0;
		}
	};

	struct stCmdStoreItem 
	{
		WORD itemId;
	};

	// 服务器返回NPC商店出售的道具
	const byte GAME_CMD_OPEN_NPC_STORE_RESULT = 39;		// s -> c
	struct stOpenNpcStoreResult : stBaseCommand
	{
		WORD count;
		stCmdStoreItem data[0];

		stOpenNpcStoreResult() : stBaseCommand(GAME_CMD_OPEN_NPC_STORE_RESULT)
		{
			count = 0;
		}

		unsigned int getSize() { return sizeof(stOpenNpcStoreResult) + count * sizeof(stCmdStoreItem); }
	};


	// 购买的物品结构
	struct stBuyItemAdd
	{
		WORD pkg;
		WORD itemId;
		WORD x;
		WORD y;
	};


	// 客户端请求购买NPC商店里的物品
	const byte GAME_CMD_BUY_ITEMS = 40;		// c -> s
	struct stBuyItems : stBaseCommand
	{
		WORD count;				// 物品数量
		DWORD totalMoney;		// 总计金币(用于和服务器验算)
		stBuyItemAdd data[0];	// 物品信息结构

		stBuyItems() : stBaseCommand(GAME_CMD_BUY_ITEMS)
		{
			count = 0;
		}

		unsigned int getSize() { return sizeof(stBuyItems) + count * sizeof(stBuyItemAdd); }
	};

	// 服务器返回购买NPC商店里的物品
	const byte GAME_CMD_BUY_ITEMS_RESULT = 41;		// s -> c
	struct stBuyItemsResult : stBaseCommand
	{
		WORD count;				// 物品数量
		DWORD totalMoney;		// 总计金币(用于和服务器验算)
		stBuyItemAdd data[0];	// 物品信息结构

		stBuyItemsResult() : stBaseCommand(GAME_CMD_BUY_ITEMS_RESULT)
		{
			count = 0;
		}

		unsigned int getSize() { return sizeof(stBuyItemsResult) + count * sizeof(stBuyItemAdd); }
	};


	typedef stBuyItemAdd stSellItemRemove;


	// 客户端请求出售物品到NPC商店里
	const byte GAME_CMD_SELL_ITEMS = 42;		// c -> s
	struct stSellItems : stBaseCommand
	{
		WORD count;					// 物品数量
		DWORD totalMoney;			// 总计金币(用于和服务器验算)
		stSellItemRemove data[0];	// 物品信息结构

		stSellItems() : stBaseCommand(GAME_CMD_SELL_ITEMS)
		{
			totalMoney = 0;
			count = 0;
		}

		unsigned int getSize() { return sizeof(stSellItems) + count * sizeof(stSellItemRemove); }
	};

	// 服务器返回出售结果
	const byte GAME_CMD_SELL_ITEMS_RESULT = 43;		// s -> c
	struct stSellItemsResult : stBaseCommand
	{
		WORD count;					// 物品数量
		DWORD totalMoney;			// 总计金币(用于和服务器验算)
		WORD result;				// 结果 0 - 成功， 1 - 失败
		stSellItemRemove data[0];	// 物品信息结构

		stSellItemsResult() : stBaseCommand(GAME_CMD_SELL_ITEMS_RESULT)
		{
			totalMoney = 0;
			count = 0;
			result = 0;
		}

		unsigned int getSize() { return sizeof(stSellItemsResult) + count * sizeof(stSellItemRemove); }
	};


	// 更新物品的混合字段
	const byte GAME_CMD_ITEM_MIXDATA = 214;
	struct stItemMixData : stBaseCommand 
	{
		WORD index;
		DWORD mixData;

		stItemMixData() : stBaseCommand(GAME_CMD_ITEM_MIXDATA)
		{
			index = 0;
			mixData = 0;
		}
	};


	// 通知客户端创建一个物品
	const byte GAME_CMD_CREATE_ITEM_RESULT = 216;		// s -> c
	struct stCreateItemResult : stBaseCommand
	{
		WORD pkg;
		WORD x;
		WORD y;
		WORD itemId;
		WORD itemCurDur;
		DWORD mixData;
		WORD result;

		stCreateItemResult() : stBaseCommand(GAME_CMD_CREATE_ITEM_RESULT)
		{
			pkg = x = y = 0;
			itemId = 0;
			itemCurDur = 0;
			mixData = 0;
			result = 0;
		}
	};

	// 装备冲星
	const byte GAME_CMD_CHANGE_ITEM_STAR = 221;
	struct stChangeItemStar : stBaseCommand 
	{
		stPkgPos destPos;	// 装备坐标
		stPkgPos srcPos;	// 高卷坐标
		BYTE star;			// 冲星后的星数
		WORD result;		// 返回值

		stChangeItemStar() : stBaseCommand(GAME_CMD_CHANGE_ITEM_STAR)
		{

		}
	};

	// 冲星结果
	const byte GAME_CMD_CHANGE_ITEM_STAR_RESULT = 222;
	struct stChangeItemStarResult : stBaseCommand 
	{
		stPkgPos destPos;	// 装备坐标
		stPkgPos srcPos;	// 高卷坐标
		BYTE star;			// 冲星后的星数
		WORD result;		// 返回值

		stChangeItemStarResult() : stBaseCommand(GAME_CMD_CHANGE_ITEM_STAR_RESULT)
		{

		}
	};


	// 交换装备
	const byte GAME_CMD_SWAP_ITEM = 113;
	struct stSwapItem : stBaseCommand 
	{
		stPkgPos srcPos;	// 高卷坐标
		WORD srcItemId;
		stPkgPos destPos;	// 装备坐标
		WORD destItemId;
		BYTE petLevel;		// 宠物等级

		stSwapItem() : stBaseCommand(GAME_CMD_SWAP_ITEM)
		{
			srcItemId = destItemId = 0;
			petLevel = 0;
		}
	};


	// 学习
	const byte GAME_CMD_LEARN_BOOK = 79;
	struct stLearnBook : stBaseCommand 
	{
		stPkgPos srcPos;	// 书的坐标
		WORD srcItemId;
		stPkgPos destPos;	// 技能界面坐标
		WORD destIconId;
		WORD result;

		stLearnBook() : stBaseCommand(GAME_CMD_LEARN_BOOK)
		{
			srcItemId = destIconId = 0;
			result = 0;
		}
	};


	// 改变物品的属性值
	const byte GAME_CMD_CHANGE_ITEM_PROP = 166;
	struct stChangeItemProp : stBaseCommand
	{
		stPkgPos pos[2];
		BYTE prop;
		WORD result;

		stChangeItemProp() : stBaseCommand(GAME_CMD_CHANGE_ITEM_PROP)
		{
			prop = 0;
			result = 0;
		}
	};
	

	// 食物之源(用魔法创建食物)
	const byte GAME_CMD_CREATE_FOOD = 119;
	struct stCreateFood : stBaseCommand
	{
		stPkgPos pos;
		WORD itemId;
		WORD result;

		stCreateFood() : stBaseCommand(GAME_CMD_CREATE_FOOD)
		{
			itemId = 0;
			result = 0;
		}
	};


	struct stCashItem 
	{
		UINT productId;		// 商城产品ID
		UINT group;			// 分类
		UINT itemId;		// 道具ID
		UINT cashPoint;		// 需求点数
	};

	// 请求商城道具列表
	const byte GAME_CMD_REQUEST_CASHITEM_LIST = 226;
	struct strRequestCashItemList : stBaseCommand 
	{
		strRequestCashItemList() : stBaseCommand(GAME_CMD_REQUEST_CASHITEM_LIST)
		{
		}
	};

	// 请求商城道具列表
	const byte GAME_CMD_REQUEST_CASHITEM_LIST_RESULT = 230;
	struct strRequestCashItemListResult : stBaseCommand 
	{
		BYTE flag;			// 清除标记, 0 - 不清除当前数据, 1 - 清除当前数据
		UINT count;			// 数量
		stCashItem data[0];	// 数据

		strRequestCashItemListResult() : stBaseCommand(GAME_CMD_REQUEST_CASHITEM_LIST_RESULT)
		{
		}

		unsigned int getSize() { return sizeof(*this) + count * sizeof(data[0]); }
	};

	// 请求商城点数余额
	const byte GAME_CMD_CASH_POINT = 232;
	struct stCashPoint : stBaseCommand
	{
		UINT cashpoint;		// 商城点数
		UINT hongli;		// 积分点数
		BYTE discount;		// 折扣(90 - 9折, 80 - 8折)
		WORD result;		// 返回值

		stCashPoint() : stBaseCommand(GAME_CMD_CASH_POINT)
		{
			cashpoint = 0;
			hongli = 0;
			discount = 100;
			result = 0;
		}
	};

	// 购买商城道具
	const byte GAME_CMD_BUY_CASH_ITEM = 233;
	struct stBuyCashItem : stBaseCommand
	{
		stPkgPos pos;
		WORD itemId;
		UINT ProductCode;
		UINT cashpoint;		// 商城点数
		UINT hongli;		// 积分点数
		BYTE discount;		// 折扣(90 - 9折, 80 - 8折)
		WORD result;		// 返回值

		stBuyCashItem() : stBaseCommand(GAME_CMD_BUY_CASH_ITEM)
		{
			itemId = 0;
			ProductCode = 0;
			cashpoint = 0;
			hongli = 0;
			discount = 100;
			result = 0;
		}
	};


	// 白装变绿装
	const byte GAME_CMD_TO_GREEN_TIEM = 134;
	struct stToGreenItem : stBaseCommand
	{
		stPkgPos destPos;	// 装备坐标
		stPkgPos srcPos;	// 宝石坐标
		WORD result;		// 返回值  0 - 成功， 1 - 不能强化的装备

		stToGreenItem() : stBaseCommand(GAME_CMD_TO_GREEN_TIEM)
		{
		}
	};

	// 用金币赌装备
	const byte GAME_CMD_GAMBLE = 246;
	struct stGamble : stBaseCommand 
	{
		BYTE GambleType;
		BYTE GambleItemClass;

		stPkgPos destPos;

		stItemData ResultItem;
		WORD result;				//0: success , 1: fail, 2: invalid gambleitem class, 3:not enough money

		stGamble() : stBaseCommand(GAME_CMD_GAMBLE)
		{

		}
	};

	// 客户端请求更新物品信息
	const byte GAME_CMD_CHANGE_ITEMINFO = 239;
	struct stChangeItemInfo : stBaseCommand 
	{
		BYTE cmd;
		stPkgPos pos;
		stItemData itemData;
		WORD Result;

		stChangeItemInfo() : stBaseCommand(GAME_CMD_CHANGE_ITEMINFO)
		{

		}
	};

	// 增加绿装武器的暴击率
	const byte GAME_CMD_CHANGE_TIEM_CRITICAL = 138;
	struct stChangeItemCritical : stBaseCommand
	{
		stPkgPos destPos;	// 装备坐标
		stPkgPos srcPos;	// 宝石坐标
		BYTE critical;		// 升级后的暴击率
		WORD result;		// 返回值  0 - 成功， 1 - 不能强化的装备

		stChangeItemCritical() : stBaseCommand(GAME_CMD_CHANGE_TIEM_CRITICAL)
		{
		}
	};

	// 增加道具的最大耐久值
	const byte GAME_CMD_USE_REPAIRSTONE = 47;
	struct stUseRepairStone : stBaseCommand
	{
		stPkgPos destPos;	// 装备坐标
		stPkgPos srcPos;	// 宝石坐标
		WORD maxDur;		// 返回最新的最大耐久值
		WORD result;		// 返回值  0 - 成功， 1 - 不能强化的装备

		stUseRepairStone() : stBaseCommand(GAME_CMD_USE_REPAIRSTONE)
		{
		}
	};


	// 给装备增加占卜石
	const byte GAME_CMD_ITEM_ADD_RUNE = 237;
	struct stItemAddRune : stBaseCommand
	{
		stPkgPos runePos[3];	// 3个占卜石
		stPkgPos itemPos[2];	// 两个辅助道具
		stPkgPos equipPos;		// 装备位置
		stItemData equipData;	// 装备数据
		WORD result;			// 返回值  0 - 成功， 1 - 不能强化的装备

		stItemAddRune() : stBaseCommand(GAME_CMD_ITEM_ADD_RUNE)
		{
		}
	};
	





















};






#pragma pack()




#endif