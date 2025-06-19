#pragma once

#ifndef __CTIME_H__
#define __CTIME_H__


// ����ʱ�䣬����ʱ��ת��
class LocalTime
{
public:
	LocalTime(){ memset(&m_tm,0,sizeof(m_tm)); }
	~LocalTime(){ }

	// ����Ӣ�ĸ�ʽ�������ַ���
    string getAscTime()
	{
		string strTime = ::asctime(&m_tm);
		return strTime;
	}

	// �������ĸ�ʽ�����ַ���
	string getStrTime()
	{
		char szBuf[256];
		sprintf(szBuf,"%04d��%02d��%02d�� %02d:%02d:%02d", 
			year(), month(), day(), 
			hour(),minute(),second());
		string strTime = szBuf;
		return strTime;
	}

	// �������ĸ�ʽ�����ַ���
	string getTimestamp()
	{
		char szBuf[256];
		sprintf(szBuf,"%04d-%02d-%02d %02d:%02d:%02d", 
			year(), month(), day(), 
			hour(),minute(),second());
		string strTime = szBuf;
		return strTime;
	}

	// ��
	int year() { return m_tm.tm_year + 1900; }

	// ��(1-12)
	int month() { return m_tm.tm_mon + 1; }

	// ��(1-31)
	int day() { return m_tm.tm_mday; }

	// ����(0-6)
	int weekday() { return m_tm.tm_wday; }

	// ��(0-365)
	int yday() { return m_tm.tm_yday; }

	// ʱ(0-23)
	int hour() { return m_tm.tm_hour; }
	
	// ��(0-59)
	int minute() { return m_tm.tm_min; }

	// ��(0-59)
	int second() { return m_tm.tm_sec; }

	// �ж��Ƿ���ͬһ��
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


// localtime ����ʱ��(����ʱ��ת��)
// gmtime	 ����ʱ��(δ����ʱ��ת��)
// ��ʵ��ʱ����
class RTime
{
public:
	RTime(void) { now(); }
	RTime(time_t time) { m_time = time; }
	virtual ~RTime(void) {}

	void time(time_t time) { m_time = time; }

	time_t time() { return m_time; }

	// ��¼��ǰʱ��
	void now() { m_time = ::time(NULL); }

	// ��ʵʱ��ת��Ϊ����
	time_t second() { return m_time; }

	// ��ñ���ʱ��(�����Ҫ�������ʱ�䣬�ȵ���now)
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
// �߾���ʱ��
class HighTime
{
public:
	HighTime() { if (!QueryPerformanceFrequency(&freq)) printf("ϵͳ��֧�ָ߾���ʱ��\n"); }
	virtual ~HighTime(){}

	// ��¼ʱ��
	void begin()
	{
		QueryPerformanceCounter(&lastTick);
	}

	// �õ���begin�����ڵ�΢��
	double end()
	{
		LARGE_INTEGER curTick;
		QueryPerformanceCounter(&curTick);
		double sec = ((double)curTick.QuadPart - (double)lastTick.QuadPart) / (double)freq.QuadPart;
		double mic = sec * 1000000.0f;	// ΢��
		return mic;
	}

private:
	LARGE_INTEGER freq;
	LARGE_INTEGER lastTick;
};

#endif

