#pragma once

class MutexLock
{
public:
	MutexLock(void);
	virtual ~MutexLock(void);

	void lock();

	void unlock();

private:
	HANDLE m_mutex;
};


class AutoMutexLock 
{ 
public: 
	AutoMutexLock(MutexLock& mutexLock) 
	{ 
		m_mutexLock = &mutexLock; 
		m_mutexLock->lock(); 
	} 

	~AutoMutexLock()
	{ 
		m_mutexLock->unlock(); 
	} 

private: 
	MutexLock* m_mutexLock; 
}; 
