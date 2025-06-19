#ifndef __GAMECOMMAND_H__
#define __GAMECOMMAND_H__

#include "BaseCommand.h"
#include "CharData.h"
#include "types.h"
#include "FightCommand.h"

#pragma pack(1)

// 处理游戏中比较杂乱的消息

#define MAX_CHAR	3

namespace GameCmd
{
	// 游戏服务器给客户端分配的ID号
	const byte GAME_CMD_CLIENT_GAME_ID = 0;		// server -> client
	struct stClientGameID : stBaseCommand
	{
		byte result;
		stClientGameID() : stBaseCommand(GAME_CMD_CLIENT_GAME_ID)
		{
			result = 0;
		}
	};

	//  客户端请求角色列表
	const byte GAME_CMD_REQUEST_CHARLIST = 250;		// client -> server
	struct stRequestCharList : stBaseCommand
	{
		char account[MAX_ACCOUNT_SIZE+1];
		char key[13];
		BYTE unk1;

		stRequestCharList() : stBaseCommand(GAME_CMD_REQUEST_CHARLIST)
		{
			ZeroMemory(account,sizeof(account));
			ZeroMemory(key,sizeof(key));
			unk1 = 1;
		}
	};

	// 服务器返回角色列表
	const byte GAME_CMD_REQUEST_CHARLIST_RESULT = 251;		// server -> client
	struct stRequestCharListResult : stBaseCommand
	{
		char account[MAX_ACCOUNT_SIZE+1];
		BYTE serverId;	// 未用
		stSelectCharInfo selectCharInfo[MAX_CHAR];
		WORD result;

		stRequestCharListResult() : stBaseCommand(GAME_CMD_REQUEST_CHARLIST_RESULT)
		{
			serverId = 1;
			result = 0;
		}
	};


	// 客户端请求创建角色
	const byte GAME_CMD_CREATE_CHAR = 252;		// client -> server
	struct stCreateChar : stBaseCommand
	{
		char account[MAX_ACCOUNT_SIZE+1];
		BYTE unk1;

		WORD charIndex;
		WORD race;
		char charName[MAX_NAME_SIZE+1];

		WORD mapId;
		WORD x;
		WORD y;
		WORD result;

		stCreateChar() : stBaseCommand(GAME_CMD_CREATE_CHAR)
		{
			ZeroMemory(account,sizeof(account));
			unk1 = 1;
			charIndex = 0;
			race = 0;
			ZeroMemory(charName,sizeof(charName));
			mapId = x = y = 0;
			result = 0;
		}
	};

	// 服务器返回创建角色的结果
	const byte GAME_CMD_CREATE_CHAR_RESULT = 253;
	struct stCreateCharResult : stBaseCommand
	{
		char account[MAX_ACCOUNT_SIZE+1];
		BYTE unk1;

		WORD charIndex;
		WORD race;
		char charName[MAX_NAME_SIZE+1];

		WORD mapId;
		WORD x;
		WORD y;
		WORD result;

		stCreateCharResult() : stBaseCommand(GAME_CMD_CREATE_CHAR_RESULT)
		{
			ZeroMemory(account,sizeof(account));
			unk1 = 1;
			charIndex = 0;
			race = 0;
			ZeroMemory(charName,sizeof(charName));
			mapId = x = y = 0;
			result = 0;
		}
	};


	// 客户端请求删除角色
	const byte GAME_CMD_DELETE_CHAR = 254;		// client -> server
	struct stDeleteChar : stBaseCommand
	{
		char account[MAX_ACCOUNT_SIZE+1];
		BYTE unk1;

		WORD charIndex;
		WORD race;
		char charName[MAX_NAME_SIZE+1];

		WORD mapId;
		WORD x;
		WORD y;
		WORD result;

		stDeleteChar() : stBaseCommand(GAME_CMD_DELETE_CHAR)
		{
			ZeroMemory(account,sizeof(account));
			unk1 = 1;
			charIndex = 0;
			race = 0;
			ZeroMemory(charName,sizeof(charName));
			mapId = x = y = 0;
			result = 0;
		}
	};


	// 服务器返回删除角色的结果
	const byte GAME_CMD_DELETE_CHAR_RESULT = 255;
	struct stDeleteCharResult : stBaseCommand
	{
		char account[MAX_ACCOUNT_SIZE+1];
		BYTE unk1;

		WORD charIndex;
		WORD race;
		char charName[MAX_NAME_SIZE+1];

		WORD mapId;
		WORD x;
		WORD y;
		WORD result;

