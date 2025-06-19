#pragma once

#ifndef __THREAD_H__
#define __THREAD_H__

#include <Windows.h>
#include "Noncopyable.h"
#include <string>
using namespace std;


class Thread : private Noncopyable
{
public:
	Thread();
	Thread(string name);
	virtual ~Thread(void);

	bool start();
	void stop();
	void sleep(DWORD millisecond);
	bool isRunning() { return m_isRuning; }
	string getName(){ return m_name; }

	// �������true�̼߳���ִ�У��������false���˳��߳�
	virtual bool run() = 0;

protected:
	static UINT WINAPI workThread(void* param);
	friend UINT WINAPI workThread(void* param);

private:
	UINT m_threadId;
	HANDLE m_hThread;
	string m_name;
	volatile bool m_isRuning;
};


#endif


