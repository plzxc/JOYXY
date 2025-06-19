// LoginServer.cpp : 定义控制台应用程序的入口点。
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

// 设置宕机日志
//ExceptionCapture excepCapture("./crashlog/loginservercash.log");


// 游戏初始化
bool createSingletons()
{
	Profiler::createSingleton();
	GuildMarkService::createSingleton();
	GuildMarkTimeTick::createSingleton();
	GuildMarkTaskManager::createSingleton();

	return true;
}

// 游戏释放资源
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
	// 初始化minidump
	MiniDump::InitMiniDump("./crashlog/", "guildmarkserver");

	srand( (unsigned)time( NULL ) );

	createSingletons();

	// 服务器初始化
	if ( !GuildMarkService::getSingleton().Init() ) {
		printf("GuildMarkService初始化服务失败");
		return 0;
	}

	GuildMarkTimeTick::getSingleton().start();

	string cmd;
	while (true)
	{
		cout << "请输入指令(exit - 退出服务器)：\n";
		cout << ">>";
		cin >> cmd;
		if (cmd == "exit") {
			break;
		}
	}

	Destroy();
	
	return 0;
}

