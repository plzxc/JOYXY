#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;


struct stPakFile
{
	string filename;		// pak�ļ���
	char key;				// ���������õ�Key
	vector<BYTE> password;	// �������ܺ������

	stPakFile()
	{
		filename = "";
		key = 0;
		password.clear();
	}
};

class FileSystem;


// �����ļ�, ���ļ���ʱֻ�ܶ�ȡ������д��
// Virtual File
class VFile
{
	friend class FileSystem;
public:
	VFile();
	virtual ~VFile();
	
	// �Ƿ��ļ��Ľ���
	bool isEnd();

	// �ļ���С
	DWORD size();

	// ��û����ַ
	void* getBuffer();

	// ��ȡ�ļ�����
	DWORD read(void* buffer, DWORD len);
	
private:
	// �ͷ����е���Դ
	void release();

private:
	BYTE* m_ptrSrc;
	BYTE* m_ptrCur;
	ULONG m_size;
};


// �ļ�ϵͳ
class FileSystem
{
	typedef map<string,stPakFile> PakFileMap;
	typedef map<string,stPakFile>::iterator PakFileMapIter;

	typedef map<VFile*,VFile*> VFileMap;
	typedef map<VFile*,VFile*>::iterator VFileMapIter;

public:
	FileSystem(void);
	virtual ~FileSystem(void);

	// ����һ��pak�ļ�
	bool attachPakFile(const char* filename, const char* password = NULL);

	// ɾ��һ��pak�ļ�
	bool detachPakFile(const char* filename);

	// ɾ�����е�PAK�ļ�
	void detachAllPakFile();

	// ��һ���ļ�
	VFile* openFile(const char* filename);

	// �ر�һ���ļ�
	void closeFile(VFile* pVFile);

protected:
	// ��ѹ�����ж�ȡ�ļ�
	VFile* openFileFromPak(const char* filename);

	// �ӱ���ϵͳ�ж�ȡ�ļ�
	VFile* openFileFromLocal(const char* filename);

private:
	// ���д򿪵�pak�ļ���Ϣ
	PakFileMap m_pakFileMap;
	VFileMap m_vFileMap;
};
