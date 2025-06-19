#pragma once

class Properties
{
	typedef map<string, string> PropMap;
	typedef map<string, string>::iterator PropMapItr;

public:
	Properties(void);
	virtual ~Properties(void);
	
	// ��������ַ���
	void parse(const char* strSrc, const char* split);

	// �������
	void clear();

	// ����һ��ֵ
	void addValue(const char* key, const char* value);
	void addValue(const char* key, unsigned int value);

	// ����key, ���һ��ֵ
	const char* getValue(const char* key);

	// ת�����ַ���
	void toSting(string& strContent, const char* split = " ");

	// ��ӡ
	void print();

private:
	PropMap m_props;
};
