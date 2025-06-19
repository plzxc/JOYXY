#pragma once

class IniParser
{
public:
	IniParser(void);
	virtual ~IniParser(void);

	// ����ini�ļ�
	bool load(const char* filename);

	// ��ȡ��������
	int readInt(const char* app, const char* key, int defaultValue = 0);

	// ��ȡ�ַ�������
	string readString(const char* app, const char* key, const char* defaultValue = "");

	// д����������
	void writeInt(const char* app, const char* key, int value);

	// д���ַ�������
	void writeString(const char* app, const char* key, const char* value);

private:
	string m_filename;
};


