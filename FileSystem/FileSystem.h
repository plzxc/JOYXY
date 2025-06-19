#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;


struct stPakFile
{
	string filename;		// pak文件名
	char key;				// 加密密码用的Key
	vector<BYTE> password;	// 经过加密后的密码

	stPakFile()
	{
		filename = "";
		key = 0;
		password.clear();
	}
};

class FileSystem;


// 虚拟文件, 此文件暂时只能读取，不能写入
// Virtual File
class VFile
{
	friend class FileSystem;
public:
	VFile();
	virtual ~VFile();
	
	// 是否文件的结束
	bool isEnd();

	// 文件大小
	DWORD size();

	// 获得缓存地址
	void* getBuffer();

	// 读取文件内容
	DWORD read(void* buffer, DWORD len);
	
private:
	// 释放所有的资源
	void release();

private:
	BYTE* m_ptrSrc;
	BYTE* m_ptrCur;
	ULONG m_size;
};


// 文件系统
class FileSystem
{
	typedef map<string,stPakFile> PakFileMap;
	typedef map<string,stPakFile>::iterator PakFileMapIter;

	typedef map<VFile*,VFile*> VFileMap;
	typedef map<VFile*,VFile*>::iterator VFileMapIter;

public:
	FileSystem(void);
	virtual ~FileSystem(void);

	// 载入一个pak文件
	bool attachPakFile(const char* filename, const char* password = NULL);

	// 删除一个pak文件
	bool detachPakFile(const char* filename);

	// 删除所有的PAK文件
	void detachAllPakFile();

	// 打开一个文件
	VFile* openFile(const char* filename);

	// 关闭一个文件
	void closeFile(VFile* pVFile);

protected:
	// 从压缩包中读取文件
	VFile* openFileFromPak(const char* filename);

	// 从本地系统中读取文件
	VFile* openFileFromLocal(const char* filename);

private:
	// 所有打开的pak文件信息
	PakFileMap m_pakFileMap;
	VFileMap m_vFileMap;
};
