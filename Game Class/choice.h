//#include <iostream>
//#include <windows.h>
//#include <conio.h>
using namespace std;

class Choice
{
private:
	int _choice;
	int _menu_size;
	char* _head;
	char** _name;
	COORD _cord;
	char arrow;
public:
	Choice(int menu_size, char* head, char* name, ...) : _menu_size(menu_size)
	{
		arrow = 26;
		_cord.X = 2;
		_cord.Y = 1;
		*&_name = new char*[menu_size];
		char** p = &name;
		_head = new char[strlen(head) + 1];
		strcpy_s(_head, strlen(head) + 1, head);
		for (int i = 0; i < menu_size; ++i)
		{
			_name[i] = new char[strlen(*p) + 1];
			strcpy_s(_name[i], strlen(*p) + 1, *p);
			++p;
		}
	}
	void ShowMenu();
	int Turn();
};
void Choice::ShowMenu()
{
	system("CLS");
	int len = _msize(_name) / sizeof(_name);
	cout << _head << endl;
	for (int i = 0; i < len; ++i)
	{
		cout << "\t" << _name[i] << endl;
	}
	//return Turn();
}
int Choice::Turn()
{
	int exit = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _cord);
	cout << arrow;
	while (exit != 13)
	{
		switch (exit = _getch())
		{
		case 72:
			if (_cord.Y > 1)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _cord);
				cout << " ";
				--_cord.Y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _cord);
				cout << arrow;
			}
			else
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _cord);
				cout << " ";
				_cord.Y = _menu_size;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _cord);
				cout << arrow;
			}
			break;
		case 80:
			if (_cord.Y < _menu_size)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _cord);
				cout << " ";
				++_cord.Y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _cord);
				cout << arrow;
			}
			else
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _cord);
				cout << " ";
				_cord.Y = 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _cord);
				cout << arrow;
			}
			break;
		}
	}
	return _cord.Y;
}