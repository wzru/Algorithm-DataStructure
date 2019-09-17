/*
	Programed by HarryShaunWang
	Created on 2019.9.12
	Last modified on 2019.9.13
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
	bool IsEmpty() const;
	int GetSize() const;
	void PushFront(const T&);
	void PushBack(const T&);
	void PopFront();
	void PopBack();
	void Insert(const iterator&, const T&);
	void Reverse();
	void Traverse();
	iterator Find(const T&, iterator);//Find from the specific position
	iterator Find(const T&);//Find from head
	bool IsExisted(const T&);
	int Count(const T&);
	void Remove(const T&);//Singly Linked List is not suitable for Erase(iterator)
	const T& Front() const;
	const T& Back() const;
	T& Front();
	T& Back();
	iterator Begin();
	iterator End();
private:
	struct Node;
	Node* head_, * tail_;
	int size_;
	enum STATUS_CODE { NORMAL, ERROR_EMPTY };
	Node* FindFirstFrom(Node*, const T&);
	void Erase(Node*, Node*);
	void Alert(int) const;//Exception
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
	bool operator != (const iterator & rhs) const
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
		Node(const T & val, Node * nxt = nullptr) : data(val), next(nxt) {}
		bool operator != (const Node & rhs) const
		{
			return next != rhs.next && data != rhs.data;
		}
};

template<typename T>inline  SinglyLinkedList<T>::SinglyLinkedList()
{
	head_ = new Node();
	tail_ = new Node();
	size_ = 0;
}

template<typename T>inline  bool  SinglyLinkedList<T>::IsEmpty() const
{
	return !size_;
}

template<typename T>inline  int  SinglyLinkedList<T>::GetSize() const
{
	return size_;
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
inline void SinglyLinkedList<T>::Insert(const iterator& it, const T& val)
{
	it.n_->next = new Node(val, it.n_->next);
	++size_;
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

template<typename T> inline void  SinglyLinkedList<T>::Traverse()
{
	std::cout << std::endl << "HEAD";
	for (Node* p = head_->next; p; p = p->next)
	{
		std::cout << " -> " << p->data;
	}
	std::cout << std::endl;
}

template<typename T>
inline typename SinglyLinkedList<T>::iterator SinglyLinkedList<T>::Find(
	const T& val, typename SinglyLinkedList<T>::iterator start)
{
	for (; start != L.end(); ++start)
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
inline int SinglyLinkedList<T>::Count(const T& val)
{
	int cnt = 0;
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
		return;
	}
	return head_->next->data;
}

template<typename T>
inline const T& SinglyLinkedList<T>::Back() const
{
	if (IsEmpty())
	{
		Alert(ERROR_EMPTY);
		return;
	}
	return tail_->data;
}

template<typename T>
inline T& SinglyLinkedList<T>::Front()
{
	if (IsEmpty())
	{
		Alert(ERROR_EMPTY);
		return;
	}
	return head_->next->data;
}

template<typename T>
inline T& SinglyLinkedList<T>::Back()
{
	if (IsEmpty())
	{
		Alert(ERROR_EMPTY);
		return;
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
inline void SinglyLinkedList<T>::Alert(int alert_type) const
{
	if (alert_type == ERROR_EMPTY)
	{
		std::cerr << "ERROR: The list is EMPTY!" << std::endl;
	}
}

#endif