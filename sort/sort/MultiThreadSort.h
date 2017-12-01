#pragma once
#include <vector>
#include <thread>
#include <algorithm>

namespace sort
{
#define THREAD_NUM 8

inline void sortThreadFunc(int* start, int* end)
{
	std::sort(start, end);
}

inline void multiThreadSort(std::vector<int>& a)
{
	int size = static_cast<int>(a.size());
	int gap = size / THREAD_NUM + 1;

	int *start, *end;
	std::vector<std::thread> threads;
	threads.reserve(THREAD_NUM);

	
	int* startAddrs[THREAD_NUM];	//ÿ���߳�����������ݵ���ʼ��ַ
	int* endAddrs[THREAD_NUM];		//ÿ���߳�����������ݵĽ�����ַ

	for (int i = 0; i < THREAD_NUM; i++)
	{
		start = &*a.begin() + i * gap;
		end = ((start + gap) < &*a.end()) ? (start + gap) : &*a.end();
		startAddrs[i] = start;
		endAddrs[i] = end;
		threads.emplace_back(sortThreadFunc, start, end);
	}

	for (auto& t : threads)
	{
		t.join();
	}

	//�ϲ����̵߳�������
	std::vector<int> result;
	result.reserve(size);

	int min, pos;
	for (int i = 0; i < size; i++)//	����ÿ���̵߳�������
	{
		min = INT32_MAX;
		for (int j = 0; j < THREAD_NUM; j++)//����ÿ���߳�
		{
			if (startAddrs[j] < endAddrs[j] && *startAddrs[j] < min)
			{
				min = *startAddrs[j];
				pos = j;
			}
		}
		startAddrs[pos]++;
		result.push_back(min);
	}

	a = std::move(result);
}

}