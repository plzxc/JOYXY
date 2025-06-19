#pragma once
#include <entity.h>

enum ServerState
{
	SS_Close,		// �ط�ά��
	SS_Free,		// ����
	SS_Normal,		// ����
	SS_Busy,		// �ǳ�æ
};

enum ServerType
{
	LoginServer = 1,		// ��½������
	GameServer = 2,			// ��Ϸ������
	GatewayServer = 3,		// ���ط�����
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
