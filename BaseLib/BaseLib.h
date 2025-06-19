#ifndef __BASELIB_H__
#define __BASELIB_H__

#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����

// ϵͳ��ͷ�ļ�
#include <windows.h>
#include <winsock2.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include <process.h>

//#include "MemoryLeak.h"

// ��׼��ͷ�ļ�
#include <map>
#include <hash_map>
#include <stack>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

// ���ÿ�ͷ�ļ�
#include "Misc.h"
#include "PlatformTypes.h"
#include "IniParser.h"
#include "Singleton.h"
#include "Logger.h"
#include "SyncLock.h"
#include "MutexLock.h"
#include "Thread.h"
#include "CTime.h"
#include "Timer.h"
#include "ByteBuffer.h"
#include "Properties.h"
#include "Profiler.h"
#include "Rand.h"
#include "EntityManager.h"

#pragma comment(lib, "ws2_32.lib")

//#ifdef _DEBUG
//#include <vld.h>
//#endif

#endif
