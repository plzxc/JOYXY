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

	string& strTitle = iniSett.readString("loginserver", "title", "��½������");
	string& strZoneName = iniSett.readString("zoneinfo", "zonename", "������");
	strTitle += "(";
	strTitle += strZoneName;
	strTitle += ")";
	SetConsoleTitle(strTitle.c_str());
	
	// �������ݿ�
	string& strHost = iniSett.readString("loginserver", "dbhost", "0.0.0.0");
	string& strDbName = iniSett.readString("loginserver", "dbbase", "appie_login_db");
	if ( !g_dbPool.connect(strHost.c_str(), "root", "crack!@#", strDbName.c_str(), 3306) ) {
		printf("�������ݿ�ʧ��\n");
		return 0;
	} 

	WORD port = iniSett.readInt("loginserver", "port", 7101);
	if (!Initialize(MAX_CLIENT, port)) {
		printf("���������˿�%dʧ��\n", port);
		return false;
	}

	return true;
}

// ���µĿͻ�������ʱ���������¼�
TCPTask* LoginService::OnAccept(WORD nClient)
{
	TCPTask* task = new LoginTask(nClient,this);
	if (task == NULL)
		return NULL;
	LoginTaskManager::getSingleton().addTask(nClient, (LoginTask*)task);
	return task;
}

// �ͻ��˶Ͽ�����
bool LoginService::OnClose(WORD nClient)
{
	// �������
	TCPTask* task = LoginTaskManager::getSingleton().getTask(nClient);
	if (task) {
		task->OnClose();
		LoginTaskManager::getSingleton().destroyTask(nClient);
	}

	return true;
}

// ���յ���Ϣ
int LoginService::OnReceive(WORD nClient, void* pData, DWORD dwDataLen)
{
	// ���������߼�
	TCPTask* task = LoginTaskManager::getSingleton().getTask(nClient);
	if (task) {
		task->processMessage(pData, dwDataLen);
	}

	return 0;
}

