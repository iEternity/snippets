#pragma once
#include <vector>
#include <stack>

namespace sort
{

	struct Range
	{
		int left;
		int right;
		Range(int l, int r) :left(l), right(r){};
	};

	/*递归版本，可能会栈溢出*/
void quickSortAux(std::vector<int>& a, int left, int right)
{
	if (left >= right) return;
	int i = left, j = right - 1;
	int pivot = a[right];
	while (i < j)
	{
		while (i < j && a[i] < pivot) i++;
		while (i < j && a[j] >= pivot) j--;
		std::swap(a[i], a[j]);
	}

	if (a[i] >= pivot)
	{
		std::swap(a[i], a[right]);
	}
	else
	{
		i++;
	}

	quickSortAux(a, left, i - 1);
	quickSortAux(a, i+1, right);
}

/*非递归版本*/
inline void quickSort(std::vector<int>& a)
{
	int size = static_cast<int>(a.size());
	std::stack<Range> ranges;
	ranges.emplace(0, size - 1);

	int left, right, i, j, pivot;
	while (!ranges.empty())
	{
		left = ranges.top().left;
		right = ranges.top().right;
		ranges.pop();

		pivot = a[right];
		i = left, j = right;

		while (i < j)
		{
			while (i < j && a[i] < pivot) i++;
			while (i < j && a[j] >= pivot) j--;

			std::swap(a[i], a[j]);
		}

		if (a[i] >= pivot)
		{
			std::swap(a[i], a[right]);
		}
		else
		{
			i++;
		}

		if (left < i - 1) ranges.emplace(left, i - 1);
		if (right > i+1) ranges.emplace(i+1, right);
	}
}

}
