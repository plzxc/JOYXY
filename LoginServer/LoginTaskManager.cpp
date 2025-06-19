#include "StdAfx.h"
#include "LoginTaskManager.h"

LoginTaskManager::LoginTaskManager(void)
{
}

LoginTaskManager::~LoginTaskManager(void)
{
}

bool LoginTaskManager::addTask(UINT id, LoginTask* task)
{
	AutoSycnLock autoLock(m_lock);
	TaskMapItr itFind = m_taskMap.find(id);
	if (itFind != m_taskMap.end()) {
		return false;
	}

	m_taskMap[id] = task;
	return true;
}

LoginTask* LoginTaskManager::getTask(UINT id)
{
	AutoSycnLock autoLock(m_lock);
	LoginTask* task = NULL;
	TaskMapItr itFind = m_taskMap.find(id);
	if (itFind != m_taskMap.end()) {
		task = itFind->second;
	}
	return task;
}

LoginTask* LoginTaskManager::removeTask(UINT id)
{
	AutoSycnLock autoLock(m_lock);
	LoginTask* task = NULL;
	TaskMapItr itFind = m_taskMap.find(id);
	if (itFind != m_taskMap.end()) {
		task = itFind->second;
		m_taskMap.erase(itFind);
	}
	return task;
}

void LoginTaskManager::destroyTask(UINT id)
{
	AutoSycnLock autoLock(m_lock);
	LoginTask* task = NULL;
	TaskMapItr itFind = m_taskMap.find(id);
	if (itFind != m_taskMap.end()) {
		task = itFind->second;
		m_taskMap.erase(itFind);
		SAFE_DELETE(task);
	}
}

bool LoginTaskManager::sendCmd(UINT id, stBaseCommand* pCmd, UINT cmdLen)
{
	AutoSycnLock autoLock(m_lock);
	LoginTask* task = NULL;
	TaskMapItr itFind = m_taskMap.find(id);
	if (itFind != m_taskMap.end()) {
		task = itFind->second;
		task->sendCmd(pCmd, cmdLen);
		return true;
	}

	return false;
}

UINT LoginTaskManager::size()
{
	AutoSycnLock autoLock(m_lock);
	return (UINT)m_taskMap.size();
}



