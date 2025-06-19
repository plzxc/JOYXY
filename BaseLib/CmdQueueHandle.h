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

	// ������Ϣ������Ϸ�߼�
	virtual bool onCmdMsg(WORD nClient, void *pCmd, DWORD cmdLen) = 0;

	// ���߳�ѭ��������Ϣ
	bool doMsg();

	// ѹ����Ϣ
	bool push(WORD nClient, void *pCmd, DWORD cmdLen);

	// ������Ϣ
	//bool pop();

private:
	// ��Ϣ����
	std::list<stCmdInfo*> m_cmdQueue;
	SyncLock m_lock;
};


#endif

