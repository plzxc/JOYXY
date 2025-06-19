#pragma once
#include <AppieTCPTask.h>
#include "BaseCommand.h"

class GuildMarkTask : public AppieTCPTask
{
public:
	GuildMarkTask(WORD id, TCPServer* pTcpServer);
	virtual ~GuildMarkTask(void);

	// 处理连接事件
	virtual bool OnAccept();

	// 处理关闭事件
	virtual bool OnClose();

	// 处理处理过的消息数据
	virtual bool processMessage(void *data, DWORD cmdLen);

protected:
	// 处理登陆和客户端之间的消息
	bool procClientCmd(stBaseCommand* pCmd, DWORD cmdLen);

	// 打包图片文件
	bool packImgFile(UINT world);

	// 发送打包的文件
	bool sendPackFile(UINT world);
};





