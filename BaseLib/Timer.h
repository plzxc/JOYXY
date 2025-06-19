#pragma once

#ifndef __TIMER_H__
#define __TIMER_H__

#include "SyncLock.h"
#include "Thread.h"


// ��ʱ�������¼�
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
	// ����true - ������ʱ��  false - ɾ����ʱ��
	virtual bool onTimer() = 0;

private:
	DWORD m_elapse;		// ��ʱʱ��
	DWORD m_lastTick;	// ��¼ʱ��
};


// ��ʱ��
class Timer : public Thread
{
public:
	Timer(void);
	virtual ~Timer(void);

	typedef map<DWORD,TimerEvent*> TimerEventMap;
	typedef map<DWORD,TimerEvent*>::iterator TimerEventMapIter;

	// ��Ӷ�ʱ��
	void addTimer(TimerEvent* event);

	// ɾ����ʱ��(ע�⣬�����ڶ�ʱ��onTimer����ɾ��)
	void deleteTimer(TimerEvent** event);

protected:
	virtual bool run();

private:
	TimerEventMap m_timerEventMap;
	SyncLock m_lock;
};


#endif

