// LoginServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <time.h>
#include "LoginedUserManager.h"
#include "InGameUserManager.h"
#include "ServerManager.h"
#include <Profiler.h>
#include "Global.h"
#include "LoginService.h"
#include "LoginTimeTick.h"
//#include "ExceptionCapture.h"
#include "MiniDump.h"
#include "LoginTaskManager.h"
#include "Profiler.h"

//#ifdef _DEBUG
//#include <vld.h>
//#endif

// ����崻���־
//ExceptionCapture excepCapture("./crashlog/loginservercash.log");


// ��Ϸ��ʼ��
bool createSingletons()
{
	Profiler::createSingleton();
	LoginedUserManager::createSingleton();
	InGameUserManager::createSingleton();
	ServerManager::createSingleton();
	Profiler::createSingleton();
	LoginService::createSingleton();
	LoginTimeTick::createSingleton();
	LoginTaskManager::createSingleton();

	return true;
}

// ��Ϸ�ͷ���Դ
bool Destroy()
{
	LoginTimeTick::getSingleton().stop();

	LoginService::getSingleton().Terminate();

	Sleep(1000);

	LoginTaskManager::destroySingleton();
	LoginedUserManager::destroySingleton();
	InGameUserManager::destroySingleton();
	ServerManager::destroySingleton();
	Profiler::destroySingleton();
	LoginService::destroySingleton();
	LoginTimeTick::destroySingleton();
	Profiler::destroySingleton();

	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// ��ʼ��minidump
	MiniDump::InitMiniDump("./crashlog/", "loginserver");

	srand( (unsigned)time( NULL ) );

	createSingletons();

	Profiler::getSingleton().setTimeout(100);

	// ��������ʼ��
	if ( !LoginService::getSingleton().Init() ) {
		printf("LoginService��ʼ������ʧ��");
		return 0;
	}

	LoginTimeTick::getSingleton().start();

	string cmd;
	while (true)
	{
		cout << "������ָ��(exit - �˳�������)��\n";
		cout << ">>";
		cin >> cmd;
		if (cmd == "exit") {
			break;
		} else if (cmd == "info") {
			LoginService::getSingleton().PrintInfo();
		}
	}

	Destroy();
	
	return 0;
}

