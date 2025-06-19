#ifndef __BASELIB_H__
#define __BASELIB_H__

#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料

// 系统库头文件
#include <windows.h>
#include <winsock2.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include <process.h>

//#include "MemoryLeak.h"

// 标准库头文件
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

// 常用库头文件
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
