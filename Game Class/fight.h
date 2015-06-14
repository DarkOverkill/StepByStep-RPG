int Fight(Character* ch, Enemy** en, int i, Item** item)
{
	enum { crit, dodger, tank };
	bool check_on_lvl_up = false;
	bool *enemy_skill_pass = new bool;
	*enemy_skill_pass = false;
	system("CLS");
	cout << "Your ";
	ch->ShowHp();
	cout << "\tEnemy ";
	en[i]->ShowHp();
	cout << "\n\tFIGHT!\n press enter\n";
	int enemy_dmg, player_dmg, enemy_hp = en[i]->Get_HP(), player_hp = ch->Get_HP();
	while ((player_hp = ch->Get_HP()) > 0 && (enemy_hp = en[i]->Get_HP()) > 0)//���� �� ������ ��� ������ �� 0 ��� �����
	{
		_getch();
		system("CLS");
		enemy_dmg = en[i]->Damage(enemy_skill_pass);//������� ����� �����
		enemy_dmg -= ch->Get_armor(); // ������� ����� ������
		if (enemy_dmg <= 0) // ���� ����� 0 ��� �����
			enemy_dmg = 1;//���������� ����������� 1
		player_dmg = ch->Damage();// ����� ������
		player_dmg -= en[i]->Get_armor();// ���� ����� ������
		if (player_dmg <= 0)// ���� ����� �  ��� �����
			player_dmg = 1;// ���������� ��������� 1

		switch (en[i]->Get_ID())
		{
		case crit:
			en[i]->minusHP(player_dmg);//������ �� ������
			ch->minusHP(enemy_dmg);// ������� �� ������
			cout << "Your ";
			ch->ShowHp();
			cout << "\tEnemy ";
			en[i]->ShowHp();
			cout << endl;
			cout << "Your strike ";
			SetTextColorYellow();
			cout << "-" << player_dmg << endl;
			SetTextColorWhite();
			*enemy_skill_pass ? (cout << "Enemy make critical strike ", SetTextColorRed()) : (cout << "Enemy strike ", SetTextColorYellow());
			cout << "-" << enemy_dmg << endl;
			SetTextColorWhite();
			cout << endl;
			break;
		case dodger:
			*enemy_skill_pass ? en[i]->minusHP(0) : en[i]->minusHP(player_dmg);//������ �� ������
			ch->minusHP(enemy_dmg);// ������� �� ������
			cout << "Your ";
			ch->ShowHp();
			cout << "\tEnemy ";
			en[i]->ShowHp();
			cout << endl;
			!*enemy_skill_pass ? (
				cout << "Your strike ",
				SetTextColorYellow(),
				cout << "-" << player_dmg,
				SetTextColorWhite(),
				cout << endl
				) :
				(
				cout << "Enemy ",
				SetTextColorGreen(),
				cout << "dodge ",
				SetTextColorWhite(),
				cout << "your strike\n");
			cout << "Enemy strike ";
			SetTextColorYellow();
			cout << "-" << enemy_dmg << endl;
			SetTextColorWhite();
			cout << endl;
			break;
		case tank:
			en[i]->minusHP(player_dmg);//������ �� ������
			ch->minusHP(enemy_dmg);// ������� �� ������
			cout << "Your ";
			ch->ShowHp();
			cout << "\tEnemy ";
			en[i]->ShowHp();
			cout << endl;
			cout << "Your strike ";
			SetTextColorYellow();
			cout << "-" << player_dmg << endl;
			SetTextColorWhite();
			cout << "Enemy strike ";
			SetTextColorYellow();
			cout << "-" << enemy_dmg << endl;
			SetTextColorWhite();
			cout << endl;
			break;
		}
	}
	_getch();
	if (ch->Get_HP() <= 0 && en[i]->Get_HP() <= 0)
	{
		cout << "Draw! You die, maybe luck will smile you next time!\n";
		exit(-1);
	}
	else if (ch->Get_HP() <= 0 && en[i]->Get_HP() > 0)
	{
		cout << "You Lose! You die, maybe luck will smile you next time!\n";
		exit(-1);
	}
	else if (ch->Get_HP() > 0 && en[i]->Get_HP() <= 0)
	{
		cout << "You Win!\n" << "You receive +" << en[i]->Get_Reward_Exp() << "exp, and " << en[i]->Get_Reward_Gold() << " gold.\n";
		check_on_lvl_up = ch->get_exp(en[i]->Get_Reward_Exp());
		ch->Set_Gold(en[i]->Get_Reward_Gold());
		if (check_on_lvl_up)
		{
			int inv_size = _msize(item) / sizeof(item); // �-�� ������ � ��������
			bool* if_ON = new bool[inv_size]; // ������������ ��� ���� ����
			for (int i = 0; i < inv_size; ++i)
			{
				if (item[i])
					item[i]->Check_on_Dress() ? if_ON[i] = true, item[i]->OFF(ch) : if_ON[i] = false; //���� ���� ����� � ������������� ��
			}
			//item[0]->OFF(ch);
			ch->lvl_Up();
			for (int i = 0; i < inv_size; ++i)
			{
				if (item[i])
				{
					if (if_ON[i]) // ���� ���� ����, �������
						item[i]->ON(ch);
				}
			}
			delete[]if_ON;
			//item[0]->ON(ch);
		}
		return 1;
	}
	return -1;
}