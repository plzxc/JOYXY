#pragma once

#ifndef __TIMER_H__
#define __TIMER_H__

#include "SyncLock.h"
#include "Thread.h"


// 定时器触发事件
class TimerEvent
{
	friend class Timer;
public:
	TimerEvent(DWORD elapse)
	{
		m_elapse = elapse;
		m_lastTick = GetTickCount();
	}
	virtual ~TimerEvent(){}


protected:
	// 返回true - 继续定时。  false - 删除定时器
	virtual bool onTimer() = 0;

private:
	DWORD m_elapse;		// 定时时间
	DWORD m_lastTick;	// 记录时间
};


// 定时器
class Timer : public Thread
{
public:
	Timer(void);
	virtual ~Timer(void);

	typedef map<DWORD,TimerEvent*> TimerEventMap;
	typedef map<DWORD,TimerEvent*>::iterator TimerEventMapIter;

	// 添加定时器
	void addTimer(TimerEvent* event);

	// 删除定时器(注意，不能在定时器onTimer里面删除)
	void deleteTimer(TimerEvent** event);

protected:
	virtual bool run();

private:
	TimerEventMap m_timerEventMap;
	SyncLock m_lock;
};


#endif

