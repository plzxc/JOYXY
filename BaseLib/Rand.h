#pragma once

#ifndef __RAND_H__
#define __RAND_H__

class Rand
{
private:
	Rand();
	~Rand();

public:

	// 用时间来初始化随机数种子
	static void srand();

	// 取一个 0 - max(不包含max) 之间的随机数
	static int rand(int max);

	// 取得一个指定数之间的随机数(包含min和max)
	static int randRange(int min, int max);

	// 判断百分比概率(num/100)
	static bool randByPercent(int num);

	// 判断千分比概率(num/1000)
	static bool randByMilli(int num);

	// 判断万分比概率(num/10000)
	static bool randByMyria(int num);
};


#endif
