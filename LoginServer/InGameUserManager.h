#pragma once
#include <EntityManager.h>
#include <Singleton.h>
#include "User.h"

// 以账号名为索引存放
class InGameUserManager : public Singleton<InGameUserManager>, public EntityManager<EntityManagerName>
{
public:
	InGameUserManager(void);
	virtual ~InGameUserManager(void);

	User* getUser(const char* name) { return (User*)getEntityByName(name); }

	// 删除指定游戏服务器ID的用户
	void deleteAllUserForGameServer(UINT serverId);

	// 删除指定网挂服务器ID的用户
	void deleteAllUserForGatewayServer(UINT serverId);
};
