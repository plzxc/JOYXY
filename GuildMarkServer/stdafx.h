// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once

#include "BaseLib.h"
#include "IOCPServer.h"
#include "SocketServer.h"
#include "Types.h"

//#define SERVER_CLASS	RakNetServer
//#define SERVER_CLASS	IOCPServer
#define SERVER_CLASS	SocketServer


// 限制只能单机
//#define LIMIT_LOCAL

// 自动注册
//#define AUTO_REGISTER



