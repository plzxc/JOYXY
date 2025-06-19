#ifndef __GUILDMARKCOMMAND_H__
#define __GUILDMARKCOMMAND_H__

#include "BaseCommand.h"
#include "types.h"

#pragma pack(1)

namespace GuildMarkCmd
{

	//////////////////////////////////////////////////////////////////////////
	//             客户端和登录服务器之间的消息		开始
	//////////////////////////////////////////////////////////////////////////

	// 验证版本号
	const byte GMARK_CMD_CHECK_VERSION = 10;		
	struct stGMarkCheckVersion : stBaseCommand
	{
		DWORD	version;
		BYTE	world;
		char	msgTicker[8][64];
		BYTE	result;

		stGMarkCheckVersion() : stBaseCommand(GMARK_CMD_CHECK_VERSION)
		{

		}
	};


	// 打包文件
	const byte GMARK_CMD_PACK_FILE = 11;		
	struct stGMarkPackFile : stBaseCommand
	{
		BYTE			world;
		BYTE			FileCnt;
		DWORD			FileSize;
		BYTE			result;
		BYTE			pFile[0];	

		stGMarkPackFile() : stBaseCommand(GMARK_CMD_PACK_FILE)
		{

		}

		unsigned int getSize() { return sizeof(*this) + FileSize; }
	};
	
	// 开始图片上传
	const byte GMARK_CMD_IMG_UPLOAD = 12;		
	struct stGMarkImgUpload : stBaseCommand
	{
		BYTE	world;
		WORD	GuildId;

		UINT	width;
		UINT	height;
		int		size;
		WORD	ImgBuf[256];		//image size (12*12)'s max sprite buffer

		stGMarkImgUpload() : stBaseCommand(GMARK_CMD_IMG_UPLOAD)
		{

		}
	};

	// 结束图片上传
	const byte GMARK_CMD_IMG_UPLOAD_END = 13;		
	struct stGMarkImgUploadEnd : stBaseCommand
	{
		BYTE	world;
		WORD	GuildId;

		stGMarkImgUploadEnd() : stBaseCommand(GMARK_CMD_IMG_UPLOAD_END)
		{

		}
	};

	// 删除图片
	const byte GMARK_CMD_IMG_DELETE = 14;
	struct stGMarkImgDelete : stBaseCommand
	{
		BYTE	world;
		WORD	GuildId;

		stGMarkImgDelete() : stBaseCommand(GMARK_CMD_IMG_DELETE)
		{

		}
	};

};

#pragma pack()

#endif