#pragma once

#ifndef __CTIME_H__
#define __CTIME_H__


// 本地时间，经过时区转换
class LocalTime
{
public:
	LocalTime(){ memset(&m_tm,0,sizeof(m_tm)); }
	~LocalTime(){ }

	// 返回英文格式的日期字符串
    string getAscTime()
	{
		string strTime = ::asctime(&m_tm);
		return strTime;
	}

	// 返回中文格式日期字符串
	string getStrTime()
	{
		char szBuf[256];
		sprintf(szBuf,"%04d年%02d月%02d日 %02d:%02d:%02d", 
			year(), month(), day(), 
			hour(),minute(),second());
		string strTime = szBuf;
		return strTime;
	}

	// 返回中文格式日期字符串
	string getTimestamp()
	{
		char szBuf[256];
		sprintf(szBuf,"%04d-%02d-%02d %02d:%02d:%02d", 
			year(), month(), day(), 
			hour(),minute(),second());
		string strTime = szBuf;
		return strTime;
	}

	// 年
	int year() { return m_tm.tm_year + 1900; }

	// 月(1-12)
	int month() { return m_tm.tm_mon + 1; }

	// 日(1-31)
	int day() { return m_tm.tm_mday; }

	// 星期(0-6)
	int weekday() { return m_tm.tm_wday; }

	// 天(0-365)
	int yday() { return m_tm.tm_yday; }

	// 时(0-23)
	int hour() { return m_tm.tm_hour; }
	
	// 分(0-59)
	int minute() { return m_tm.tm_min; }

	// 秒(0-59)
	int second() { return m_tm.tm_sec; }

	// 判断是否是同一天
	bool isSameDay(LocalTime& localTime)
	{
		if (localTime.year() == year() &&
			localTime.month() == month() && 
			localTime.day() == day())
		{
			return true;
		}

		return false;
	}

public:
	tm m_tm;
};


// localtime 当地时间(经过时区转换)
// gmtime	 世界时间(未经过时区转换)
// 真实的时间类
class RTime
{
public:
	RTime(void) { now(); }
	RTime(time_t time) { m_time = time; }
	virtual ~RTime(void) {}

	void time(time_t time) { m_time = time; }

	time_t time() { return m_time; }

	// 记录当前时间
	void now() { m_time = ::time(NULL); }

	// 真实时间转换为秒数
	time_t second() { return m_time; }

	// 获得本地时间(如果想要获得最新时间，先调用now)
	LocalTime getLocalTime()
	{
		LocalTime sysTime;
		sysTime.m_tm = *::localtime(&m_time);
		return sysTime;
	}

private:
	time_t m_time;
};


// high time
// 高精度时间
class HighTime
{
public:
	HighTime() { if (!QueryPerformanceFrequency(&freq)) printf("系统不支持高精度时钟\n"); }
	virtual ~HighTime(){}

	// 记录时间
	void begin()
	{
		QueryPerformanceCounter(&lastTick);
	}

	// 得到从begin到现在的微妙
	double end()
	{
		LARGE_INTEGER curTick;
		QueryPerformanceCounter(&curTick);
		double sec = ((double)curTick.QuadPart - (double)lastTick.QuadPart) / (double)freq.QuadPart;
		double mic = sec * 1000000.0f;	// 微妙
		return mic;
	}

private:
	LARGE_INTEGER freq;
	LARGE_INTEGER lastTick;
};

#endif

