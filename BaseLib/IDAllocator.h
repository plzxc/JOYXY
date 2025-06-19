#pragma once

#ifndef __IDALLOCATOR_H__
#define __IDALLOCATOR_H__

#include "SyncLock.h"

// ID��������ID�Ǵ�0��ʼ����ġ�

#define INVALID_ID	0xFFFF

class IDAllocator
{
private:
	IDAllocator();

public:
	IDAllocator(WORD max);
	virtual ~IDAllocator(void);

	// �������ID,����ʹ��
	void resetMaxID(WORD max);

	// ����һ��ID
	WORD allocateID();

	// ����һ��ID
	bool recycleID(WORD id);

private:
	WORD m_max;	// �����ֵ
	map<WORD,WORD> m_idMap;
	SyncLock m_lock;
};

#endif