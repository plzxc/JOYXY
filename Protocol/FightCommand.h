#ifndef __FIGHTCOMMAND_H__
#define __FIGHTCOMMAND_H__

// ս����ص���Ϣ

#include "BaseCommand.h"
#include "types.h"


#pragma pack(1)


namespace GameCmd
{

	// �������������
	const byte GAME_CMD_CHAR_ATTACK_MON = 22;	// c -> s, s -> c
	struct stCharAttckMon : stBaseCommand
	{
		WORD x;
		WORD y;
		WORD attackType;
		WORD targetId;
		WORD damage;
		DWORD exp;
		BYTE OldPath;	// �����255��˵���Ǳ���
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



	// ������������
	const byte GAME_CMD_CHAR_ATTACK_CHAR = 30;		// c -> s, s -> c
	struct stCharAttackChar : stBaseCommand
	{
		WORD x;
		WORD y;
		WORD AttackClass;
		WORD TargetId;
		WORD Damage;
		BYTE OldPath;	// �����255��˵���Ǳ���

		stCharAttackChar() : stBaseCommand(GAME_CMD_CHAR_ATTACK_CHAR)
		{

		}
	};



	// ֪ͨ�ͻ��˹�������
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

	// ֪ͨ�ͻ�����ұ���Ҵ���
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


	// ֪ͨ�ͻ�����ұ��������
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

	// ֪ͨ�ͻ��˹��������Ʒ�ͽ��
	const byte GAME_CMD_MONDROPITEM = 45;		// s -> c
	struct stMonDropItem : stBaseCommand
	{
		DWORD money;	// �����
		WORD mapX;		// �����
		WORD mapY;
		WORD firstId;	// ������ID
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


	// ��������
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
		
		BYTE hpPer;	// ����ֵ�İٷֱ�

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

	// ����ɾ��
	const byte GAME_CMD_MON_REMOVE = 95;		// s -> c
	struct stMonRemove : stBaseCommand
	{
		stMonRemove() : stBaseCommand(GAME_CMD_MON_REMOVE)
		{
		}
	};

	// �����ƶ�
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

	// �����ƶ�ֹͣ
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

	// NPC�ƶ�
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

	// NPC�ƶ�ֹͣ
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

	// ����ֹͣ���������ʧ��
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

	// ���︴��
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


	// ���﹥�����
	const byte GAME_CMD_MON_ATTACK_CHAR = 25;		// s -> c
	struct stMonAttackChar : stBaseCommand
	{
		WORD x;
		WORD y;
		WORD AttackClass;
		WORD TargetId;
		WORD Damage;
		BYTE OldPath;	// �����255��˵���Ǳ���

		stMonAttackChar() : stBaseCommand(GAME_CMD_MON_ATTACK_CHAR)
		{
			x = y = 0;
			AttackClass= 0;
			TargetId = 0;
			Damage = 0;
			OldPath = 0;
		}
	};

	// ���ħ����������(����)
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

	// ���ħ����������(Ⱥ��)
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

	// ���ħ���������(����)
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


	// ���ħ���������(Ⱥ��)
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


	// ��Ҽ��ܹ�������(����)
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


	// ��Ҽ��ܹ�������(Ⱥ��)
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


	// ��Ҽ��ܹ������(����)
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


	// ��Ҽ��ܹ�������(Ⱥ��)
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


	// ���º���״̬
	const byte GAME_CMD_CHANGE_REDNAME = 118;		// s -> c
	struct stChangeRedName : stBaseCommand
	{
		WORD time;

		stChangeRedName() : stBaseCommand(GAME_CMD_CHANGE_REDNAME)
		{
			time = 0;
		}
	};


	// �������״̬
	const byte GAME_CMD_CLEAR_SKILL_STATE = 78;		// s -> c
	struct stClearSkillState : stBaseCommand
	{
		WORD skill;

		stClearSkillState() : stBaseCommand(GAME_CMD_CLEAR_SKILL_STATE)
		{
			skill = 0;
		}
	};


	// ͬ������Ѫ��
	const byte GAME_CMD_SET_MONHP = 247;		// s -> c
	struct stSetMonHP : stBaseCommand
	{
		BYTE type;		// 0 - ��ս�����Ѫ��, 1 - ��ͨ����Ѫ��
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