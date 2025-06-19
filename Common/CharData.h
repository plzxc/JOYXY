#ifndef __CHARDATA_H__
#define __CHARDATA_H__

#include "ItemData.h"
#include "Types.h"


#pragma pack(1)


// 角色基础数据，存于数据库和User
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
	UINT str;		// 力量
	UINT con;		// 体力
	UINT dex;		// 敏捷
	UINT wiz;		// 精神力
	UINT intgent;	// 智力
	DWORD money;
	DWORD safeMoney;
	DWORD pkCount;
	WORD inPrision;
	WORD marriage;	// 是否结婚
	char matename[MAX_NAME_SIZE+1];	// 配偶名称
	BYTE events[MAX_EVENT+1];// 事件和任务表
	WORD battleProp;	// 战斗属性(水火风)
	DWORD guildid;		// 工会ID(无效工会ID-65535)
	DWORD bioRhythm;	// 3高
	DWORD offlineTime;	// 最后下线时间
	DWORD usedExpTime;	// 已经领取的双倍时间
	DWORD unuseExpTime;	// 未领取的双倍时间
	WORD unusedEgg;		// 未领取的金蛋数量
	DWORD reincarnate;	// 转生次数(0-表示没有转生，否则表示转生的次数)

	stCharBase()
	{
        ZeroMemory(this, sizeof(*this));
	}
};

// 物品结构(存储结构)
struct stItemData 
{
	WORD itemId;		// 物品ID
	UINT uinId;			// 唯一ID
	UINT time;			// 可用时间
	BYTE bind;			// 是否绑定
	WORD duration;		// 耐久
	union {
		DWORD mixData;	// 混合数据

		// 装备信息
		struct EQUIPINFO 
		{
			BYTE slot[3];	// 3个槽
			BYTE prop : 4;	// 属性类型
			BYTE star : 4;	// 星数(属性数值)
		};
		EQUIPINFO equipInfo;

		// 宠物信息
		struct PETINFO
		{
			BYTE property;	// 属性
			BYTE petLevel;	// 等级
			WORD petExp;	// 宠物经验值
		};
		PETINFO petInfo;
	};

	// 装备扩展信息
	struct EQUIPINFO_EX
	{
		BYTE attack;	// 攻击力
		BYTE attackPer;
		BYTE critical;	// 暴击率
		BYTE none2;
		BYTE phyDef;	// 物理防御力
		BYTE phyDefPer;
		BYTE magDef;	// 魔法防御力
		BYTE magDefPer;
		BYTE hp;		// 生命值
		BYTE hpPer;
		BYTE mp;		// 魔法值
		BYTE mpPer;
		BYTE sp;		// 技能值
		BYTE spPer;
		BYTE atkAcc;	// 命中率
		BYTE defAcc;	// 躲避率
	};
	BYTE frozen;	// 是否解封(0-白装，1-未解封，2-解封)
	EQUIPINFO_EX equipInfoex;

	WORD maxDur;		// 最大耐久
	BYTE reserved[38];


	stItemData()
	{
		Init();
	}

	//////////////////////////////////////////////////////////////////////////
	// 装备接口

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

	// 处理未解封的道具
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
	// 宠物接口

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


	// 如果返回255说明没有空的洞了
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


// 技能结构
struct stSkillData 
{
	WORD id;	// 技能书的ID号
	UINT exp;	// 技能经验值
	UINT cd;	// 冷却时间
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

// 玩家身上装备的物品
struct stCharEquipItems
{
	stItemData equips[EQUIP_CX][EQUIP_CY];
};

// 玩家背包里的物品
struct stCharBagItems
{
	stItemData bag[MAX_BAG_PAGE][BAG_CX][BAG_CY];
};

// 玩家银行里的物品
struct stCharSafeItems 
{
	stItemData safe[MAX_SAFE_PAGE][SAFE_CX][SAFE_CY];
};

// 快捷栏里的物品
struct stCharQuickItems
{
	stItemData quickItems[QUICK_CX][QUICK_CY];
};

// 玩家职业技能
struct stCharJobSkills
{
	stSkillData skills[JOB_CX][JOB_CY];
};

// 玩家的魔法
struct stCharMagics
{
	stSkillData magic[MAX_MAGIC_PAGE][MAGIC_CX][MAGIC_CY];
};

// 玩家的技能
struct stCharSkills
{
	stSkillData skill[MAX_SKILL_PAGE][SKILL_CX][SKILL_CY];
};

// 玩家二进制数据
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


// 角色选择界面中的角色信息结构
struct stSelectCharInfo
{
	BYTE isExist;				// 0 no character, 1 valide
	DWORD charid;				// 角色唯一ID号
	WORD index;					// 角色索引号(0,1,2) [charIndex]
	WORD race;					// 种族(战士,法师，游侠)
	char charName[MAX_NAME_SIZE+1];			// 角色名
	WORD mapId;					// 地图ID
	BYTE isMerrage;				// 是否已经结婚 0 - 未婚, 1 - 结婚
	BYTE isInGuild;				// 是否有工会 0 - 未加工会, 1 - 加入工会了

	stSelectCharInfo()
	{
		ZeroMemory(this, sizeof(*this));
	}
};











#pragma pack()


#endif






