#ifndef __SOCKET_CLIENT_H__
#define __SOCKET_CLIENT_H__
#include "TCPClient.h"
#include "ByteBuffer.h"


class SocketClient : public TCPClient
{
public:
	SocketClient();
	virtual ~SocketClient();

	// 关闭服务
	virtual void Shutdown();

	// 连接服务器
	virtual bool Connect(const char* strIP, WORD nPort);

	// ping服务器
	virtual bool Ping();

	// 断开客户端
	virtual bool Disconnect();

	// 重新连接
	virtual bool Reconnect();

	// 是否正在连接中(TCP阻塞模式不需要这个状态)
	virtual bool IsWaitConnect();

	//判断是否和服务器处于连接状态
	virtual bool IsConnect();

	// 发送数据
	virtual bool SendData(void* data, DWORD len);

	// 打印运行信息
	virtual void PrintInfo();

	// 处理接收到的消息(在主线程中调用)
	virtual void HandleCommand();

public:
	void Send();
	void Recv();
	void ParsePacket();

protected:
	static DWORD WINAPI SendThread(void* param);
	static DWORD WINAPI RecvThread(void* param);

private:
	volatile bool m_isRunning;
	bool m_isConnected;
	string m_strIP;
	WORD m_nPort;
	SOCKET m_socket;
	HANDLE 	m_threadSend;
	HANDLE	m_threadRecv;

	SyncLock m_sendLock;
	ByteBuffer m_sendBuff;
	
 	//SyncLock m_recvLock;
 	ByteBuffer m_recvBuff;

	SyncLock m_cmdQueLock;
	queue<ByteBuffer*> m_cmdQueue;
};




#endif