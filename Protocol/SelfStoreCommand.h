#ifndef __SELFSTORECOMMAND_H__
#define __SELFSTORECOMMAND_H__

// ��̯��ص���Ϣ

#include "BaseCommand.h"
#include "types.h"
#include "PackageManager.h"

#pragma pack(1)

namespace GameCmd
{

	// ��̯��ʼ
	const byte MAX_STOREITEM_NUM = 8;
	const byte GAME_CMD_SELF_STORE_OPEN = 240;
	struct stSelfStoreOpen : stBaseCommand
	{
		stItemEx item[MAX_STOREITEM_NUM];
		DWORD itemPrice[MAX_STOREITEM_NUM];
		WORD result;

		stSelfStoreOpen() : stBaseCommand(GAME_CMD_SELF_STORE_OPEN)
		{
			result = 0;
		}
	};

	// ̯λ״̬
	const byte GAME_CMD_SELF_STORE_STATE = 241;
	struct stSelfStoreState : stBaseCommand
	{
		BYTE state;
		stSelfStoreState() : stBaseCommand(GAME_CMD_SELF_STORE_STATE)
		{
			state = 0;
		}
	};

	// ��ȡ����
	const byte GAME_CMD_SELF_STORE_REQUEST_CATAGORY = 242;
	struct stSelfStoreRequestCatagory : stBaseCommand
	{
		WORD targetId;
		WORD result;
		stSelfStoreRequestCatagory() : stBaseCommand(GAME_CMD_SELF_STORE_REQUEST_CATAGORY)
		{
			targetId = 0;
			result = 0;
		}
	};

	// ������Ʒ
	const byte GAME_CMD_SELF_STORE_BUYITEM = 243;
	struct stSelfStoreBuyItem : stBaseCommand
	{
		WORD targetId;
		BYTE index;
		stItemEx item;
		DWORD price;
		WORD result;
		stSelfStoreBuyItem() : stBaseCommand(GAME_CMD_SELF_STORE_BUYITEM)
		{
			targetId = 0;
			index = 0;
			price = 0;
			result = 0;
		}
	};


};

#pragma pack()




#endif