#pragma once 
#include <vector>

namespace sort
{

	/*÷±Ω”≤Â»Î≈≈–Ú*/
inline void insertSort(std::vector<int>& a)
{
	int tmp, i, j;
	for (i = 1; i < (int)a.size(); i++)
	{
		tmp = a[i];
		for (j = i; j > 0 && tmp < a[j - 1]; --j)
		{
			a[j] = a[j-1];
		}
		a[j] = tmp;
	}
}


}