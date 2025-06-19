#ifndef __MISSIONCOMMAND_H__
#define __MISSIONCOMMAND_H__

// 任务相关的消息

#include "BaseCommand.h"
#include "types.h"
#include "PackageManager.h"
#include "BaseData.h"

#pragma pack(1)

namespace GameCmd
{
	// 购买的物品结构
	struct stMissionItem
	{
		WORD pkg;
		WORD itemId;
		WORD x;
		WORD y;

		stMissionItem()
		{
			ZeroMemory(this, sizeof(*this));
		}
	};


	// 开始任务
	const byte GAME_CMD_START_MISSION = 225;
	struct stStartMission : stBaseCommand
	{
		WORD missionId;
		WORD result;

		stStartMission() : stBaseCommand(GAME_CMD_START_MISSION)
		{
			missionId = 0;
			result = 0;
		}
	};

	// 结束任务
	const byte GAME_CMD_END_MISSION = 227;
	struct stEndMission : stBaseCommand
	{
		WORD missionId;
		BYTE MonNum;
		stMissionItem item[MISS_ITEM_NUM];
		WORD result;

		stEndMission() : stBaseCommand(GAME_CMD_END_MISSION)
		{
			MonNum = 0;
			result = 0;
		}
	};

	// 结束任务
	const byte GAME_CMD_END_MISSION_RESULT = 228;
	struct stEndMissionResult : stBaseCommand
	{
		WORD missionId;
		DWORD exp;
		DWORD money;
		stMissionItem item[8];
		WORD result;

		stEndMissionResult() : stBaseCommand(GAME_CMD_END_MISSION_RESULT)
		{
			exp = 0;
			money = 0;
			result = 0;
		}
	};

	// 取消任务
	const byte GAME_CMD_CANCEL_MISSION = 229;
	struct stCancelMission : stBaseCommand
	{
		WORD missionId;
		WORD result;
		stCancelMission() : stBaseCommand(GAME_CMD_CANCEL_MISSION)
		{
			missionId = 0;
			result = 0;
		}
	};

	// 事件任务
	const byte GAME_CMD_EVENT_MISSION = 93;
	struct stEventMission : stBaseCommand
	{
		BYTE StoryNum;
		WORD EventNum;
		stMissionItem AddItem[6];
		WORD result;

		stEventMission() : stBaseCommand(GAME_CMD_EVENT_MISSION)
		{
			StoryNum = 0;
			EventNum = 0;
			result = 0;
		}
	};


	// 洗职业技能任务
	const byte GAME_CMD_REMOVE_JOB = 205;
	struct stRemoveJob : stBaseCommand
	{
		stPkgPos pos;
		WORD itemId;
		WORD result;

		stRemoveJob() : stBaseCommand(GAME_CMD_REMOVE_JOB)
		{
			itemId = 0;
			result = 0;
		}
	};


	// npc菜单
	const byte GAME_CMD_GET_NPCMENU = 106;
	struct stGetNpcMenu : stBaseCommand
	{
		WORD npcid;
		WORD scriptId;

		stGetNpcMenu() : stBaseCommand(GAME_CMD_GET_NPCMENU)
		{
			npcid = 0;
			scriptId = 0;
		}
	};


	#define NPCMSGLINE 12

	struct NPCMSG
	{
		BYTE LineNum;
		char strmsg[NPCMSGLINE][64];

		NPCMSG()
		{
			LineNum = 0;
			ZeroMemory(strmsg,sizeof(strmsg));
		}
	};

	// npc菜单返回值
	const byte GAME_CMD_GET_NPCMENU_RESULT = 120;
	struct stGetNpcMenuResult : stBaseCommand
	{
		WORD npcid;
		BYTE dlgType;	// 0 - 文字框, 1 - 菜单框
		BYTE btnType;	// 按钮类型 0 - 确定，1 - 确定/取消
		NPCMSG npcMsg;	// 消息内容

		stGetNpcMenuResult() : stBaseCommand(GAME_CMD_GET_NPCMENU_RESULT)
		{
			npcid = 0;
			dlgType = 0;
			btnType = 0;
		}
	};


	// 点击npc菜单
	const byte GAME_CMD_CLICK_NPCMENU = 132;
	struct stClickNpcMenu : stBaseCommand
	{
		WORD npcid;
		BYTE line;	// 选中的行号(244 - 确定, 255 - 取消)

		stClickNpcMenu() : stBaseCommand(GAME_CMD_CLICK_NPCMENU)
		{
			npcid = 0;
			line = 0;
		}
	};

};

#pragma pack()




#endif