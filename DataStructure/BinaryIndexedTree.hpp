/*
    Programed by HarryShaunWang
    2018.11.1
*/
#ifndef BINARYINDEXEDTREE_HPP
#define BINARYINDEXEDTREE_HPP

#include <vector>

template <typename T>
class BinaryIndexedTree
{
public:
    BinaryIndexedTree (int _size = 0) : size (_size) //[1,size]
    {
        A.resize (size + 1);
        C.resize (size + 1);
    }
    bool isEmpty()
    {
        return size == 0;
    }
    int getSize()
    {
        return size;
    }
    void resize (int _size)
    {
        C.resize (_size + 1);
        A.resize (_size + 1);
        for (int i = size + 1; i <= _size; ++i)
            if (left (i) <= size)
                C[i] = getSum (left (i), size);
        size = _size;
    }
    void add (int i, const T &x) //a[i]+=x;
    {
        if (i > size)
            resize (i);
        A[i] += x;
        for (; i <= size; i += lowbit (i))
            C[i] += x;
    }
    T getSum (int l, int r) //sum[l...r]
    {
        return calcSum (r) - calcSum (l - 1);
    }
    const T &operator[] (int i)
    {
        return A[i];
    }

private:
    int size;
    std::vector<T> C, A;

    int lowbit (int x)
    {
        return x & (-x);
    }
    int left (int i)
    {
        return i - lowbit (i) + 1;
    }
    T calcSum (int i) //sum[1...i]
    {
        T sum = C[0];
        if (i > size)
            resize (i);
        for (; i; i -= lowbit (i))
            sum += C[i];
        return sum;
    }
};

#endif
