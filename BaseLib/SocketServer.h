#pragma once

#include <winsock2.h>
#include <map>
#include <queue>
#include <list>
using namespace std;
#include "ByteBuffer.h"
#include "TCPServer.h"
#include "IDAllocator.h"
#include "Misc.h"


#pragma comment(lib,"ws2_32.lib")


#pragma warning(disable:4313 4244 4200)


struct stConnect
{
	SOCKET sock;
	ByteBuffer recvBuff;
	ByteBuffer sendBuff;

	stConnect()
		: recvBuff(512), sendBuff(512)
	{
		reset();
	}

	void reset()
	{
		sock = INVALID_SOCKET;
		recvBuff.resize(512);
		sendBuff.resize(512);
	}
};


//typedef map<WORD,ByteBuffer*> SendMap;
//typedef map<WORD,ByteBuffer*>::iterator SendMapItr;


class SocketServer : public TCPServer
{
public:
	SocketServer(void);
	virtual ~SocketServer(void);

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


protected:
	//���ͺͽ��յ��̺߳���
	static DWORD WINAPI SendThreadProc(LPVOID pParam);
	static DWORD WINAPI RecvThreadProc(LPVOID pParam);
	static DWORD WINAPI ListenThreadProc(LPVOID pParam);
	void Send();
	void Recv();
	void AcceptConnect();

	void setBuffSize(SOCKET socket);
	void printBuffSize(SOCKET socket);

	void setTimeout(SOCKET socket);
	void printTimeout(SOCKET socket);


protected:
	short m_nServerPort;

	SyncLock m_sendLock;
	//SendMap m_sendBuff;

	SyncLock m_recvLock;
	list< pair< stCmdData*, int > > m_listPacketRecv;

	stConnect *m_aClient;

	SOCKET m_hSocket;
	int m_nMaxClient;
	int m_nCurClient;

private:
	bool m_bRunning;
	HANDLE m_threadSend;
	HANDLE m_threadRecv;
	HANDLE m_threadListen;
};









