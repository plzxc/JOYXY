#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include "TCPTask.h"
#include "IDAllocator.h"


struct stCmdData
{
	WORD		nClient;
	ByteBuffer	buffer;		// ����/���ջ���

	stCmdData()
		: buffer(512)
	{
		nClient = INVALID_ID;
		buffer.clearBuffer();
	}
};


typedef map<WORD,TCPTask*> TaskMap;
typedef map<WORD,TCPTask*>::iterator TaskMapItr;

class TCPServer
{
public:
	virtual ~TCPServer(void){}

	// ��ʼ��
	virtual bool Initialize(WORD nMaxClient, WORD nPort) = 0;

	// ��ֹ����
	virtual void Terminate() = 0;

	// �Ͽ��ͻ���
	virtual bool Disconnect(WORD nClient) = 0;

	// ��������
	virtual bool SendData(WORD nClient, void* data, DWORD len) = 0;

	// ��ӡ������Ϣ
	virtual void PrintInfo() = 0;

	// ������յ�����Ϣ(�����߳��е���)
	virtual void HandleCommand() = 0;

protected:
	// ���µĿͻ�������ʱ���������¼�
	virtual TCPTask* OnAccept(WORD nClient) = 0;

	// �ͻ��˶Ͽ�����
	virtual bool OnClose(WORD nClient) = 0;

	// ���յ���Ϣ
	virtual int OnReceive(WORD nClient, void* pData, DWORD dwDataLen) = 0;

	// ���󱨸�
	virtual int OnError(WORD nClient, int iError, bool isSend) {return 0;}

	// ������ֹ�¼�
	virtual int OnTerminate() {return 0;}
};


#endif