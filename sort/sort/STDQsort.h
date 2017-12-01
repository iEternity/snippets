#pragma once
#include <vector>

namespace sort
{

inline void stdQsort(std::vector<int>& a)
{
	std::qsort(&*a.begin(), a.size(), sizeof(int),
		[](const void* a, const void* b)->int
	{
		return (*(int*)a) - (*(int*)b);
	}
	);
}

}