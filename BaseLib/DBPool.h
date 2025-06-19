#pragma once

#ifndef __DBPOOL_H__
#define __DBPOOL_H__
#include "DBHandle.h"

class DBPool; 


class AutoDBHandle
{
public:
	AutoDBHandle(DBPool& dbPool);
	virtual ~AutoDBHandle();

	DBHandle* handle();

private:
	DBPool& m_dbPool;
	DBHandle* m_handle;
};



class DBPool
{
public:
	typedef map<unsigned long,DBHandle*> HandleMap;
	typedef map<unsigned long,DBHandle*>::iterator HandleMapIt;

public:
	DBPool(int maxHandle = 5);
	virtual ~DBPool(void);

	void close();

	bool connect(const char* host, const char* user, const char* passwd, const char *db, UINT port = 3306);

	DBHandle* getHandle();

	bool putHandle(DBHandle* handle);

	
private:
	HandleMap m_freeHandleMap;		// 不使用的连接
	HandleMap m_busyHandleMap;		// 使用中的连接
	int m_maxHandel;
};

#endif

