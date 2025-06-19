#ifndef __GUILDCOMMAND_H__
#define __GUILDCOMMAND_H__

// ������ص���Ϣ

#include "BaseCommand.h"
#include "types.h"
#include "Guild.h"


#pragma pack(1)

namespace GameCmd
{


	// ��������		c -> s, s -> c
	const byte GAME_CMD_CREATE_GUILD = 131;
	struct stCreateGuild : stBaseCommand 
	{
		WORD guildId;
		char guildName[MAX_NAME_SIZE+1];
		char charName[MAX_NAME_SIZE+1];
		WORD result;

		stCreateGuild() : stBaseCommand(GAME_CMD_CREATE_GUILD)
		{
			guildId = 0;
			ZeroMemory(guildName,  sizeof(guildName));
			ZeroMemory(charName,  sizeof(charName));
			result = 0;
		}
	};

	// ɾ������		c -> s, s -> c
	const byte GAME_CMD_DELETE_GUILD = 133;
	struct stDeleteGuild : stBaseCommand 
	{
		WORD guildId;
		char guildName[MAX_NAME_SIZE+1];
		char charName[MAX_NAME_SIZE+1];
		WORD result;

		stDeleteGuild() : stBaseCommand(GAME_CMD_DELETE_GUILD)
		{
			guildId = 0;
			ZeroMemory(guildName,  sizeof(guildName));
			ZeroMemory(charName,  sizeof(charName));
			result = 0;
		}
	};


	// ������빤��		c -> s, s -> c
	const byte GAME_CMD_JOIN_GUILD = 135;
	struct stJoinGuild : stBaseCommand 
	{
		WORD targetId;
		WORD guildId;
		char charName[MAX_NAME_SIZE+1];
		WORD result;

		stJoinGuild() : stBaseCommand(GAME_CMD_JOIN_GUILD)
		{
			targetId = 0;
			guildId = 0;
			ZeroMemory(charName,  sizeof(charName));
			result = 0;
		}
	};

	// ���빤��		c -> s, s -> c
	const byte GAME_CMD_JOIN_GUILD_RESULT = 136;
	struct stJoinGuildResult : stBaseCommand 
	{
		WORD targetId;
		WORD guildId;
		char charName[MAX_NAME_SIZE+1];
		WORD result;

		stJoinGuildResult() : stBaseCommand(GAME_CMD_JOIN_GUILD_RESULT)
		{
			targetId = 0;
			guildId = 0;
			ZeroMemory(charName,  sizeof(charName));
			result = 0;
		}
	};

	// �˳�����
	const byte GAME_CMD_EXIT_GUILD = 137;
	struct stExitGuild : stBaseCommand 
	{
		WORD guildId;
		char charName[MAX_NAME_SIZE+1];
		WORD result;

		stExitGuild() : stBaseCommand(GAME_CMD_EXIT_GUILD)
		{
			guildId = 0;
			ZeroMemory(charName,  sizeof(charName));
			result = 0;
		}
	};


	// �ͻ������󹤻��Ա��Ϣ
	const byte GAME_CMD_READ_GUILDMEMBER_INFO = 139;	// client -> server
	struct stReadGuildMemberInfo : stBaseCommand
	{
		stReadGuildMemberInfo() : stBaseCommand(GAME_CMD_READ_GUILDMEMBER_INFO)
		{
		}
	};

	// �ͻ������󹤻��Ա��Ϣ(��Ϣ��ͬ��)
	const byte GAME_CMD_READ_GUILDMEMBER_INFO_RESULT = 139;	// server -> client
	struct stReadGuildMemberInfoResult : stBaseCommand
	{
		WORD guildId;
		WORD guildpoint;
		BYTE bBeingProclaimSiegeWarfare;
		char GuildName[MAX_NAME_SIZE+1];
		stGuildMemberInfo member[MAX_GUILD_MEMBER];

		stReadGuildMemberInfoResult() : stBaseCommand(GAME_CMD_READ_GUILDMEMBER_INFO_RESULT)
		{
		}
	};


	// ������֪ͨ�ͻ��˹����Ա��������Ϣ
	const byte GAME_CMD_UPDATE_GUIILDMEMBER_POS = 140;	// server -> client
	struct stUpdateGuildMemberPos : stBaseCommand
	{
		BYTE pos;
		char charName[MAX_NAME_SIZE+1];

		stUpdateGuildMemberPos() : stBaseCommand(GAME_CMD_UPDATE_GUIILDMEMBER_POS)
		{
			pos = 0;
			ZeroMemory(charName, sizeof(charName));
		}
	};

	// ������֪ͨ�ͻ��˹���ĵ���
	const byte GAME_CMD_UPDATE_GUILD_POINT = 236;	// server -> client
	struct stUpdateGuildPoint : stBaseCommand
	{
		WORD guildId;
		WORD point;
		WORD result;

		stUpdateGuildPoint() : stBaseCommand(GAME_CMD_UPDATE_GUILD_POINT)
		{
			guildId = 0;
			point = 0;
			result = 0;
		}
	};

	// ���й����Ա�����
	const byte GAME_CMD_CALL_GUILDMEMBER = 102;
	struct stCallGuildMember : stBaseCommand
	{
		BYTE type;						// 0 - ���봫��, 1 - ������
		char name1[MAX_NAME_SIZE+1];	// �����ߵ�����
		char name2[MAX_NAME_SIZE+1];	// �������ߵ�����
		stCallGuildMember() : stBaseCommand(GAME_CMD_CALL_GUILDMEMBER)
		{
			type = 0;
			ZeroMemory(name1,sizeof(name1));
			ZeroMemory(name2,sizeof(name2));
		}
	};

	// ������ȡ������
	const byte GAME_CMD_CHANGE_GUILDMEMBER_POSITION = 104;	// client -> server
	struct stChangeGuildMemberPosition : stBaseCommand
	{
		char name[16+1];	// ���޸��ߵ�����
		WORD position;		// ְ��

		stChangeGuildMemberPosition() : stBaseCommand(GAME_CMD_CHANGE_GUILDMEMBER_POSITION)
		{
		}
	};

};

#pragma pack()




#endif