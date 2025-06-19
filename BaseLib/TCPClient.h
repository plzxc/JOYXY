#pragma once

class TCPClient
{
public:
	virtual ~TCPClient(void){}

	// �رշ���
	virtual void Shutdown() = 0;

	// ���ӷ�����
	virtual bool Connect(const char* strIP, WORD nPort) = 0;

	// ping������
	virtual bool Ping() = 0;

	// �Ͽ��ͻ���
	virtual bool Disconnect() = 0;

	// ��������
	virtual bool Reconnect() = 0;

	// �Ƿ�����������
	virtual bool IsWaitConnect() = 0;

	//�ж��Ƿ�ͷ�������������״̬
	virtual bool IsConnect() = 0;

	// ��������
	virtual bool SendData(void* data, DWORD len) = 0;

	// ��ӡ������Ϣ
	virtual void PrintInfo() = 0;

	// ������յ�����Ϣ(�����߳��е���)
	virtual void HandleCommand() = 0;

protected:
	// ���ӳɹ����������¼�
	virtual bool OnConnect() = 0;

	// �Ͽ����ӣ��������¼�
	virtual bool OnClose() = 0;

	// ���յ���Ϣ
	virtual int OnReceive(void* pData, DWORD dwDataLen) = 0;
};
