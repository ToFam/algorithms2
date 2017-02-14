#pragma once

#include <PriorityQueue.h>

template <typename T>
class AdressablePQ : public PriorityQueue<T>
{
public:
    virtual T remove(T handle) = 0;
    virtual void decreaseKey(T handle, int key) = 0;

    void merge(AdressablePQ<T>* other)
    {
        merge(other->forest);
    }

protected:
    struct Node
    {
        PQElement<T> data;
        Node*   parent;
        Node*   left;
        Node*   right;
        Node*   child;

        Node()
        {
            parent = nullptr;
            child = nullptr;
            left = this;
            right = this;
        }

        Node(PQElement<T> e) : Node()
        {
            data = e;
        }
    };

    Node*   forest = nullptr;

private:
    virtual void merge(Node* otherForest) = 0;
};
