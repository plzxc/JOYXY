#ifndef __MEMORY_LEAK_H__
#define __MEMORY_LEAK_H__

#include <map>
#include <hash_map>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <fstream>
using namespace std;

#pragma warning(disable:4291)

//////////////////////////////////////////////////////////////////////////
// �ڴ���ٵ��Խṹ

// �����ڴ�ĸ���
void addTrack(void* ptr, size_t size, const char* file, unsigned int line);

// �ͷ��ڴ�ĸ���
void removeTrack(void* ptr);

// �����ǰ�ڴ���ټ�¼
void printTrack();




//////////////////////////////////////////////////////////////////////////
// new, delete, new[], delete[] �������

__inline void* operator new(size_t size, const char* file, unsigned int line)
{
	void* ptr = (void*)malloc(size);
	addTrack(ptr,size,file,line);
	return ptr;
}

__inline void operator delete(void* ptr)
{
	removeTrack(ptr);
	free(ptr);
}


__inline void* operator new [](size_t size, const char* file, unsigned int line)
{
	void* ptr = (void*)malloc(size);
	addTrack(ptr,size,file,line);
	return ptr;
}

__inline void operator delete [](void* ptr)
{
	removeTrack(ptr);
	free(ptr);
}


#define DEBUG_NEW new(__FILE__,__LINE__)
#define new DEBUG_NEW




#endif