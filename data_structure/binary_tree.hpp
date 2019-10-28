/*
    Programed by HarryShaunWang
    Created on 2019.10.28
    Last modified on 2019.10.28
*/
#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <queue>

template<typename T>
class BinaryTree
{
public:
    class iterator;
    BinaryTree();
    BinaryTree (const std::string &);
    ~BinaryTree();
    void Clear (iterator it = GetRoot()) const;
    bool IsEmpty (iterator it = GetRoot()) const;
    size_t GetSize (iterator it = GetRoot()) const;
    size_t GetDepth (iterator it = GetRoot()) const;
    iterator GetRoot();
    T GetValue (iterator);
    void Assign (iterator, const T &);
    iterator GetParent (iterator);
    iterator GetLeftChild (iterator);
    iterator GetRightChild (iterator);
    iterator GetLeftSibling (iterator);
    iterator GetRightSibling (iterator);
    void InsertChild (iterator, bool, iterator);
    void InsertLeft (iterator, iterator);
    void InsertRight (iterator, iterator);
    void DeleteChild (iterator, bool);
    void DeleteLeft (iterator);
    void DeleteRight (iterator);
    template<typename VisitFunction>
    void PreorderTraverse (VisitFunction, iterator it = GetRoot());
    template<typename VisitFunction>
    void InorderTraverse (VisitFunction, iterator it = GetRoot());
    template<typename VisitFunction>
    void PostorderTraverse (VisitFunction, iterator it = GetRoot());
    template<typename VisitFunction>
    void LevelTraverse (VisitFunction, iterator it = GetRoot());
private:
    struct Node;
    Node *root_;
    size_t size_;
    static const T DEFAULT_VALUE = T();
    static const iterator EMPTY_ITERATOR = iterator();
    enum STATUS_CODE { NORMAL, ERROR_EMPTY, ERROR_INDEX_OUT_OF_BOUND, ERROR_ITERATOR_INVALID, ERROR_NONEXISTENT, ERROR_TARGET_EXISTENT };
    void Alert (unsigned int) const; //Exception
};

template<typename T>
class BinaryTree<T>::iterator
{
public:
    iterator() = default;
    iterator (Node *n) : n_ (n) {}
    ~iterator()
    {
        delete n_;
    }
    T &operator *()
    {
        return n_->data;
    }
    size_t GetSize()
    {
        return n_->size;
    }
    iterator GetParent()
    {
        return iterator (n_->p);
    }
    bool HasLeftChild()
    {
        return n_->lc != nullptr;
    }
    bool HasRightChild()
    {
        return n_->rc != nullptr;
    }
    iterator GetLeftChild()
    {
        return iterator (n_->lc);
    }
    iterator GetRightChild()
    {
        return iterator (n_->rc);
    }
private:
    Node *n_;
    bool IsValid()
    {
        return n_ != nullptr;
    }
};

template<typename T>
struct BinaryTree<T>::Node
{
    T data;
    Node *lc, * rc;
    Node *p;
    size_t size;
    Node() = default;
    Node (const T &val, Node *lc = nullptr, Node *rc = nullptr,
          Node *p =  nullptr, size_t size = 0) :
        data (val), lc (lc), rc (rc), p (p),
        size (size) {}
};

template<typename T>
inline BinaryTree<T>::BinaryTree()
{
    root_ = new Node();
    size_ = 0;
}

template<typename T>
inline BinaryTree<T>::~BinaryTree()
{
    Clear();
    root_ = nullptr;
}

template<typename T>
inline void BinaryTree<T>::Clear (typename BinaryTree<T>::iterator it) const
{
    std::queue<typename BinaryTree<T>::iterator> Q;
    Q.push (it);
    while (!Q.empty())
    {
        auto x = Q.front();
        Q.pop();
        if (x.HasLeftChild())
        {
            Q.push (x.GetLeftChild());
        }
        if (x.HasRightChild())
        {
            Q.push (x.GetRightChild());
        }
        delete x.n_;
    }
}

template<typename T>
inline bool BinaryTree<T>::IsEmpty (typename BinaryTree<T>::iterator it) const
{
    return GetSize (it) == 0;
}

template<typename T>
inline size_t BinaryTree<T>::GetSize (typename BinaryTree<T>::iterator it) const
{
    return it.GetSize();
}

