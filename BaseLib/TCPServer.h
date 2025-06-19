#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include "TCPTask.h"
#include "IDAllocator.h"


struct stCmdData
{
	WORD		nClient;
	ByteBuffer	buffer;		// 发送/接收缓存

	stCmdData()
		: buffer(512)
	{
		nClient = INVALID_ID;
		buffer.clearBuffer();
	}
};


typedef map<WORD,TCPTask*> TaskMap;
typedef map<WORD,TCPTask*>::iterator TaskMapItr;

class TCPServer
{
public:
	virtual ~TCPServer(void){}

	// 初始化
	virtual bool Initialize(WORD nMaxClient, WORD nPort) = 0;

	// 终止服务
	virtual void Terminate() = 0;

	// 断开客户端
	virtual bool Disconnect(WORD nClient) = 0;

	// 发送数据
	virtual bool SendData(WORD nClient, void* data, DWORD len) = 0;

	// 打印运行信息
	virtual void PrintInfo() = 0;

	// 处理接收到的消息(在主线程中调用)
	virtual void HandleCommand() = 0;

protected:
	// 有新的客户端连接时，产生的事件
	virtual TCPTask* OnAccept(WORD nClient) = 0;

	// 客户端断开连接
	virtual bool OnClose(WORD nClient) = 0;

	// 接收到消息
	virtual int OnReceive(WORD nClient, void* pData, DWORD dwDataLen) = 0;

	// 错误报告
	virtual int OnError(WORD nClient, int iError, bool isSend) {return 0;}

	// 服务终止事件
	virtual int OnTerminate() {return 0;}
};


#endif