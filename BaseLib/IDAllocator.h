#pragma once

#ifndef __IDALLOCATOR_H__
#define __IDALLOCATOR_H__

#include "SyncLock.h"

// ID分配器，ID是从0开始分配的。

#define INVALID_ID	0xFFFF

class IDAllocator
{
private:
	IDAllocator();

public:
	IDAllocator(WORD max);
	virtual ~IDAllocator(void);

	// 重设最大ID,谨慎使用
	void resetMaxID(WORD max);

	// 分配一个ID
	WORD allocateID();

	// 回收一个ID
	bool recycleID(WORD id);

private:
	WORD m_max;	// 最大数值
	map<WORD,WORD> m_idMap;
	SyncLock m_lock;
};

#endif