		stDeleteCharResult() : stBaseCommand(GAME_CMD_DELETE_CHAR_RESULT)
		{
			ZeroMemory(account,sizeof(account));
			unk1 = 1;
			charIndex = 0;
			race = 0;
			ZeroMemory(charName,sizeof(charName));
			mapId = x = y = 0;
			result = 0;
		}
	};


	// 客户端请求角色完整数据
	const byte GAME_CMD_READ_CHARINFO = 3;		// client -> server
	struct stReadCharInfo : stBaseCommand
	{
		char account[MAX_ACCOUNT_SIZE+1];
		byte unk1;
		char charName[MAX_NAME_SIZE+1];
		WORD charIndex;
		DWORD charid;		// 角色唯一编号
		UINT clientId;		// 客户端网络ID
		byte isFree;		// 1 - 是免费用户

		stReadCharInfo() : stBaseCommand(GAME_CMD_READ_CHARINFO)
		{
			ZeroMemory(account,sizeof(account));
			unk1 = 0;
			ZeroMemory(charName,sizeof(charName));
			charIndex = 0;
			charid = 0;
			clientId = 0;
			isFree = 0;
		}
	};



	// 服务器返回角色完整数据
	const byte GAME_CMD_READ_CHARINFO_RESULT = 4;	// server -> client
	struct stReadCharInfoResult : stBaseCommand
	{
		char account[MAX_ACCOUNT_SIZE+1];
		BYTE unk1;
		char BirthDay[7];
		char EMail[41];

		char charName[MAX_NAME_SIZE+1];
		char nickName[MAX_NAME_SIZE+1];
		BYTE nickNameColor;
		WORD x;
		WORD y;
		WORD mapId;

		WORD countryId;
		WORD race;
		WORD job;
		WORD health;
		WORD poison;
		WORD moveSpeed;
		BYTE bioRhythm[3];

		WORD family;
		BYTE familyLevel;
		char familyName[MAX_NAME_SIZE+1];
		WORD isFamilyJang;

		WORD bDoWed;
		char partenerName[MAX_NAME_SIZE+1];

		WORD cPK;
		DWORD money;
		DWORD safeMoney;

		BYTE events[MAX_EVENT+1];

		UINT attack;
		UINT defence_str;
		UINT defence_mag;

		UINT Str;
		UINT Wiz;
		UINT Int;
		UINT Con;
		UINT Dex;

		WORD level;
		BYTE SelfStore;
		DWORD curExp;
		UINT levelUpPoint;	

		UINT maxHP;
		UINT maxMP;
		UINT maxJP;
		UINT maxSP;	

		UINT curHP;			
		UINT curMP;
		UINT curJP;
		UINT curSP;

		WORD curHG;

		BYTE charAttrib;

		//interface info
		stCharBinaryData binData;

		stReadCharInfoResult() : stBaseCommand(GAME_CMD_READ_CHARINFO_RESULT)
		{
			ZeroMemory(account,sizeof(account));
			unk1 = 1;
			ZeroMemory(BirthDay,sizeof(BirthDay));
			ZeroMemory(EMail,sizeof(EMail));

			ZeroMemory(charName,sizeof(charName));
			ZeroMemory(nickName,sizeof(nickName));
			nickNameColor = 0;
			x = 0;
			y = 0;
			mapId = 0;

			countryId = 0;;
			race = 0;
			job = 0;
			health = 0;
			poison = 0;
			moveSpeed = 0;
			ZeroMemory(bioRhythm,sizeof(bioRhythm));

			family = 0;
			ZeroMemory(familyName,sizeof(familyName));
			isFamilyJang = 0;

			bDoWed = 0;
			ZeroMemory(partenerName,sizeof(partenerName));

			cPK = 0;
			money = 0;
			safeMoney = 0;

			ZeroMemory(events,sizeof(events));

			attack = 0;
			defence_str = 0;
			defence_mag = 0;

			Str = 0;
			Wiz = 0;
			Int = 0;
			Con = 0;
			Dex = 0;

			level = 0;
			SelfStore = 0;
			curExp = 0;
			levelUpPoint = 0;	

			maxHP = 0;
			maxMP = 0;
			maxJP = 0;
			maxSP = 0;	

			curHP = 0;			
			curMP = 0;
			curJP = 0;
			curSP = 0;
			curHG = 0;

			charAttrib = 0;
		}
	};




	//////////////////////////////////////////////////////////////////////////



	// 客户端请求游戏信息
	const byte GAME_CMD_GAMEINFO = 96;		// client -> client
	struct stGameInfo : stBaseCommand
	{
		stGameInfo() : stBaseCommand(GAME_CMD_GAMEINFO)
		{
		}
	};


