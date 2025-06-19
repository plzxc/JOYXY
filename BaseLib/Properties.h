#pragma once

class Properties
{
	typedef map<string, string> PropMap;
	typedef map<string, string>::iterator PropMapItr;

public:
	Properties(void);
	virtual ~Properties(void);
	
	// 输入解析字符串
	void parse(const char* strSrc, const char* split);

	// 清空数据
	void clear();

	// 增加一个值
	void addValue(const char* key, const char* value);
	void addValue(const char* key, unsigned int value);

	// 根据key, 获得一个值
	const char* getValue(const char* key);

	// 转换到字符串
	void toSting(string& strContent, const char* split = " ");

	// 打印
	void print();

private:
	PropMap m_props;
};
