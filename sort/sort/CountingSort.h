#pragma once
#include <vector>
#include "Utility.h"

namespace sort
{
	
	inline void countingSort(std::vector<int>& a)
	{
		int maxNum = utility::max(a);
		int minNum = utility::min(a);

		std::vector<int> counts(maxNum - minNum + 1);
		for (auto& n : a)
		{
			counts[n - minNum]++;
		}

		int count = 0, size = (int)counts.size();
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < counts[i]; j++)
			{
				a[count++] = minNum + i;
			}
		}
	}
}
