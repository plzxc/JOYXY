#pragma once
#include <EntityManager.h>
#include <Singleton.h>
#include "User.h"

// 以账号名为索引存放
class LoginedUserManager : public Singleton<LoginedUserManager>, public EntityManager<EntityManagerName>
{
public:
	LoginedUserManager(void);
	virtual ~LoginedUserManager(void);

	User* getUser(const char* account) { return (User*)getEntityByName(account); }
};
