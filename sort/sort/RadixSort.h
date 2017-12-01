#pragma once
#include <vector>

namespace sort
{
/*
	������� 877��455��644��837��494��174��53��������
	��һ�����򣨸�λ��		�ڶ�������ʮλ��		���������򣨰�λ��
	053					837					053
	644					644					174
	494					053					455
	174					455					644
	455					174					794
	877					877					837
	837					794					877
*/


	/*����������ݵ����λ��*/
	inline int maxBit(std::vector<int>& a)
	{
		if (a.empty()) return 0;

		int max = a[0];
		for (auto n : a)
		{
			max = n > max ? n : max;
		}

		int result = 0;
		while (max > 0)
		{
			result++;
			max /= 10;
		}

		return result;
	}

	/*�������*/
	template<typename T, int size>
	void zeroArray(T (&array)[size])
	{
		for (int i = 0; i < size; i++)
		{
			array[i] = 0;
		}
	}

	/*��������*/
	inline void radixSort(std::vector<int>& a)
	{
		int size = static_cast<int>(a.size());
		int bitCount = maxBit(a);	//�������������λ��
		int radix = 1, k, j;
		int count[10]; //ͳ�Ƹ���
		std::vector<int> tmp(size);	//��ʱ����

		for (int i = 0; i < bitCount; i++)	//�ӵ�λ����λ������ÿλ��ֵ��ÿ������������
		{
			zeroArray(count);

			for (j = 0; j < size; j++)	//����ÿ����
			{
				k = (a[j] / radix) % 10;
				count[k]++;
			}

			for (j = 1; j < 10; j++)
			{
				count[j] += count[j - 1];
			}

			for (j = size-1; j >= 0; j--)
			{
				k = (a[j] / radix) % 10;
				tmp[count[k]-1] = a[j];
				count[k]--;
			}

			std::swap(a, tmp);

			radix *= 10;
		}
	}

}