// LoginServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <time.h>
#include "Profiler.h"
#include "Global.h"
#include "GuildMarkService.h"
#include "GuildMarkTimeTick.h"
#include "GuildMarkTaskManager.h"
//#include "ExceptionCapture.h"
#include "MiniDump.h"

//#ifdef _DEBUG
//#include <vld.h>
//#endif

// ����崻���־
//ExceptionCapture excepCapture("./crashlog/loginservercash.log");


// ��Ϸ��ʼ��
bool createSingletons()
{
	Profiler::createSingleton();
	GuildMarkService::createSingleton();
	GuildMarkTimeTick::createSingleton();
	GuildMarkTaskManager::createSingleton();

	return true;
}

// ��Ϸ�ͷ���Դ
bool Destroy()
{
	GuildMarkTimeTick::getSingleton().stop();

	GuildMarkService::getSingleton().Terminate();

	Sleep(1000);

	GuildMarkTaskManager::destroySingleton();
	Profiler::destroySingleton();
	GuildMarkService::destroySingleton();
	GuildMarkTimeTick::destroySingleton();

	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// ��ʼ��minidump
	MiniDump::InitMiniDump("./crashlog/", "guildmarkserver");

	srand( (unsigned)time( NULL ) );

	createSingletons();

	// ��������ʼ��
	if ( !GuildMarkService::getSingleton().Init() ) {
		printf("GuildMarkService��ʼ������ʧ��");
		return 0;
	}

	GuildMarkTimeTick::getSingleton().start();

	string cmd;
	while (true)
	{
		cout << "������ָ��(exit - �˳�������)��\n";
		cout << ">>";
		cin >> cmd;
		if (cmd == "exit") {
			break;
		}
	}

	Destroy();
	
	return 0;
}

