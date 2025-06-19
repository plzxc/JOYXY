#pragma once
#include "Singleton.h"
#include "LoginTask.h"
#include "SyncLock.h"
#include "BaseCommand.h"

class LoginTaskManager : public Singleton<LoginTaskManager>
{
public:
	typedef map<UINT,LoginTask*> TaskMap;
	typedef map<UINT,LoginTask*>::iterator TaskMapItr;

	LoginTaskManager(void);
	virtual ~LoginTaskManager(void);

	bool addTask(UINT id, LoginTask* task);

	LoginTask* getTask(UINT id);

	LoginTask* removeTask(UINT id);

	void destroyTask(UINT id);

	bool sendCmd(UINT id, stBaseCommand* pCmd, UINT cmdLen);

	UINT size();

private:
	TaskMap m_taskMap;
	SyncLock m_lock;
};
