#ifndef __BASECOMMAND_H__
#define __BASECOMMAND_H__

#pragma warning(disable:4200)

#pragma pack(1)

// �ͻ��˺ͷ�����֮��Ļ�����Ϣ�ṹ
struct stBaseCommand 
{
	BYTE message;
	UINT id;

	stBaseCommand(BYTE message2)
	{
		id = (UINT)-1;
		message = message2;
	}
};


// �������ͷ�����֮��Ļ�����Ϣ�ṹ
struct stServerBaseCommand 
{
	BYTE cmd;	// ����Ϣ
	BYTE para;	// ����Ϣ

	stServerBaseCommand(BYTE cmd2, BYTE para2)
	{
		cmd = cmd2;
		para = para2;
	}
};


//////////////////////////////////////////////////////////////////////////

// ��ǰ�������汾
#define	SERVER_VERSION	142

__inline void XOR(void* data, int size, byte key)
{
	byte *ss=(byte*)data;
	for(int i=0; i<size; i++)
		ss[i]^=key;
}

__inline void XorCommand(void* data, int size, byte key)
{
	byte *ss=((byte*)data) + 1;
	for(int i=0; i<size-1; i++)
		ss[i]^=key;
}

__inline stBaseCommand* CopyCmdData(stBaseCommand* dest, stBaseCommand* src, DWORD cmdLen)
{
	DWORD baseLen = sizeof(stBaseCommand);
	BYTE* temp1 = (BYTE*)dest;
	BYTE* temp2 = (BYTE*)src;
	memcpy(temp1+baseLen,temp2+baseLen,cmdLen-baseLen);
	return dest;
}


//////////////////////////////////////////////////////////////////////////

#pragma pack()


#endif