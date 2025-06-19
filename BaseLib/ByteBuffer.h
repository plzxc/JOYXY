#pragma once

#ifndef __BYTE_BUFFER_H__
#define __BYTE_BUFFER_H__

#include "ObjectPool.h"

//#define USE_STL_BYTE	// 使用stl

class ByteBuffer// : public ObjectPool<ByteBuffer,200>
{
private:
	ByteBuffer();

public:
	ByteBuffer(UINT size);
	virtual ~ByteBuffer(void);

	// debug function
	void dump();

	// 从缓存的末尾写入数据(缓存数据会增加)
	bool write(const void* data, UINT size);

	// 从缓存的头部读取数据(缓存数据会减少)
	bool read(void* data, UINT size);

	// 从缓存头部开始，移除指定大小的数据(缓存数据会减少)
	bool remove(UINT size);

	// 从指定位置取指定大小的连续的数据，但不改变缓存数据
	bool get(void* data, UINT size, UINT offset = 0);

	// 获得缓存首地址
	void* getBuffer();

	// 清除缓存
	void clearBuffer(); 

	// 取得缓存区的大小(即数据的字节数)
	size_t size();

	// 重新分配内存(注意：所有存在的数据都将被清除，慎用！)
	void resize(UINT size);

protected:
	// 预先计算缓存大小，不够就申请新内存
	void writeReserve(UINT size);

private:
#ifdef USE_STL_BYTE
	vector<BYTE> m_buffer;
#else
	BYTE* m_buffer;
#endif
	volatile UINT m_curSize;
	volatile UINT m_maxSize;
	SyncLock m_lock;
};


#endif


