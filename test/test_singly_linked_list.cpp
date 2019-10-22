#include "../data_structure/singly_linked_list.hpp"
#include <fstream>
#include <vector>
#include <ctime>
#include <map>

using namespace std;

const int TYPE_NUMBER = 3;

typedef SinglyLinkedList<int>* LP;

typedef int ElemType;

struct List
{
	LP p;
	string name;
	List(LP p_ = nullptr, string name_ = "") :
		p(p_), name(name_) {}
};
vector<List*> VL;
inline void RepeatPrint(const string& s, int count, char c = '\0')
{
	while (count--)
	{
		cout << s;
	}
	if (c)
	{
		cout << c;
	}
}
inline void PrintTableInformation()
{
	int max_index_length = 4, max_name_length = 6;
	for (int i = 0; i < VL.size(); ++i)
	{
		if (max_name_length < VL[i]->name.size())
		{
			max_name_length = VL[i]->name.size();
		}
	}
	int row_length = max_index_length + max_name_length + 1;
	RepeatPrint("-", row_length, '\n');
	cout.width(max_index_length);
	cout << "ID" << "|";
	cout.width(max_name_length);
	cout << "NAME" << endl;
	RepeatPrint("-", row_length, '\n');
	for (int i = 0; i < VL.size(); ++i)
	{
		cout.width(max_index_length);
		cout << i << "|";
		cout.width(max_name_length);
		cout << VL[i]->name << endl;
	}
	RepeatPrint("-", row_length, '\n');
}

