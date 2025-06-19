#pragma once

#include <windows.h>
#include <Dbghelp.h>

//#pragma auto_inline (off)
#pragma comment( lib, "DbgHelp" )

namespace MiniDump{
	// ��ʼ��dump������name��Ҫ��չ����
	void InitMiniDump(const char* path, const char* name);

	// �쳣����
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


