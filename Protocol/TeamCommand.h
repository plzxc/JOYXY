#ifndef __TEAMCOMMAND_H__
#define __TEAMCOMMAND_H__

// 组队相关的消息

#include "BaseCommand.h"
#include "types.h"


#pragma pack(1)

namespace GameCmd
{
	// 队伍信息
	struct stTeamInfo 
	{
		WORD targetId;
		char name[MAX_NAME_SIZE+1];
		UINT hp;
		UINT maxHP;
		WORD teamId;
		BYTE teamType;
		WORD index;

		stTeamInfo()
		{
			ZeroMemory(this, sizeof(*this));
		}
	};

	// 创建队伍
	const byte GAME_CMD_TEAM_CREATE = 81;			// c->s, s -> c
	struct stTeamCreate : stBaseCommand
	{
		stTeamInfo info;
		WORD result;
		stTeamCreate() : stBaseCommand(GAME_CMD_TEAM_CREATE)
		{
			result = 0;
		}
	};

	// 解散队伍
	const byte GAME_CMD_TEAM_BREAK = 83;			// c->s, s -> c
	struct stTeamBreak : stBaseCommand
	{
		stTeamInfo info;
		WORD result;
		stTeamBreak() : stBaseCommand(GAME_CMD_TEAM_BREAK)
		{
			result = 0;
		}
	};

	// 加入队伍
	const byte GAME_CMD_TEAM_JOIN = 85;			// c->s, s -> c
	struct stTeamJoin : stBaseCommand
	{
		stTeamInfo info;
		WORD result;
		stTeamJoin() : stBaseCommand(GAME_CMD_TEAM_JOIN)
		{
			result = 0;
		}
	};

	// 加入队伍
	const byte GAME_CMD_TEAM_JOIN_RESULT = 86;			// c->s, s -> c
	struct stTeamJoinResult : stBaseCommand
	{
		stTeamInfo info;
		WORD result;
		stTeamJoinResult() : stBaseCommand(GAME_CMD_TEAM_JOIN_RESULT)
		{
			result = 0;
		}
	};

	// 踢掉一个成员(或某个成员主动离开)
	const byte GAME_CMD_TEAM_LEAVE = 87;			// c->s, s -> c
	struct stTeamLeave : stBaseCommand
	{
		stTeamInfo info;
		WORD result;
		stTeamLeave() : stBaseCommand(GAME_CMD_TEAM_LEAVE)
		{
			result = 0;
		}
	};

	//////////////////////////////////////////////////////////////////////////

	// 队伍经验
	const byte GAME_CMD_TEAM_EXP = 89;			// c->s, s -> c
	struct stTeamExp : stBaseCommand
	{
		DWORD exp;
		stTeamExp() : stBaseCommand(GAME_CMD_TEAM_EXP)
		{
		}
	};

	// 队伍中升级
	const byte GAME_CMD_TEAM_LEVELUP = 90;			// c->s, s -> c
	struct stTeamLevelUp : stBaseCommand
	{
		WORD level;
		UINT UpPoint[4];
		DWORD exp;
		stTeamLevelUp() : stBaseCommand(GAME_CMD_TEAM_LEVELUP)
		{
		}
	};

	// 队伍中改变血量
	const byte GAME_CMD_TEAM_CHANGE_HP = 91;			// c->s, s -> c
	struct stTeamChangeHP : stBaseCommand
	{
		WORD index;
		UINT hp;
		UINT maxHP;
		stTeamChangeHP() : stBaseCommand(GAME_CMD_TEAM_CHANGE_HP)
		{
		}
	};

};

#pragma pack()




#endif