template<typename T>
inline size_t BinaryTree<T>::GetDepth (typename BinaryTree<T>::iterator it) const
{
    return it.IsValid() ? std::max (GetDepth (it.GetLeftChild()),
                                    GetDepth (it.GetRightChild())) + 1 : 0;
}

template<typename T>
inline typename BinaryTree<T>::iterator BinaryTree<T>::GetRoot()
{
    if (root_ == nullptr)
    {
        return Alert (ERROR_EMPTY);
    }
    return iterator (root_);
}

template<typename T>
inline T BinaryTree<T>::GetValue (typename BinaryTree<T>::iterator it)
{
    if (!it.IsValid())
    {
        Alert (ERROR_ITERATOR_INVALID);
        return DEFAULT_VALUE;
    }
    return *it;
}

template<typename T>
inline void BinaryTree<T>::Assign (typename BinaryTree<T>::iterator it,
                                   const T &val)
{
    if (!it.IsValid())
    {
        Alert (ERROR_ITERATOR_INVALID);
        return DEFAULT_VALUE;
    }
    *it = val;
}

template<typename T>
inline typename BinaryTree<T>::iterator BinaryTree<T>::GetParent (
    typename BinaryTree<T>::iterator it)
{
    if (!it.IsValid())
    {
        Alert (ERROR_ITERATOR_INVALID);
        return EMPTY_ITERATOR;
    }
    return it.GetParent();
}

template<typename T>
inline typename BinaryTree<T>::iterator BinaryTree<T>::GetLeftChild (
    typename BinaryTree<T>::iterator it)
{
    if (!it.IsValid())
    {
        Alert (ERROR_ITERATOR_INVALID);
        return EMPTY_ITERATOR;
    }
    return it.GetLeftChild();
}

template<typename T>
inline typename BinaryTree<T>::iterator BinaryTree<T>::GetRightChild (
    typename BinaryTree<T>::iterator it)
{
    if (!it.IsValid())
    {
        Alert (ERROR_ITERATOR_INVALID);
        return EMPTY_ITERATOR;
    }
    return it.GetRightChild();
}

template<typename T>
inline typename BinaryTree<T>::iterator BinaryTree<T>::GetLeftSibling (
    typename BinaryTree<T>::iterator it)
{
    if (!it.IsValid())
    {
        Alert (ERROR_ITERATOR_INVALID);
        return EMPTY_ITERATOR;
    }
    if ( (it.n_)->p == nullptr || (it.n_)->p->lc == it.n_)
    {
        Alert (ERROR_NONEXISTENT);
        return EMPTY_ITERATOR;
    }
    return it.GetParent().GetLeftChild();
}

template<typename T>
inline typename BinaryTree<T>::iterator BinaryTree<T>::GetRightSibling (
    typename BinaryTree<T>::iterator it)
{
    if (!it.IsValid())
    {
        Alert (ERROR_ITERATOR_INVALID);
        return EMPTY_ITERATOR;
    }
    if ( (it.n_)->p == nullptr || (it.n_)->p->rc == it.n_)
    {
        Alert (ERROR_NONEXISTENT);
        return EMPTY_ITERATOR;
    }
    return it.GetParent().GetRightChild();
}

template<typename T>
inline void BinaryTree<T>::InsertChild (
    typename BinaryTree<T>::iterator parent, bool lr,
    typename BinaryTree<T>::iterator child)
{
    if (!parent.IsValid() || !child.IsValid())
    {
        return Alert (ERROR_ITERATOR_INVALID);
    }
    if ( (child.n_)->rc != nullptr)
    {
        return Alert (ERROR_TARGET_EXISTENT);
    }
    return lr ? InsertRight (parent, child) : InsertLeft (parent, child);
}

template<typename T>
inline void BinaryTree<T>::InsertLeft (typename BinaryTree<T>::iterator parent,
                                       typename BinaryTree<T>::iterator child)
{
    (child.n_)->rc = (parent.n_)->lc;
    (child.n_)->p = parent.n_;
    if (parent.HasLeftChild())
    {
        (parent.n_)->size += child.GetSize() - (parent.n_)->lc->size;
    }
    (parent.n_)->lc = child.n_;
}

