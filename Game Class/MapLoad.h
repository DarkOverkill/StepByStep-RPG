#include <fstream>
extern Enemy** en;
extern Character c;
extern int* width_of_map;
extern int* height_of_map;
extern int** ID_enemy;
extern Item** item;
int Fight(Character* ch, Enemy** en, int i, Item** item);
void LoadMap(int**& Map, int**&ID_enemy, int* width, int* height, COORD &player_cord, COORD &exit_cord)
{
	ifstream inFile("Map\\map_1.txt");
	if (inFile.fail())
	{
		cout << "Error! Don't find map!";
		_getch();
		exit(-1);
	}
	else
	{
		int temp_width = 0, temp_height = 1; // ширина висота карти
		char ch; // символ на карты
		int enemys = 0; // к-ть ворогів
		while (inFile)
		{
			inFile.get(ch);
			if (temp_height == 1 && ch != 10) // рахуемо ширину поки незустрынем перший символ переходу на нову строку
				++temp_width;
			if (ch == 10) // якщо переход на нову строку плюсуем висоту
				++temp_height;
			if (isdigit(ch))
				++enemys;
		}
		inFile.close();
		*&Map = new int*[temp_height]; // створюем масив, для збереження інфи по клітин карти
		*&ID_enemy = new int*[temp_height];
		*&en = new Enemy*[enemys];
		int id = 0;
		for (int i = 0; i < temp_height; ++i)
		{
			Map[i] = new int[temp_width];
			ID_enemy[i] = new int[temp_width];
		}
		*height = temp_height;
		*width = temp_width;
		inFile.open("Map\\map_1.txt");
		int w = 0, h = 0; //width height
		while (inFile)
		{
			inFile.get(ch); // зчитуєм символ з файлу
			switch (ch)
			{
			case 10: // нова сторка
				++h; // збільшили висоту
				w = 0; // зкинули ширину на 0
				break;
			case 101: // точка входу персонажа
				Map[h][w] = 1;
				player_cord.X = w++; // кординати перонажу
				player_cord.Y = h;
				break;
			case 32: // пробел
				Map[h][w++] = 0;
				break;
			case 120:
				Map[h][w] = 120;
				exit_cord.X = w++;
				exit_cord.Y = h;
				break;
			default:
				if (isdigit(ch))
				{
					int class_of_en = rand() % 3;
					switch (class_of_en)
					{
					case 0:
						switch (ch)
						{
						case '2':
							en[id] = new Crit_2;
							en[id]->Set_ID(0);
							break;
						case '3':
							en[id] = new Crit_3;
							en[id]->Set_ID(0);
							break;
						case '4':
							en[id] = new Crit_4;
							en[id]->Set_ID(0);
							break;
						default:
							en[id] = new Crit_1;
							en[id]->Set_ID(0);
						}
						break;
					case 1:
						switch (ch)
						{
						case '2':
							en[id] = new Dodger_2;
							en[id]->Set_ID(1);
							break;
						case '3':
							en[id] = new Dodger_3;
							en[id]->Set_ID(1);
							break;
						case '4':
							en[id] = new Dodger_4;
							en[id]->Set_ID(1);
							break;
						default:
							en[id] = new Dodger_1;
							en[id]->Set_ID(1);
						}
						break;
					case 2:
						switch (ch)
						{
						case '2':
							en[id] = new Tank_2;
							en[id]->Set_ID(2);
							break;
						case '3':
							en[id] = new Tank_3;
							en[id]->Set_ID(2);
							break;
						case '4':
							en[id] = new Tank_4;
							en[id]->Set_ID(2);
							break;
						default:
							en[id] = new Tank_1;
							en[id]->Set_ID(2);
						}
						break;
					}

					ID_enemy[h][w] = id++;
				}
				Map[h][w++] = static_cast<int>(ch);
			}
		}
	}
}

void DrawMap(int** map, const int* width, const int* height)
{
	system("CLS");
	for (int i = 0; i < *height; ++i)
	{
		for (int j = 0; j < *width; ++j)
		{
			if (map[i][j] == 1) // player
			{
				SetTextColorGreen();
				cout << static_cast<char>(map[i][j]);
				SetTextColorWhite();
			}
			else
			{
				if (isdigit(static_cast<char>(map[i][j]))) // enemy
				{
					SetTextColorRed();
					cout << static_cast<char>(map[i][j]);
					SetTextColorWhite();
				}
				else if (map[i][j] == 120) // exit
				{
					SetTextColorGreen();
					cout << static_cast<char>(map[i][j]);
					SetTextColorWhite();
				}
				else if (map[i][j] == 42) //wall
					cout << static_cast<char>(219);
				else
					cout << static_cast<char>(map[i][j]);
			}
		}
		cout << endl;
	}
	c.ShowInfo();
}

