#pragma once

#ifndef __DBHANDLE_H__
#define __DBHANDLE_H__

#include <mysql.h>

enum {
	DB_BYTE,		// 1�ֽ�
	DB_WORD,		// 2�ֽ�
	DB_DWORD,		// 4�ֽ�
	DB_QWORD,		// 8�ֽ�
	DB_STR,			// �ַ���
	DB_BIN,			// ����������
};

// �ֶνṹ
struct dbField
{
	const char*		name;	// �ֶ�����
	int				type;	// ��������
	UINT	size;	// ���ݳ���
};



class DBHandle
{
public:
	DBHandle(void);
	virtual ~DBHandle(void);

	//////////////////////////////////////////////////////////////////////////
	// �������ݿ�����ӿڣ��Ƚ���

	// connect mysql database
	bool connect(const char* host, const char* user, const char* passwd, const char *db, UINT port = 3306);

	// close the connection
	void close();

	// �Ƿ�������
	bool isConnected();

	// ping���ݿ�
	void ping();

	// ����SQL��䣬��ֹע�빥��
	string& escapeString(string& strSrc, string& strDest);

	// �����Զ��ύģʽ
	bool setAutoCommit(bool isOpen);

	// �����ύ
	bool commit();

	// �ع�
	bool rollback();

	// ��һ�����ݿ�
	bool openDatabase(const char* dbName);

	// ִ��SQL���
	bool query(string& strSQL);

	// ִ��SQL��䣬֧���ַ�����ʽ��
	bool queryF(const char* szFormat, ...);

	// ����ֶε�����
	UINT getFieldsNum();

	//  ������ݵ�����
	UINT getRowNum();

	// ����ֶε�����
	const char* getFieldName(UINT index);

	// ��ȡ������
	bool fetchRow();

	// ȡ���ַ����ֶ�ֵ
	string getStrField(UINT index);

	// ȡ�������ֶ�ֵ
	int getIntField(UINT index);

	// ȡ�ö������ֶ�ֵ
	bool getBinField(UINT index, void* data, int len);

	// ȡ�����һ�β����ID��
	ULONGLONG getInsertId();

	//////////////////////////////////////////////////////////////////////////
	// ��չ���ݿ�����ӿڣ��ṹ�ȽϹ̶���
	
	// ��ѯ����
	UINT exeSelect(const char* tableName, const char* where, const char* order, dbField* fields, BYTE** data, UINT limit = 0, UINT limitFrom = 0);

	// ��������
	UINT exeInsert(const char* tableName, dbField* fields, void* data);

	// ��������
	UINT exeUpdate(const char* tableName, const char* where, dbField* fields, void* data);

	// ɾ������
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


