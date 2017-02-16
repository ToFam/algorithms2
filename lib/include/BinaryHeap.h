#pragma once

#include <PriorityQueue.h>

template <typename T>
class BinaryHeap : public PriorityQueue<T>
{
public:
    BinaryHeap(int size = 10)
    {
        data = new PQElement<T>[size];
        max = size;
        filled = 0;
    }

    ~BinaryHeap()
    {
        delete[] data;
    }

    virtual void insert(PQElement<T> e)
	{
        if (filled == max)
        {
            PQElement<T>* newdata = new PQElement<T>[max * 2];

            for (int i = 0; i < max; i++)
            {
                newdata[i] = data[i];
            }

            delete[] data;
            data = newdata;
            max = max * 2;
        }

        siftUp(filled, e);
        filled++;
	}

	virtual size_t size() const
	{
        return filled;
	}

    virtual PQElement<T> min() const
	{
        return filled > 0 ? data[0] : PQElement<T>();
	}

    virtual PQElement<T> deleteMin()
	{
        PQElement<T> rtn = min();
        filled--;
        if (filled > 0)
            siftDown(0, data[filled]);
        return rtn;
	}

private:

    void siftUp(int index, PQElement<T> e)
    {
        int parent = (index - 1) / 2;

        if (index <= 0)
        {
            data[0] = e;
        }
        else if (data[parent].key > e.key)
        {
            data[index] = data[parent];
            siftUp(parent, e);
        }
        else
        {
            data[index] = e;
        }
    }

    void siftDown(int index, PQElement<T> e)
    {
        int left = index * 2 + 1;
        int right = index * 2 + 2;

        if ((left  < filled && data[left].key  < e.key) ||
            (right < filled && data[right].key < e.key))
        {
            if (right >= filled || data[left].key < data[right].key)
            {
                data[index] = data[left];
                siftDown(left, e);
            }
            else
            {
                data[index] = data[right];
                siftDown(right, e);
            }
        }
        else
        {
            data[index] = e;
        }
    }

    PQElement<T>* data;
    int filled, max;
};
