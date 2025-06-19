#pragma once
#include <entity.h>
#include "LoginTask.h"

class User : public Entity
{
public:
	User(LoginTask* task);
	virtual ~User(void);

	void GenerateKey();
	const char* getKey();

	void setIP(const char* ip);
	const char* getIP();

	// 游戏服务器ID
	void setZoneId(UINT zonid);
	UINT getZoneId();

	void setGatewayId(UINT gatewayid);
	UINT getGatewayId();

	void setLoginTimes(UINT times);
	UINT getLoginTimes();

	LoginTask* getLoginTask();

	bool sendCmd(void* pCmd, UINT cmdLen); 

	// delay 延时秒数
	void disconnect(DWORD delay = 0);

private:
	UINT m_zoneId;
	UINT m_gatewayId;
	UINT m_loginTimes;	// 强制登陆次数
	char m_key[13];
	
	char m_ip[MAX_IP_SIZE+1];
	LoginTask* m_task;
};
