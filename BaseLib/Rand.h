#pragma once

#ifndef __RAND_H__
#define __RAND_H__

class Rand
{
private:
	Rand();
	~Rand();

public:

	// ��ʱ������ʼ�����������
	static void srand();

	// ȡһ�� 0 - max(������max) ֮��������
	static int rand(int max);

	// ȡ��һ��ָ����֮��������(����min��max)
	static int randRange(int min, int max);

	// �жϰٷֱȸ���(num/100)
	static bool randByPercent(int num);

	// �ж�ǧ�ֱȸ���(num/1000)
	static bool randByMilli(int num);

	// �ж���ֱȸ���(num/10000)
	static bool randByMyria(int num);
};


#endif
