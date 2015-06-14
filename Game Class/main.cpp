#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <iomanip>
using namespace std;

#include "SetColor.h"
#include "manual.h"
#include "choice.h"
#include "Character.h"
#include "Enemy.h"
#include "MapLoad.h"
#include "inventory.h"
#include "fight.h"


Character c;
Enemy** en;
int** ID_enemy; //id ворога відносно кординат на карті(номер клітини)
int* width_of_map = new int;
int* height_of_map = new int;
int size_of_inv = 5;
Item** item = new Item*[size_of_inv];
void Go_to_Shop(Item* shop[])
{
	const int count_items = 3;
	char* name[count_items];
	for (int i = 0; i < count_items; ++i)
	{
		name[i] = shop[i]->Name();
	}
	Choice shop_menu(4, "Assortiment of the shop: ", name[0], name[1], name[2], "Exit");
	int choice_in_shop = 0;
	while (choice_in_shop != 4)
	{
		shop_menu.ShowMenu();
		choice_in_shop = shop_menu.Turn();
		system("CLS");
		if (choice_in_shop != 4)
		{
			shop[choice_in_shop - 1]->ShowInfo();
			shop[choice_in_shop - 1]->ShowCost();
			char buy = 0;
			cout << "Your gold: " << c.Get_Gold() << endl << endl;
			cout << "\n\tWant to buy? Yes - y / No - n\n";
			while (buy != 'y' && buy != 'n')
				buy = _getch();
			if (buy == 'y')
			{
				if (c.Get_Gold() >= shop[choice_in_shop - 1]->Get_Cost())
				{
					for (int i = 0; i < _msize(item) / sizeof(item); ++i)
					{
						if (item[i] == NULL)
						{
							item[i] = shop[choice_in_shop - 1];
							c.Set_Gold(-shop[choice_in_shop - 1]->Get_Cost());
							i = _msize(item) / sizeof(item);
							cout << "You buy " << shop[choice_in_shop - 1]->Name();
							Sleep(700);
						}
						else if (i == (_msize(item) / sizeof(item)-1) && (item[i] != NULL))
						{
							cout << "Your inventory is fool!\n";
							Sleep(700);
						}
					}
				}
				else
				{
					cout << "You haven't enough gold!\n";
					Sleep(700);
				}
			}
		}
	}
}
void Inventory()
{
	int inv_size = _msize(item) / sizeof(item);
	char** name = new char*[inv_size];
	for (int i = 0; i < inv_size; ++i)
	{
		if (item[i])
			name[i] = item[i]->Name();
		else
			name[i] = "N/A";
	}
	Choice inventory_menu(6, "Inventory: ", name[0], name[1], name[2], name[3], name[4], "Exit");
	COORD look_on_off;
	look_on_off.X = 25;
	look_on_off.Y = 0;
	
	int choice_in_inv = 0;
	while (choice_in_inv != 6)
	{
		inventory_menu.ShowMenu();
		for (int i = 0; i < inv_size; ++i)
		{
			if (item[i])
			{
				look_on_off.Y = i + 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), look_on_off);
				item[i]->Check_on_Dress() ? cout << "on" : cout << "off";
			}
		}
		choice_in_inv = inventory_menu.Turn();
		if (choice_in_inv != (inv_size + 1) && item[choice_in_inv - 1] != NULL)
		{
			if (!item[choice_in_inv - 1]->Check_on_Dress())
				item[choice_in_inv - 1]->ON(&c);
			else
				item[choice_in_inv - 1]->OFF(&c);
		}
	}
}
int main()
{
	Item* shop[3] = { new Armor_1, new Weapon_1, new Weapon_2 };
	for (int i = 0; i < size_of_inv; ++i)
	{
		item[i] = NULL;
	}
	srand(unsigned(time(NULL)));
	int** Map = NULL;
	COORD player_cord;
	COORD exit_cord;
	Choice menu(5, "menu ", "Start", "Controls", "Settings", "About Game", "Exit");
	int start_game = 0;
	while (start_game != 1)
	{
		menu.ShowMenu();
		start_game = menu.Turn();
		system("CLS");
		switch (start_game)
		{
		case 1:
			break;
		case 2: 
			Controls();
			_getch();
			break;
		case 3:
			cout << "in progres...\n";
			_getch();
			break;
		case 4:
			cout << "Turn based RPG.\nCreator - Maxym Fedas\n";
			_getch();
			break;
		case 5:
			exit(0);
			break;
		}
	}
	LoadMap(Map, ID_enemy, width_of_map, height_of_map, player_cord, exit_cord);
	DrawMap(Map, width_of_map, height_of_map);
	int re_turn = 0;
	
	while (re_turn != 27)
	{
		re_turn = Turn(Map, player_cord, exit_cord);
		if (re_turn == 111)
		{
			if (item[0])
			{
				item[0]->ON(&c);
				DrawMap(Map, width_of_map, height_of_map);
			}
		}
		if (re_turn == 102)
		{
			if (item[0])
			{
				item[0]->OFF(&c);
				DrawMap(Map, width_of_map, height_of_map);
			}
		}
		if (re_turn == 115)
		{
			Go_to_Shop(shop);
			DrawMap(Map, width_of_map, height_of_map);
		}
		if (re_turn == 105)
		{
			Inventory();
			DrawMap(Map, width_of_map, height_of_map);
		}
	};
	return 0;
}