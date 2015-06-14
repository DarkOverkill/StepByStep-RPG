class Character
{
private:
	struct
	{
		int _str;//сила, влияет на силу удара
		int _dex;//ловка, броня
		int _vit;//винос, к-во НР
	}attributes;
	int _hp; // текущее НР
	int _max_hp; // lvl*2 + vit*5 
	int _armor; // +2 for every 3 dex
	int _dmg; // lvl*1.5 + _str
	int _exp; // текущий опыт
	int _exp_next_lvl; // опыт на след уровень
	int _lvl; // уровень
	int _gold; //деньги
	friend class Item;
public:
	Character() : _lvl(1), _exp(0), _exp_next_lvl(100), _gold(0)
	{
		attributes._str = 5;
		attributes._dex = 5;
		attributes._vit = 5;
		_max_hp = _lvl * 2 + attributes._vit * 6;
		_hp = _max_hp;
		_armor = (attributes._dex / 3) * 2;
		_dmg = static_cast<int>(_lvl * 1.5) + attributes._str;	
	}
	void ShowInfo();
	void lvl_Up();
	bool get_exp(unsigned int);
	void ShowHp();
	void minusHP(int);
	void Set_HP(int n)
	{
		while (_hp < _max_hp && n)
		{
			++_hp;
			--n;
		}
	}
	int Get_HP()
	{
		return (_hp);
	}
	int Get_armor()
	{
		return _armor;
	}
	int Damage()
	{
		int turn_dmg = rand() % 4 + _dmg; // дамаг хода, разброс рандома от dmg-0 до dmg+3
		return turn_dmg;
	}
	void Set_Exp(int exp)
	{
		_exp += exp;
	}
	void Set_Gold(int gold)
	{
		_gold += gold;
	}
	int Get_Gold()
	{
		return _gold;
	}
	void ShowAttributes();
};
void Character::ShowAttributes()
{
	cout << "\tYour str - " << attributes._str << endl;
	cout << "\tYour dex - " << attributes._dex << endl;
	cout << "\tYour vit - " << attributes._vit << endl;
}
void Character::ShowHp()
{
	int percent;
	percent = _hp*100 / _max_hp;
	cout << "HP: ";
	if (percent < 30)
		SetTextColorRed();
	else if (percent < 70)
		SetTextColorYellow();
	else
		SetTextColorGreen();
	for (int i = 0; i < 100; i+=10)
	{
		if (i < percent)
			cout << static_cast<char>(219);
		else
			cout << " ";
	}
	SetTextColorWhite();
	cout << setw(3) << _hp << " / " << _max_hp;
}
void Character::minusHP(int dmg)
{
	_hp -=dmg;
}
bool Character::get_exp(unsigned int exp)
{
	_exp += exp;
	if (_exp >= _exp_next_lvl) 
		return true;
	return false;	
}
void Character::ShowInfo()
{
	//system("CLS");
	cout << "LVL [" << _lvl << "] \t";
	ShowHp();
	cout << "\t\texp: " << _exp << " / " << _exp_next_lvl << "\tGold: " << _gold << "$\n\n";
	cout << "str - " << attributes._str << endl;
	cout << "dex - " << attributes._dex << endl;
	cout << "vit - " << attributes._vit << endl;
	cout << "\tdmg: " << _dmg << "-" <<_dmg + 4;
	cout << "\tarmor: " << _armor << endl;
}

void Character::lvl_Up()
{
	cout << "NEW LEVEL! press ";
	SetTextColorYellow();
	cout << "+";
	SetTextColorWhite();
	cout << " to add parameters\n";
	int continion = 0;
	while (continion != 43)
	{
		continion = _getch();
	}
	++_lvl;
	_exp_next_lvl *= 2;
	int attribute_plus = 3;
	Choice a(3 , "Select attribute which you want to increase:", "Strength", "Dexterity", "Vitality");
	while (attribute_plus--)
	{
		a.ShowMenu();
		cout << "\nYou have free attributes: " << attribute_plus + 1 << endl << endl;
		ShowAttributes();
		switch (a.Turn())
		{
		case 1:
			++attributes._str;
			break;
		case 2:
			++attributes._dex;
			break;
		case 3:
			++attributes._vit;
			break;
		}
	}
	_max_hp = _lvl * 2 + attributes._vit * 6;
	_hp = _max_hp;
	_armor = (attributes._dex / 3) * 2;
	_dmg = static_cast<int>(_lvl * 1.5) + attributes._str;
	system("CLS");
}