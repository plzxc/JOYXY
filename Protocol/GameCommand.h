#ifndef __GAMECOMMAND_H__
#define __GAMECOMMAND_H__

#include "BaseCommand.h"
#include "CharData.h"
#include "types.h"
#include "FightCommand.h"

#pragma pack(1)

// ������Ϸ�бȽ����ҵ���Ϣ

#define MAX_CHAR	3

namespace GameCmd
{
	// ��Ϸ���������ͻ��˷����ID��
	const byte GAME_CMD_CLIENT_GAME_ID = 0;		// server -> client
	struct stClientGameID : stBaseCommand
	{
		byte result;
		stClientGameID() : stBaseCommand(GAME_CMD_CLIENT_GAME_ID)
		{
			result = 0;
		}
	};

	//  �ͻ��������ɫ�б�
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

	// ���������ؽ�ɫ�б�
	const byte GAME_CMD_REQUEST_CHARLIST_RESULT = 251;		// server -> client
	struct stRequestCharListResult : stBaseCommand
	{
		char account[MAX_ACCOUNT_SIZE+1];
		BYTE serverId;	// δ��
		stSelectCharInfo selectCharInfo[MAX_CHAR];
		WORD result;

		stRequestCharListResult() : stBaseCommand(GAME_CMD_REQUEST_CHARLIST_RESULT)
		{
			serverId = 1;
			result = 0;
		}
	};


	// �ͻ������󴴽���ɫ
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

	// ���������ش�����ɫ�Ľ��
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


	// �ͻ�������ɾ����ɫ
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


	// ����������ɾ����ɫ�Ľ��
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


	// �ͻ��������ɫ��������
	const byte GAME_CMD_READ_CHARINFO = 3;		// client -> server
	struct stReadCharInfo : stBaseCommand
	{
		char account[MAX_ACCOUNT_SIZE+1];
		byte unk1;
		char charName[MAX_NAME_SIZE+1];
		WORD charIndex;
		DWORD charid;		// ��ɫΨһ���
		UINT clientId;		// �ͻ�������ID
		byte isFree;		// 1 - ������û�

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



	// ���������ؽ�ɫ��������
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



	// �ͻ���������Ϸ��Ϣ
	const byte GAME_CMD_GAMEINFO = 96;		// client -> client
	struct stGameInfo : stBaseCommand
	{
		stGameInfo() : stBaseCommand(GAME_CMD_GAMEINFO)
		{
		}
	};


	// ������ҵ���Ϣ
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

	// ������ҵ���Ϣ
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


	// �ͻ���������Ϸ��Ϣ����ֵ(��������������ҵ�����)
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


	// ����������Ϣ
	const byte GAME_CMD_WEATHERINFO = 35;	// server -> client
	struct stWeatherInfo : stBaseCommand
	{
		BYTE state;		// ��������
		WORD fall;		// ����
		BYTE wind;		// ���� 0 - �� 1 - �£� 2 - ��
		BYTE lightning;	// �ƹ� 0 - �رգ� 1 - ����

		stWeatherInfo() : stBaseCommand(GAME_CMD_WEATHERINFO)
		{
			state = 0;
			fall = 0;
			wind = 0;
			lightning = 0;
		}
	};


	// �ͻ��˼��ͬ��
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


	// �ͻ��������뿪��Ϸ
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

	// �ͻ����뿪��Ϸ����ֵ
	const byte GAME_CMD_LOGOUT_RESULT = 163;	// server -> client
	struct stLogOutResult : stBaseCommand
	{
		stLogOutResult() : stBaseCommand(GAME_CMD_LOGOUT_RESULT)
		{
		}
	};


	// �л���ͼ�����ͼ��
	const byte GAME_CMD_CHANGEMAP = 61;	// c -> s
	struct stChangeMap : stBaseCommand
	{
		BYTE mapId;
		stChangeMap() : stBaseCommand(GAME_CMD_CHANGEMAP)
		{
			mapId = 0;
		}
	};


	// ������Ϣ
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

	// NPC��Ϣ
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


	// �������Ʒ��Ϣ
	struct stDropItemInfo
	{
		WORD x;
		WORD y;
		WORD itemId;
		DWORD sum;	// �������(����ǽ�ҵ��ߵĻ�)
		UINT color;

		stDropItemInfo()
		{
			ZeroMemory(this,sizeof(*this));
		}
	};

	// ��ͼ�ϵ������Ʒ��Ϣ
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


	// ������֪ͨ�ͻ��˴���һ����ɫ
	const byte GAME_CMD_CREATE_CHAR_INFO = 28;		// s -> c
	struct stCreateCharInfo : stBaseCommand
	{
		stCharInfo charInfo;
		stCreateCharInfo() : stBaseCommand(GAME_CMD_CREATE_CHAR_INFO)
		{
			ZeroMemory(&charInfo,sizeof(charInfo));
		}
	};


	// ������֪ͨ�ͻ���ɾ��һ����ɫ
	const byte GAME_CMD_REMOVE_CHAR = 49;		// s -> c
	struct stRemoveChar : stBaseCommand
	{
		stRemoveChar() : stBaseCommand(GAME_CMD_REMOVE_CHAR)
		{
		}
	};


	// �ͻ�������NPC����
	const byte GAME_CMD_NPC_TRANSFER = 219;		// c -> s
	struct stNpcTransfer : stBaseCommand
	{
		BYTE index;					// 0 ~ 10
		WORD result;				// 0 : �ɹ�, 1 : ��Ҳ���, 2 : ��Ч��������
		stNpcTransfer() : stBaseCommand(GAME_CMD_NPC_TRANSFER)
		{
			index = 0;
			result = 0;
		}
	};

	// �ͻ�����������֮��ĵ�ͼ���ͣ�δ�ã�
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

	// ���Ҵ��ͽ����δ�ã�
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

	// ������Ϣ
	const byte GAME_CMD_CHATTING = 34;
	struct stChatting : stBaseCommand
	{
		BYTE chatType;	 // ��������
		char name[MAX_NAME_SIZE+1];
	};


	// ����
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

	
	// ���µ�ͼ������
	const byte GAME_CMD_CHANGE_LUMINOSITY = 62;		// s -> c
	struct stChangeLuminosity : stBaseCommand
	{
		DWORD luminosity;	// ��ͼ������

		stChangeLuminosity() : stBaseCommand(GAME_CMD_CHANGE_LUMINOSITY)
		{
		}
	};







};

#pragma pack()

#endif