	// 其他玩家的信息
	struct stCharInfo
	{
		WORD c_x;
		WORD c_y;
		WORD m_x;
		WORD m_y;

		BYTE time_walk;
		BYTE DungenNum;
		BYTE countryId;
		BYTE race;
		BYTE ActionMode;

		BYTE health;
		BYTE FairMode;
		DWORD LastSkill;

		WORD GuildId;
		BYTE GuildLevel;
		WORD Dress;
		WORD equip[4];
		char name[MAX_NAME_SIZE+1];
		char NickName[MAX_NAME_SIZE+1];
		BYTE NickNameColor;
		BYTE bMarriage;
		BYTE PetLevel;

		BYTE CharLevel;
		BYTE SelfStore;

		stCharInfo()
		{
			ZeroMemory(this,sizeof(*this));
		}
	};

	// 其他玩家的信息
	struct stCharInfoMsg
	{
		BYTE MessageType;
		UINT id;

		stCharInfo charInfo;

		stCharInfoMsg()
		{
			ZeroMemory(this,sizeof(*this));
		}
	};


	// 客户端请求游戏信息返回值(返回其他在线玩家的数据)
	const byte GAME_CMD_GAMEINFO_RESULT = 97;		// client -> client  (CharsInfo)
	struct stGameInfoResult : stBaseCommand
	{
		WORD count;
		stCharInfoMsg data[0];

		stGameInfoResult() : stBaseCommand(GAME_CMD_GAMEINFO_RESULT)
		{
			count = 0;
		}

		unsigned int getSize() { return sizeof(stGameInfoResult) + count * sizeof(stCharInfoMsg); }
	};


	// 返回天气信息
	const byte GAME_CMD_WEATHERINFO = 35;	// server -> client
	struct stWeatherInfo : stBaseCommand
	{
		BYTE state;		// 天气类型
		WORD fall;		// 风力
		BYTE wind;		// 风向 0 - 左， 1 - 下， 2 - 右
		BYTE lightning;	// 灯光 0 - 关闭， 1 - 开启

		stWeatherInfo() : stBaseCommand(GAME_CMD_WEATHERINFO)
		{
			state = 0;
			fall = 0;
			wind = 0;
			lightning = 0;
		}
	};


	// 客户端检查同步
	const byte GAME_CMD_CHECKASYNC = 158;	// client -> server
	struct stCheckSync : stBaseCommand
	{
		char name[128];
		DWORD tick;
		WORD result;

		stCheckSync() : stBaseCommand(GAME_CMD_CHECKASYNC)
		{
			tick = result = 0;
		}
	};


	// 客户端请求离开游戏
	const byte GAME_CMD_LOGOUT = 162;	// client -> server
	struct stLogOut : stBaseCommand
	{
		// (0 restart),(1 exit),(2 go to world select),(3 move nation) 
		BYTE type;

		stLogOut() : stBaseCommand(GAME_CMD_LOGOUT)
		{
			type = 0;
		}
	};

	// 客户端离开游戏返回值
	const byte GAME_CMD_LOGOUT_RESULT = 163;	// server -> client
	struct stLogOutResult : stBaseCommand
	{
		stLogOutResult() : stBaseCommand(GAME_CMD_LOGOUT_RESULT)
		{
		}
	};


	// 切换地图（大地图）
	const byte GAME_CMD_CHANGEMAP = 61;	// c -> s
	struct stChangeMap : stBaseCommand
	{
		BYTE mapId;
		stChangeMap() : stBaseCommand(GAME_CMD_CHANGEMAP)
		{
			mapId = 0;
		}
	};


	// 怪物信息
	const byte GAME_CMD_MONINFO = 199;	// s -> c
	struct stMonInfo : stBaseCommand
	{
		WORD count;
		stMonCreate data[0];
		stMonInfo() : stBaseCommand(GAME_CMD_MONINFO)
		{
			count = 0;
		}

		unsigned int getSize() { return sizeof(stMonInfo) + count * sizeof(stMonCreate);  }
	};


	struct stNpcCreate
	{
		BYTE MessageType;
		UINT id;

		WORD c_x;
		WORD c_y;
		WORD m_x;
		WORD m_y;

		BYTE mapId;
		BYTE npcClass;
		BYTE npcFunc;
		BYTE storeId;

		stNpcCreate()
		{
			ZeroMemory(this,sizeof(*this));
		}
	};

