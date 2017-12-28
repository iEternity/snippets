#pragma once
#include <string>
using namespace std;
/*
    文本串：BBC ABCDAB ABCDABCDABDE
    模式串：ABCDABD
    问题：在文本串中找出第一个匹配模式串的位置
    1. 针对模式串进行预处理，求出以每个字符为结尾的子串的最长的：前缀和后缀相同 的长度。
    如：
        pattern:    A   B   C   D   A   B   D
        next:       0   0   0   0   1   2   0
*/

int naiveStringSearch(const string& pattern, const string& text)
{
	int i = 0;	// 模式串pattern的下标
	int	j = 0;	// 文本串text的下标
	int patternLen = pattern.length();
	int textLen = text.length();

	while (i < patternLen && j < textLen)
	{
		// 相同则各前进一步
		if (pattern[i] == text[j])
		{
			i++;
			j++;
		}
		//	不相同则 i归0，j回到本次比较的起始位置的下一个位置
		else
		{
			j = j - i + 1;
			i = 0;
		}
	}

	if (i == patternLen)
	{
		return j - i;
	}
	else
	{
		return -1;
	}
}

void getNext(string pattern, int next[])
{
	next[0] = -1;
	next[1] = 0;
	int i = 1, j = 0;

	while (i < pattern.length())
	{
		if (j == -1 || pattern[i] == pattern[j])
		{
			i++;
			j++;
			next[i] = j;
			cout << j << endl;
		}
		else
		{
			j = next[j];
		}
	}
}

int kmpSearch(const string& pattern, const string& text)
{
	int patternLen = pattern.size();
	int textLen = text.size();
	int* next = new int[pattern.length() + 1];
	getNext(pattern, next);

	int i = 0, j = 0;
	while (i < textLen && j < patternLen)
	{
		if (j == -1 || pattern[j] == text[i])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}

	delete[] next;

	if (j == pattern.length())
	{
		return i - j;
	}

	return -1;
}