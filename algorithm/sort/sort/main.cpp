#pragma warning(disable:4996)
#include <iostream>
#include <chrono>
#include <vector>
#include <functional>
#include <algorithm>
#include "Utility.h"
#include "STDSort.h"
#include "STDQsort.h"
#include "InsertSort.h"
#include "ShellSort.h"
#include "SelectSort.h"
#include "BubbleSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "HeapSort.h"
#include "RadixSort.h"
#include "CountingSort.h"
#include "BucketSort.h"
#include "MultiThreadSort.h"

using namespace std;

const string pathPrefix = "TestData/";

using SortFunction = std::function < void(std::vector<int>&)>;

void initDirectory();
std::string testSort(const SortFunction& sortFunction, const std::string& filename, const std::string& tag);

int main()
{
	initDirectory();

	std::vector<string> files =
	{
		"data_10000",
		"data_100000",
		"data_500000",
		"data_1000000"
	};

	std::vector<std::string> outputFiles;
	for (auto& filename : files)
	{
		outputFiles.push_back(testSort(sort::stdSort,		filename, "01-stdSort"));
		outputFiles.push_back(testSort(sort::stdQsort,		filename, "02-stdQsort"));
		outputFiles.push_back(testSort(sort::insertSort,	filename, "03-insertSort"));
		outputFiles.push_back(testSort(sort::shellSort,		filename, "04-shellSort"));
		outputFiles.push_back(testSort(sort::selectSort,	filename, "05-selectSort"));
		outputFiles.push_back(testSort(sort::bubbleSort,	filename, "06-bubbleSort"));
		outputFiles.push_back(testSort(sort::quickSort,		filename, "07-quickSort"));
		outputFiles.push_back(testSort(sort::mergeSort,		filename, "08-mergeSort"));
		outputFiles.push_back(testSort(sort::heapSort,		filename, "09-heapSort"));
		outputFiles.push_back(testSort(sort::radixSort,		filename, "10-radixSort"));
		outputFiles.push_back(testSort(sort::countingSort,	filename, "11-countingSort"));
		outputFiles.push_back(testSort(sort::bucketSort,	filename, "12-bucketSort"));
		outputFiles.push_back(testSort(sort::multiThreadSort, filename, "13-multiThreadSort"));

		cout << "标准结果： " << outputFiles[0].data() << endl;
		for (int i = 1; i < (int)outputFiles.size(); i++)
		{
			if (utility::isSameFile(outputFiles[0].data(), outputFiles[i].data()))
			{
				cout << "结果正确： " << outputFiles[i].data() << endl;
			}
			else
				cerr << "结果错误： " << outputFiles[i].data() << endl;
		}
		cout << endl;
		outputFiles.clear();
	}

	system("pause");
}

void initDirectory()
{
	const char* cmd =
		"if not exist TestData\\output\\ "
		"(mkdir TestData\\output\\)"
		"else (del TestData\\output\\* /q)";
	::system(cmd);
}

std::string testSort(const SortFunction& sortFunction, const std::string& filename, const std::string& tag)
{
	std::string filepath = pathPrefix + filename;
	vector<int> a;

	utility::loadArrayFromFile(filepath.c_str(), a);

	auto start = utility::now();
	sortFunction(a);
	auto end = utility::now();
	auto elapsed = utility::timeDifference(start, end);

	char buf[128];
	_snprintf_s(buf, sizeof buf, "%soutput/%s_%I64dms_%s",
				pathPrefix.c_str(),
				tag.c_str(),
				elapsed,
				filename.c_str());
	utility::saveArrayToFile(buf, a);
	return buf;
}

