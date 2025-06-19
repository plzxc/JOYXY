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
	// 有新的客户端连接时，产生的事件
	virtual TCPTask* OnAccept(WORD nClient);

	// 客户端断开连接
	virtual bool OnClose(WORD nClient);

	// 接收到消息
	virtual int OnReceive(WORD nClient, void* pData, DWORD dwDataLen);
};
