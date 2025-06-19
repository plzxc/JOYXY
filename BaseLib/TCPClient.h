#pragma once

class TCPClient
{
public:
	virtual ~TCPClient(void){}

	// 关闭服务
	virtual void Shutdown() = 0;

	// 连接服务器
	virtual bool Connect(const char* strIP, WORD nPort) = 0;

	// ping服务器
	virtual bool Ping() = 0;

	// 断开客户端
	virtual bool Disconnect() = 0;

	// 重新连接
	virtual bool Reconnect() = 0;

	// 是否正在连接中
	virtual bool IsWaitConnect() = 0;

	//判断是否和服务器处于连接状态
	virtual bool IsConnect() = 0;

	// 发送数据
	virtual bool SendData(void* data, DWORD len) = 0;

	// 打印运行信息
	virtual void PrintInfo() = 0;

	// 处理接收到的消息(在主线程中调用)
	virtual void HandleCommand() = 0;

protected:
	// 连接成功，产生的事件
	virtual bool OnConnect() = 0;

	// 断开连接，产生的事件
	virtual bool OnClose() = 0;

	// 接收到消息
	virtual int OnReceive(void* pData, DWORD dwDataLen) = 0;
};
