#include "../data_structure/singly_linked_list.hpp"
#include <ctime>

using std::cout;
using std::endl;
using std::cin;

template<typename T>
void gen(SinglyLinkedList<T>& L, int k)
{
	while (k--)
	{
		if (k & 1)
		{
			L.PushBack(rand());
		}
		else
		{
			L.PushFront(rand());
		}
	}
}

int main()
{
	srand((int)time(NULL));
	SinglyLinkedList<int> L;
	// gen (L, 5);
	// L.Traverse();
	// L.Reverse();
	// L.Traverse();
	SinglyLinkedList<int>::iterator it;
	while (1)
	{
		cout << endl
			<< "0  : IsEmpty()" << endl
			<< "1  : GetSize()" << endl
			<< "2 x: PushFront(x)" << endl
			<< "3 x: PushBack(x)" << endl
			<< "4  : PopFront(x)" << endl
			<< "5  : PopBack(x)" << endl
			<< "6  : Reverse()" << endl;
		int x, y;
		cin >> x;
		switch (x)
		{
		case 0:
			cout << L.IsEmpty() << endl;
			break;
		case 1:
			cout << L.GetSize() << endl;
			break;
		case 2:
			cin >> y;
			L.PushFront(y);
			break;
		case 3:
			cin >> y;
			L.PushBack(y);
			break;
		case 4:
			L.PopFront();
			break;
		case 5:
			L.PopBack();
			break;
		case 6:
			L.Reverse();
			break;
		case 7:
			for (auto i = L.Begin(); i!=L.End(); ++i)
				cout << *i << " -> " << endl;
			break;
		}
		L.Traverse();
	}
	return 0;
}