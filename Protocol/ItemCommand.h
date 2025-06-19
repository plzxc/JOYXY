#ifndef __ITEMCOMMAND_H__
#define __ITEMCOMMAND_H__

// ��Ʒ��ص���Ϣ

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


	// ʹ����Ʒ
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

	// ʹ����Ʒ�ķ���ֵ
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


	// ����(�����ӡ)
	const byte GAME_CMD_CHECKUP_ITEM = 11;
	struct stCheckupItem : stBaseCommand 
	{
		stPkgPos destPos;	// װ������
		stPkgPos srcPos;	// ��ʯ����
		stItemData data;	// ���������
		WORD result;		// ����ֵ

		stCheckupItem() : stBaseCommand(GAME_CMD_CHECKUP_ITEM)
		{

		}
	};



	// �ƶ���Ʒ
	const byte GAME_CMD_MOVE_ITEM = 12;			// c -> s
	struct stMoveItem : stBaseCommand
	{
		WORD srcPkg;	// Դ����
		WORD srcX;		// ԭ����
		WORD srcY;
		WORD destPkg;	// Ŀ�����
		WORD destX;		// Ŀ������
		WORD destY;
		WORD result;	// ����ֵ
	
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


	// �ƶ���Ʒ
	const byte GAME_CMD_MOVE_ITEM_RESULT = 13;			// s -> c
	struct stMoveItemResult : stBaseCommand
	{
		WORD srcPkg;	// Դ����
		WORD srcX;		// ԭ����
		WORD srcY;
		WORD destPkg;	// Ŀ�����
		WORD destX;		// Ŀ������
		WORD destY;
		WORD result;	// ����ֵ

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


	// װ����Ʒ
	const byte GAME_CMD_EQUIP_ITEM = 37;
	struct stEquipItem : stBaseCommand
	{
		WORD srcPkg;	// Դ����
		WORD srcX;
		WORD srcY;

		WORD destPkg;	// Ŀ�����
		WORD destX;
		WORD destY;

		WORD itemId;	// ��Ʒid
		BYTE petLevel;	// ����ȼ�
		stEquipItem() : stBaseCommand(GAME_CMD_EQUIP_ITEM)
		{
		}
	};



	// ��������������ҷ��͵���
	const byte GAME_CMD_ADDITEM = 159;	// server -> client
	struct stAddItem : stBaseCommand
	{
		stPkgPos pos;
		stItemData itemData;

		stAddItem() : stBaseCommand(GAME_CMD_ADDITEM)
		{
		}
	};


	// ֪ͨ�ͻ��˸�����Ʒ�;�
	const byte GAME_CMD_SET_ITEMDUR = 107;		// s -> c
	struct stSetItemDur : stBaseCommand
	{
		WORD index;	// װ�������ϵ�λ��
		WORD dur;	// �;�ֵ
		stSetItemDur() : stBaseCommand(GAME_CMD_SET_ITEMDUR)
		{
			index = 0;
			dur = 0;
		}
	};


	// �ͻ����������Ʒ
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


	// �ͻ����������Ʒ����ֵ
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


	// �ͻ�����������Ʒ����ͼ
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
		BYTE dice;		// ������ֵ
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


	// ֪ͨ�ͻ���ɾ����ͼ�ϵ���Ʒ
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


	// �ͻ��������NPC�̵�
	const byte GAME_CMD_OPEN_NPC_STORE = 38;		// c -> s
	struct stOpenNpcStore : stBaseCommand
	{
		WORD npcId;
		BYTE type;	// 0 - ���� 1 - ����
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

	// ����������NPC�̵���۵ĵ���
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


	// �������Ʒ�ṹ
	struct stBuyItemAdd
	{
		WORD pkg;
		WORD itemId;
		WORD x;
		WORD y;
	};


	// �ͻ���������NPC�̵������Ʒ
	const byte GAME_CMD_BUY_ITEMS = 40;		// c -> s
	struct stBuyItems : stBaseCommand
	{
		WORD count;				// ��Ʒ����
		DWORD totalMoney;		// �ܼƽ��(���ںͷ���������)
		stBuyItemAdd data[0];	// ��Ʒ��Ϣ�ṹ

		stBuyItems() : stBaseCommand(GAME_CMD_BUY_ITEMS)
		{
			count = 0;
		}

		unsigned int getSize() { return sizeof(stBuyItems) + count * sizeof(stBuyItemAdd); }
	};

	// ���������ع���NPC�̵������Ʒ
	const byte GAME_CMD_BUY_ITEMS_RESULT = 41;		// s -> c
	struct stBuyItemsResult : stBaseCommand
	{
		WORD count;				// ��Ʒ����
		DWORD totalMoney;		// �ܼƽ��(���ںͷ���������)
		stBuyItemAdd data[0];	// ��Ʒ��Ϣ�ṹ

		stBuyItemsResult() : stBaseCommand(GAME_CMD_BUY_ITEMS_RESULT)
		{
			count = 0;
		}

		unsigned int getSize() { return sizeof(stBuyItemsResult) + count * sizeof(stBuyItemAdd); }
	};


	typedef stBuyItemAdd stSellItemRemove;


	// �ͻ������������Ʒ��NPC�̵���
	const byte GAME_CMD_SELL_ITEMS = 42;		// c -> s
	struct stSellItems : stBaseCommand
	{
		WORD count;					// ��Ʒ����
		DWORD totalMoney;			// �ܼƽ��(���ںͷ���������)
		stSellItemRemove data[0];	// ��Ʒ��Ϣ�ṹ

		stSellItems() : stBaseCommand(GAME_CMD_SELL_ITEMS)
		{
			totalMoney = 0;
			count = 0;
		}

		unsigned int getSize() { return sizeof(stSellItems) + count * sizeof(stSellItemRemove); }
	};

	// ���������س��۽��
	const byte GAME_CMD_SELL_ITEMS_RESULT = 43;		// s -> c
	struct stSellItemsResult : stBaseCommand
	{
		WORD count;					// ��Ʒ����
		DWORD totalMoney;			// �ܼƽ��(���ںͷ���������)
		WORD result;				// ��� 0 - �ɹ��� 1 - ʧ��
		stSellItemRemove data[0];	// ��Ʒ��Ϣ�ṹ

		stSellItemsResult() : stBaseCommand(GAME_CMD_SELL_ITEMS_RESULT)
		{
			totalMoney = 0;
			count = 0;
			result = 0;
		}

		unsigned int getSize() { return sizeof(stSellItemsResult) + count * sizeof(stSellItemRemove); }
	};


	// ������Ʒ�Ļ���ֶ�
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


	// ֪ͨ�ͻ��˴���һ����Ʒ
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

	// װ������
	const byte GAME_CMD_CHANGE_ITEM_STAR = 221;
	struct stChangeItemStar : stBaseCommand 
	{
		stPkgPos destPos;	// װ������
		stPkgPos srcPos;	// �߾�����
		BYTE star;			// ���Ǻ������
		WORD result;		// ����ֵ

		stChangeItemStar() : stBaseCommand(GAME_CMD_CHANGE_ITEM_STAR)
		{

		}
	};

	// ���ǽ��
	const byte GAME_CMD_CHANGE_ITEM_STAR_RESULT = 222;
	struct stChangeItemStarResult : stBaseCommand 
	{
		stPkgPos destPos;	// װ������
		stPkgPos srcPos;	// �߾�����
		BYTE star;			// ���Ǻ������
		WORD result;		// ����ֵ

		stChangeItemStarResult() : stBaseCommand(GAME_CMD_CHANGE_ITEM_STAR_RESULT)
		{

		}
	};


	// ����װ��
	const byte GAME_CMD_SWAP_ITEM = 113;
	struct stSwapItem : stBaseCommand 
	{
		stPkgPos srcPos;	// �߾�����
		WORD srcItemId;
		stPkgPos destPos;	// װ������
		WORD destItemId;
		BYTE petLevel;		// ����ȼ�

		stSwapItem() : stBaseCommand(GAME_CMD_SWAP_ITEM)
		{
			srcItemId = destItemId = 0;
			petLevel = 0;
		}
	};


	// ѧϰ
	const byte GAME_CMD_LEARN_BOOK = 79;
	struct stLearnBook : stBaseCommand 
	{
		stPkgPos srcPos;	// �������
		WORD srcItemId;
		stPkgPos destPos;	// ���ܽ�������
		WORD destIconId;
		WORD result;

		stLearnBook() : stBaseCommand(GAME_CMD_LEARN_BOOK)
		{
			srcItemId = destIconId = 0;
			result = 0;
		}
	};


	// �ı���Ʒ������ֵ
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
	

	// ʳ��֮Դ(��ħ������ʳ��)
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
		UINT productId;		// �̳ǲ�ƷID
		UINT group;			// ����
		UINT itemId;		// ����ID
		UINT cashPoint;		// �������
	};

	// �����̳ǵ����б�
	const byte GAME_CMD_REQUEST_CASHITEM_LIST = 226;
	struct strRequestCashItemList : stBaseCommand 
	{
		strRequestCashItemList() : stBaseCommand(GAME_CMD_REQUEST_CASHITEM_LIST)
		{
		}
	};

	// �����̳ǵ����б�
	const byte GAME_CMD_REQUEST_CASHITEM_LIST_RESULT = 230;
	struct strRequestCashItemListResult : stBaseCommand 
	{
		BYTE flag;			// ������, 0 - �������ǰ����, 1 - �����ǰ����
		UINT count;			// ����
		stCashItem data[0];	// ����

		strRequestCashItemListResult() : stBaseCommand(GAME_CMD_REQUEST_CASHITEM_LIST_RESULT)
		{
		}

		unsigned int getSize() { return sizeof(*this) + count * sizeof(data[0]); }
	};

	// �����̳ǵ������
	const byte GAME_CMD_CASH_POINT = 232;
	struct stCashPoint : stBaseCommand
	{
		UINT cashpoint;		// �̳ǵ���
		UINT hongli;		// ���ֵ���
		BYTE discount;		// �ۿ�(90 - 9��, 80 - 8��)
		WORD result;		// ����ֵ

		stCashPoint() : stBaseCommand(GAME_CMD_CASH_POINT)
		{
			cashpoint = 0;
			hongli = 0;
			discount = 100;
			result = 0;
		}
	};

	// �����̳ǵ���
	const byte GAME_CMD_BUY_CASH_ITEM = 233;
	struct stBuyCashItem : stBaseCommand
	{
		stPkgPos pos;
		WORD itemId;
		UINT ProductCode;
		UINT cashpoint;		// �̳ǵ���
		UINT hongli;		// ���ֵ���
		BYTE discount;		// �ۿ�(90 - 9��, 80 - 8��)
		WORD result;		// ����ֵ

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


	// ��װ����װ
	const byte GAME_CMD_TO_GREEN_TIEM = 134;
	struct stToGreenItem : stBaseCommand
	{
		stPkgPos destPos;	// װ������
		stPkgPos srcPos;	// ��ʯ����
		WORD result;		// ����ֵ  0 - �ɹ��� 1 - ����ǿ����װ��

		stToGreenItem() : stBaseCommand(GAME_CMD_TO_GREEN_TIEM)
		{
		}
	};

	// �ý�Ҷ�װ��
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

	// �ͻ������������Ʒ��Ϣ
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

	// ������װ�����ı�����
	const byte GAME_CMD_CHANGE_TIEM_CRITICAL = 138;
	struct stChangeItemCritical : stBaseCommand
	{
		stPkgPos destPos;	// װ������
		stPkgPos srcPos;	// ��ʯ����
		BYTE critical;		// ������ı�����
		WORD result;		// ����ֵ  0 - �ɹ��� 1 - ����ǿ����װ��

		stChangeItemCritical() : stBaseCommand(GAME_CMD_CHANGE_TIEM_CRITICAL)
		{
		}
	};

	// ���ӵ��ߵ�����;�ֵ
	const byte GAME_CMD_USE_REPAIRSTONE = 47;
	struct stUseRepairStone : stBaseCommand
	{
		stPkgPos destPos;	// װ������
		stPkgPos srcPos;	// ��ʯ����
		WORD maxDur;		// �������µ�����;�ֵ
		WORD result;		// ����ֵ  0 - �ɹ��� 1 - ����ǿ����װ��

		stUseRepairStone() : stBaseCommand(GAME_CMD_USE_REPAIRSTONE)
		{
		}
	};


	// ��װ������ռ��ʯ
	const byte GAME_CMD_ITEM_ADD_RUNE = 237;
	struct stItemAddRune : stBaseCommand
	{
		stPkgPos runePos[3];	// 3��ռ��ʯ
		stPkgPos itemPos[2];	// ������������
		stPkgPos equipPos;		// װ��λ��
		stItemData equipData;	// װ������
		WORD result;			// ����ֵ  0 - �ɹ��� 1 - ����ǿ����װ��

		stItemAddRune() : stBaseCommand(GAME_CMD_ITEM_ADD_RUNE)
		{
		}
	};
	





















};






#pragma pack()




#endif