#pragma once
#include <vector>
#include <algorithm>

namespace sort
{
	inline void stdSort(std::vector<int>& a)
	{
		std::sort(a.begin(), a.end());
	}

}