#pragma once
#include <entitymanager.h>
#include <Singleton.h>
#include "Server.h"



class ServerManager : public Singleton<ServerManager>, public EntityManager<EntityManagerID,EntityManagerLongID>
{
public:

	typedef map<UINT,Server*> ServerMap;
	typedef map<UINT,Server*>::iterator ServerMapItr;
	typedef map< UINT,map<UINT,Server*> > GatewayMap;
	typedef map< UINT,map<UINT,Server*> >::iterator GatewayMapItr;

	ServerManager(void);
	virtual ~ServerManager(void);

	// ͨ����ʱID����ȡ������
	Server* getServerByTempID(UINT longId) { return (Server*)getEntityByLongID(longId); }

	// ͨ��������ID��ȡ������
	Server* getServer(UINT id) { return (Server*)getEntityByID(id); }

	// ɾ��������
	bool removeServer(Server* pServer);

	// ��ӷ�����
	bool addServer(Server* pServer);

	// ����һ�����е����ط�����
	Server* findGatewayServer(UINT zoneid);

private:
	GatewayMap m_gateMap;
};
