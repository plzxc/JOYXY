#include <windows.h>

#ifndef __SYNCLOCK_H__
#define __SYNCLOCK_H__


class SyncLock
{
public:
	SyncLock() 
	{
		InitializeCriticalSection(&m_csObject); 
	}

	~SyncLock()
	{ 
		DeleteCriticalSection(&m_csObject);
	}

public:
	void lock()   
	{
		EnterCriticalSection(&m_csObject);
	}

	void unlock() 
	{
		LeaveCriticalSection(&m_csObject);
	}

private:
	CRITICAL_SECTION m_csObject;
};



class AutoSycnLock 
{ 
public: 
	AutoSycnLock(SyncLock& syncLock) 
	{ 
		m_syncLock = &syncLock; 
		m_syncLock->lock(); 
	} 

	~AutoSycnLock()
	{ 
		m_syncLock->unlock(); 
	} 

private: 
	SyncLock* m_syncLock; 
}; 



#endif