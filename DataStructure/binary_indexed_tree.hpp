/*
    Programed by HarryShaunWang
    Created on 2018.11.1
    Last modified on 2018.11.10
*/
#ifndef BINARY_INDEXED_TREE_HPP
#define BINARY_INDEXED_TREE_HPP

#include <vector>

template <typename T>
class BinaryIndexedTree
{
public:
    BinaryIndexedTree() = default;
    BinaryIndexedTree (int size); //[1,size]
    ~BinaryIndexedTree() = default;
    bool isEmpty();
    int getSize();
    void resize (int size);
    void modify (int i, const T &x); //a[i]=x;
    T getSum (int l, int r);        //sum[l...r]
    const T &operator[] (int i);

private:
    int size_;
    std::vector<T> C_, A_;

    int lowbit (int x);
    int left (int i);
    T calcSum (int i); //sum[1...i]
};

template <typename T>
BinaryIndexedTree<T>::BinaryIndexedTree (int size) : size_ (size), A_ (std::vector<T> (size)), C_ (std::vector<T> (size)) {}

template <typename T>
bool BinaryIndexedTree<T>::isEmpty()
{
    return size_ == 0;
}

template <typename T>
int BinaryIndexedTree<T>::getSize()
{
    return size_;
}

template <typename T>
void BinaryIndexedTree<T>::resize (int size) //refactory BIT
{
    C_.resize (size + 1);
    A_.resize (size + 1);
    for (int i = size_ + 1; i <= size; ++i)
        if (left (i) <= size_)
            C_[i] = getSum (left (i), size_);
    size_ = size;
}

template <typename T>
void BinaryIndexedTree<T>::modify (int i, const T &x)
{
    if (i > size_)
        resize (i);
    T delta = x - A_[i];
    for (; i <= size_; i += lowbit (i))
        C_[i] += delta;
    A_[i] = x;
}

template <typename T>
T BinaryIndexedTree<T>::getSum (int l, int r)
{
    return calcSum (r) - calcSum (l - 1);
}

template <typename T>
const T &BinaryIndexedTree<T>::operator[] (int i)
{
    return A_[i];
}

template <typename T>
int BinaryIndexedTree<T>::lowbit (int x)
{
    return x & (-x);
}

template <typename T>
int BinaryIndexedTree<T>::left (int i)
{
    return i - lowbit (i) + 1;
}

template <typename T>
T BinaryIndexedTree<T>::calcSum (int i)
{
    T sum = C_[0];
    if (i > size_)
        resize (i);
    for (; i; i -= lowbit (i))
        sum += C_[i];
    return sum;
}

#endif