inline void PrintInformation1()
{
	system("color 0C");
	RepeatPrint("-", 50, '\n');
	cout << "0 Select one table to do further operations" << endl
		<< "1 Create new table" << endl
		<< "2 Delete table" << endl
		<< "3 Load new table from file" << endl
		<< "4 Save table to file" << endl
		<< "5 Save all tables to files" << endl
		<< "6 Print all tables" << endl
		<< "7 Quit" << endl;
	cout << "Press a number(0~7) that you want to do: ";
}
inline void PrintInformation2()
{
	system("color 0E");
	RepeatPrint("-", 50, '\n');
	cout << "2 Destroy this table" << endl
		<< "3 Clear this table" << endl
		<< "4 Print whether this table is EMPTY" << endl
		<< "5 Print the LENGTH of this table" << endl
		<< "6 Get a VALUE by INDEX in this table" << endl
		<< "7 Find the FIRST element that satisfies function compare()" << endl
		<< "8 Get the PRECURSOR of the element found by VALUE" << endl
		<< "9 Get the SUCCESSOR of the element found by VALUE" << endl
		<< "10 Insert an element before the element found by INDEX" << endl
		<< "11 Erase an element found by INDEX" << endl
		<< "12 Traverse this table" << endl
		<< "13 Return" << endl;
	cout<< "Press a number(2~13) that you want to do: ";
}
auto CreateNewTable(string table_name)
{
	List* nlp = new List{ new SinglyLinkedList<int>, table_name };
	VL.push_back(nlp);
	return nlp->p;
}
int GetTableId()
{
	int id;
INPUT_ID:
	cout << "Please input the INDEX of table(0~" << (VL.size() - 1) << "): ";
	cin >> id;
	if (id < 0 || id >= VL.size())
	{
		cout << "INVALID INDEX!" << endl;
		goto INPUT_ID;
	}
	return id;
}
size_t GetIndex()
{
	cout << "Please input the INDEX of the element: ";
	size_t x;
	cin >> x;
	return x;
}
void DeleteTable(int id)
{
	delete VL[id];
	VL.erase(VL.begin() + id);
}
void ClearTable(int id)
{
	VL[id]->p->Clear();
}
inline bool IsEmpty(int id)
{
	return VL[id]->p->IsEmpty();
}
size_t GetSize(int id)
{
	return VL[id]->p->GetSize();
}
ElemType GetElement()
{
	cout << "Please input the VALUE of the element: ";
	ElemType e;
	cin >> e;
	return e;
}
void visit(const ElemType& x)
{
	cout << x << "->";
}
void Save(int id)
{
	string file_path = VL[id]->name;
	ofstream outfile;
	outfile.open(file_path.c_str());
	for (auto it = VL[id]->p->Begin(); it != VL[id]->p->End(); ++it)
		outfile << *it<<endl;
	outfile.close();
}
int main()
{
	//srand ( (int) time (NULL));
	PrintTableInformation();
	while (1)
	{
		string table_name;
		string file_path;
		ifstream infile;
		SinglyLinkedList<int>* p;
		int table_id;
		int op1, op2;
		int idx;
		ElemType e;
	INPUT_OP1:
		PrintInformation1();
		cin >> op1;
		switch (op1)
		{
		case 0:
			table_id = GetTableId();
			while (1)
			{
			INPUT_OP2:
				PrintInformation2();
				cin >> op2;
				switch (op2)
				{
				case 2:
					DeleteTable(table_id);
					break;
				case 3:
					ClearTable(table_id);
					break;
				case 4:
					if (IsEmpty(table_id))
					{
						cout << "Yes" << endl;
					}
					else
					{
						cout << "No" << endl;
					}
					break;
				case 5:
					cout << GetSize(table_id) << endl;
					break;
				case 6:
					idx = GetIndex();
					cout << VL[table_id]->p->Get(idx);
					break;
				case 7:
					e = GetElement();
					auto it = VL[table_id]->p->Find(e);
					if (it == VL[table_id]->p->End())
					{
						cout << "NOT FOUND!" << endl;
					}
					else
					{
						int count = 1;
						auto itt = VL[table_id]->p->Begin();
						while (itt != VL[table_id]->p->Find(e))
						{
							++itt;
							++count;
						}
						cout << "FOUND!" << endl << count << endl;
					}
					break;
				case 8:
					e = GetElement();
					it = VL[table_id]->p->GetPrecursor(e);
					if (it == VL[table_id]->p->End())
					{
						cout << "NOT FOUND!" << endl;
					}
					else
					{
						cout << "FOUND!" << endl << *it << endl;
					}
					break;
				case 9:
					e = GetElement();
					it = VL[table_id]->p->GetSuccessor(e);
					if (it == VL[table_id]->p->End())
					{
						cout << "NOT FOUND!" << endl;
					}
					else
					{
						cout << "FOUND!" << endl << *it << endl;
					}
					break;
				case 10:
					idx = GetIndex();
					e = GetElement();
					it = VL[table_id]->p->Insert(idx, e);
					if (it == VL[table_id]->p->End())
					{
						cout << "NOT FOUND!" << endl;
					}
					else
					{
						cout << "Insert successfully!" << endl << *it << endl;
					}
					break;
				case 11:
					idx = GetIndex();
					cout << VL[table_id]->p->Erase(idx) << endl;
					break;
				case 12:
					VL[table_id]->p->Traverse(visit);
					break;
				case 13:
					goto INPUT_OP1;
					break;
				default:
					goto INPUT_OP2;
				}
			}
			break;
		case 1:
			//PrintTableInformation();
			cout << "Please input the NAME of table that you want to create: ";
			cin >> table_name;
			CreateNewTable(table_name);
			cout << "Table created successfully!" << endl;
			break;
		case 2:
			//PrintTableInformation();
			cout << "Please input the INDEX of table that you want to delete: ";
			table_id = GetTableId();
			DeleteTable(table_id);
			cout << "Table deleted successfully!" << endl;
			break;
		case 3:
			cout << "Please input the file path: ";
			cin >> file_path;
			table_name = file_path;
			p = CreateNewTable(table_name);
			infile.open(file_path.c_str());
			while (infile >> e)
			{
				p->PushBack(e);
			}
			infile.close();
			break;
		case 4:
			table_id = GetTableId();
			Save(table_id);
			break;
		case 5:
			for (int i = 0; i < VL.size(); ++i)
				Save(i);
			break;
		case 6:
			PrintTableInformation();
			break;
		case 7:
			cout << "Process QUIT!" << endl;
			return 0;
		default:
			cout << "INVALID INPUT!" << endl;
			goto INPUT_OP1;
		}
	}
	return 0;
}