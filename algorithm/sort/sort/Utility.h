#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <assert.h>

namespace utility
{
	inline int max(const std::vector<int>& a)
	{
		assert(!a.empty());

		int result = a[0];
		for (auto& n : a)
		{
			result = (n > result) ? n : result;
		}
		return result;
	}

	inline int min(const std::vector<int>& a)
	{
		assert(!a.empty());

		int result = a[0];
		for (auto& n : a)
		{
			result = (n < result) ? n : result;
		}
		return result;
	}

	template<typename T>
	bool loadArrayFromFile(const char* filename, std::vector<T>& array)
	{
		std::ifstream ifs(filename);
		if (ifs)
		{
			ifs.seekg(0, std::ios::end);
			int size = static_cast<int>(ifs.tellg());
			ifs.seekg(0, std::ios::beg);

			array.reserve(size);

			T t;
			while (ifs >> t)
			{
				array.push_back(t);
			}
		}
		else
		{
			std::cerr << "failed to open: " << filename << std::endl;
			return false;
		}

		return true;
	}

	template<typename T>
	bool saveArrayToFile(const char* filename, const std::vector<T>& a)
	{
		std::ofstream ofs(filename, std::ios::trunc);
		if (ofs)
		{
			for (auto& n : a)
			{
				ofs << n << endl;
			}
		}
		else
		{
			std::cerr << "failed to open: " << filename << std::endl;
			return false;
		}

		return true;
	}

	inline bool isSameFile(const char* filename1, const char* filename2)
	{
		std::ifstream ifs1(filename1);
		std::ifstream ifs2(filename2);
		if (ifs1 && ifs2)
		{
			int n1, n2;
			while (ifs1 >> n1 && ifs2 >> n2)
			{
				if (n1 != n2)
				{
					return false;
				}
			}
			ifs2 >> n2;
		}
		else
		{
			if (!ifs1) std::cerr << "failed to open: " << filename1 << std::endl;
			if (!ifs2) std::cerr << "failed to open: " << filename2 << std::endl;
			false;
		}

		return ifs1.eof() && ifs2.eof();
	}

	inline std::chrono::steady_clock::time_point now()
	{
		return std::chrono::steady_clock().now();
	}

	inline long long timeDifference(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end)
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	}
}