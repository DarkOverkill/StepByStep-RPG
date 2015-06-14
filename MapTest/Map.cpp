#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <cctype>
using namespace std;
void Turn(COORD &, int**, const int*, const int*);
int main()
{
	char ch;
	COORD cord;
	int** matrix;
	int width = 0, height = 1;
	ifstream inFile3("test.txt");
	while (inFile3)
	{
		inFile3.get(ch);
		if (height == 1 && ch != 10)
			++width;
		if (ch == 10)
			++height;
	}
	inFile3.close();
	*&matrix = new int*[height];
	for (int i = 0; i < height; ++i)
	{
		matrix[i] = new int[width];
	}
	inFile3.open("test.txt");
	int i = 0, j = 0;
	while (inFile3)
	{
		inFile3.get(ch);
		switch (ch)
		{
		case 10:
			++j;
			i = 0;
			break;
		case 101:
			matrix[j][i] = 4;
			cord.X = i++;
			cord.Y = j;
			break;
		case 32:
			matrix[j][i++] = 0;
			break;
		default:
				   matrix[j][i++] = static_cast<int>(ch);
		}
	}
	//for (int i = 0; i < height; ++i)
	//{
	//	for (int j = 0; j < width; ++j)
	//		cout << static_cast<char>(matrix[i][j]);
	//	cout << endl;
	//}
	Turn(cord, matrix, &height, &width);
	system("CLS");
	Turn(cord, matrix, &height, &width);
	return 0;
}
void Turn(COORD &cord, int** matrix, const int* height, const int* width)
{
	int t = 0;
	for (int i = 0; i < *height; ++i)
	{
		for (int j = 0; j < *width; ++j)
		{
			if (matrix[i][j] == 4)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
				cout << static_cast<char>(matrix[i][j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
			else
			{
				if (isdigit (static_cast<char>(matrix[i][j]) ) )
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
					cout << static_cast<char>(matrix[i][j]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				}
				else if (matrix[i][j] == 120)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
					cout << static_cast<char>(matrix[i][j]);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				}
				else
					cout << static_cast<char>(matrix[i][j]);
			}
		}
		cout << endl;
	}
	while (t != 27)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
		t = _getch();
		switch (t)
		{
		case 72:
			if (matrix[cord.Y - 1][cord.X] != 42)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
				cout << " ";
				--cord.Y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
				cout << static_cast<char>(4);
				Sleep(100);
			}
			break;
		case 80:
			if (matrix[cord.Y + 1][cord.X] != 42)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
				cout << " ";
				++cord.Y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
				cout << static_cast<char>(4);
				Sleep(100);
			}
			break;
		case 77:
			if (matrix[cord.Y][cord.X + 1] != 42)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
				cout << " ";
				++cord.X;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
				cout << static_cast<char>(4);
				Sleep(100);
			}
			break;
		case 75:
			if (matrix[cord.Y][cord.X - 1] != 42)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
				cout << " ";
				--cord.X;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
				cout << static_cast<char>(4);
				Sleep(100);
			}
			break;
		}

	}
}