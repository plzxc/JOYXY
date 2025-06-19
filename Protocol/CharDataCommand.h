#ifndef __CHARDATACOMMAND_H__
#define __CHARDATACOMMAND_H__

// 角色数据相关的消息

#include "BaseCommand.h"
#include "types.h"
#include "Item.h"
#include "PackageManager.h"

#pragma pack(1)



namespace GameCmd
{

	// 客户端请求开始游戏
	const byte GAME_CMD_STARTGAME = 65;	// client -> server
	struct stStartGame : stBaseCommand
	{
		char account[MAX_ACCOUNT_SIZE+1];
		byte unk1;

		stStartGame() : stBaseCommand(GAME_CMD_STARTGAME)
		{
		}
	};


	// 服务器返回开始开始游戏消息的结果
	const byte GAME_CMD_STARTGAME_RESULT = 175;	// server -> client
	struct stStartGameResult : stBaseCommand
	{
		char account[MAX_ACCOUNT_SIZE+1];
		BYTE RemainSiegeTime;
		BYTE OpenningCastleGate;
		BYTE GuildWarfareIng;
		BYTE SiegeWinnerKind;
		char SiegeWinnerGuildName[MAX_NAME_SIZE+1];
		WORD SiegeWinnerGuildID;

		BYTE NationalWarTime;
		BYTE OtherKingdom;

		BYTE ItemTaxRate;
		BYTE ItemTaxKind[4];
		UINT BankCommission;

		BYTE EventType;
		BYTE s_month;
		BYTE s_day;			
		BYTE e_month;
		BYTE e_day;			
		WORD EventItemId;
		WORD EventProb;

		BYTE ptl_state;
		BYTE ptl_dgn;
		WORD ptl_x;
		WORD ptl_y;
		BYTE ptl_to_dgn;
		WORD ptl_to_x;
		WORD ptl_to_y;
		BYTE ptl_level_s;
		BYTE ptl_level_e;
		BYTE ptl_info;

		BYTE ChristMasEventState;
		BYTE ChristMasItemCurrentCount[8];

		//nation offence Guild Info
		WORD HostilityGuildID[5];
		char HostilityGuildName[5][MAX_NAME_SIZE+1];

		BYTE AttacSkipFrame;
		BYTE AttacSkipFrameEx;

		stStartGameResult() : stBaseCommand(GAME_CMD_STARTGAME_RESULT)
		{
			ZeroMemory(account,sizeof(account));
			RemainSiegeTime = 0;
			OpenningCastleGate = 0;
			GuildWarfareIng = 0;
			SiegeWinnerKind = 0;
			ZeroMemory(SiegeWinnerGuildName,sizeof(SiegeWinnerGuildName));
			SiegeWinnerGuildID = 0;

			NationalWarTime = 0;
			OtherKingdom = 0;

			ItemTaxRate = 0;
			ZeroMemory(ItemTaxKind,sizeof(ItemTaxKind));
			BankCommission = 0;

			EventType = 0;
			s_month = 0;
			s_day = 0;			
			e_month = 0;
			e_day = 0;			
			EventItemId = 0;
			EventProb = 0;

			ptl_state = 0;
			ptl_dgn = 0;
			ptl_x = 0;
			ptl_y = 0;
			ptl_to_dgn = 0;
			ptl_to_x = 0;
			ptl_to_y = 0;
			ptl_level_s = 0;
			ptl_level_e = 0;
			ptl_info = 0;

			ChristMasEventState = 0;
			ZeroMemory(ChristMasItemCurrentCount,sizeof(ChristMasItemCurrentCount));

			//nation offence Guild Info
			for (int i=0;i<5;i++) {
				HostilityGuildID[i] = 0xFFFF;
				ZeroMemory(HostilityGuildName[i], MAX_NAME_SIZE+1);
			}

			AttacSkipFrame = 0;
			AttacSkipFrameEx = 0;
		}
	};



	// 客户端通知服务器激活角色
	const byte GAME_CMD_ACTIVECHAR = 223;	// client -> server
	struct stActiveChar : stBaseCommand
	{
		BYTE isActive;

		stActiveChar() : stBaseCommand(GAME_CMD_ACTIVECHAR)
		{
			isActive = true;
		}
	};


	// 客户端验证角色上线位置
	const byte GAME_CMD_STARTPOSITION = 44;	// client -> server
	struct stStartPosition : stBaseCommand
	{
		WORD x;
		WORD y;
		BYTE mapId;

		stStartPosition() : stBaseCommand(GAME_CMD_STARTPOSITION)
		{
			x = y = mapId = 0;
		}
	};


