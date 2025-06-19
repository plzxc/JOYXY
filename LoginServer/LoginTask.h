#pragma once
#include <AppieTCPTask.h>
#include "BaseCommand.h"


enum LoginState
{
	LS_VERIFY_VERSION,	// ��֤�汾 
	LS_VERIFY_ACCOUNT,	// ��֤�˺�
	LS_VERIFY_KEY,		// ��֤��Կ
	LS_SERVERLIST,		// �������б�
	LS_SYNC_KEY,		// ͬ����Կ
};


class LoginTask : public AppieTCPTask
{
public:
	LoginTask(WORD id, TCPServer* pTcpServer);
	virtual ~LoginTask(void);

	// ���������¼�
	virtual bool OnAccept();

	// ����ر��¼�
	virtual bool OnClose();

	// �����������Ϣ����
	virtual bool processMessage(void *data, DWORD cmdLen);

public:
	void setState(LoginState state);
	LoginState getState();

protected:
	// �����½�Ϳͻ���֮�����Ϣ
	bool procClientCmd(stBaseCommand* pCmd, DWORD cmdLen);

	// �����½����Ϸ������֮�����Ϣ
	bool procGameServerCmd(stServerBaseCommand* pCmd, DWORD cmdLen);

	// �����½�����ط�����֮�����Ϣ
	bool procGatewayServerCmd(stServerBaseCommand* pCmd, DWORD cmdLen);

protected:
	// ���ݿ����
	time_t GetUserEndTime(const char* account);
	bool VerifyAccount(const char* account, const char* password, WORD& error);
	bool VerifyServer(DWORD id, const char* ip, WORD port, char* name, BOOL& isNew);

	// �̳���صĲ�ѯ
	bool GetUserCashInfo(const char* account, UINT& cashpoint, UINT& hongli);
	bool SubUserCashInfo(const char* account, UINT cashpoint, UINT hongli);

	// ���
	bool ChangeAccountStatus(const char* account, const char* status);

	string m_account;
	LoginState m_state;
};
