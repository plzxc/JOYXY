#pragma once

#ifndef __EXCEPTION_CAPTURE_H__
#define __EXCEPTION_CAPTURE_H__

#include "SyncLock.h"
#include "StackWalker.h"

// 带文件输出
class FileStackWalker : public StackWalker
{
public:
	FileStackWalker(const char* outputFile);
	virtual ~FileStackWalker();

protected:
	virtual void OnOutput(LPCSTR szText);

private:
	char m_szFileName[MAX_PATH];
	FILE* m_pFile;
};


// 异常捕捉
// 举例： 
// 在全局中这样定义下，就可以用了
// ExceptionCapture expCapture("./crashlog/crash.log");
class ExceptionCapture
{
public:
	ExceptionCapture(const char* outputFile);
	virtual ~ExceptionCapture(void);
	
	static LONG WINAPI UnhandledExceptionFilter(struct _EXCEPTION_POINTERS* ExceptionInfo);

private:
	static char m_szFileName[MAX_PATH];
};

#endif
