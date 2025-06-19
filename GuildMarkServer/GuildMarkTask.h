#pragma once
#include <AppieTCPTask.h>
#include "BaseCommand.h"

class GuildMarkTask : public AppieTCPTask
{
public:
	GuildMarkTask(WORD id, TCPServer* pTcpServer);
	virtual ~GuildMarkTask(void);

	// ���������¼�
	virtual bool OnAccept();

	// ����ر��¼�
	virtual bool OnClose();

	// �����������Ϣ����
	virtual bool processMessage(void *data, DWORD cmdLen);

protected:
	// �����½�Ϳͻ���֮�����Ϣ
	bool procClientCmd(stBaseCommand* pCmd, DWORD cmdLen);

	// ���ͼƬ�ļ�
	bool packImgFile(UINT world);

	// ���ʹ�����ļ�
	bool sendPackFile(UINT world);
};





