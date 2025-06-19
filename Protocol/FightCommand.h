#ifndef __FIGHTCOMMAND_H__
#define __FIGHTCOMMAND_H__

// 战斗相关的消息

#include "BaseCommand.h"
#include "types.h"


#pragma pack(1)


namespace GameCmd
{

	// 玩家物理攻击怪物
	const byte GAME_CMD_CHAR_ATTACK_MON = 22;	// c -> s, s -> c
	struct stCharAttckMon : stBaseCommand
	{
		WORD x;
		WORD y;
		WORD attackType;
		WORD targetId;
		WORD damage;
		DWORD exp;
		BYTE OldPath;	// 如果是255，说明是暴击
		stCharAttckMon() : stBaseCommand(GAME_CMD_CHAR_ATTACK_MON)
		{
			x = 0;
			y = 0;
			attackType = 0;
			targetId = 0;
			damage = 0;
			exp = 0;
			OldPath = 0;
		}
	};



	// 玩家物理攻击玩家
	const byte GAME_CMD_CHAR_ATTACK_CHAR = 30;		// c -> s, s -> c
	struct stCharAttackChar : stBaseCommand
	{
		WORD x;
		WORD y;
		WORD AttackClass;
		WORD TargetId;
		WORD Damage;
		BYTE OldPath;	// 如果是255，说明是暴击

		stCharAttackChar() : stBaseCommand(GAME_CMD_CHAR_ATTACK_CHAR)
		{

		}
	};



	// 通知客户端怪物死亡
	const byte GAME_CMD_MONDEAD = 24;		// s -> c
	struct stMonDead : stBaseCommand
	{
		WORD attackType;
		WORD targetId;
		WORD x;
		WORD y;
		DWORD exp;
		WORD level;
		BYTE OldPath;
		stMonDead() : stBaseCommand(GAME_CMD_MONDEAD)
		{
			attackType = 0;
			targetId = 0;
			x = 0;
			y = 0;
			exp = 0;
			level = 0;
			OldPath = 0;
		}
	};

	// 通知客户端玩家被玩家打死
	const byte GAME_CMD_CHAR_DEAD_BY_CHAR = 32;		// s -> c
	struct stCharDeadByChar : stBaseCommand
	{
		WORD attackType;
		WORD targetId;
		WORD x;
		WORD y;
		DWORD exp;
		WORD level;
		BYTE OldPath;
		stCharDeadByChar() : stBaseCommand(GAME_CMD_CHAR_DEAD_BY_CHAR)
		{
			attackType = 0;
			targetId = 0;
			x = 0;
			y = 0;
			exp = 0;
			level = 0;
			OldPath = 0;
		}
	};


	// 通知客户端玩家被怪物打死
	const byte GAME_CMD_CHAR_DEAD_BY_MON = 33;		// s -> c
	struct stCharDeadByMon : stBaseCommand
	{
		WORD attackType;
		WORD targetId;
		WORD x;
		WORD y;
		DWORD exp;
		WORD level;
		BYTE OldPath;
		stCharDeadByMon() : stBaseCommand(GAME_CMD_CHAR_DEAD_BY_MON)
		{
			attackType = 0;
			targetId = 0;
			x = 0;
			y = 0;
			exp = 0;
			level = 0;
			OldPath = 0;
		}
	};
	

	struct DROPITEMINFO
	{
		WORD itemId;
		WORD x;
		WORD y;
		UINT color;
	};

	// 通知客户端怪物掉落物品和金币
	const byte GAME_CMD_MONDROPITEM = 45;		// s -> c
	struct stMonDropItem : stBaseCommand
	{
		DWORD money;	// 金币数
		WORD mapX;		// 金币在
		WORD mapY;
		WORD firstId;	// 归属者ID
		DWORD count;
		DROPITEMINFO data[0];
		stMonDropItem() : stBaseCommand(GAME_CMD_MONDROPITEM)
		{
			money = 0;
			mapX = 0;
			mapY = 0;
			firstId = 0;
			count = 0;
		}

		unsigned int getSize() { return sizeof(stMonDropItem) + count * sizeof(data[0]); }
	};


	// 创建怪物
	const byte GAME_CMD_MON_CREATE = 20;		// s -> c
	struct stMonCreate : stBaseCommand
	{
		WORD c_x;
		WORD c_y;
		WORD m_x;
		WORD m_y;

		BYTE speed;
		BYTE mapId;
		BYTE race;
		BYTE mode;
		BYTE time;
		BYTE level;
		
		BYTE hpPer;	// 生命值的百分比

