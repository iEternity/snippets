#pragma once
#include <vector>

namespace sort
{
/*
	假设针对 877，455，644，837，494，174，53进行排序
	第一次排序（个位）		第二次排序（十位）		第三次排序（百位）
	053					837					053
	644					644					174
	494					053					455
	174					455					644
	455					174					794
	877					877					837
	837					794					877
*/


	/*待排序的数据的最大位数*/
	inline int maxBit(std::vector<int>& a)
	{
		if (a.empty()) return 0;

		int max = a[0];
		for (auto n : a)
		{
			max = n > max ? n : max;
		}

		int result = 0;
		while (max > 0)
		{
			result++;
			max /= 10;
		}

		return result;
	}

	/*清空数组*/
	template<typename T, int size>
	void zeroArray(T (&array)[size])
	{
		for (int i = 0; i < size; i++)
		{
			array[i] = 0;
		}
	}

	/*基数排序*/
	inline void radixSort(std::vector<int>& a)
	{
		int size = static_cast<int>(a.size());
		int bitCount = maxBit(a);	//所有数据中最长的位数
		int radix = 1, k, j;
		int count[10]; //统计个数
		std::vector<int> tmp(size);	//临时数组

		for (int i = 0; i < bitCount; i++)	//从低位到高位依次以每位的值对每个数进行排序
		{
			zeroArray(count);

			for (j = 0; j < size; j++)	//遍历每个数
			{
				k = (a[j] / radix) % 10;
				count[k]++;
			}

			for (j = 1; j < 10; j++)
			{
				count[j] += count[j - 1];
			}

			for (j = size-1; j >= 0; j--)
			{
				k = (a[j] / radix) % 10;
				tmp[count[k]-1] = a[j];
				count[k]--;
			}

			std::swap(a, tmp);

			radix *= 10;
		}
	}

}