	// 客户端读取留言
	const byte GAME_CMD_READ_CHATMSG = 122;	// client -> server
	struct stReadChatMsg : stBaseCommand
	{
		stReadChatMsg() : stBaseCommand(GAME_CMD_READ_CHATMSG)
		{
		}
	};


	// 客户端读取留言返回值
	const byte GAME_CMD_READ_CHATMSG_RESULT = 122;	// server -> client
	struct stReadChatMsgResult : stBaseCommand
	{
		stReadChatMsgResult() : stBaseCommand(GAME_CMD_READ_CHATMSG_RESULT)
		{
		}
	};


	// 客户端发送移动消息
	const byte GAME_CMD_CHARMOVE = 29;	// c -> s, s -> c
	struct stCharMove : stBaseCommand
	{
		WORD x;
		WORD y;
		WORD speed;
		stCharMove() : stBaseCommand(GAME_CMD_CHARMOVE)
		{
			x = y = 0;
			speed = 0;
		}
	};


	// 客户端发送移动停止的消息
	const byte GAME_CMD_CHARMOVE_EX = 202;	// c -> s, s -> c
	struct stCharMoveEx : stBaseCommand
	{
		WORD x;
		WORD y;
		stCharMoveEx() : stBaseCommand(GAME_CMD_CHARMOVE_EX)
		{
			x = y = 0;
		}
	};

	// 客户端发送宠物移动消息
	const byte GAME_CMD_PETMOVE = 217;	// c -> s, s -> c
	struct stPetMove : stBaseCommand
	{
		WORD x;
		WORD y;
		stPetMove() : stBaseCommand(GAME_CMD_PETMOVE)
		{
			x = y = 0;
		}
	};


	// 客户端发送宠物移动停止的消息
	const byte GAME_CMD_PETMOVE_EX = 218;	// c -> s, s -> c
	struct stPetMoveEx : stBaseCommand
	{
		WORD x;
		WORD y;
		stPetMoveEx() : stBaseCommand(GAME_CMD_PETMOVE_EX)
		{
			x = y = 0;
		}
	};


	// 使用升级点
	const byte GAME_CMD_USE_LEVELPOINT = 46;	// c -> s
	struct stUseLevelPoint : stBaseCommand
	{
		WORD UpClass;
		UINT max;
		stUseLevelPoint() : stBaseCommand(GAME_CMD_USE_LEVELPOINT)
		{
			UpClass = max = 0;
		}
	};


	// 使用升级点的返回值
	const byte GAME_CMD_USE_LEVELPOINT_RESULT = 47;	// s -> c
	struct stUseLevelPointResult : stBaseCommand
	{
		WORD UpClass;
		WORD max;
		stUseLevelPointResult() : stBaseCommand(GAME_CMD_USE_LEVELPOINT_RESULT)
		{
			UpClass = max = 0;
		}
	};


	// 角色升级
	const byte GAME_CMD_LEVEL_UP = 56;		// s -> c
	struct stLevelUp : stBaseCommand
	{
		WORD level;
		UINT UpPoint[4];
		stLevelUp() : stBaseCommand(GAME_CMD_LEVEL_UP)
		{
			level = 0;
			ZeroMemory(UpPoint,sizeof(UpPoint));
		}
	};



	// 服务器通知客户端更新主角的某个属性值
	const byte GAME_CMD_CHANGE_CHAR_PROPERTY = 92;		// c -> s, s -> c
	struct stChangeCharProperty : stBaseCommand
	{
		WORD UpClass;	// 改变的属性类型
		DWORD value;	// 改变的属性值

		stChangeCharProperty() : stBaseCommand(GAME_CMD_CHANGE_CHAR_PROPERTY)
		{

		}
	};


	// 存钱到银行
	const byte GAME_CMD_DEPOSIT_MONEY = 14;		// c -> s, s -> c
	struct stDepositMoney : stBaseCommand
	{
		DWORD money;

		stDepositMoney() : stBaseCommand(GAME_CMD_DEPOSIT_MONEY)
		{
		}
	};

	// 取钱
	const byte GAME_CMD_WITHDRAW_MONEY = 17;		// c -> s, s -> c
	struct stWithdrawMoney : stBaseCommand
	{
		DWORD money;

		stWithdrawMoney() : stBaseCommand(GAME_CMD_WITHDRAW_MONEY)
		{
		}
	};


	// 把银行里的钱变为纸钱道具
	const byte GAME_CMD_MONEY_TO_ITEM = 116;		// c -> s, s -> c
	struct stMoneyToItem : stBaseCommand
	{
		WORD pkg;
		WORD x;
		WORD y;
		WORD itemId;

		DWORD money;
		WORD result;

