/*
	Programed by HarryShaunWang
	Created on 2019.9.12
	Last modified on 2019.10.28
*/
#ifndef SINGLY_LINKED_LIST_HPP
#define SINGLY_LINKED_LIST_HPP

#include <iostream>

template<typename T>
class SinglyLinkedList
{
public:
	class iterator;
	SinglyLinkedList();
	~SinglyLinkedList();
	bool IsEmpty() const;
	size_t GetSize() const;
	void Clear() const;
	T& Get(size_t);
	iterator GetPrecursor(const T&);
	iterator GetSuccessor(const T&);
	void PushFront(const T&);
	void PushBack(const T&);
	void PopFront();
	void PopBack(); 
	iterator Insert(size_t, const T&);
	void Insert(const iterator&, const T&);
	T Erase(size_t);
	void Reverse();
	template<class VisitFunction>
		void Traverse(VisitFunction);
	template<class CompareFunction>
		iterator FindIf(const T&, CompareFunction); //Find which satisfies CompareFunction(a, b)
	iterator Find(const T&, iterator); //Find from the specific position
	iterator Find(const T&); //Find from head
	bool IsExisted(const T&);
	size_t Count(const T&);
	void Remove(const T&);
	const T& Front() const;
	const T& Back() const;
	T& Front();
	T& Back();
	iterator Begin();
	iterator End();
private:
	struct Node;
	Node* head_, * tail_;
	size_t size_;
	enum STATUS_CODE { NORMAL, ERROR_EMPTY, ERROR_INDEX_OUT_OF_BOUND };
	Node* FindFirstFrom(Node*, const T&);
	void Erase(Node*, Node*);
	void Alert(unsigned int) const; //Exception
};

template<typename T>
class SinglyLinkedList<T>::iterator
{
public:
	iterator() = default;
	iterator(Node* n) : n_(n) {}
	const T& operator *() const
	{
		return n_->data;
	}
	T& operator *()
	{
		return n_->data;
	}
	iterator operator +(size_t rhs)
	{
		Node* res = n_;
		while (rhs--)
		{
			++res;
		}
		return res;
	}
	iterator& operator ++ (int)
	{
		iterator tmp = *this;
		++(*this);
		return tmp;
	}
	iterator& operator ++()
	{
		n_ = n_->next;
		return *this;
	}
	bool operator != (const iterator& rhs) const
	{
		return n_ != rhs.n_;
	}
private:
	Node* n_;
};

template<typename T>
struct SinglyLinkedList<T>::Node
{
	T data;
	Node* next;
	Node() = default;
	Node(const T& val, Node* nxt = nullptr) : data(val), next(nxt) {}
	bool operator != (const Node& rhs) const
	{
		return next != rhs.next && data != rhs.data;
	}
};

template<typename T>inline  SinglyLinkedList<T>::SinglyLinkedList()
{
	head_ = new Node();
	size_ = 0;
}

template<typename T>inline  SinglyLinkedList<T>::~SinglyLinkedList()
{
	Clear();
	delete head_;
}

template<typename T>inline  bool  SinglyLinkedList<T>::IsEmpty() const
{
	return !size_;
}

template<typename T>inline  size_t  SinglyLinkedList<T>::GetSize() const
{
	return size_;
}

template<typename T>inline  void  SinglyLinkedList<T>::Clear() const
{
	Node* p = head_->next;
	while (p)
	{
		Node* tmp = p->next;
		delete p;
		p = tmp;
	}
}

template<typename T>inline  T& SinglyLinkedList<T>::Get(size_t pos)
{
	if (pos > GetSize() || pos == 0)
	{
		Alert(ERROR_INDEX_OUT_OF_BOUND);
		return *head_;
	}
	return *(Begin() + (pos - 1)).data;
}

template<typename T>
inline typename SinglyLinkedList<T>::iterator SinglyLinkedList<T>::GetPrecursor(const T& val)
{
	Node* fp = head_, *p = fp->next;
	while (p && p->data != val)
	{
		fp = p;
		p = fp->next;
	}
	if (fp != head_ && p && p->data == val) return iterator(fp);
	else return End();
}

template<typename T>
inline bool equal(const T& val1, const T& val2)
{
	return val1 == val2;
}

template<typename T>
inline typename SinglyLinkedList<T>::iterator SinglyLinkedList<T>::GetSuccessor(const T& val)
{
	return FindIf(val, equal) + 1;
}

template<typename T>inline  void  SinglyLinkedList<T>::PushFront(const T& val)
{
	Node* p = new Node(val);
	p->next = head_->next;
	head_->next = p;
	if (IsEmpty())
	{
		tail_ = p;
	}
	++size_;
}

template<typename T>inline  void  SinglyLinkedList<T>::PushBack(const T& val)
{
	if (IsEmpty())
	{
		PushFront(val);
		return;
	}
	Node* p = new Node(val);
	tail_->next = p;
	tail_ = p;
	++size_;
}


template<typename T>inline  void  SinglyLinkedList<T>::PopFront()
{
	if (IsEmpty())
	{
		std::cerr << "ERROR: The list is EMPTY!" << std::endl;
		return;
	}
	Node* p = head_->next;
	head_->next = p->next;
	delete p;
	--size_;
}

template<typename T>inline  void  SinglyLinkedList<T>::PopBack()
{
	if (IsEmpty())
	{
		return Alert(ERROR_EMPTY);
	}
	if (GetSize() == 1)
	{
		return PopFront();
	}
	Node* p = head_->next;
	while (p->next != tail_)
	{
		p = p->next;
	}
	delete tail_;
	tail_ = p;
	tail_->next = nullptr;
	--size_;
}

