#pragma once

#ifndef __APPIE_TCP_TASK_H__
#define __APPIE_TCP_TASK_H__

class AppieTCPTask : public TCPTask
{
public:
	AppieTCPTask(WORD id, TCPServer* pTCPServer);
	virtual ~AppieTCPTask(void);

	virtual bool sendCmd(void* pCmd, UINT cmdLen);

protected:
	// ��������յ������ݣ������������
	virtual bool parseRecvData();
};

#endif