int Check_on_Enemy(int** map, const COORD& cord)
{
	if (isdigit(map[cord.Y][cord.X]))
	{
		char to_fight = 0;
		COORD temp;
		temp.X = *width_of_map + 2;
		temp.Y = 10;
		en[ID_enemy[cord.Y][cord.X]]->Who_I_Am();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
		cout << "Fight: Yes - y / No - n";
		while (to_fight != 'y' && to_fight != 'n')
		{
			to_fight = _getch();
		}
		if (to_fight == 'y')
		{
			Fight(&c, en, ID_enemy[cord.Y][cord.X], item);
			DrawMap(map, width_of_map, height_of_map);
			return 1;
		}
		DrawMap(map, width_of_map, height_of_map);
		return -1;
	}
	return 1;
}
void Regeneration()
{
	c.Set_HP(1); //реген ХП
	COORD temp;
	temp.Y = *height_of_map;
	temp.X = 16;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
	c.ShowHp();
}

int Turn(int** map, COORD& player_cord, COORD& exit_cord)
{
	int turn = 0;
	COORD next_cell;
	turn = _getch();
	if (turn == 224)
		turn = _getch();
	switch (turn)
	{
	case 72: //up
		if (map[player_cord.Y - 1][player_cord.X] != 42)
		{
			next_cell.X = player_cord.X;
			next_cell.Y = player_cord.Y - 1;
			if (Check_on_Enemy(map, next_cell) == 1)
			{
				map[player_cord.Y][player_cord.X] = 0;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), player_cord);
				cout << " ";
				--player_cord.Y;
				map[player_cord.Y][player_cord.X] = 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), player_cord);
				SetTextColorGreen();
				cout << static_cast<char>(map[player_cord.Y][player_cord.X]);
				SetTextColorWhite();
				Regeneration();
				Sleep(100);
			}
		}
		break;
	case 80: // down
		if (map[player_cord.Y + 1][player_cord.X] != 42)
		{
			next_cell.X = player_cord.X;
			next_cell.Y = player_cord.Y + 1;
			if (Check_on_Enemy(map, next_cell) == 1)
			{
				map[player_cord.Y][player_cord.X] = 0;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), player_cord);
				cout << " ";
				++player_cord.Y;
				map[player_cord.Y][player_cord.X] = 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), player_cord);
				SetTextColorGreen();
				cout << static_cast<char>(map[player_cord.Y][player_cord.X]);
				SetTextColorWhite();
				Regeneration();
				Sleep(100);
			}
		}
		break;
	case 77: //right
		if (map[player_cord.Y][player_cord.X + 1] != 42)
		{
			next_cell.X = player_cord.X + 1;
			next_cell.Y = player_cord.Y;
			if (Check_on_Enemy(map, next_cell) == 1)
			{
				map[player_cord.Y][player_cord.X] = 0;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), player_cord);
				cout << " ";
				++player_cord.X;
				map[player_cord.Y][player_cord.X] = 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), player_cord);
				SetTextColorGreen();
				cout << static_cast<char>(map[player_cord.Y][player_cord.X]);
				SetTextColorWhite();
				Regeneration();
				Sleep(100);
			}
		}
		break;
	case 75: // left
		if (map[player_cord.Y][player_cord.X - 1] != 42)
		{
			next_cell.X = player_cord.X - 1;
			next_cell.Y = player_cord.Y;
			if (Check_on_Enemy(map, next_cell) == 1)
			{
				map[player_cord.Y][player_cord.X] = 0;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), player_cord);
				cout << " ";
				--player_cord.X;
				map[player_cord.Y][player_cord.X] = 1;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), player_cord);
				SetTextColorGreen();
				cout << static_cast<char>(map[player_cord.Y][player_cord.X]);
				SetTextColorWhite();
				Regeneration();
				Sleep(100);
			}
		}
		break;
	}
	if (player_cord.X == exit_cord.X && player_cord.Y == exit_cord.Y)
	{
		cout << "Congratulate you win! To be continion...\n";
		_getch();
		exit(0);
	}
	return turn;
}