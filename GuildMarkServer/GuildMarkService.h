#pragma once

#include "GuildMarkTask.h"
#include <Singleton.h>

class GuildMarkService : public SERVER_CLASS, public Singleton<GuildMarkService>
{
public:
	GuildMarkService(void);
	virtual ~GuildMarkService(void);

	bool Init();

protected:
	// ���µĿͻ�������ʱ���������¼�
	virtual TCPTask* OnAccept(WORD nClient);

	// �ͻ��˶Ͽ�����
	virtual bool OnClose(WORD nClient);

	// ���յ���Ϣ
	virtual int OnReceive(WORD nClient, void* pData, DWORD dwDataLen);
};
