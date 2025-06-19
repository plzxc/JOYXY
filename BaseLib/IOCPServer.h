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

#define IoSend	1	// 发送事件
#define IoRecv	2	// 接收事件
#define IoExit	3	// 退出系统

enum ConnState
{
	ConnActive = 0,		// 有效链接
	ConnDeactive = 1,	// 无效链接
};

struct IoDataBase : public OVERLAPPED
{
	WORD	nClient;		// 客户端索引号
	BYTE	IoMode;			// IO操作符
	WSABUF	WsaBuf;			// 发送时用

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
	SyncLock usedLock;		// 使用锁
	BOOL isUsing;			// 是否正在使用

	DWORD dwSentBytes;		// 已经发送的字节数
	ByteBuffer buffer;		// 发送缓存(Work线程中使用)

	//SyncLock sendLock;		// 使用锁
	ByteBuffer sendBuffer;	// 发送缓存(Send线程中使用)

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
	char buffer[MAX_USER_PACK_SIZE];	// 单次接收缓存
	ByteBuffer byteBuffer;				// 所有数据缓存(用于解析和拆包)

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

	// 初始化
	virtual bool Initialize(WORD nMaxClient, WORD nPort);

	// 终止服务
	virtual void Terminate();

	// 断开客户端
	virtual bool Disconnect(WORD nClient);

	// 发送数据
	virtual bool SendData(WORD nClient, void* data, DWORD len);

	// 打印运行信息
	virtual void PrintInfo();

	// 处理接收到的消息(在主线程中调用)
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