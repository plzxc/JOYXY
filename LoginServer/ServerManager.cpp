#include "StdAfx.h"
#include "servermanager.h"

ServerManager::ServerManager(void)
{
}

ServerManager::~ServerManager(void)
{
}

// ɾ��������
bool ServerManager::removeServer(Server* pServer)
{
	if (pServer == NULL)
		return false;

	UINT zoneid = pServer->getZoneId();
	if (pServer->getType() == GatewayServer) {
		// �����ر���ɾ��
		GatewayMapItr itFind = m_gateMap.find(zoneid);
		if (itFind != m_gateMap.end()) {
			ServerMapItr itFind2 = itFind->second.find(pServer->getID());
			if (itFind2 != itFind->second.end()) {
				itFind->second.erase(itFind2);
			}
		}
	} else if (pServer->getType() == GameServer) {
		GatewayMapItr itFind = m_gateMap.find(zoneid);
		if (itFind != m_gateMap.end()) {
			m_gateMap.erase(itFind);
		}
	}

	this->removeEntity(pServer);
	
	return true;
}

// ��ӷ�����
bool ServerManager::addServer(Server* pServer)
{
	UINT zoneid = pServer->getZoneId();
	if (pServer->getType() == GatewayServer) {
		GatewayMapItr itFind = m_gateMap.find(zoneid);
		if (itFind == m_gateMap.end()) {
			return false;
		}
		ServerMapItr itFind2 = itFind->second.find(pServer->getID());
		if (itFind2 != itFind->second.end()) {
			return false;
		}
		itFind->second[pServer->getID()] = pServer;
	} else if (pServer->getType() == GameServer) {
		GatewayMapItr itFind = m_gateMap.find(zoneid);
		if (itFind == m_gateMap.end()) {
			map<UINT,Server*> serverMap;
			m_gateMap[zoneid] = serverMap;
		}
	}

	if ( !this->addEntity(pServer) )
		return false;

	return true;
}


Server* ServerManager::findGatewayServer(UINT zoneid)
{
	GatewayMapItr itFind = m_gateMap.find(zoneid);
	if (itFind == m_gateMap.end()) {
		return NULL;
	}

	/*
	Server* pServer = NULL;
	for (ServerMapItr it = itFind->second.begin(); it != itFind->second.end(); ++it) {
		pServer = it->second;
		break;
	}
	*/

	Server* pServer = NULL;
	if (!itFind->second.empty()) {
		pServer = itFind->second.begin()->second;
	}

	return pServer;
}





