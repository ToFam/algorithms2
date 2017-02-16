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

    PQElement<T> min() const
    {
        return pMin ? pMin->data : PQElement<T>();
    }

    PQElement<T> deleteMin()
    {
        if (pMin != nullptr)
            return remove(pMin);
        return PQElement<T>();
    }

    PQElement<T> remove(T handle)
    {
        Node* e = find(handle, this->forest);
        if (e == nullptr)
            return PQElement<T>();

        return remove(e);
    }

    void decreaseKey(T handle, int key)
    {
        Node* n = find(handle, this->forest);

        if (n->data.key > key)
        {
            n->data.key = key;
            cut(n);
        }
    }

private:
    typedef typename AdressablePQ<T>::Node Node;
    Node*   pMin = nullptr;
    size_t  numElements = 0;

private:
    PQElement<T> remove(Node* n)
    {
        if (numElements > 0)
            numElements--;
        else
            return PQElement<T>();

        PQElement<T> e = n->data;

        if (this->forest == n)
        {
            if (this->forest->right != this->forest)
            {
                this->forest->right->left = this->forest->left;
                this->forest->left->right = this->forest->right;
                this->forest = this->forest->right;
            }
            else
            {
                if (n->child == nullptr)
                {
                    delete n;
                    this->forest = nullptr;
                    pMin = nullptr;
                    return e;
                }
                else
                {
                    this->forest = n->child;
                    delete n;
                    pMin = this->forest;
                    makeTopLevel();
                    topUnion();
                    updateMin();
                    return e;
                }
            }
        }
        else
        {
            n->left->right = n->right;
            n->right->left = n->left;
        }

        if (n->child != nullptr)
        {
            cutChildren(n);
        }

        delete n;
        makeTopLevel();
        topUnion();
        updateMin();

        return e;
    }

    void cutChildren(Node* n)
    {
        Node* left = n->child;
        Node* right = n->child->left;

        right->right = this->forest;
        left->left = this->forest->left;

        this->forest->left->right = left;
        this->forest->left = right;
    }

    Node* find(T handle, Node* start) const
    {
        Node* it = start;
        do
        {
            if (it->data.value == handle)
                return it;

            if (it->child != nullptr)
            {
                Node* rtn = find(handle, it->child);
                if (rtn != nullptr)
                    return rtn;
            }

            it = it->right;
        } while (it != start);
        return nullptr;
    }

    int count(Node* start) const
    {
        int counter = 0;
        Node* it = start;
        do
        {
            counter++;
            if (it->child != nullptr)
            {
                counter += count(it->child);
            }

            it = it->right;
        } while (it != start);
        return counter;
    }

    void makeTopLevel()
    {
        Node* it = this->forest;
        do
        {
            it->parent = nullptr;
            it = it->right;
        }while (it != this->forest);
    }

    void updateMin()
    {
        Node* it = this->forest;
        pMin = this->forest;
        do
        {
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
        {
            a->child = b;
            b->left = b;
            b->right = b;
        }
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

    Node* extractForest()
    {
        Node* rtn = this->forest;
        this->forest = nullptr;
        pMin = nullptr;
        numElements = 0;
        return rtn;
    }

    void insertForest(Node* otherForest)
    {
        if (otherForest == nullptr)
            return;

        numElements += count(otherForest);

        if (this->forest == nullptr)
        {
            this->forest = otherForest;
        }
        else
        {
            otherForest->left->right = this->forest;
            this->forest->left->right = otherForest;

            this->forest->left = otherForest->left;
            otherForest->left = this->forest;

            topUnion();
        }
        updateMin();
    }
};
