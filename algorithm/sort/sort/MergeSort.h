#pragma once
#include <vector>

namespace sort
{
	inline void mergeSortAux(std::vector<int>& a, std::vector<int>& result, int start, int end)
	{
		if (start >= end) return;

		int mid = (start + end) / 2;
		mergeSortAux(a, result, start, mid);
		mergeSortAux(a, result, mid + 1, end);

		result.clear();
		int i = start, j = mid + 1;
		while (i <= mid && j <= end)
		{
			if (a[i] <= a[j])
			{
				result.push_back(a[i++]);
			}
			else
			{
				result.push_back(a[j++]);
			}
		}

		while (i <= mid) result.push_back(a[i++]);
		while (j <= end) result.push_back(a[j++]);

		for (int i = start; i <= end; i++)
		{
			a[i] = result[i - start];
		}
	}

	inline void mergeSort(std::vector<int>& a)
	{
		int len = static_cast<int>(a.size());

		std::vector<int> result;
		result.reserve(len);
		
		mergeSortAux(a, result, 0, len-1);
	}

}
