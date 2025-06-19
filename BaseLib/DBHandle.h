#pragma once

#ifndef __DBHANDLE_H__
#define __DBHANDLE_H__

#include <mysql.h>

enum {
	DB_BYTE,		// 1字节
	DB_WORD,		// 2字节
	DB_DWORD,		// 4字节
	DB_QWORD,		// 8字节
	DB_STR,			// 字符串
	DB_BIN,			// 二进制数据
};

// 字段结构
struct dbField
{
	const char*		name;	// 字段名称
	int				type;	// 数据类型
	UINT	size;	// 数据长度
};



class DBHandle
{
public:
	DBHandle(void);
	virtual ~DBHandle(void);

	//////////////////////////////////////////////////////////////////////////
	// 基础数据库操作接口（比较灵活）

	// connect mysql database
	bool connect(const char* host, const char* user, const char* passwd, const char *db, UINT port = 3306);

	// close the connection
	void close();

	// 是否连接中
	bool isConnected();

	// ping数据库
	void ping();

	// 过滤SQL语句，防止注入攻击
	string& escapeString(string& strSrc, string& strDest);

	// 设置自动提交模式
	bool setAutoCommit(bool isOpen);

	// 立即提交
	bool commit();

	// 回滚
	bool rollback();

	// 打开一个数据库
	bool openDatabase(const char* dbName);

	// 执行SQL语句
	bool query(string& strSQL);

	// 执行SQL语句，支持字符串格式化
	bool queryF(const char* szFormat, ...);

	// 获得字段的数量
	UINT getFieldsNum();

	//  获得数据的行数
	UINT getRowNum();

	// 获得字段的名称
	const char* getFieldName(UINT index);

	// 获取行数据
	bool fetchRow();

	// 取得字符串字段值
	string getStrField(UINT index);

	// 取得整形字段值
	int getIntField(UINT index);

	// 取得二进制字段值
	bool getBinField(UINT index, void* data, int len);

	// 取个最近一次插入的ID号
	ULONGLONG getInsertId();

	//////////////////////////////////////////////////////////////////////////
	// 扩展数据库操作接口（结构比较固定）
	
	// 查询数据
	UINT exeSelect(const char* tableName, const char* where, const char* order, dbField* fields, BYTE** data, UINT limit = 0, UINT limitFrom = 0);

	// 插入数据
	UINT exeInsert(const char* tableName, dbField* fields, void* data);

	// 更新数据
	UINT exeUpdate(const char* tableName, const char* where, dbField* fields, void* data);

	// 删除数据
	UINT exeDelete(const char* tableName, const char* where);

private:
	// release Result
	void releaseResult();

	UINT fillDataByRow(MYSQL_ROW row, unsigned long* lengths, const dbField* fields, BYTE* data);

private:
	MYSQL m_MySql;
	MYSQL_RES *m_pResult;
	MYSQL_FIELD *m_pFields;
	MYSQL_ROW m_row;
	UINT m_numfields;
	ULONGLONG m_numrows;
	//BOOL m_bUTF8;
};


#endif