		stMoneyToItem() : stBaseCommand(GAME_CMD_MONEY_TO_ITEM)
		{
		}
	};

	// 把纸币道具变为金币
	const byte GAME_CMD_ITEM_TO_MONEY = 114;		// c -> s, s -> c
	struct stItemToMoney : stBaseCommand
	{
		WORD pkg;
		WORD x;
		WORD y;
		WORD itemId;

		DWORD money;
		WORD result;

		stItemToMoney() : stBaseCommand(GAME_CMD_ITEM_TO_MONEY)
		{
		}
	};


	// 改变转向
	const byte GAME_CMD_CHANGE_DIR = 63;		// c -> s, s -> c
	struct stChangeDir : stBaseCommand
	{
		BYTE dir;

		stChangeDir() : stBaseCommand(GAME_CMD_CHANGE_DIR)
		{
		}
	};


	// 注册国家公民权
	const byte GAME_CMD_REGIST_CONTRY = 141;	// c -> s, s -> c
	struct stRegistCountry : stBaseCommand
	{
		stPkgPos srcPos;
		WORD itemId;
		WORD country;
		char charName[13];
		WORD result;

		stRegistCountry() : stBaseCommand(GAME_CMD_REGIST_CONTRY)
		{

		}
	};


	// 开始职业技能
	const byte GAME_CMD_START_JOB_SKILL = 99;
	struct stStartJobSkill : stBaseCommand
	{
		BYTE level;
		BYTE jobProb;

		WORD targetId;
		WORD job;
		WORD state;
		WORD result;

		stStartJobSkill() : stBaseCommand(GAME_CMD_START_JOB_SKILL)
		{

		}
	};


	// 移动物品到职业技能栏
	const byte GAME_CMD_MOVEITEM_TO_JOBPACK = 101;
	struct stMoveItemToJobPack : stBaseCommand
	{
		WORD targetId;
		WORD index;
		stPkgPos srcPos;
		stItemData itemData;
		WORD result;

		stMoveItemToJobPack() : stBaseCommand(GAME_CMD_MOVEITEM_TO_JOBPACK)
		{

		}
	};

	// 使用职业技能
	const byte GAME_CMD_USE_JOB_SKILL = 103;
	struct stUseJobSkill : stBaseCommand
	{
		WORD targetId;
		DWORD money;
		WORD skillId[3];
		stItemEx ItemEx[2];
		WORD curJP;
		WORD result;  // 0 - XX , 1 - XX , 2 - JP不够, 3 - XX, 4 - 2+3

		stUseJobSkill() : stBaseCommand(GAME_CMD_USE_JOB_SKILL)
		{

		}

		unsigned int getSize() { return sizeof(stUseJobSkill); }
	};

	// 关闭职业技能界面
	const byte GAME_CMD_CLOSE_JOBPACK = 105;
	struct stCloseJobPack : stBaseCommand
	{
		WORD TargetId;
		WORD result;

		stCloseJobPack() : stBaseCommand(GAME_CMD_CLOSE_JOBPACK)
		{

		}
	};


	// 角色复活
	const byte GAME_CMD_CHAR_REVIVE = 198;
	struct stCharRevive : stBaseCommand
	{
		stCharRevive() : stBaseCommand(GAME_CMD_CHAR_REVIVE)
		{
		}
	};


	// 自动回复
	const byte GAME_CMD_AUTO_RECOVERY = 48;
	struct stAutoRecovery : stBaseCommand
	{
		UINT HP;
		UINT MP;
		UINT SP;
		UINT JP;

		stAutoRecovery() : stBaseCommand(GAME_CMD_AUTO_RECOVERY)
		{
		}
	};


	const DWORD MAX_TAG_SIZE = 100;
	struct stTagInfo 
	{
		DWORD num;
		DWORD time;
		BYTE flag;
		char receiver[MAX_NAME_SIZE+1];
		char sender[MAX_NAME_SIZE+1];
		char string[MAX_TAG_SIZE+1];

		stTagInfo()
		{
			ZeroMemory(this, sizeof(*this));
		}
	};


	// 请求当前的短消息
	const byte GAME_CMD_REQUEST_TAG = 122;
	struct stRequestTag : stBaseCommand
	{
		stRequestTag() : stBaseCommand(GAME_CMD_REQUEST_TAG)
		{
		}
	};


	// 请求当前的短消息的返回
	const byte GAME_CMD_REQUEST_TAG_RESULT = 123;
	struct stRequestTagResult : stBaseCommand
	{
		BYTE count;
		stTagInfo data[0];
		stRequestTagResult() : stBaseCommand(GAME_CMD_REQUEST_TAG_RESULT)
		{
			count = 0;
		}

