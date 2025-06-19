#ifndef __CHARDATA_H__
#define __CHARDATA_H__

#include "ItemData.h"
#include "Types.h"


#pragma pack(1)


// ��ɫ�������ݣ��������ݿ��User
struct stCharBase 
{
	//DWORD charid;
	char charName[MAX_NAME_SIZE+1];
	char nickName[MAX_NAME_SIZE+1];
	DWORD nickColor;
	WORD race;
	WORD job;
	WORD countryId;
	WORD mapId;
	WORD x;
	WORD y;
	WORD level;
	DWORD exp;
	UINT levelupPoint;
	WORD health;
	UINT hp;
	UINT mp;
	WORD jp;
	UINT sp;
	WORD hungry;
	UINT str;		// ����
	UINT con;		// ����
	UINT dex;		// ����
	UINT wiz;		// ������
	UINT intgent;	// ����
	DWORD money;
	DWORD safeMoney;
	DWORD pkCount;
	WORD inPrision;
	WORD marriage;	// �Ƿ���
	char matename[MAX_NAME_SIZE+1];	// ��ż����
	BYTE events[MAX_EVENT+1];// �¼��������
	WORD battleProp;	// ս������(ˮ���)
	DWORD guildid;		// ����ID(��Ч����ID-65535)
	DWORD bioRhythm;	// 3��
	DWORD offlineTime;	// �������ʱ��
	DWORD usedExpTime;	// �Ѿ���ȡ��˫��ʱ��
	DWORD unuseExpTime;	// δ��ȡ��˫��ʱ��
	WORD unusedEgg;		// δ��ȡ�Ľ�����
	DWORD reincarnate;	// ת������(0-��ʾû��ת���������ʾת���Ĵ���)

	stCharBase()
	{
        ZeroMemory(this, sizeof(*this));
	}
};

// ��Ʒ�ṹ(�洢�ṹ)
struct stItemData 
{
	WORD itemId;		// ��ƷID
	UINT uinId;			// ΨһID
	UINT time;			// ����ʱ��
	BYTE bind;			// �Ƿ��
	WORD duration;		// �;�
	union {
		DWORD mixData;	// �������

		// װ����Ϣ
		struct EQUIPINFO 
		{
			BYTE slot[3];	// 3����
			BYTE prop : 4;	// ��������
			BYTE star : 4;	// ����(������ֵ)
		};
		EQUIPINFO equipInfo;

		// ������Ϣ
		struct PETINFO
		{
			BYTE property;	// ����
			BYTE petLevel;	// �ȼ�
			WORD petExp;	// ���ﾭ��ֵ
		};
		PETINFO petInfo;
	};

	// װ����չ��Ϣ
	struct EQUIPINFO_EX
	{
		BYTE attack;	// ������
		BYTE attackPer;
		BYTE critical;	// ������
		BYTE none2;
		BYTE phyDef;	// ���������
		BYTE phyDefPer;
		BYTE magDef;	// ħ��������
		BYTE magDefPer;
		BYTE hp;		// ����ֵ
		BYTE hpPer;
		BYTE mp;		// ħ��ֵ
		BYTE mpPer;
		BYTE sp;		// ����ֵ
		BYTE spPer;
		BYTE atkAcc;	// ������
		BYTE defAcc;	// �����
	};
	BYTE frozen;	// �Ƿ���(0-��װ��1-δ��⣬2-���)
	EQUIPINFO_EX equipInfoex;

	WORD maxDur;		// ����;�
	BYTE reserved[38];


	stItemData()
	{
		Init();
	}

	//////////////////////////////////////////////////////////////////////////
	// װ���ӿ�

	BYTE getProp()
	{
		return equipInfo.prop;
	}

	void setProp(BYTE prop)
	{
		equipInfo.prop = prop;
	}

	BYTE getPropNum()
	{
		return equipInfo.star;
	}

	void setPropNum(BYTE prop)
	{
		equipInfo.star = prop;
	}

	BYTE getStar()
	{
		return equipInfo.star;
	}

	void setStar(BYTE star)
	{
		//mixData = ((mixData & 0xFFFFFF00) | star);
		equipInfo.star = star;
	}

