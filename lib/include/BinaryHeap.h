#pragma once

#include <PriorityQueue.h>

template <typename T>
class BinaryHeap : public PriorityQueue<T>
{
public:
	virtual void insert(T t)
	{

	}

	virtual size_t size() const
	{
		return 0;
	}

	virtual T min()
	{
		return T();
	}

	virtual T deleteMin()
	{
		return T();
	}

private:
};