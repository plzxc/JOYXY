#pragma once

#ifndef __CMDQUEUE_HANDLE_H__
#define __CMDQUEUE_HANDLE_H__

#include "ObjectPool.h"

struct stCmdInfo// : public ObjectPool<stCmdInfo, 200>
{
	WORD nClient;
	ByteBuffer* buffer;

	stCmdInfo()
	{
		nClient = (WORD)-1;
		buffer = new ByteBuffer(1024);
	}

	~stCmdInfo()
	{
		nClient = (WORD)-1;
		SAFE_DELETE(buffer);
	}
};

class CmdQueueHandle
{
public:
	CmdQueueHandle(void);
	virtual ~CmdQueueHandle(void);

	// 根据消息处理游戏逻辑
	virtual bool onCmdMsg(WORD nClient, void *pCmd, DWORD cmdLen) = 0;

	// 单线程循环处理消息
	bool doMsg();

	// 压入消息
	bool push(WORD nClient, void *pCmd, DWORD cmdLen);

	// 弹出消息
	//bool pop();

private:
	// 消息队列
	std::list<stCmdInfo*> m_cmdQueue;
	SyncLock m_lock;
};


#endif