		stMonCreate() : stBaseCommand(GAME_CMD_MON_CREATE)
		{
			c_x = 0;
			c_y = 0;
			m_x = 0;
			m_y = 0;
			speed = 0;
			mapId = 0;
			race = 0;
			mode = 0;
			time = 1;
			level = 0;
			hpPer = 100;
		}
	};

	// 怪物删除
	const byte GAME_CMD_MON_REMOVE = 95;		// s -> c
	struct stMonRemove : stBaseCommand
	{
		stMonRemove() : stBaseCommand(GAME_CMD_MON_REMOVE)
		{
		}
	};

	// 怪物移动
	const byte GAME_CMD_MON_MOVE = 21;		// s -> c
	struct stMonMove : stBaseCommand
	{
		WORD x;
		WORD y;

		stMonMove() : stBaseCommand(GAME_CMD_MON_MOVE)
		{
			x = y = 0;
		}
	};

	// 怪物移动停止
	const byte GAME_CMD_MON_MOVEEX = 203;		// s -> c
	struct stMonMoveEx : stBaseCommand
	{
		WORD x;
		WORD y;

		stMonMoveEx() : stBaseCommand(GAME_CMD_MON_MOVEEX)
		{
			x = y = 0;
		}
	};

	// NPC移动
	const byte GAME_CMD_NPC_MOVE = 168;		// s -> c
	struct stNpcMove : stBaseCommand
	{
		WORD x;
		WORD y;

		stNpcMove() : stBaseCommand(GAME_CMD_NPC_MOVE)
		{
			x = y = 0;
		}
	};

	// NPC移动停止
	const byte GAME_CMD_NPC_MOVEEX = 204;		// s -> c
	struct stNpcMoveEx : stBaseCommand
	{
		WORD x;
		WORD y;

		stNpcMoveEx() : stBaseCommand(GAME_CMD_NPC_MOVEEX)
		{
			x = y = 0;
		}
	};

	// 怪物停止活动（怪物消失）
	const byte GAME_CMD_MON_INACTIVE = 121;		// s -> c
	struct stMonInactive : stBaseCommand
	{
		WORD monId;
		BYTE result;

		stMonInactive() : stBaseCommand(GAME_CMD_MON_INACTIVE)
		{
			monId = result = 0;
		}
	};

	// 怪物复活
	const byte GAME_CMD_MON_REVIVE = 27;		// s -> c
	struct stMonRevive : stBaseCommand
	{
		WORD c_x;
		WORD c_y;
		WORD m_x;
		WORD m_y;

		BYTE speed;
		BYTE mapId;
		BYTE race;
		BYTE mode;
		BYTE time;
		BYTE level;
		BYTE hpPer;

		stMonRevive() : stBaseCommand(GAME_CMD_MON_REVIVE)
		{
			c_x = 0;
			c_y = 0;
			m_x = 0;
			m_y = 0;
			speed = 0;
			mapId = 0;
			race = 0;
			mode = 0;
			time = 1;
			level = 0;
			hpPer = 100;
		}
	};


	// 怪物攻击玩家
	const byte GAME_CMD_MON_ATTACK_CHAR = 25;		// s -> c
	struct stMonAttackChar : stBaseCommand
	{
		WORD x;
		WORD y;
		WORD AttackClass;
		WORD TargetId;
		WORD Damage;
		BYTE OldPath;	// 如果是255，说明是暴击

		stMonAttackChar() : stBaseCommand(GAME_CMD_MON_ATTACK_CHAR)
		{
			x = y = 0;
			AttackClass= 0;
			TargetId = 0;
			Damage = 0;
			OldPath = 0;
		}
	};

	// 玩家魔法攻击怪物(单攻)
	const byte GAME_CMD_CHAR_MAGATTACK_MON = 57;
	struct stCharMagAttackMon : stBaseCommand
	{
		WORD magClass;
		BYTE magPos;

		WORD targetId;

		WORD c_x;
		WORD c_y;
		WORD damage;
		DWORD exp;

		BYTE OldPath;

		stCharMagAttackMon() : stBaseCommand(GAME_CMD_CHAR_MAGATTACK_MON)
		{

		}
	};

	// 玩家魔法攻击怪物(群攻)
	const byte GAME_CMD_CHAR_MAGATTACK_MON_EX = 58;
	struct stCharMagAttackMonEx : stBaseCommand
	{
		WORD magClass;
		BYTE magPos;

		WORD targetId[8];
		WORD damage[8];

		WORD c_x;
		WORD c_y;

		DWORD exp;
		BYTE OldPath;

		stCharMagAttackMonEx() : stBaseCommand(GAME_CMD_CHAR_MAGATTACK_MON_EX)
		{

		}
	};

