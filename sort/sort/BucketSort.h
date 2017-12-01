#pragma once
#include <vector>
#include <cmath>
#include "Utility.h"

namespace sort
{
	struct ListNode
	{
		int val;
		ListNode* next;
		ListNode(int v = 0) :val(v), next(nullptr){};
	};

	inline void insert(ListNode*& head, int val)
	{
		if (head == nullptr)
		{
			head = new ListNode(val);
			return;
		}

		if (head->val >= val)
		{
			ListNode* p = new ListNode(val);
			p->next = head;
			head = p;
			return;
		}

		ListNode* cur = head ->next, *pre = head;
		while (cur)
		{
			if (cur->val >= val)
			{
				ListNode* node = new ListNode(val);
				node->next = cur;
				pre->next = node;
				return;
			}
			pre = cur;
			cur = cur->next;
		}

		pre->next = new ListNode(val);
	}

	inline void deleteList(ListNode* h)
	{
		ListNode* t = nullptr;
		while (h)
		{
			t = h->next;
			delete h;
			h = t;
		}
	}

	inline void bucketSort(std::vector<int>& a)
	{
		int size = static_cast<int>(a.size());

		int minV = utility::min(a);
		int maxV = utility::max(a);
		int bucketCount = (int)sqrt(maxV - minV) + 1;
		std::vector<ListNode*> buckets(bucketCount, nullptr);

		int index;
		for (auto& n : a)
		{
			index = (n-minV) / bucketCount;
			insert(buckets.at(index), n);
		}

		index = 0;
		ListNode* t = nullptr;
		for (int i = 0; i < bucketCount; i++)
		{
			t = buckets[i];
			while (t)
			{
				a[index++] = t->val;
				t = t->next;
			}
		}

		for (int i = 0; i < bucketCount;i++)
		{
			deleteList(buckets[i]);
		}
	}
}