	// ����δ���ĵ���
	void procFrozen()
	{
		if (frozen != 2) {
			ZeroMemory(&equipInfoex,sizeof(equipInfoex));
		}
	}

	bool isFrozen()
	{
		return frozen == 2;
	}

	////////////////////////////////////////////////////////////////////////// 
	// ����ӿ�

	BYTE getPetLevel()
	{
		return petInfo.petLevel;
	}

	void setPetLevel(BYTE level)
	{
		petInfo.petLevel = level;
	}

	void setPetExp(WORD exp)
	{
		petInfo.petExp = exp;
	}

	WORD getPetExp()
	{
		return petInfo.petExp;
	}

	BYTE getPetProperty()
	{
		return petInfo.property;
	}

	void setPetProperty(BYTE prop)
	{
		petInfo.property = prop;
	}


	// �������255˵��û�пյĶ���
	BYTE getFreeSlot()
	{
		DWORD itemId = INVALID_ITEM_ID;
		for (int i=0; i<3; i++) {
			itemId = equipInfo.slot[i];
			if (itemId == INVALID_ITEM_ID)
				return i;
		}

		return 255;
	}

	// index(0, 1, 2)
	BYTE getSlotItemId(BYTE index)
	{
		if (index > 2) 
			return 0;

		return equipInfo.slot[index];
	}

	void setSoltItemId(BYTE index, BYTE itemId)
	{
		if (index > 2) 
			return;

		equipInfo.slot[index] = itemId;
	}

	void Init()
	{
		ZeroMemory(this,sizeof(*this));
	}
};


// ���ܽṹ
struct stSkillData 
{
	WORD id;	// �������ID��
	UINT exp;	// ���ܾ���ֵ
	UINT cd;	// ��ȴʱ��
	BYTE reserved[20];

	stSkillData()
	{
		Init();
	}

	void Init()
	{
		ZeroMemory(this,sizeof(*this));
	}
};



using namespace PkgSize;

// �������װ������Ʒ
struct stCharEquipItems
{
	stItemData equips[EQUIP_CX][EQUIP_CY];
};

// ��ұ��������Ʒ
struct stCharBagItems
{
	stItemData bag[MAX_BAG_PAGE][BAG_CX][BAG_CY];
};

// ������������Ʒ
struct stCharSafeItems 
{
	stItemData safe[MAX_SAFE_PAGE][SAFE_CX][SAFE_CY];
};

// ����������Ʒ
struct stCharQuickItems
{
	stItemData quickItems[QUICK_CX][QUICK_CY];
};

// ���ְҵ����
struct stCharJobSkills
{
	stSkillData skills[JOB_CX][JOB_CY];
};

// ��ҵ�ħ��
struct stCharMagics
{
	stSkillData magic[MAX_MAGIC_PAGE][MAGIC_CX][MAGIC_CY];
};

// ��ҵļ���
struct stCharSkills
{
	stSkillData skill[MAX_SKILL_PAGE][SKILL_CX][SKILL_CY];
};

// ��Ҷ���������
struct stCharBinaryData
{
	stCharEquipItems	equipItems;
	stCharBagItems		bagItems;
	stCharSafeItems		safeItems;
	stCharQuickItems	quickItems;
	stCharJobSkills		jobSkills;
	stCharMagics		magics;
	stCharSkills		skills;
};


// ��ɫѡ������еĽ�ɫ��Ϣ�ṹ
struct stSelectCharInfo
{
	BYTE isExist;				// 0 no character, 1 valide
	DWORD charid;				// ��ɫΨһID��
	WORD index;					// ��ɫ������(0,1,2) [charIndex]
	WORD race;					// ����(սʿ,��ʦ������)
	char charName[MAX_NAME_SIZE+1];			// ��ɫ��
	WORD mapId;					// ��ͼID
	BYTE isMerrage;				// �Ƿ��Ѿ���� 0 - δ��, 1 - ���
	BYTE isInGuild;				// �Ƿ��й��� 0 - δ�ӹ���, 1 - ���빤����

	stSelectCharInfo()
	{
		ZeroMemory(this, sizeof(*this));
	}
};











#pragma pack()


#endif






