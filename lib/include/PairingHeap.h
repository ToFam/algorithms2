#pragma once

#include <AdressablePQ.h>

template <typename T>
class PairingHeap : public AdressablePQ<T>
{
public:
    void insert(PQElement<T> e)
    {
        if (this->forest == nullptr)
        {
            this->forest = new Node(e);
            pMin = this->forest;
        }
        else
        {
            Node* n = new Node(e);

            n->right = this->forest;
            n->left = this->forest->left;

            this->forest->left->right = n;
            this->forest->left = n;

            if (pMin->data.key > e.key)
            {
                pMin = n;
            }
        }
        numElements++;
    }

    size_t size() const
    {
        return numElements;
    }

    PQElement<T> min()
    {
        return pMin ? pMin->data : PQElement<T>();
    }

    PQElement<T> deleteMin()
    {
        if (numElements > 0)
            numElements--;
        else
            return PQElement<T>();

        PQElement<T> e = pMin->data;

        if (this->forest == pMin)
        {
            if (this->forest->right != this->forest)
            {
                this->forest->right->left = this->forest->left;
                this->forest->left->right = this->forest->right;
                this->forest = this->forest->right;
            }
            else
            {
                if (pMin->child == nullptr)
                {
                    delete pMin;
                    this->forest = nullptr;
                    pMin = nullptr;
                    return e;
                }
                else
                {
                    this->forest = pMin->child;
                    delete pMin;
                    pMin = this->forest;
                    makeTopLevel(this->forest);
                    topUnion();
                    makeTopLevel(this->forest);
                    return e;
                }
            }
        }
        else
        {
            pMin->left->right = pMin->right;
            pMin->right->left = pMin->left;
        }

        if (pMin->child != nullptr)
        {
            Node* left = pMin->child;
            Node* right = pMin->child->left;

            right->right = this->forest;
            left->left = this->forest->left;

            this->forest->left->right = left;
            this->forest->left = right;
        }

        delete pMin;
        pMin = this->forest;
        makeTopLevel(this->forest);
        topUnion();
        makeTopLevel(this->forest);

        return e;
    }

    T remove(T handle)
    {
        return T();
    }

    void decreaseKey(T handle, int key)
    {

    }

private:
    typedef typename AdressablePQ<T>::Node Node;
    Node*   pMin = nullptr;
    size_t  numElements = 0;

private:
    void makeTopLevel(Node* it)
    {
        do
        {
            it->parent = nullptr;
            if (pMin->data.key > it->data.key)
                pMin = it;
            it = it->right;
        }while (it != this->forest);
    }

    void topUnion()
    {
        Node* it = this->forest;
        if (it->right == it)
            return;
        this->forest = unioN(it, it->right);
        it = this->forest->right;

        while(it != this->forest && it->right != this->forest)
        {
            it = unioN(it, it->right)->right;
        }
    }

    Node* unioN(Node* a, Node* b)
    {
        if (a->data.key < b->data.key)
        {
            link(a, b);
            return a;
        }
        else
        {
            link(b, a);
            return b;
        }
    }

    void link(Node* a, Node* b)
    {
        b->parent = a;
        b->left->right = b->right;
        b->right->left = b->left;
        if (a->child == nullptr)
            a->child = b;
        else
        {
            b->left = a->child->left;
            b->right = a->child;

            a->child->left->right = b;
            a->child->left = b;
        }
    }

    void cut(Node* a)
    {
        if (a->parent && a->parent->child == a)
        {
            if (a->right != a)
                a->parent->child = a->right;
            else
                a->parent->child = nullptr;
        }
        a->parent = nullptr;

        a->right->left = a->left;
        a->left->right = a->right;

        a->left = this->forest->left;
        a->right = this->forest;
        this->forest->left->right = a;
        this->forest->left = a;
    }

    void merge(Node* otherForest)
    {

    }
};