template<typename T>
inline void BinaryTree<T>::InsertRight (typename BinaryTree<T>::iterator parent,
                                        typename BinaryTree<T>::iterator child)
{
    (child.n_)->rc = (parent.n_)->rc;
    (child.n_)->p = parent.n_;
    if (parent.HasRightChild())
    {
        (parent.n_)->size += child.GetSize() - (parent.n_)->rc->size;
    }
    (parent.n_)->rc = child.n_;
}

template<typename T>
inline void BinaryTree<T>::DeleteChild (
    typename BinaryTree<T>::iterator parent,
    bool lr)
{
    if (!parent.IsValid())
    {
        return Alert (ERROR_ITERATOR_INVALID);
    }
    return lr ? DeleteRight (parent) : DeleteRight (parent);
}

template<typename T>
inline void BinaryTree<T>::DeleteLeft (typename BinaryTree<T>::iterator parent)
{
    if (parent.HasLeftChild())
    {
        parent.n_->size -= (parent.n_)->lc.size;
    }
    delete (parent.n_)->lc;
    (parent.n_)->lc = nullptr;
}

template<typename T>
inline void BinaryTree<T>::DeleteRight (typename BinaryTree<T>::iterator parent)
{
    if (parent.HasRightChild())
    {
        parent.n_->size -= (parent.n_)->lc.size;
    }
    delete (parent.n_)->rc;
    (parent.n_)->rc = nullptr;
}

template<typename T>
template<typename VisitFunction>
inline void BinaryTree<T>::PreorderTraverse (VisitFunction VF,
        typename BinaryTree<T>::iterator it)
{
    if (!it.IsValid())
    {
        return Alert (ERROR_ITERATOR_INVALID);
    }
    VF (*it);
    PreorderTraverse (VF, it.GetLeftChild());
    PreorderTraverse (VF, it.GetRightChild());
}

template<typename T>
template<typename VisitFunction>
inline void BinaryTree<T>::InorderTraverse (VisitFunction VF,
        typename BinaryTree<T>::iterator it)
{
    if (!it.IsValid())
    {
        return Alert (ERROR_ITERATOR_INVALID);
    }
    PreorderTraverse (VF, it.GetLeftChild());
    VF (*it);
    PreorderTraverse (VF, it.GetRightChild());
}

template<typename T>
template<typename VisitFunction>
inline void BinaryTree<T>::PostorderTraverse (VisitFunction VF,
        typename BinaryTree<T>::iterator it)
{
    if (!it.IsValid())
    {
        return Alert (ERROR_ITERATOR_INVALID);
    }
    PreorderTraverse (VF, it.GetLeftChild());
    PreorderTraverse (VF, it.GetRightChild());
    VF (*it);
}

template<typename T>
template<typename VisitFunction>
inline void BinaryTree<T>::LevelTraverse (VisitFunction VF,
        typename BinaryTree<T>::iterator it)
{
    std::queue<typename BinaryTree<T>::iterator> Q;
    Q.push (it);
    while (!Q.empty())
    {
        auto x = Q.front();
        Q.pop();
        VF (*x);
        if (x.HasLeftChild())
        {
            Q.push (x.GetLeftChild());
        }
        if (x.HasRightChild())
        {
            Q.push (x.GetRightChild());
        }
    }
}

template<typename T>
inline void BinaryTree<T>::Alert (unsigned int alert_type) const
{
    if (alert_type == ERROR_EMPTY)
    {
        std::cerr << "ERROR: The tree is EMPTY!" << std::endl;
    }
    else if (alert_type == ERROR_INDEX_OUT_OF_BOUND)
    {
        std::cerr << "ERROR: The index is OUR OF BOUND!" << std::endl;
    }
    else if (alert_type == ERROR_ITERATOR_INVALID)
    {
        std::cerr << "ERROR: The iterator is INVALID!" << std::endl;
    }
    else if (alert_type == ERROR_NONEXISTENT)
    {
        std::cerr << "ERROR: The target is NONEXISTENT!" << std::endl;
    }
    else if (alert_type == ERROR_TARGET_EXISTENT)
    {
        std::cerr << "ERROR: The target has been EXISTED!" << std::endl;
    }
}

#endif