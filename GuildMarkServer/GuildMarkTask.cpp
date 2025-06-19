#include "StdAfx.h"
#include "GuildMarkTask.h"
#include "Global.h"
#include "GuildMarkCommand.h"
#include "GuildMarkTaskManager.h"
using namespace GuildMarkCmd;

// ÿ��40K
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
	printf("�пͻ����������� id=%u\n", getID());

	return true;
}

bool GuildMarkTask::OnClose()
{
	printf("�ͻ��� %d �ر�����\n", getID());
	
	return true;
}


// �����½�Ϳͻ���֮�����Ϣ
bool GuildMarkTask::procClientCmd(stBaseCommand* pCmd, DWORD cmdLen)
{
	using namespace GuildMarkCmd;
	bool isDisconnect = false;
	byte message = pCmd->message;
	WORD nClient = getID();

	XorCommand(pCmd, cmdLen, message);

	switch(message)
	{
	case GMARK_CMD_CHECK_VERSION:	// ���汾��
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
				// �ͻ��˹���ͼ��汾�ͷ�������ͼ��汾��һ�¾ʹ��ʹ������ļ�
				sendPackFile(rev->world);
			}
		}
		break;
	case GMARK_CMD_IMG_UPLOAD:// ��ʼͼƬ�ϴ�
		{
			stGMarkImgUpload* rev = (stGMarkImgUpload*)pCmd;
			char dicFile[250];
			sprintf(dicFile, ".\\world%d", rev->world);
			// �ȳ��Դ����ļ���
			CreateDirectory(dicFile, NULL);
			sprintf(dicFile, ".\\world%d\\gm_%d.dic", rev->world, rev->GuildId);
			FILE* pFile = fopen(dicFile, "w+b");
			if (pFile != NULL) {
				fwrite(&rev->width, sizeof(UINT), 1, pFile);
				fwrite(&rev->height, sizeof(UINT), 1, pFile);
				fwrite(&rev->size, sizeof(int), 1, pFile);
				fwrite(rev->ImgBuf, rev->size*sizeof(WORD), 1, pFile);
				fclose(pFile);
				printf("%s �ϴ��ļ��ɹ� %s\n", getIP(), dicFile);

				// ����汾��һ��
				IniParser iniSett;
				iniSett.load(CONFIG_FILE);
				char szKey[250];
				sprintf(szKey, "world%d", rev->world);
				int version = iniSett.readInt("GUILDMARKVERSION", szKey);
				version++;
				iniSett.writeInt("GUILDMARKVERSION", szKey, version);

				// ����ɰ��ļ�
				packImgFile(rev->world);

				// ֪ͨ�ͻ���ͼ�귢�����
				stGMarkImgUploadEnd cmd;
				cmd.GuildId = rev->GuildId;
				cmd.world = rev->world;
				sendCmd(&cmd, sizeof(cmd));
			} else {
				printf("%s �ϴ��ļ�ʧ�� %s\n", getIP(), dicFile);

				stGMarkImgUploadEnd cmd;
				cmd.GuildId = 65535;
				cmd.world = rev->world;
				sendCmd(&cmd, sizeof(cmd));
			}
		}
		break;
	case GMARK_CMD_IMG_DELETE:	// ɾ��ͼƬ
		{
			stGMarkImgUpload* rev = (stGMarkImgUpload*)pCmd;
			char dicFile[250];
			sprintf(dicFile, ".\\world%d\\gm_%d.dic", rev->world, rev->GuildId);
			DeleteFile(dicFile);
			printf("%s ɾ���ļ� %s\n", getIP(), dicFile);
		}
		break;
	default:
		{
#ifdef _DEBUG
			printf("GuildMaskForClientδ������Ϣ %d\n", message);
#endif
			return false;
		}
		break;
	}

	if (isDisconnect) {
		printf("GuildMarkTask �Ƿ��Ŀͻ��ˣ������������Ͽ����� id=%d, message=%d, ip=%s\n", nClient, message, getIP());
		disconnect();
	}

#ifdef _DEBUG
	//printf("�Ѵ�����Ϣ %d\n", message);
#endif
	return true;
}

bool GuildMarkTask::processMessage(void *data, DWORD cmdLen)
{
	procClientCmd((stBaseCommand*)data, cmdLen);

	return true;
}


// ���ͼƬ�ļ�
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

// ���ʹ�����ļ�
bool GuildMarkTask::sendPackFile(UINT world)
{
	//const int DELAY = 50;

	char szPackFile[255] = "";
	sprintf(szPackFile, ".\\world%d\\marks%d.pac", world, world);
	FILE* pFile = fopen(szPackFile, "r+b");
	if (pFile == NULL) {
		printf("��ȡ�ļ� %s ʧ��", szPackFile);
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
			// �������ʣ�µ�
			sendSize = fileSize;
			fileSize = 0;
		} else {
			// ����ÿһ֡������
			sendSize = MAX_TRANSFILE_SIZE;
			fileSize -= MAX_TRANSFILE_SIZE;
		}

		cmd->FileSize = sendSize;
		fread(cmd->pFile, 1, sendSize, pFile);
		if (fileSize == 0) {
			// �ļ��������
			cmd->result = 0;
			fclose(pFile);
			printf("%s ���ش���ļ����\n", getIP());
		}
		sendCmd(cmd, cmd->getSize());
		//Sleep(DELAY);
		cmd->FileCnt = 1;
	}

	return true;
}







