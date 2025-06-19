#include "StdAfx.h"
#include "GuildMarkTaskManager.h"

GuildMarkTaskManager::GuildMarkTaskManager(void)
{
}

GuildMarkTaskManager::~GuildMarkTaskManager(void)
{
}

bool GuildMarkTaskManager::addTask(UINT id, GuildMarkTask* task)
{
	AutoSycnLock autoLock(m_lock);
	TaskMapItr itFind = m_taskMap.find(id);
	if (itFind != m_taskMap.end()) {
		return false;
	}

	m_taskMap[id] = task;
	return true;
}

GuildMarkTask* GuildMarkTaskManager::getTask(UINT id)
{
	AutoSycnLock autoLock(m_lock);
	GuildMarkTask* task = NULL;
	TaskMapItr itFind = m_taskMap.find(id);
	if (itFind != m_taskMap.end()) {
		task = itFind->second;
	}
	return task;
}

GuildMarkTask* GuildMarkTaskManager::removeTask(UINT id)
{
	AutoSycnLock autoLock(m_lock);
	GuildMarkTask* task = NULL;
	TaskMapItr itFind = m_taskMap.find(id);
	if (itFind != m_taskMap.end()) {
		task = itFind->second;
		m_taskMap.erase(itFind);
	}
	return task;
}

void GuildMarkTaskManager::destroyTask(UINT id)
{
	AutoSycnLock autoLock(m_lock);
	GuildMarkTask* task = NULL;
	TaskMapItr itFind = m_taskMap.find(id);
	if (itFind != m_taskMap.end()) {
		task = itFind->second;
		m_taskMap.erase(itFind);
		SAFE_DELETE(task);
	}
}

bool GuildMarkTaskManager::sendCmd(UINT id, stBaseCommand* pCmd, UINT cmdLen)
{
	AutoSycnLock autoLock(m_lock);
	GuildMarkTask* task = NULL;
	TaskMapItr itFind = m_taskMap.find(id);
	if (itFind != m_taskMap.end()) {
		task = itFind->second;
		task->sendCmd(pCmd, cmdLen);
		return true;
	}

	return false;
}

UINT GuildMarkTaskManager::size()
{
	AutoSycnLock autoLock(m_lock);
	return (UINT)m_taskMap.size();
}



