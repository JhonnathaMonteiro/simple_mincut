#ifndef FIBONACCI_HEAP_H_
#define FIBONACCI_HEAP_H_

#include <cstddef>

template <class V>
class FibonacciHeap;

template <class V>
struct node
{
private:
    node<V> *prev;
    node<V> *next;
    node<V> *child;
    node<V> *parent;
    V value;
    int degree;
    bool marked;

public:
    friend class FibonacciHeap<V>;
    node<V> *getPrev() { return prev; }
    node<V> *getNext() { return next; }
    node<V> *getChild() { return child; }
    node<V> *getParent() { return parent; }
    V getValue() { return value; }
    bool isMarked() { return marked; }

    int vertexID = 0;

    bool hasChildren() { return child; }
    bool hasParent() { return parent; }
};

template <class V>
class FibonacciHeap
{
protected:
    node<V> *heap;

public:
    FibonacciHeap()
    {
        heap = _empty();
    }
    virtual ~FibonacciHeap()
    {
        if (heap)
        {
            _deleteAll(heap);
        }
    }
    node<V> *insert(int vID, V value)
    {
        node<V> *ret = _singleton(value);
        ret->vertexID = vID;
        heap = _merge(heap, ret);
        return ret;
    }
    void merge(FibonacciHeap &other)
    {
        heap = _merge(heap, other.heap);
        other.heap = _empty();
    }

    bool isEmpty()
    {
        return heap == NULL;
    }

    V getMinimum()
    {
        return heap->value;
    }

    int extractMin()
    {
        node<V> *old = heap;
        heap = _extractMin(heap);
        int ret = old->vertexID;
        delete old;
        return ret;
    }

    void decreaseKey(node<V> *n, V value)
    {
        heap = _decreaseKey(heap, n, value);
    }

    node<V> *find(V value)
    {
        return _find(heap, value);
    }

private:
    node<V> *_empty()
    {
        return NULL;
    }

    node<V> *_singleton(V value)
    {
        node<V> *n = new node<V>;
        n->value = value;
        n->prev = n->next = n;
        n->degree = 0;
        n->marked = false;
        n->child = NULL;
        n->parent = NULL;
        return n;
    }

    node<V> *_merge(node<V> *a, node<V> *b)
    {
        if (a == NULL)
            return b;
        if (b == NULL)
            return a;
        if (a->value > b->value)
        {
            node<V> *temp = a;
            a = b;
            b = temp;
        }
        node<V> *an = a->next;
        node<V> *bp = b->prev;
        a->next = b;
        b->prev = a;
        an->prev = bp;
        bp->next = an;
        return a;
    }

    void _deleteAll(node<V> *n)
    {
        if (n != NULL)
        {
            node<V> *c = n;
            do
            {
                node<V> *d = c;
                c = c->next;
                _deleteAll(d->child);
                delete d;
            } while (c != n);
        }
    }

    void _addChild(node<V> *parent, node<V> *child)
    {
        child->prev = child->next = child;
        child->parent = parent;
        parent->degree++;
        parent->child = _merge(parent->child, child);
    }

    void _unMarkAndUnParentAll(node<V> *n)
    {
        if (n == NULL)
            return;
        node<V> *c = n;
        do
        {
            c->marked = false;
            c->parent = NULL;
            c = c->next;
        } while (c != n);
    }

    node<V> *_extractMin(node<V> *n)
    {
        _unMarkAndUnParentAll(n->child);
        if (n->next == n)
        {
            n = n->child;
        }
        else
        {
            n->next->prev = n->prev;
            n->prev->next = n->next;
            n = _merge(n->next, n->child);
        }
        if (n == NULL)
            return n;
        node<V> *trees[64] = {NULL};

        while (true)
        {
            if (trees[n->degree] != NULL)
            {
                node<V> *t = trees[n->degree];
                if (t == n)
                    break;
                trees[n->degree] = NULL;
                if (n->value < t->value)
                {
                    t->prev->next = t->next;
                    t->next->prev = t->prev;
                    _addChild(n, t);
                }
                else
                {
                    t->prev->next = t->next;
                    t->next->prev = t->prev;
                    if (n->next == n)
                    {
                        t->next = t->prev = t;
                        _addChild(t, n);
                        n = t;
                    }
                    else
                    {
                        n->prev->next = t;
                        n->next->prev = t;
                        t->next = n->next;
                        t->prev = n->prev;
                        _addChild(t, n);
                        n = t;
                    }
                }
                continue;
            }
            else
            {
                trees[n->degree] = n;
            }
            n = n->next;
        }
        node<V> *min = n;
        do
        {
            if (n->value < min->value)
                min = n;
            n = n->next;
        } while (n != n);
        return min;
    }

    node<V> *_cut(node<V> *heap, node<V> *n)
    {
        if (n->next == n)
        {
            n->parent->child = NULL;
        }
        else
        {
            n->next->prev = n->prev;
            n->prev->next = n->next;
            n->parent->child = n->next;
        }
        n->next = n->prev = n;
        n->marked = false;
        return _merge(heap, n);
    }

    node<V> *_decreaseKey(node<V> *heap, node<V> *n, V value)
    {
        if (n->value < value)
            return heap;
        n->value = value;
        if (n->parent == NULL)
        {
            heap = value < heap->value ? n : heap;
            return heap;
        }
        if (n->value < n->parent->value)
        {
            heap = _cut(heap, n);
            node<V> *parent = n->parent;
            n->parent = NULL;
            while (parent != NULL && parent->marked)
            {
                heap = _cut(heap, parent);
                n = parent;
                parent = n->parent;
                n->parent = NULL;
            }
            if (parent != NULL && parent->parent != NULL)
                parent->marked = true;
        }
        return heap;
    }

    node<V> *_find(node<V> *heap, int vID)
    {
        node<V> *n = heap;
        if (n == NULL)
            return NULL;
        do
        {
            if (n->vertexID == vID)
                return n;
            node<V> *ret = _find(n->child, vID);
            if (ret)
                return ret;
            n = n->next;
        } while (n != heap);
        return NULL;
    }
};

#endif // FIBONACCI_HEAP_H_