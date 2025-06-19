#ifndef __SOCKET_CLIENT_H__
#define __SOCKET_CLIENT_H__
#include "TCPClient.h"
#include "ByteBuffer.h"


class SocketClient : public TCPClient
{
public:
	SocketClient();
	virtual ~SocketClient();

	// �رշ���
	virtual void Shutdown();

	// ���ӷ�����
	virtual bool Connect(const char* strIP, WORD nPort);

	// ping������
	virtual bool Ping();

	// �Ͽ��ͻ���
	virtual bool Disconnect();

	// ��������
	virtual bool Reconnect();

	// �Ƿ�����������(TCP����ģʽ����Ҫ���״̬)
	virtual bool IsWaitConnect();

	//�ж��Ƿ�ͷ�������������״̬
	virtual bool IsConnect();

	// ��������
	virtual bool SendData(void* data, DWORD len);

	// ��ӡ������Ϣ
	virtual void PrintInfo();

	// ������յ�����Ϣ(�����߳��е���)
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