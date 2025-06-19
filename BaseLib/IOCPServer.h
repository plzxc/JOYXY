#ifndef __IOCPSERVER_H__
#define __IOCPSERVER_H__

#include <Windows.h>
#include <winsock2.h>
#include <map>
#include <queue>
#pragma comment(lib,"ws2_32.lib")
#include "IDAllocator.h"
#include "ByteBuffer.h"
#include "TCPServer.h"
using namespace std;

#define IoSend	1	// �����¼�
#define IoRecv	2	// �����¼�
#define IoExit	3	// �˳�ϵͳ

enum ConnState
{
	ConnActive = 0,		// ��Ч����
	ConnDeactive = 1,	// ��Ч����
};

struct IoDataBase : public OVERLAPPED
{
	WORD	nClient;		// �ͻ���������
	BYTE	IoMode;			// IO������
	WSABUF	WsaBuf;			// ����ʱ��

	IoDataBase()
	{
		IoMode=IoExit;
		WsaBuf.buf=NULL;
		WsaBuf.len=0;
		reset();
	}

	void reset()
	{
		// init OVERLAPPED
		Internal=0;
		InternalHigh=0;
		Offset=0;
		OffsetHigh=0;
		hEvent=0;

		// init SOverlapped
		nClient=INVALID_ID;
	}
};

struct IoSendData : public IoDataBase
{
	SyncLock usedLock;		// ʹ����
	BOOL isUsing;			// �Ƿ�����ʹ��

	DWORD dwSentBytes;		// �Ѿ����͵��ֽ���
	ByteBuffer buffer;		// ���ͻ���(Work�߳���ʹ��)

	//SyncLock sendLock;		// ʹ����
	ByteBuffer sendBuffer;	// ���ͻ���(Send�߳���ʹ��)

	IoSendData() 
		: buffer(512), sendBuffer(512)
	{
		IoMode = IoSend;
		dwSentBytes = 0;
		isUsing = FALSE;
	}
};

struct IoRecvData : public IoDataBase
{
	char buffer[MAX_USER_PACK_SIZE];	// ���ν��ջ���
	ByteBuffer byteBuffer;				// �������ݻ���(���ڽ����Ͳ��)

	IoRecvData()
		: byteBuffer(1024)
	{
		ZeroMemory(buffer,sizeof(buffer));
		IoMode = IoRecv;
		WsaBuf.buf=buffer;
		WsaBuf.len=MAX_USER_PACK_SIZE;
	}
};

struct IoConnect
{
	ConnState state;
	WORD	nClient;
	SOCKET	socket;
	char	IP[20];

	IoSendData ioSendData;
	IoRecvData ioRecvData;

	IoConnect()
	{
		state = ConnDeactive;
		nClient = INVALID_ID;
		socket = INVALID_SOCKET;
		ZeroMemory(IP,sizeof(IP));
	}
};


class IOCPServer : public TCPServer
{
	typedef map<WORD,IoConnect*> ConnMap;
	typedef map<WORD,IoConnect*>::iterator ConnMapItr;

public:
	IOCPServer(void);
	virtual ~IOCPServer(void);

	// ��ʼ��
	virtual bool Initialize(WORD nMaxClient, WORD nPort);

	// ��ֹ����
	virtual void Terminate();

	// �Ͽ��ͻ���
	virtual bool Disconnect(WORD nClient);

	// ��������
	virtual bool SendData(WORD nClient, void* data, DWORD len);

	// ��ӡ������Ϣ
	virtual void PrintInfo();

	// ������յ�����Ϣ(�����߳��е���)
	virtual void HandleCommand();

public:
	void Accept();
	void Work();
	void Send();

private:
	static UINT WINAPI AcceptThread(void* pParam);
	static UINT WINAPI WorkThread(void* pParam);
	static UINT WINAPI SendThread(void* pParam);

	bool PostRecv(WORD nClient);
	void ParsePacket(WORD nClient, IoRecvData* pIoRecvData);
	void RemoveConn(WORD nClient);

private:
	volatile bool m_isRuning;
	WORD m_workThreadNum;
	SOCKET m_listenSocket;
	HANDLE m_hCompletionPort;
	
	SyncLock m_connLock;
	ConnMap m_connMap;
	IDAllocator m_idAllocator;

	SyncLock m_cmdQueLock;
	queue<stCmdData*> m_cmdQueue;
};


#endif