	// NPC信息
	const byte GAME_CMD_NPCINFO = 200;	// s -> c
	struct stNpcInfo : stBaseCommand
	{
		WORD count;
		stNpcCreate data[0];
		stNpcInfo() : stBaseCommand(GAME_CMD_NPCINFO)
		{
			count = 0;
		}

		unsigned int getSize() { return sizeof(stNpcInfo) + count * sizeof(stNpcCreate);  }
	};


	// 掉落的物品信息
	struct stDropItemInfo
	{
		WORD x;
		WORD y;
		WORD itemId;
		DWORD sum;	// 金币数量(如果是金币道具的话)
		UINT color;

		stDropItemInfo()
		{
			ZeroMemory(this,sizeof(*this));
		}
	};

	// 地图上掉落的物品信息
	const byte GAME_CMD_MAPDROPITEMINFO = 36;	// s -> c
	struct stMapDropItemInfo : stBaseCommand
	{
		WORD count;
		stDropItemInfo data[0];
		stMapDropItemInfo() : stBaseCommand(GAME_CMD_MAPDROPITEMINFO)
		{
			count = 0;
		}

		unsigned int getSize() { return sizeof(stMapDropItemInfo) + count * sizeof(stDropItemInfo);  }
	};


	// 服务器通知客户端创建一个角色
	const byte GAME_CMD_CREATE_CHAR_INFO = 28;		// s -> c
	struct stCreateCharInfo : stBaseCommand
	{
		stCharInfo charInfo;
		stCreateCharInfo() : stBaseCommand(GAME_CMD_CREATE_CHAR_INFO)
		{
			ZeroMemory(&charInfo,sizeof(charInfo));
		}
	};


	// 服务器通知客户端删除一个角色
	const byte GAME_CMD_REMOVE_CHAR = 49;		// s -> c
	struct stRemoveChar : stBaseCommand
	{
		stRemoveChar() : stBaseCommand(GAME_CMD_REMOVE_CHAR)
		{
		}
	};


	// 客户端请求NPC传送
	const byte GAME_CMD_NPC_TRANSFER = 219;		// c -> s
	struct stNpcTransfer : stBaseCommand
	{
		BYTE index;					// 0 ~ 10
		WORD result;				// 0 : 成功, 1 : 金币不够, 2 : 无效的索引号
		stNpcTransfer() : stBaseCommand(GAME_CMD_NPC_TRANSFER)
		{
			index = 0;
			result = 0;
		}
	};

	// 客户端请求两国之间的地图传送（未用）
	const byte GAME_CMD_CHANGEMAP_COUNTRY = 128;		// c -> s
	struct stChangeMapCountry : stBaseCommand
	{
		BYTE mapId;
		WORD destX;
		WORD destY;
		WORD result;

		stChangeMapCountry() : stBaseCommand(GAME_CMD_CHANGEMAP_COUNTRY)
		{
			mapId = 0;
			destX = destY = 0;
			result = 0;
		}
	};

	// 国家传送结果（未用）
	const byte GAME_CMD_CHANGEMAP_COUNTRY_RESULT = 129;		// s -> c
	struct stChangeMapCountryResult : stBaseCommand
	{
		BYTE mapId;
		WORD destX;
		WORD destY;
		WORD result;

		stChangeMapCountryResult() : stBaseCommand(GAME_CMD_CHANGEMAP_COUNTRY_RESULT)
		{
			mapId = 0;
			destX = destY = 0;
			result = 0;
		}
	};

	// 聊天信息
	const byte GAME_CMD_CHATTING = 34;
	struct stChatting : stBaseCommand
	{
		BYTE chatType;	 // 聊天类型
		char name[MAX_NAME_SIZE+1];
	};


	// 传送
	const byte GAME_CMD_CHAR_TRANSFER = 108;
	struct stCharTransfer : stBaseCommand
	{
		//char name[MAX_NAME_SIZE+1];
		WORD x;
		WORD y;
		BYTE mapId;
		BYTE result;

		stCharTransfer() : stBaseCommand(GAME_CMD_CHAR_TRANSFER)
		{
			//ZeroMemory(name,sizeof(name));
			x = 0;
			y = 0;
			mapId = 0;
			result = 0;
		}
	};

	
	// 更新地图的亮度
	const byte GAME_CMD_CHANGE_LUMINOSITY = 62;		// s -> c
	struct stChangeLuminosity : stBaseCommand
	{
		DWORD luminosity;	// 地图的亮度

		stChangeLuminosity() : stBaseCommand(GAME_CMD_CHANGE_LUMINOSITY)
		{
		}
	};







};

#pragma pack()

#endif