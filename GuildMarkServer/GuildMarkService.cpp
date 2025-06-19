#include "StdAfx.h"
#include "GuildMarkService.h"
#include "GuildMarkTaskManager.h"
#include "Global.h"

#define	MAX_CLIENT	2048

GuildMarkService::GuildMarkService(void)
{
}

GuildMarkService::~GuildMarkService(void)
{
}

bool GuildMarkService::Init()
{
	IniParser iniSett;
	iniSett.load(CONFIG_FILE);

	string& strTitle = iniSett.readString("SERVER", "title", "����ͼ���");
	SetConsoleTitle(strTitle.c_str());

	WORD port = iniSett.readInt("SERVER", "port", 4001);
	if (!Initialize(MAX_CLIENT, port)) {
		printf("���������˿�%dʧ��\n", port);
		return false;
	}

	return true;
}

// ���µĿͻ�������ʱ���������¼�
TCPTask* GuildMarkService::OnAccept(WORD nClient)
{
	TCPTask* task = new GuildMarkTask(nClient,this);
	if (task == NULL)
		return NULL;
	GuildMarkTaskManager::getSingleton().addTask(nClient, (GuildMarkTask*)task);
	return task;
}

// �ͻ��˶Ͽ�����
bool GuildMarkService::OnClose(WORD nClient)
{
	// �������
	TCPTask* task = GuildMarkTaskManager::getSingleton().getTask(nClient);
	if (task) {
		task->OnClose();
		GuildMarkTaskManager::getSingleton().destroyTask(nClient);
	}

	return true;
}

// ���յ���Ϣ
int GuildMarkService::OnReceive(WORD nClient, void* pData, DWORD dwDataLen)
{
	// ���������߼�
	TCPTask* task = GuildMarkTaskManager::getSingleton().getTask(nClient);
	if (task) {
		task->processMessage(pData, dwDataLen);
	}

	return 0;
}

