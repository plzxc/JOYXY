#pragma once
#include <EntityManager.h>
#include <Singleton.h>
#include "User.h"

// ���˺���Ϊ�������
class LoginedUserManager : public Singleton<LoginedUserManager>, public EntityManager<EntityManagerName>
{
public:
	LoginedUserManager(void);
	virtual ~LoginedUserManager(void);

	User* getUser(const char* account) { return (User*)getEntityByName(account); }
};
