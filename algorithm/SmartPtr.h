// 2017.12.22
#include <iostream>
using namespace std;

template<typename T>
class SmartPtr
{
public:
	SmartPtr(T* ptr):
		count_(new int(1)),
		ptr_(ptr)
	{
	}

	SmartPtr(SmartPtr& other)
	{
		ptr_ = other.ptr_;
		count_ = other.count_;
		(*count_)++;
	}

	SmartPtr& operator=(SmartPtr& other)
	{
		(*(other.count_))++;

		countDown();

		ptr_ = other.ptr_;
		count_ = other.count_;

		return *this;
	}

	~SmartPtr()
	{
		countDown();
	}

	T* operator->() const
	{
		return ptr_;
	}

	T& operator*()
	{
		return *ptr;
	}

private:
	void countDown()
	{
		--*count_;
		if (*count_ == 0)
		{
			if (ptr_)
			{
				delete ptr_;
			}
			delete count_;

			ptr_ = nullptr;
			count_ = nullptr;
			cout << "引用计数为0，释放对象！" << endl;
		}
	}

private:
	int*	count_;
	T*		ptr_;
};


class Test
{
public:
	Test() { cout << "ctor" << endl; }
	~Test() { cout << "dtor" << endl; }
};

void test()
{
	using Ptr = SmartPtr<Test>;
	{
		Ptr p1 = new Test();
		Ptr p2(p1);
		Ptr p3 = new Test();
		p3 = p2;
	}
	SmartPtr<Test> p = nullptr;
}

