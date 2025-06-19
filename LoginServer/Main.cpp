// LoginServer.cpp : 定义控制台应用程序的入口点。
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

// 设置宕机日志
//ExceptionCapture excepCapture("./crashlog/loginservercash.log");


// 游戏初始化
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

// 游戏释放资源
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
	// 初始化minidump
	MiniDump::InitMiniDump("./crashlog/", "loginserver");

	srand( (unsigned)time( NULL ) );

	createSingletons();

	Profiler::getSingleton().setTimeout(100);

	// 服务器初始化
	if ( !LoginService::getSingleton().Init() ) {
		printf("LoginService初始化服务失败");
		return 0;
	}

	LoginTimeTick::getSingleton().start();

	string cmd;
	while (true)
	{
		cout << "请输入指令(exit - 退出服务器)：\n";
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

