#include "StdAfx.h"
#include ".\ingameusermanager.h"

InGameUserManager::InGameUserManager(void)
{
}

InGameUserManager::~InGameUserManager(void)
{
}


void InGameUserManager::deleteAllUserForGameServer(UINT serverId)
{
	struct stDeleteUser : public stCallBack<User> 
	{
		vector<User*>* m_vecRemove;
		UINT m_gameSvrID;
		stDeleteUser(UINT gameSvrID, vector<User*>* vecRemove2) 
			: m_gameSvrID(gameSvrID), m_vecRemove(vecRemove2)  {}
			virtual bool exec(User* pUser)
			{
				if (pUser->getZoneId() == m_gameSvrID) {
					m_vecRemove->push_back(pUser);
				}
				return true;
			}
	};

	vector<User*> vecRemove;
	stDeleteUser cb(serverId, &vecRemove);
	this->exec(cb);

	while(!vecRemove.empty()) {
		User* pUser = vecRemove[vecRemove.size()-1];
		vecRemove.pop_back();
		this->removeEntity(pUser);
		SAFE_DELETE(pUser);
	}
}



void InGameUserManager::deleteAllUserForGatewayServer(UINT serverId)
{
	struct stDeleteUser : public stCallBack<User> 
	{
		vector<User*>* m_vecRemove;
		UINT m_gameSvrID;
		stDeleteUser(UINT gameSvrID, vector<User*>* vecRemove2) 
			: m_gameSvrID(gameSvrID), m_vecRemove(vecRemove2)  {}
			virtual bool exec(User* pUser)
			{
				if (pUser->getGatewayId() == m_gameSvrID) {
					m_vecRemove->push_back(pUser);
				}
				return true;
			}
	};

	vector<User*> vecRemove;
	stDeleteUser cb(serverId, &vecRemove);
	this->exec(cb);

	while(!vecRemove.empty()) {
		User* pUser = vecRemove[vecRemove.size()-1];
		vecRemove.pop_back();
		this->removeEntity(pUser);
		SAFE_DELETE(pUser);
	}
}











