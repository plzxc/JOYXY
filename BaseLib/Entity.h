#pragma once

#ifndef __ENTITY_H__
#define __ENTITY_H__

// 同时以ID和Name为索引的对象
class Entity
{
public:
	Entity() : m_id(0),m_longId(0),m_name("") {}
	virtual ~Entity(void) {}

	void setID(DWORD id) { m_id = id; }
	DWORD getID() { return m_id; }

	void setLongID(DWORD longId) { m_longId = longId; }
	QWORD getLongID(){ return m_longId; }

	void setName(const char* name) { m_name = string(name); }
	//void setName(string& name) { m_name = name; }
	const char* getName() { return m_name.c_str(); }

private:
	DWORD m_id;
	QWORD m_longId;
	string m_name;
};

#endif


