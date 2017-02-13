#pragma once

template <typename T>
class PriorityQueue
{
public:
	virtual void insert(T t) = 0;
	virtual size_t size() const = 0;
	virtual T min() = 0;
	virtual T deleteMin() = 0;
};