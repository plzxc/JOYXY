#ifndef __PROFILER_H__
#define __PROFILER_H__


#define OPEN_PF


// �������ܷ�����ʹ��ͳһ�ĳ�ʱʱ��
#ifdef OPEN_PF
	#define FUNC_PF(log) FuncProfiler pf(log, 0);
#else
	#define FUNC_PF(log)
#endif

// �������ܷ�����ʹ��ָ���ĳ�ʱʱ��
#ifdef OPEN_PF
	#define FUNC_PF_EXT(log, time)	FuncProfiler pf(log, time);
#else
	#define FUNC_PF_EXT(log, time)
#endif



#ifdef OPEN_PF
	#define CODE_PF_BEGIN()			Profiler::getSingleton().begin();
	#define CODE_PF_END(log)	Profiler::getSingleton().end(log);
#else
	#define CODE_PF_BEGIN()
	#define CODE_PF_END(log)
#endif


/************************************************************************/
/* �������ܷ����ࣨ��ȷ��΢�                                                                     */
/************************************************************************/
class FuncProfiler
{
public:
	//FuncProfiler(const char* log, double timeout = 0);
	FuncProfiler(const char* log, DWORD timeout = 0);
	virtual ~FuncProfiler();

private:
	string m_strLog;
	//double m_timeout;
	//LARGE_INTEGER m_feq;
	//LARGE_INTEGER m_lastTick;
	DWORD m_timeout;
	DWORD m_lastTick;
};




/************************************************************************/
/* ��������ܷ����ࣨ��ȷ��΢�                                                                     */
/************************************************************************/
struct stPF
{
	//LARGE_INTEGER lastTick;
	DWORD lastTick;
};

class Profiler : public Singleton<Profiler>
{
public:
	Profiler(void);
	virtual ~Profiler(void);

	/**
	 * @brief	��¼��ʼʱ��
	 * @param	
	 * @return	
	*/
	void begin();

	/**
	 * @brief	��������ʱ��
	 * @param	log	��־˵��
	 * @param	timeout ��ʱʱ��,Ĭ����������������жϳ�ʱ
	 * @return	
	*/
	//void end(const char* log, double timeout = 0);
	void end(const char* log, DWORD timeout = 0);

	/**
	 * @brief	������־���
	 * @param	
	 * @return	
	*/
	void openLog() { m_isLogOpened = true; }

	/**
	 * @brief	�ر���־���
	 * @param	
	 * @return	
	*/
	void closeLog() { m_isLogOpened = false; }

	/**
	 * @brief	�ж�����־����Ƿ���
	 * @param	
	 * @return	
	*/
	bool isLogOpened() { return m_isLogOpened; }

	/**
	 * @brief	���ó�ʱʱ��
	 * @param	
	 * @return	
	*/
	//void setTimeout(double timeout) { m_timeout = timeout; }
	void setTimeout(DWORD timeout) { m_timeout = timeout; }

	/**
	 * @brief	ȡ�ó�ʱʱ��
	 * @param	
	 * @return	
	*/
	//double getTimeout() { return m_timeout; }
	DWORD getTimeout() { return m_timeout; }

private:
	bool m_isLogOpened;
	DWORD m_timeout;
	DWORD m_lastTick;
	//double m_timeout;
	//LARGE_INTEGER m_feq;
	stack<stPF> m_fpItems;
};



#endif