#pragma once

#include <cstddef>

template <typename T>
struct PQElement
{
    T value;
    int key;

    PQElement()
    {
        key = -1;
    }

    PQElement(T v, int k)
    {
        value = v;
        key = k;
    }
};

template<typename T>
bool operator==(PQElement<T> a, PQElement<T> b)
{
    return a.key == b.key && a.value == b.value;
}

template <typename T>
class PriorityQueue
{
public:
    virtual void insert(PQElement<T> e) = 0;
	virtual size_t size() const = 0;
    virtual PQElement<T> min() = 0;
    virtual PQElement<T> deleteMin() = 0;
};
