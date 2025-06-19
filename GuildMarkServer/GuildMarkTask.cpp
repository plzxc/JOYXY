#include "StdAfx.h"
#include "GuildMarkTask.h"
#include "Global.h"
#include "GuildMarkCommand.h"
#include "GuildMarkTaskManager.h"
using namespace GuildMarkCmd;

// 每秒40K
#define MAX_TRANSFILE_SIZE 40000



GuildMarkTask::GuildMarkTask(WORD id, TCPServer* pTcpServer)
: AppieTCPTask(id,pTcpServer)
{

}

GuildMarkTask::~GuildMarkTask(void)
{
}

bool GuildMarkTask::OnAccept()
{
	printf("有客户端请求连接 id=%u\n", getID());

	return true;
}

bool GuildMarkTask::OnClose()
{
	printf("客户端 %d 关闭连接\n", getID());
	
	return true;
}


// 处理登陆和客户端之间的消息
bool GuildMarkTask::procClientCmd(stBaseCommand* pCmd, DWORD cmdLen)
{
	using namespace GuildMarkCmd;
	bool isDisconnect = false;
	byte message = pCmd->message;
	WORD nClient = getID();

	XorCommand(pCmd, cmdLen, message);

	switch(message)
	{
	case GMARK_CMD_CHECK_VERSION:	// 检查版本号
		{
			stGMarkCheckVersion* rev = (stGMarkCheckVersion*)pCmd;

			int clientVersion = rev->version;
	
			IniParser iniSett;
			iniSett.load(CONFIG_FILE);

			char szKey[250];
			sprintf(szKey, "world%d", rev->world);
			DWORD version = (DWORD)iniSett.readInt("GUILDMARKVERSION", szKey, 0);

			for (int i=0; i<MAX_TICKER; ++i) {	
				sprintf(szKey, "msg%d", i+1);
				string& strMsg = iniSett.readString("MSGTICKER", szKey, " ");
				strncpy(rev->msgTicker[i], strMsg.c_str(), 63);
			}
			
			rev->version = version;
			rev->result = clientVersion == version ? 0 : 1;
			sendCmd(rev, cmdLen);
			
			if (clientVersion != version) {
				// 客户端工会图标版本和服务器的图标版本不一致就传送打包后的文件
				sendPackFile(rev->world);
			}
		}
		break;
	case GMARK_CMD_IMG_UPLOAD:// 开始图片上传
		{
			stGMarkImgUpload* rev = (stGMarkImgUpload*)pCmd;
			char dicFile[250];
			sprintf(dicFile, ".\\world%d", rev->world);
			// 先尝试创建文件夹
			CreateDirectory(dicFile, NULL);
			sprintf(dicFile, ".\\world%d\\gm_%d.dic", rev->world, rev->GuildId);
			FILE* pFile = fopen(dicFile, "w+b");
			if (pFile != NULL) {
				fwrite(&rev->width, sizeof(UINT), 1, pFile);
				fwrite(&rev->height, sizeof(UINT), 1, pFile);
				fwrite(&rev->size, sizeof(int), 1, pFile);
				fwrite(rev->ImgBuf, rev->size*sizeof(WORD), 1, pFile);
				fclose(pFile);
				printf("%s 上传文件成功 %s\n", getIP(), dicFile);

				// 工会版本升一级
				IniParser iniSett;
				iniSett.load(CONFIG_FILE);
				char szKey[250];
				sprintf(szKey, "world%d", rev->world);
				int version = iniSett.readInt("GUILDMARKVERSION", szKey);
				version++;
				iniSett.writeInt("GUILDMARKVERSION", szKey, version);

				// 打包成包文件
				packImgFile(rev->world);

				// 通知客户端图标发送完毕
				stGMarkImgUploadEnd cmd;
				cmd.GuildId = rev->GuildId;
				cmd.world = rev->world;
				sendCmd(&cmd, sizeof(cmd));
			} else {
				printf("%s 上传文件失败 %s\n", getIP(), dicFile);

				stGMarkImgUploadEnd cmd;
				cmd.GuildId = 65535;
				cmd.world = rev->world;
				sendCmd(&cmd, sizeof(cmd));
			}
		}
		break;
	case GMARK_CMD_IMG_DELETE:	// 删除图片
		{
			stGMarkImgUpload* rev = (stGMarkImgUpload*)pCmd;
			char dicFile[250];
			sprintf(dicFile, ".\\world%d\\gm_%d.dic", rev->world, rev->GuildId);
			DeleteFile(dicFile);
			printf("%s 删除文件 %s\n", getIP(), dicFile);
		}
		break;
	default:
		{
#ifdef _DEBUG
			printf("GuildMaskForClient未处理消息 %d\n", message);
#endif
			return false;
		}
		break;
	}

	if (isDisconnect) {
		printf("GuildMarkTask 非法的客户端，服务器主动断开连接 id=%d, message=%d, ip=%s\n", nClient, message, getIP());
		disconnect();
	}

#ifdef _DEBUG
	//printf("已处理消息 %d\n", message);
#endif
	return true;
}

