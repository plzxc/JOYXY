#pragma once
#include "Singleton.h"
#include "GuildMarkTask.h"
#include "SyncLock.h"
#include "BaseCommand.h"

class GuildMarkTaskManager : public Singleton<GuildMarkTaskManager>
{
public:
	typedef map<UINT,GuildMarkTask*> TaskMap;
	typedef map<UINT,GuildMarkTask*>::iterator TaskMapItr;

	GuildMarkTaskManager(void);
	virtual ~GuildMarkTaskManager(void);

	bool addTask(UINT id, GuildMarkTask* task);

	GuildMarkTask* getTask(UINT id);

	GuildMarkTask* removeTask(UINT id);

	void destroyTask(UINT id);

	bool sendCmd(UINT id, stBaseCommand* pCmd, UINT cmdLen);

	UINT size();

private:
	TaskMap m_taskMap;
	SyncLock m_lock;
};
