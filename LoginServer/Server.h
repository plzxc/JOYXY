#pragma once
#include <entity.h>

enum ServerState
{
	SS_Close,		// 关服维护
	SS_Free,		// 很闲
	SS_Normal,		// 正常
	SS_Busy,		// 非常忙
};

enum ServerType
{
	LoginServer = 1,		// 登陆服务器
	GameServer = 2,			// 游戏服务器
	GatewayServer = 3,		// 网关服务器
};

class Server : public Entity
{
public:
	Server(void);
	virtual ~Server(void);

	void setType(ServerType type);
	ServerType getType();

	void setState(ServerState state);
	ServerState getState();

	void setZoneId(UINT zoneid);
	UINT getZoneId();

	void setIsNew(BOOL isNew);
	BOOL isNew();

	void setIP(const char* ip);
	const char* getIP();

	void setPort(WORD port);
	WORD getPort();

	void setOnlineNum(DWORD num);
	DWORD getOnlineNum();

	void setMaxNum(DWORD num);
	DWORD getMaxNum();


private:
	UINT m_zoneid;
	ServerType m_type;
	ServerState m_state;
	BOOL m_isNew;
	string m_strIP;
	WORD m_port;
	DWORD m_onlineNum;
	DWORD m_maxNum;
};
