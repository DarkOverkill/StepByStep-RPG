extern int* width_of_map;
class Enemy
{
protected:
	int _max_hp;
	int _hp;
	int _dmg;
	int _armor;
	int _reward_gold;
	int _reward_exp;
	int _id;
public:
	Enemy() :_reward_gold(rand() % 11 + 20), _reward_exp(45)
	{}
	virtual int Damage(bool* Foo)
	{
		int dmg_turn;
		dmg_turn = rand() % 4 + _dmg;// дамаг от dmg + 0 до dmg + 3
		return dmg_turn;
	}
	virtual void Who_I_Am() = 0;
	void Set_ID(int id)
	{
		_id = id;
	}
	int Get_ID()
	{
		return _id;
	}
	int Get_HP()
	{
		return _hp;
	}
	int Get_armor()
	{
		return _armor;
	}
	void minusHP(int dmg)
	{
		_hp -= dmg;
	}
	void ShowHp();
	int Get_Reward_Exp()
	{
		return _reward_exp;
	}
	int Get_Reward_Gold()
	{
		return _reward_gold;
	}
};
void Enemy::ShowHp()
{
	int percent;
	percent = _hp * 100 / _max_hp;
	cout << "HP: ";
	if (percent < 30)
		SetTextColorRed();
	else if (percent < 70)
		SetTextColorYellow();
	else
		SetTextColorGreen();
	for (int i = 0; i < 100; i += 10)
	{
		if (i < percent)
			cout << static_cast<char>(219);
		else
			cout << " ";
	}
	SetTextColorWhite();
	cout << _hp << " / " << _max_hp;
}

class Crit_1 : public Enemy
{
protected:
	int _crit_chance; //в процентах
	double _crit_power; // множитель урона
public:
	Crit_1() : _crit_chance(15), _crit_power(1.7)
	{
		_hp = _max_hp = 20;  _armor = 1; _dmg = 5;
	}
	int Damage(bool *skill_pass)
	{
		int dmg_turn; //дамаг текущего хода
		int temp; // для опредиления прошол ли крит
		temp = rand() % 100;
		(temp < _crit_chance) ? (*skill_pass = true) : (*skill_pass = false);
		if (*skill_pass)
		{
			dmg_turn = static_cast<int>( (rand() % 4 + _dmg) * _crit_power );
			return dmg_turn;
		}
		else
		{
			dmg_turn = rand() % 4 + _dmg;
			return dmg_turn;
		}
	}
	void Who_I_Am()
	{
		COORD temp;
		temp.X = *width_of_map + 3;
		temp.Y = 2;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
		cout << "Crit";
		++temp.Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
		cout << "HP: " << _hp;
		++temp.Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
		cout << "Armor: " << _armor;
		++temp.Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
		cout << "Damage: " << _dmg << "-" << _dmg + 3; 
		++temp.Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
		cout << "Crit chance: " << _crit_chance <<"%"; 
		++temp.Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
		cout << "Crit power: " << _crit_power << endl;
	}
};
class Crit_2 : public Crit_1
{
public:
	Crit_2() 
	{
		_hp = _max_hp *= 2; 
		_armor += 1; 
		_dmg *= 1.8;
		_crit_chance += 3;
		_crit_power += 0.2;
		_reward_exp *= 2;
		_reward_gold += 15;
	}
};
class Crit_3 : public Crit_2
{
public:
	Crit_3()
	{
		_hp = _max_hp *= 2;
		_armor += 1;
		_dmg *= 1.8;
		_crit_chance += 3;
		_crit_power += 0.2;
		_reward_exp *= 2;
		_reward_gold += 15;
	}
};
class Crit_4 : public Crit_3
{
public:
	Crit_4()
	{
		_hp = _max_hp *= 2;
		_armor += 1;
		_dmg *= 1.8;
		_crit_chance += 3;
		_crit_power += 0.2;
		_reward_exp *= 2;
		_reward_gold += 15;
	}
};
class Dodger_1 : public Enemy
{
protected:
	int evesition_chance; // шанс уворота
public:
	Dodger_1() : evesition_chance(22)
	{
		_hp = _max_hp = 18; _armor = 2; _dmg = 5;
	}
	int Damage(bool *skill_pass)
	{
		int dmg_turn; // дамаг текущего хода
		int temp_skill_pass; // проход скила
		temp_skill_pass = rand() % 100;
		(temp_skill_pass < evesition_chance) ? (*skill_pass = true) : (*skill_pass = false);
		dmg_turn = rand() % 4 + _dmg;
		return dmg_turn;
	}
	void Who_I_Am()
	{
		COORD temp;
		temp.X = *width_of_map + 3;
		temp.Y = 2;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
		cout << "Dodger";
		++temp.Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
		cout << "HP: " << _hp;
		++temp.Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
		cout << "Armor: " << _armor;
		++temp.Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
		cout << "Damage: " << _dmg << "-" << _dmg + 3;
		++temp.Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
		cout << "Evesition chance: " << evesition_chance << "%\n";
	}
};
class Dodger_2 : public Dodger_1
{
public:
	Dodger_2()
	{
		_hp = _max_hp *= 1.5;
		_armor += 2;
		_dmg *= 1.8;
		evesition_chance += 5;
		_reward_exp *= 2;
		_reward_gold += 15;
	}
};
class Dodger_3 : public Dodger_2
{
public:
	Dodger_3()
	{
		_hp = _max_hp *= 1.5;
		_armor += 2;
		_dmg *= 1.8;
		evesition_chance += 5;
		_reward_exp *= 2;
		_reward_gold += 15;
	}
};
class Dodger_4 : public Dodger_3
{
public:
	Dodger_4()
	{
		_hp = _max_hp *= 1.5;
		_armor += 2;
		_dmg *= 1.8;
		evesition_chance += 5;
		_reward_exp *= 2;
		_reward_gold += 15;
	}
};

class Tank_1 : public Enemy
{
public:
	Tank_1()
	{
		_hp = _max_hp = 30;
		_armor = 4;
		_dmg = 4;	
	}
	void Who_I_Am()
	{
		COORD temp;
		temp.X = *width_of_map + 3;
		temp.Y = 2;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
		cout << "Tank";
		++temp.Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
		cout << "HP: " << _hp;
		++temp.Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
		cout << "Armor: " << _armor;
		++temp.Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
		cout << "Damage: " << _dmg << "-" << _dmg + 3 << endl;
	}
};
class Tank_2 : public Tank_1
{
public:
	Tank_2()
	{
		_hp = _max_hp *= 2.2;
		_armor = +3;
		_dmg *= 1.8;
		_reward_exp *= 2;
		_reward_gold += 15;
	}
};
class Tank_3 : public Tank_2
{
public:
	Tank_3()
	{
		_hp = _max_hp *= 2.2;
		_armor = +3;
		_dmg *= 1.8;
		_reward_exp *= 2;
		_reward_gold += 15;
	}
};
class Tank_4 : public Tank_3
{
public:
	Tank_4()
	{
		_hp = _max_hp *= 2.2;
		_armor = +3;
		_dmg *= 1.8;
		_reward_exp *= 2;
		_reward_gold += 15;
	}
};