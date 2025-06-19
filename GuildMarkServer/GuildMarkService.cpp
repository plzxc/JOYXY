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

	string& strTitle = iniSett.readString("SERVER", "title", "工会图标服");
	SetConsoleTitle(strTitle.c_str());

	WORD port = iniSett.readInt("SERVER", "port", 4001);
	if (!Initialize(MAX_CLIENT, port)) {
		printf("创建监听端口%d失败\n", port);
		return false;
	}

	return true;
}

// 有新的客户端连接时，产生的事件
TCPTask* GuildMarkService::OnAccept(WORD nClient)
{
	TCPTask* task = new GuildMarkTask(nClient,this);
	if (task == NULL)
		return NULL;
	GuildMarkTaskManager::getSingleton().addTask(nClient, (GuildMarkTask*)task);
	return task;
}

// 客户端断开连接
bool GuildMarkService::OnClose(WORD nClient)
{
	// 处理掉线
	TCPTask* task = GuildMarkTaskManager::getSingleton().getTask(nClient);
	if (task) {
		task->OnClose();
		GuildMarkTaskManager::getSingleton().destroyTask(nClient);
	}

	return true;
}

// 接收到消息
int GuildMarkService::OnReceive(WORD nClient, void* pData, DWORD dwDataLen)
{
	// 处理正常逻辑
	TCPTask* task = GuildMarkTaskManager::getSingleton().getTask(nClient);
	if (task) {
		task->processMessage(pData, dwDataLen);
	}

	return 0;
}

