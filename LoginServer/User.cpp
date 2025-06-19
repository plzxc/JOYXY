#include "StdAfx.h"
#include ".\user.h"
#include "LoginedUserManager.h"
#include "InGameUserManager.h"
#include "LoginTimeTick.h"


class TimeForUnregUser : public TimerEvent
{
public:
	TimeForUnregUser(DWORD elapse) : TimerEvent(elapse) {}
	virtual ~TimeForUnregUser(void){}

	string m_account;

protected:
	virtual bool onTimer()
	{
		User* user = NULL;
		user = LoginedUserManager::getSingleton().getUser(m_account.c_str());
		if (user == NULL) {
			user = InGameUserManager::getSingleton().getUser(m_account.c_str());
		}
		if (user) {
			user->disconnect(0);
		}
		return false;
	}
};



char SKeyTable[]=
{
		'0','1','2','3','4','5','6','7','8','9',
		'a','b','c','d','e','f','g','h','i','j',
		'k','l','m','n','o','p','q','r','s','t',
		'u','v','w','x','y','z',
		'A','B','C','D','E','F','G','H','I','J',
		'K','L','M','N','O','P','Q','R','S','T',
		'U','V','W','X','Y','Z'
};



User::User(LoginTask* task)
{
	m_zoneId = 0;
	m_gatewayId = 0;
	m_loginTimes = 0;
	m_task = task;
	ZeroMemory(m_key, sizeof(m_key));
	ZeroMemory(m_ip, sizeof(m_ip));
}

User::~User(void)
{
	m_task = NULL;
}



void User::GenerateKey()
{
	int keyNum = sizeof(SKeyTable)/sizeof(char);
	for (int i=0; i<sizeof(m_key)-1; i++)
		((byte*)m_key)[i] = SKeyTable[rand()%keyNum];
}

const char* User::getKey()
{
	return m_key;
}

void User::setIP(const char* ip)
{
	strncpy(m_ip, ip, MAX_IP_SIZE);
}

const char* User::getIP()
{
	return m_ip;
}

void User::setZoneId(UINT zonid)
{
	m_zoneId = zonid;
}

UINT User::getZoneId()
{
	return m_zoneId;
}

void User::setGatewayId(UINT gatewayid)
{
	m_gatewayId = gatewayid;
}

UINT User::getGatewayId()
{
	return m_gatewayId;
}

void User::setLoginTimes(UINT times)
{
	m_loginTimes = times;
}

UINT User::getLoginTimes()
{
	return m_loginTimes;
}

LoginTask* User::getLoginTask()
{
	return m_task;
}

bool User::sendCmd(void* pCmd, UINT cmdLen)
{
	if (m_task) 
		return m_task->sendCmd(pCmd, cmdLen);

	return false;
}

void User::disconnect(DWORD delay)
{
	if (delay == 0) {
		if (m_task) {
			try
			{
				m_task->disconnect();
				m_task = NULL;
			}
			catch (...)
			{
				printf("断开,意外的异常");	
			}
		}
	} else {
		TimeForUnregUser* event = new TimeForUnregUser(delay*1000);
		event->m_account = getName();
		LoginTimeTick::getSingleton().addTimer(event);
	}
}

