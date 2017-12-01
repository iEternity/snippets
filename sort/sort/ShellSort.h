#pragma once
#include <vector>
// 23, 4, 6, 66, 54, 34, 22, 99
namespace sort
{
	/*Ï£¶ûÅÅÐò*/
inline void shellSort(std::vector<int>& a)
{
	int len = (int)a.size();
	int step = len >> 1;
	while (step > 0)
	{
		for (int i = 0; i < step; i++)
		{
			for (int j = i + step; j < len; j += step)
			{
				int tmp = a[j], k = 0;
				for (k = j; k - step >= 0 && tmp < a[k-step]; k -= step)
				{
					a[k] = a[k - step];
				}
				a[k] = tmp;
			}
		}

		step >>= 1;
	}
}

}