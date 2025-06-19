#pragma once

#ifndef __TCPTASK_H__
#define __TCPTASK_H__

#include "ByteBuffer.h"
//#include <winsock2.h>

enum TaskState
{
	notuse = 0,	// 刚建立连接
	verify,		// 等待验证
	okay,		// 建立稳定连接
	recycle,	// 回收连接
};


// 处理消息的接口
class MessageHandle
{
public:
	MessageHandle(){}
	virtual ~MessageHandle(){}
	virtual bool processMessage(void *data, DWORD cmdLen) = 0;
};


class TCPServer;

// 默认数据包格式
// WORD | BIN
// Size | Datas
// 前两个字节代表大小，后面是指定长度的数据

class TCPTask : public MessageHandle
{
public:
	TCPTask(WORD id, TCPServer* pTCPServer);
	virtual ~TCPTask(void);

	// 取得分配的ID号
	WORD getID();

	// 获得SOCKET句柄
	//SOCKET getSocket();

	// 获得IP地址
	const char* getIP();

	// 关闭连接
	void disconnect();

	// 进入下一个状态
	void enterNextState();

	// 发送数据(原样数据发送，不做任何处理)
	virtual bool sendData(void* data, DWORD len);

	// 发送数据(处理后发送，处理： 前两个字节表示长度，后面跟数据)
	virtual bool sendCmd(void* pCmd, UINT cmdLen);

	// 回收连接
	virtual void recycleTask();

	// 能否回收连接
	virtual bool canRecycle();

	// 处理连接事件
	virtual bool OnAccept() {return true;}

	// 处理关闭事件
	virtual bool OnClose() {return true;}

public:
	// 关闭消息发送(系统底层使用，外层不要调用此函数)
	// 设置此状态后，将不处理消息发送
	void closeSendMsg() { m_isCanSendMsg = false; }

	// 是否是断开状态
	bool isCanSendMsg() { return m_isCanSendMsg; }

	// 处理接收到的数据
	virtual bool processRecvData(void* data, DWORD len);

	// 分析拆解收到的数据，并放入队列中
	virtual bool parseRecvData();

	// 处理处理过的消息数据
	virtual bool processMessage(void *data, DWORD cmdLen){return true;}

	void setIP(const char* strIP);

private:
	TaskState m_state;
	WORD m_id;
	DWORD m_recycleTick;
	//SOCKET m_hSocket;
	char m_szIP[20];
	bool m_isCanSendMsg;	// 是否可以发送消息
	

protected:
	ByteBuffer* m_recvBuffer;
	TCPServer* m_pTCPServer;
};


#endif