		unsigned int getSize() { return sizeof(this) + count * sizeof(data[0]); }
	};


	// 发送短消息
	const byte GAME_CMD_SEND_TAG = 124;
	struct stSendTag : stBaseCommand
	{
		stTagInfo tagInfo;
		WORD result;
		stSendTag() : stBaseCommand(GAME_CMD_SEND_TAG)
		{
			result = 0;
		}
	};


	// 读取和删除短消息
	const byte GAME_CMD_READ_AND_DELETE_TAG = 126;
	struct stReadAndDeleteTag : stBaseCommand
	{
		DWORD num[30];
		DWORD ReadFlag;
		DWORD DeleteFlag;
		WORD result;

		stReadAndDeleteTag() : stBaseCommand(GAME_CMD_READ_AND_DELETE_TAG)
		{
			ZeroMemory(num, sizeof(num));
			ReadFlag = 0;
			DeleteFlag = 0;
			result = 0;
		}
	};


	// 更新角色的属性(水风火)
	const byte GAME_CMD_CHANGE_CHAR_ATTRIB = 164;
	struct stChangeCharAttrib : stBaseCommand
	{
		stPkgPos srcPos;	// 属性物品的位置
		WORD itemId;		// 其实可以不用这个字段滴
		WORD result;

		stChangeCharAttrib() : stBaseCommand(GAME_CMD_CHANGE_CHAR_ATTRIB)
		{
			itemId = 0;
			result = 0;
		}
	};


	// 设置昵称和昵称颜色
	const byte GAME_CMD_NICK_SETTING = 144;
	struct stNickSetting : stBaseCommand
	{
		WORD targetID;
		char nickName[MAX_NAME_SIZE+1];
		BYTE nickColor;
		WORD result;

		stNickSetting() : stBaseCommand(GAME_CMD_NICK_SETTING)
		{
			ZeroMemory(nickName,sizeof(nickName));
			targetID = 0;
			nickColor = 0;
			result = 0;
		}
	};


	// 呼叫伴侣到身边
	const byte GAME_CMD_CALL_MYDEAR = 100;
	struct stCallMyDear : stBaseCommand
	{
		BYTE type;					// 0 - 申请传送, 1 - 申请结果
		char name[MAX_NAME_SIZE+1];	// 呼叫者的名字
		//BYTE agree;				// 只在type==1时有效, agree==0表示不同意，agree==1表示同意
		stCallMyDear() : stBaseCommand(GAME_CMD_CALL_MYDEAR)
		{
			type = 0;
			ZeroMemory(name,sizeof(name));
			//agree = 0;
		}
	};


	// 邀请结婚
	const byte GAME_CMD_MARRIAGE = 109;
	struct stMarriage : stBaseCommand
	{
		WORD targetId;
		stPkgPos pos[2];
		WORD result;

		stMarriage() : stBaseCommand(GAME_CMD_MARRIAGE)
		{
			targetId = 0;
			result = 0;
		}
	};

	// 结婚的结果
	const byte GAME_CMD_MARRIAGE_RESULT = 110;
	struct stMarriageResult : stBaseCommand
	{
		WORD targetId;
		stPkgPos pos[2];
		WORD result;

		stMarriageResult() : stBaseCommand(GAME_CMD_MARRIAGE_RESULT)
		{
			targetId = 0;
			result = 0;
		}
	};


	// 邀请离婚
	const byte GAME_CMD_UNMARRY	 = 111;
	struct stUnmarry : stBaseCommand
	{
		WORD targetId;
		stPkgPos pos[2];
		WORD result;

		stUnmarry() : stBaseCommand(GAME_CMD_UNMARRY)
		{
			targetId = 0;
			result = 0;
		}
	};

	// 离婚的结果
	const byte GAME_CMD_UNMARRY_RESULT = 112;
	struct stUnmarryResult : stBaseCommand
	{
		WORD targetId;
		stPkgPos pos[2];
		WORD result;

		stUnmarryResult() : stBaseCommand(GAME_CMD_UNMARRY_RESULT)
		{
			targetId = 0;
			result = 0;
		}
	};

	// 更新3高数据
	const byte GAME_CMD_UPDATE_BIORHYTHM = 220;		// s -> c
	struct stUpdateBioRhythm : stBaseCommand
	{
		BYTE BioRhythmState[3];

		stUpdateBioRhythm() : stBaseCommand(GAME_CMD_UPDATE_BIORHYTHM)
		{
			ZeroMemory(BioRhythmState,sizeof(BioRhythmState));
		}
	};


};




#pragma pack()




#endif