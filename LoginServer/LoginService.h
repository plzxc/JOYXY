#pragma once

#include "LoginTask.h"
#include <Singleton.h>

class LoginService : public SERVER_CLASS, public Singleton<LoginService>
{
public:
	LoginService(void);
	virtual ~LoginService(void);

	bool Init();

protected:
	// ���µĿͻ�������ʱ���������¼�
	virtual TCPTask* OnAccept(WORD nClient);

	// �ͻ��˶Ͽ�����
	virtual bool OnClose(WORD nClient);

	// ���յ���Ϣ
	virtual int OnReceive(WORD nClient, void* pData, DWORD dwDataLen);
};