	// 玩家魔法攻击玩家(单攻)
	const byte GAME_CMD_CHAR_MAGATTACK_CHAR = 59;
	struct stCharMagAttackChar : stBaseCommand
	{
		WORD magClass;
		BYTE magPos;

		WORD targetId;

		WORD c_x;
		WORD c_y;
		WORD damage;

		BYTE OldPath;

		stCharMagAttackChar() : stBaseCommand(GAME_CMD_CHAR_MAGATTACK_CHAR)
		{

		}
	};


	// 玩家魔法攻击玩家(群攻)
	const byte GAME_CMD_CHAR_MAGATTACK_CHAR_EX = 60;
	struct stCharMagAttackCharEx : stBaseCommand
	{
		WORD magClass;
		BYTE magPos;

		WORD targetId[8];
		WORD damage[8];

		WORD c_x;
		WORD c_y;

		stCharMagAttackCharEx() : stBaseCommand(GAME_CMD_CHAR_MAGATTACK_CHAR_EX)
		{

		}
	};


	// 玩家技能攻击怪物(单攻)
	const byte GAME_CMD_CHAR_SKILLATTACK_MON = 50;
	struct stCharSkillAttackMon : stBaseCommand
	{
		WORD c_x;
		WORD c_y;
		WORD AttackClass[3];
		BYTE AttackClassPos[3];
		WORD ResultSkill;
		WORD TargetId;
		WORD Damage;
		DWORD CurExp;
		BYTE OldPath;

		stCharSkillAttackMon() : stBaseCommand(GAME_CMD_CHAR_SKILLATTACK_MON)
		{

		}
	};


	// 玩家技能攻击怪物(群攻)
	const byte GAME_CMD_CHAR_SKILLATTACK_MON_EX = 51;
	struct stCharSkillAttackMonEx : stBaseCommand
	{
		WORD c_x;
		WORD c_y;
		WORD AttackClass;
		BYTE AttackClassPos;

		WORD TargetId[8];
		WORD Damage[8];

		DWORD CurExp;
		BYTE OldPath;

		stCharSkillAttackMonEx() : stBaseCommand(GAME_CMD_CHAR_SKILLATTACK_MON_EX)
		{

		}
	};


	// 玩家技能攻击玩家(单攻)
	const byte GAME_CMD_CHAR_SKILLATTACK_CHAR = 54;
	struct stCharSkillAttackChar : stBaseCommand
	{
		WORD c_x;
		WORD c_y;
		WORD AttackClass[3];
		BYTE AttackClassPos[3];
		WORD ResultSkill;
		WORD TargetId;
		WORD Damage;
		BYTE OldPath;

		stCharSkillAttackChar() : stBaseCommand(GAME_CMD_CHAR_SKILLATTACK_CHAR)
		{

		}
	};


	// 玩家技能攻击怪物(群攻)
	const byte GAME_CMD_CHAR_SKILLATTACK_CHAR_EX = 55;
	struct stCharSkillAttackCharEx : stBaseCommand
	{
		WORD c_x;
		WORD c_y;
		WORD AttackClass;
		BYTE AttackClassPos;

		WORD TargetId[8];
		WORD Damage[8];

		BYTE OldPath;

		stCharSkillAttackCharEx() : stBaseCommand(GAME_CMD_CHAR_SKILLATTACK_CHAR_EX)
		{

		}
	};


	// 更新红名状态
	const byte GAME_CMD_CHANGE_REDNAME = 118;		// s -> c
	struct stChangeRedName : stBaseCommand
	{
		WORD time;

		stChangeRedName() : stBaseCommand(GAME_CMD_CHANGE_REDNAME)
		{
			time = 0;
		}
	};


	// 清除技能状态
	const byte GAME_CMD_CLEAR_SKILL_STATE = 78;		// s -> c
	struct stClearSkillState : stBaseCommand
	{
		WORD skill;

		stClearSkillState() : stBaseCommand(GAME_CMD_CLEAR_SKILL_STATE)
		{
			skill = 0;
		}
	};


	// 同步怪物血量
	const byte GAME_CMD_SET_MONHP = 247;		// s -> c
	struct stSetMonHP : stBaseCommand
	{
		BYTE type;		// 0 - 城战怪物的血量, 1 - 普通怪物血量
		UINT maxHP;
		UINT curHP;

		stSetMonHP() : stBaseCommand(GAME_CMD_SET_MONHP)
		{
			type = 0;
			maxHP = 0;
			curHP = 0;
		}
	};


};

#pragma pack()




#endif