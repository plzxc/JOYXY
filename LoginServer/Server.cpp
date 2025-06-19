#include "StdAfx.h"
#include "server.h"

Server::Server(void)
{
	m_state = SS_Free;
	m_isNew = FALSE;
	m_strIP = "0.0.0.0";
	m_port = 0;
	m_onlineNum = 0;
	m_maxNum = 1000;
	m_zoneid = 0;
}

Server::~Server(void)
{
}

void Server::setType(ServerType type)
{
	m_type = type;
}

ServerType Server::getType()
{
	return m_type;
}

void Server::setState(ServerState state)
{
	m_state = state;
}

ServerState Server::getState()
{
	return m_state;
}

void Server::setZoneId(UINT zoneid)
{
	m_zoneid = zoneid;
}

UINT Server::getZoneId()
{
	return m_zoneid;
}

void Server::setIsNew(BOOL isNew)
{
	m_isNew = isNew;
}

BOOL Server::isNew()
{
	return m_isNew;
}

void Server::setIP(const char* ip)
{
	m_strIP = ip;
}

const char* Server::getIP()
{
	return m_strIP.c_str();
}

void Server::setPort(WORD port)
{
	m_port = port;
}

WORD Server::getPort()
{
	return m_port;
}

void Server::setOnlineNum(DWORD num)
{
	m_onlineNum = num;
}

DWORD Server::getOnlineNum()
{
	return m_onlineNum;
}

void Server::setMaxNum(DWORD num)
{
	m_maxNum = num;
}

DWORD Server::getMaxNum()
{
	return m_maxNum;
}

