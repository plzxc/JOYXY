#ifndef _SINGLETON_H
#define _SINGLETON_H

#include <cassert>


template <typename T> class Singleton
{
protected:
	static T* ms_Singleton;
	Singleton() { ms_Singleton = NULL; }

	~Singleton() { }

public:
	static void createSingleton()
	{
		ms_Singleton =  new T;
	}

	static void destroySingleton()
	{
		delete ms_Singleton;
		ms_Singleton = NULL;
	}

	static T& getSingleton()
	{ assert(ms_Singleton);  return (*ms_Singleton); }

	static T* getSingletonPtr()
	{ return (ms_Singleton); }
};

template <typename T> T* Singleton <T>::ms_Singleton = 0;


#endif
