void Controls()
{
	cout << "To move you charecter use keys: " << static_cast<char>(24) << static_cast<char>(25) << static_cast<char>(26) << static_cast<char>(27) << endl;
	cout << "To enter shop press: " << "s\n";
	cout << "To look your inventory press: " << "i\n";
	cout << "For exit from game press Esc \n";
	cout << "\n\tDescription of elements:\n";
	SetTextColorGreen();
	cout << static_cast<char>(1);
	SetTextColorWhite();
	cout << " - your charecter.\n";
	SetTextColorRed();
	cout << "1";
	SetTextColorWhite();
	cout << " - enemy, digit is a level of the enemy.\n";
	SetTextColorGreen();
	cout << "x";
	SetTextColorWhite();
	cout << " - exit, to win the game you must go there.\n";

	cout << "\n\tTutorial:\n";
	cout << "Map load, from .txt file, you can make your oun map, draw it by exemple, set in the directory /Map, were is located .exe file of the game and renamed it to \"map_1.txt\".\n";
	cout << "Type of enemy load randomly every time.\n";
	cout << "To input item, you must enter your inventory end chose which you want to input. Be careful, look if there if enough of parametrs to input. If you have two or more the same"
		<< " items, only one of them can be on you, but there is no restrictions if the items diffrent.\n";
	cout << "You heal one HP for turn.\n";
	cout << "\n\tParameters affect:\n";
	cout << "Every 3 dex is give to you 2 armor\n";
	cout << "HP = lvl * 5 + vit * 5\n";
	cout << "Damage = lvl * 1.5 + str\t + random from 0 to 4";
}