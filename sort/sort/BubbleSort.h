#pragma once
#include <vector>

namespace sort
{
	/*ц╟ещеепР*/
inline void bubbleSort(std::vector<int>& a)
{
	int len = static_cast<int>(a.size());
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				std::swap(a[j], a[j + 1]);
			}
		}
	}
}

}