bool GuildMarkTask::processMessage(void *data, DWORD cmdLen)
{
	procClientCmd((stBaseCommand*)data, cmdLen);

	return true;
}


// 打包图片文件
bool GuildMarkTask::packImgFile(UINT world)
{
	char szFile[255] = "";
	sprintf(szFile, ".\\world%d\\*.dic", world);

	WIN32_FIND_DATA fd;
	HANDLE hFile = ::FindFirstFile(szFile, &fd);
	if (hFile == INVALID_HANDLE_VALUE) {
		return false;
	}

	vector<string> vecFileName;
	do {
		if ( !(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
			string strFileName = fd.cFileName;
			vecFileName.push_back(strFileName);
		}
	} while(::FindNextFile(hFile, &fd));

	UINT count = (UINT)vecFileName.size();

	sprintf(szFile, ".\\world%d\\marks%d.pac", world, world);
	FILE* file = NULL;
	file = fopen(szFile, "w+b");
	if (file == NULL) return false;
	fwrite(&count, sizeof(count), 1, file);
	BYTE dicImage[50 * 1024];
	for (UINT i=0; i<count; ++i) {
		string strFileName = vecFileName[i];
		size_t pos1 = strFileName.find_first_of("_");
		size_t pos2 = strFileName.find_first_of(".");
		string strGuildId = strFileName.substr(pos1+1, pos2 - pos1 - 1);
		UINT guildId = atoi(strGuildId.c_str());
		fwrite(&guildId, sizeof(guildId), 1, file);

		sprintf(szFile, ".\\world%d\\%s", world, strFileName.c_str());
		FILE* dicFile = fopen(szFile, "r+b");
		if (dicFile == NULL) {
			fclose(file);
			return false;
		}
		fseek(dicFile, 0, SEEK_END);
		long fileSize = ftell(dicFile);
		fseek(dicFile, 0, SEEK_SET);
		fread(dicImage, fileSize, 1, dicFile);
		fclose(dicFile);

		fwrite(dicImage, fileSize, 1, file);
	}

	fclose(file);
	
	return true;
}

// 发送打包的文件
bool GuildMarkTask::sendPackFile(UINT world)
{
	//const int DELAY = 50;

	char szPackFile[255] = "";
	sprintf(szPackFile, ".\\world%d\\marks%d.pac", world, world);
	FILE* pFile = fopen(szPackFile, "r+b");
	if (pFile == NULL) {
		printf("读取文件 %s 失败", szPackFile);
		return false;
	}

	fseek(pFile, 0, SEEK_END);
	long fileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	stGMarkPackFile* cmd = NULL;
	BUFF_CMD(cmd, stGMarkPackFile);
	cmd->world = world;
	cmd->FileCnt = 0;
	cmd->result = 1;

	while (fileSize > 0) {
		long sendSize = 0;
		if (fileSize < MAX_TRANSFILE_SIZE) {
			// 发送最后剩下的
			sendSize = fileSize;
			fileSize = 0;
		} else {
			// 发送每一帧的数据
			sendSize = MAX_TRANSFILE_SIZE;
			fileSize -= MAX_TRANSFILE_SIZE;
		}

		cmd->FileSize = sendSize;
		fread(cmd->pFile, 1, sendSize, pFile);
		if (fileSize == 0) {
			// 文件发送完毕
			cmd->result = 0;
			fclose(pFile);
			printf("%s 下载打包文件完毕\n", getIP());
		}
		sendCmd(cmd, cmd->getSize());
		//Sleep(DELAY);
		cmd->FileCnt = 1;
	}

	return true;
}