template<typename T>
inline typename SinglyLinkedList<T>::iterator SinglyLinkedList<T>::Insert(size_t pos, const T& val)
{
	if (pos > GetSize() + 1 || pos == 0)
	{
		Alert(ERROR_INDEX_OUT_OF_BOUND);
		return End();
	}
	Node* fp = head_, * p = fp->next;
	while (p && p->data != val)
	{
		fp = p;
		p = p->next;
	}
	if (p)
	{
		fp->next = new Node(val);
		fp->next->next = p;
	}
	return iterator(fp->next);
}

template<typename T>
inline void SinglyLinkedList<T>::Insert(const iterator& it, const T& val)
{
	it.n_->next = new Node(val, it.n_->next);
	++size_;
}

template<typename T>
inline T SinglyLinkedList<T>::Erase(size_t pos)
{
	if (pos > GetSize() || pos == 0)
	{
		Alert(ERROR_INDEX_OUT_OF_BOUND);
	}
	Node* fp = head_, *p = fp->next;
	for (int i = 1; i < pos; ++i)
	{
		fp = p;
		p = p->next;
	}
	Node* tmp = p;
	T val = tmp->data;
	fp->next = p->next;
	delete tmp;
	return val;
}

template<typename T>inline  void  SinglyLinkedList<T>::Reverse()
{
	Node* first = nullptr, * second = head_->next, * third = nullptr;
	while (second)
	{
		third = second->next;
		second->next = first;
		first = second;
		second = third;
	}
	tail_ = head_->next;
	head_->next = first;
}

template<typename T>
template<class VisitFunction>
inline void SinglyLinkedList<T>::Traverse(VisitFunction vf)
{
	for (auto it = Begin(); it != End(); ++it)
		vf((*it).data);
}

template<typename T>
template<class CompareFunction>
inline typename SinglyLinkedList<T>::iterator SinglyLinkedList<T>::FindIf(
	const T& val, CompareFunction cf)
{
	auto it = Begin();
	for (; it != End(); ++it)
	{
		if (cf((*it).data, val))
		{
			break;
		}
	}
	return it;
}

template<typename T>
inline typename SinglyLinkedList<T>::iterator SinglyLinkedList<T>::Find(
	const T& val, typename SinglyLinkedList<T>::iterator start)
{
	for (; start != End(); ++start)
		if (*start == val)
		{
			return start;
		}
}

template<typename T>
inline typename SinglyLinkedList<T>::iterator SinglyLinkedList<T>::Find(
	const T& val)
{
	return Find(val, Begin());
}

template<typename T>
inline bool SinglyLinkedList<T>::IsExisted(const T& val)
{
	return FindFirstFrom(head_->next, val) != nullptr;
}

template<typename T>
inline size_t SinglyLinkedList<T>::Count(const T& val)
{
	size_t cnt = 0;
	Node* res = FindFirstFrom(head_->next, val);
	while (res != nullptr)
	{
		++cnt;
		res = FindFirstFrom(res->next, val);
	}
	return cnt;
}

template<typename T>
inline void SinglyLinkedList<T>::Remove(const T& val)
{
	Node* p = head_->next, * fp = head_;
	while (p)
	{
		if (p->data == val)
		{
			Erase(p, fp);
		}
		fp = p, p = p->next;
	}
}

template<typename T>
inline const T& SinglyLinkedList<T>::Front() const
{
	if (IsEmpty())
	{
		Alert(ERROR_EMPTY);
		return T();
	}
	return head_->next->data;
}

template<typename T>
inline const T& SinglyLinkedList<T>::Back() const
{
	if (IsEmpty())
	{
		Alert(ERROR_EMPTY);
		return T();
	}
	return tail_->data;
}

template<typename T>
inline T& SinglyLinkedList<T>::Front()
{
	if (IsEmpty())
	{
		Alert(ERROR_EMPTY);
		return T();
	}
	return head_->next->data;
}

template<typename T>
inline T& SinglyLinkedList<T>::Back()
{
	if (IsEmpty())
	{
		return Alert(ERROR_EMPTY);
	}
	return tail_->data;
}

template<typename T>
inline typename SinglyLinkedList<T>::iterator SinglyLinkedList<T>::Begin()
{
	return iterator(head_->next);
}

template<typename T>
inline typename SinglyLinkedList<T>::iterator SinglyLinkedList<T>::End()
{
	return iterator(nullptr);
}

template<typename T>
inline typename SinglyLinkedList<T>::Node* SinglyLinkedList<T>::FindFirstFrom(
	typename SinglyLinkedList<T>::Node* start, const T& val)
{
	while (start && start->data != val)
	{
		start = start->next;
	}
	return start;
}

template<typename T>
inline void SinglyLinkedList<T>::Erase(Node* p, Node* fp)
{
	if (p == tail_)
	{
		PopBack();
	}
	else
	{
		fp->next = p->next;
		delete p;
	}
}

template<typename T>
inline void SinglyLinkedList<T>::Alert(unsigned int alert_type) const
{
	if (alert_type == ERROR_EMPTY)
	{
		std::cerr << "ERROR: The list is EMPTY!" << std::endl;
	}
	else if (alert_type == ERROR_INDEX_OUT_OF_BOUND)
	{
		std::cerr << "ERROR: The index is OUR OF BOUND!" << std::endl;
	}
}

#endif
