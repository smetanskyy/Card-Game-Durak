#include "Game.h"

ostream& operator << (ostream &show, const Card &card);
ostream& operator << (ostream &show, const Player &obj);

//задаємо рандомно козирь
Suit SetTrumps();

int main()
{
	srand(time(nullptr));
	int countCardsInDeck = 36;
	char name[20];
	cout << "Hello, you're playing the game DURAK.\n";
	cout << "What is your name: ";
	cin.getline(name, 20);
	//перевірка правильності введення данних, якщо ні задаємо unknown
	if (name[0] == '\0' || name[0] >= ' ' && name[0] <= '@')
		strcpy_s(name, 20, "unknown");
	cout << "You can play with computer or see how play computers!\n";
	bool personInGame = false;
	char choice;
	cout << "You will play ('Y' - yes or 'N' - no): ";
	do
	{
		cin >> choice;
		switch (choice)
		{
		case 'Y':
		case'y':
			personInGame = true;
			cout << "You in game! Good luck!\n";
			break;
		case 'N':
		case 'n':
			personInGame = false;
			cout << "You will watch the game!\n";
			break;
		default:
			cout << "Try again!:  ";
			break;
		}
		if (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n')
			break;
	} while (true);

	cout << "How many players (min 2 max 6): ";
	int countPlayers = 0;
	do
	{
		cin >> choice;
		switch (choice)
		{
		case '2':
			countPlayers = 2;
			break;
		case '3':
			countPlayers = 3;
			break;
		case '4':
			countPlayers = 4;
			break;
		case '5':
			countPlayers = 5;
			break;
		case '6':
			countPlayers = 6;
			break;
		default:
			cout << "Try again!: ";
			break;
		}
	} while (countPlayers == 0);
	system("cls");
	Suit trumps = SetTrumps();
	Card ** deck = CreateDeck(trumps);
	Game game{ deck, name, personInGame, countPlayers, countCardsInDeck };
	game.AllGame();
	return 0;
}

ostream& operator << (ostream &show, const Card &card)
{
	switch (card.rank)
	{
	case Six:
		show << "6";
		break;
	case Seven:
		show << "7";
		break;
	case Eight:
		show << "8";
		break;
	case Nine:
		show << "9";
		break;
	case Ten:
		show << "10";
		break;
	case Jack:
		show << "J";
		break;
	case Queen:
		show << "Q";
		break;
	case King:
		show << "K";
		break;
	case Ace:
		show << "A";
		break;
	}
	show << "";
	switch (card.suit)
	{
	case Diamonds:
		show << "D";
		break;
	case Hearts:
		show << "H";
		break;
	case Spades:
		show << "S";
		break;
	case Clubs:
		show << "C";
		break;
	}
	return show;
}


ostream& operator << (ostream &show, const Player &obj)
{
	show << "NAME: " << obj.name << "\t";
	show << "CARDS: ";
	for (int i = 0; i < obj.countCards; i++)
	{
		cout << *obj.cardsOnhands[i] << " ";
	}
	return show;
}

Suit SetTrumps()
{
	Suit trumps;
	switch (rand() % 4)
	{
	case Diamonds:
		trumps = Diamonds;
		cout << "TRUMPS IS Diamonds\n\n";
		break;
	case Hearts:
		trumps = Hearts;
		cout << "TRUMPS IS Hearts\n\n";
		break;
	case Spades:
		trumps = Spades;
		cout << "TRUMPS IS Spades\n\n";
		break;
	case Clubs:
		trumps = Clubs;
		cout << "TRUMPS IS Clubs\n\n";
		break;
	}
	return trumps;
}