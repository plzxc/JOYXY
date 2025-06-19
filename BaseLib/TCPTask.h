#pragma once

#ifndef __TCPTASK_H__
#define __TCPTASK_H__

#include "ByteBuffer.h"
//#include <winsock2.h>

enum TaskState
{
	notuse = 0,	// �ս�������
	verify,		// �ȴ���֤
	okay,		// �����ȶ�����
	recycle,	// ��������
};


// ������Ϣ�Ľӿ�
class MessageHandle
{
public:
	MessageHandle(){}
	virtual ~MessageHandle(){}
	virtual bool processMessage(void *data, DWORD cmdLen) = 0;
};


class TCPServer;

// Ĭ�����ݰ���ʽ
// WORD | BIN
// Size | Datas
// ǰ�����ֽڴ����С��������ָ�����ȵ�����

class TCPTask : public MessageHandle
{
public:
	TCPTask(WORD id, TCPServer* pTCPServer);
	virtual ~TCPTask(void);

	// ȡ�÷����ID��
	WORD getID();

	// ���SOCKET���
	//SOCKET getSocket();

	// ���IP��ַ
	const char* getIP();

	// �ر�����
	void disconnect();

	// ������һ��״̬
	void enterNextState();

	// ��������(ԭ�����ݷ��ͣ������κδ���)
	virtual bool sendData(void* data, DWORD len);

	// ��������(������ͣ����� ǰ�����ֽڱ�ʾ���ȣ����������)
	virtual bool sendCmd(void* pCmd, UINT cmdLen);

	// ��������
	virtual void recycleTask();

	// �ܷ��������
	virtual bool canRecycle();

	// ���������¼�
	virtual bool OnAccept() {return true;}

	// ����ر��¼�
	virtual bool OnClose() {return true;}

public:
	// �ر���Ϣ����(ϵͳ�ײ�ʹ�ã���㲻Ҫ���ô˺���)
	// ���ô�״̬�󣬽���������Ϣ����
	void closeSendMsg() { m_isCanSendMsg = false; }

	// �Ƿ��ǶϿ�״̬
	bool isCanSendMsg() { return m_isCanSendMsg; }

	// ������յ�������
	virtual bool processRecvData(void* data, DWORD len);

	// ��������յ������ݣ������������
	virtual bool parseRecvData();

	// �����������Ϣ����
	virtual bool processMessage(void *data, DWORD cmdLen){return true;}

	void setIP(const char* strIP);

private:
	TaskState m_state;
	WORD m_id;
	DWORD m_recycleTick;
	//SOCKET m_hSocket;
	char m_szIP[20];
	bool m_isCanSendMsg;	// �Ƿ���Է�����Ϣ
	

protected:
	ByteBuffer* m_recvBuffer;
	TCPServer* m_pTCPServer;
};


#endif
