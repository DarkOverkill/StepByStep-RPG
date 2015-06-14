const int LEN = 25;
enum kind{ armor, weapon };
class Item
{
protected:
	int _id;
	char _name[LEN];
	int _hp_plus;
	int _dmg_plus;
	int _armor_plus;
	int _str_plus;
	int _dex_plus;
	int _vit_plus;
	bool _on_off;
	int _cost;
	struct
	{
		int _lvl_require;
		int _str_require;
		int _dex_require;
		int _vit_require;
	} requires;
	friend class Character;
public:
	Item() : _id(-1), _hp_plus(0), _dmg_plus(0), _armor_plus(0), _str_plus(0), _dex_plus(0), _vit_plus(0), _on_off(false), _cost(0)
	{
		strcpy_s(_name, LEN, "no name");
		requires._lvl_require = 1;
		requires._str_require = requires._dex_require = requires._vit_require = 0;
	}
	void ShowInfo()
	{
		switch (_id)
		{
		case armor:
			cout << "Armor: ";
			break;
		case weapon:
			cout << "Weapon: ";
			break;
		}
		cout << _name << endl << endl;
		if (_hp_plus)
			cout << "HP +" << _hp_plus << endl;
		if (_dmg_plus)
			cout << "Damage +" << _dmg_plus << endl;
		if (_armor_plus)
			cout << "Armor +" << _armor_plus << endl;
		if (_str_plus)
			cout << "Strength +" << _str_plus << endl;
		if (_dex_plus)
			cout << "Dexterity +" << _dex_plus << endl;
		if (_vit_plus)
			cout << "Vitality +" << _vit_plus << endl;
		cout << "\n\tRequires:\n";
		cout << "Need lvl - [" << requires._lvl_require << "]\n";
		if (requires._str_require)
			cout << "Need str - " << requires._str_require << endl;
		if (requires._dex_require)
			cout << "Need dex - " << requires._dex_require << endl;
		if (requires._vit_require)
			cout << "Need vit - " << requires._vit_require << endl;
		cout << endl;
	}
	bool Check_on_Dress()
	{
		return _on_off;
	}
	bool Check_Requires(Character* c)
	{
		if ((requires._str_require <= c->attributes._str) && (requires._dex_require <= c->attributes._dex) && (requires._vit_require <= c->attributes._vit) && (requires._lvl_require <= c->_lvl))
			return true;
		return false;
	}
	bool ON(Character *c)
	{
		if (Check_Requires(c))
		{
			if (!Check_on_Dress())
			{
				c->_hp += _hp_plus;
				c->_max_hp += _hp_plus;
				c->_dmg += _dmg_plus;
				c->_armor += _armor_plus;
				c->attributes._str += _str_plus;
				c->attributes._dex += _dex_plus;
				c->attributes._vit += _vit_plus;
				_on_off = true;
			}
		}
		return _on_off;
	}
	void OFF(Character *c)
	{
		if (Check_on_Dress())
		{
			c->_max_hp -= _hp_plus;
			if (c->_hp > c->_max_hp)
				c->_hp = c->_max_hp;
			c->_dmg -= _dmg_plus;
			c->_armor -= _armor_plus;
			c->attributes._str -= _str_plus;
			c->attributes._dex -= _dex_plus;
			c->attributes._vit -= _vit_plus;
			_on_off = false;
		}
	}
	void ShowCost()
	{
		cout << "Cost: " << _cost << " gold.\n";
	}
	int Get_Cost()
	{
		return _cost;
	}
	char* Name()
	{
		return _name;
	}
};
class Armor_1 : public Item
{
public:
	Armor_1()
	{
		_id = armor;
		strcpy_s(_name, LEN - 1, "Armor of Fear");
		_hp_plus = 50;
		_armor_plus = 5;
		_cost = 220;
		_str_plus = 1;
		requires._lvl_require = 2;
		requires._str_require = 6;
		requires._vit_require = 6;
	}
};
class Weapon_1 : public Item
{
public:
	Weapon_1()
	{
		_id = weapon;
		strcpy_s(_name, LEN - 1, "Frostmourne");
		_dmg_plus = 25;
		_armor_plus = 2;
		_cost = 250;
		requires._lvl_require = 4;
		requires._str_require = 9;
		requires._dex_require = 7;
	}
};
class Weapon_2 : public Item
{
public:
	Weapon_2()
	{
		_id = weapon;
		strcpy_s(_name, LEN - 1, "Dauntless");
		_dmg_plus = 10;
		_cost = 150;
		requires._lvl_require = 2;
		requires._str_require = 5;
		requires._dex_require = 6;
	}
};