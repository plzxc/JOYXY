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
		m_FreePointer = *reinterpret_cast<byte**>(rp); //����ͷ4���ֽڱ���ǿ�С�����Ϊָ����һ�ڴ���ָ�룬����m_NewPointer��ָ������һ���ڴ�飬�Ա��´η���ʹ�á�
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
		byte **cur = reinterpret_cast<byte**>(m_FreePointer); //ǿ��ת��Ϊ˫ָ�룬�⽫�ı�ÿ���ڴ��ͷ4���ֽڵĺ��塣
		byte *next = m_FreePointer;
		for(int i = 0; i < BLOCK_NUM-1; i++)
		{
			next += sizeof(T);
			*cur = next;
			cur = reinterpret_cast<byte**>(next); //�������������ÿ���ڴ���ͷ4���ֽھͱ���ǿ�С�����Ϊָ����һ���ڴ���ָ�룬 ���γ����ڴ�������ṹ��
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