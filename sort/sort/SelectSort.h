#pragma once
#include <vector>

namespace sort
{
	/*ºÚµ•—°‘Ò≈≈–Ú*/
inline void selectSort(std::vector<int>& a)
{
	int min, minPos;
	int len = (int)a.size();
	for (int i = 1; i < len; i++)
	{
		min = a[i-1];
		minPos = i - 1;
		for (int j = i; j < len; j++)
		{
			if (a[j] < min)
			{
				min = a[j];
				minPos = j;
			}
		}
		
		a[minPos] = a[i - 1];
		a[i - 1] = min;
	}
}

}