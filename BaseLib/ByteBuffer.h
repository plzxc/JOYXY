#pragma once

#ifndef __BYTE_BUFFER_H__
#define __BYTE_BUFFER_H__

#include "ObjectPool.h"

//#define USE_STL_BYTE	// ʹ��stl

class ByteBuffer// : public ObjectPool<ByteBuffer,200>
{
private:
	ByteBuffer();

public:
	ByteBuffer(UINT size);
	virtual ~ByteBuffer(void);

	// debug function
	void dump();

	// �ӻ����ĩβд������(�������ݻ�����)
	bool write(const void* data, UINT size);

	// �ӻ����ͷ����ȡ����(�������ݻ����)
	bool read(void* data, UINT size);

	// �ӻ���ͷ����ʼ���Ƴ�ָ����С������(�������ݻ����)
	bool remove(UINT size);

	// ��ָ��λ��ȡָ����С�����������ݣ������ı仺������
	bool get(void* data, UINT size, UINT offset = 0);

	// ��û����׵�ַ
	void* getBuffer();

	// �������
	void clearBuffer(); 

	// ȡ�û������Ĵ�С(�����ݵ��ֽ���)
	size_t size();

	// ���·����ڴ�(ע�⣺���д��ڵ����ݶ�������������ã�)
	void resize(UINT size);

protected:
	// Ԥ�ȼ��㻺���С���������������ڴ�
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


