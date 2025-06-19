#pragma once
#include <AppieTCPTask.h>
#include "BaseCommand.h"


enum LoginState
{
	LS_VERIFY_VERSION,	// 验证版本 
	LS_VERIFY_ACCOUNT,	// 验证账号
	LS_VERIFY_KEY,		// 验证密钥
	LS_SERVERLIST,		// 服务器列表
	LS_SYNC_KEY,		// 同步密钥
};


class LoginTask : public AppieTCPTask
{
public:
	LoginTask(WORD id, TCPServer* pTcpServer);
	virtual ~LoginTask(void);

	// 处理连接事件
	virtual bool OnAccept();

	// 处理关闭事件
	virtual bool OnClose();

	// 处理处理过的消息数据
	virtual bool processMessage(void *data, DWORD cmdLen);

public:
	void setState(LoginState state);
	LoginState getState();

protected:
	// 处理登陆和客户端之间的消息
	bool procClientCmd(stBaseCommand* pCmd, DWORD cmdLen);

	// 处理登陆和游戏服务器之间的消息
	bool procGameServerCmd(stServerBaseCommand* pCmd, DWORD cmdLen);

	// 处理登陆和网关服务器之间的消息
	bool procGatewayServerCmd(stServerBaseCommand* pCmd, DWORD cmdLen);

protected:
	// 数据库操作
	time_t GetUserEndTime(const char* account);
	bool VerifyAccount(const char* account, const char* password, WORD& error);
	bool VerifyServer(DWORD id, const char* ip, WORD port, char* name, BOOL& isNew);

	// 商城相关的查询
	bool GetUserCashInfo(const char* account, UINT& cashpoint, UINT& hongli);
	bool SubUserCashInfo(const char* account, UINT cashpoint, UINT hongli);

	// 封号
	bool ChangeAccountStatus(const char* account, const char* status);

	string m_account;
	LoginState m_state;
};
