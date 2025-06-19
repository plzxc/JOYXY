#pragma once

#include <windows.h>
#include <Dbghelp.h>

//#pragma auto_inline (off)
#pragma comment( lib, "DbgHelp" )

namespace MiniDump{
	// 初始化dump参数（name不要扩展名）
	void InitMiniDump(const char* path, const char* name);

	// 异常处理
	LONG WINAPI MyUnhandledExceptionFilter(struct _EXCEPTION_POINTERS* ExceptionInfo);
};

#define TRY		__try
#define EXCEPT	__except(MiniDump::MyUnhandledExceptionFilter(GetExceptionInformation()))

/*
TRY 
{

}
EXCEPT
{
}
*/


