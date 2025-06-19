#ifndef __OBJECT_POOL_H__
#define __OBJECT_POOL_H__

#include <assert.h>
#include "SyncLock.h"

typedef unsigned char byte;

template <class T, int BLOCK_NUM= 50>
class ObjectPool
{
public:
	static void *operator new(size_t allocLen)
	{
		m_syncLock.lock();
		assert(sizeof(T) == allocLen);
		if(!m_FreePointer)
			AllocNew();
		byte *rp = m_FreePointer;
		m_FreePointer = *reinterpret_cast<byte**>(rp); //由于头4个字节被“强行”解释为指向下一内存块的指针，这里m_NewPointer就指向了下一个内存块，以备下次分配使用。
		m_syncLock.unlock();
		return rp;
	}
	static void operator delete(void *dp)
	{
		m_syncLock.lock();
		*reinterpret_cast<byte**>(dp) = m_FreePointer;
		m_FreePointer = static_cast<byte*>(dp);
		m_syncLock.unlock();
	}
private:
	static void AllocNew()
	{
		m_FreePointer = new byte[sizeof(T) * BLOCK_NUM];
		byte **cur = reinterpret_cast<byte**>(m_FreePointer); //强制转型为双指针，这将改变每个内存块头4个字节的含义。
		byte *next = m_FreePointer;
		for(int i = 0; i < BLOCK_NUM-1; i++)
		{
			next += sizeof(T);
			*cur = next;
			cur = reinterpret_cast<byte**>(next); //这样，所分配的每个内存块的头4个字节就被“强行“解释为指向下一个内存块的指针， 即形成了内存块的链表结构。
		}
		*cur = 0;
	}
	static SyncLock m_syncLock;
	static byte *m_FreePointer;

protected:
	~ObjectPool()
	{
	}
};

template<class T, int BLOCK_NUM >
SyncLock ObjectPool<T, BLOCK_NUM >::m_syncLock;

template<class T, int BLOCK_NUM >
byte* ObjectPool<T, BLOCK_NUM >::m_FreePointer;

#endif