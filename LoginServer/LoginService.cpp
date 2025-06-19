#include "StdAfx.h"
#include "LoginService.h"
#include "LoginTaskManager.h"
#include "Global.h"

#define	MAX_CLIENT	2048
#define CONFIG_FILE	"./config.ini"

LoginService::LoginService(void)
{
}

LoginService::~LoginService(void)
{
}

bool LoginService::Init()
{
	logger.start("./log/loginserver.log", "LS", true);

	IniParser iniSett;
	iniSett.load(CONFIG_FILE);

	string& strTitle = iniSett.readString("loginserver", "title", "登陆服务器");
	string& strZoneName = iniSett.readString("zoneinfo", "zonename", "大区名");
	strTitle += "(";
	strTitle += strZoneName;
	strTitle += ")";
	SetConsoleTitle(strTitle.c_str());
	
	// 连接数据库
	string& strHost = iniSett.readString("loginserver", "dbhost", "0.0.0.0");
	string& strDbName = iniSett.readString("loginserver", "dbbase", "appie_login_db");
	if ( !g_dbPool.connect(strHost.c_str(), "root", "crack!@#", strDbName.c_str(), 3306) ) {
		printf("连接数据库失败\n");
		return 0;
	} 

	WORD port = iniSett.readInt("loginserver", "port", 7101);
	if (!Initialize(MAX_CLIENT, port)) {
		printf("创建监听端口%d失败\n", port);
		return false;
	}

	return true;
}

// 有新的客户端连接时，产生的事件
TCPTask* LoginService::OnAccept(WORD nClient)
{
	TCPTask* task = new LoginTask(nClient,this);
	if (task == NULL)
		return NULL;
	LoginTaskManager::getSingleton().addTask(nClient, (LoginTask*)task);
	return task;
}

// 客户端断开连接
bool LoginService::OnClose(WORD nClient)
{
	// 处理掉线
	TCPTask* task = LoginTaskManager::getSingleton().getTask(nClient);
	if (task) {
		task->OnClose();
		LoginTaskManager::getSingleton().destroyTask(nClient);
	}

	return true;
}

// 接收到消息
int LoginService::OnReceive(WORD nClient, void* pData, DWORD dwDataLen)
{
	// 处理正常逻辑
	TCPTask* task = LoginTaskManager::getSingleton().getTask(nClient);
	if (task) {
		task->processMessage(pData, dwDataLen);
	}

	return 0;
}

