#pragma once
#include <vector>

namespace sort
{
	/*×î´ó»¯¶Ñ*/
inline void maxHeapify(std::vector<int>& a, int start, int end)
{
	int parent = start;
	int child = 2 * start + 1;
	while (child <= end)
	{
		if (child+1 <= end && a[child] < a[child + 1])
		{
			child++;
		}
		if (a[parent] >= a[child])
		{
			return;
		}
		else
		{
			std::swap(a[parent], a[child]);
			parent = child;
			child = 2 * parent + 1;
		}
	}
}

inline void heapSort(std::vector<int>& a)
{
	int len = static_cast<int>(a.size());
	for (int i = len/2-1; i >= 0; i--)
	{
		maxHeapify(a, i, len - 1);
	}

	for (int i = len - 1; i >= 0; i--)
	{
		std::swap(a[i], a[0]);
		maxHeapify(a, 0, i - 1);
	}
}

}