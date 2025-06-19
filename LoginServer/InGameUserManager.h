#pragma once
#include <EntityManager.h>
#include <Singleton.h>
#include "User.h"

// ���˺���Ϊ�������
class InGameUserManager : public Singleton<InGameUserManager>, public EntityManager<EntityManagerName>
{
public:
	InGameUserManager(void);
	virtual ~InGameUserManager(void);

	User* getUser(const char* name) { return (User*)getEntityByName(name); }

	// ɾ��ָ����Ϸ������ID���û�
	void deleteAllUserForGameServer(UINT serverId);

	// ɾ��ָ�����ҷ�����ID���û�
	void deleteAllUserForGatewayServer(UINT serverId);
};
