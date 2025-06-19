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

	// 通过临时ID来获取服务器
	Server* getServerByTempID(UINT longId) { return (Server*)getEntityByLongID(longId); }

	// 通过服务器ID获取服务器
	Server* getServer(UINT id) { return (Server*)getEntityByID(id); }

	// 删除服务器
	bool removeServer(Server* pServer);

	// 添加服务器
	bool addServer(Server* pServer);

	// 查找一个空闲的网关服务器
	Server* findGatewayServer(UINT zoneid);

private:
	GatewayMap m_gateMap;
};
