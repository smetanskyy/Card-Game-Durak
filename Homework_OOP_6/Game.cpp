#include "Game.h"

const char* names[]{ "OLIVER", "HARRY", "JACK", "GEORGE", "NOAH", "CHARLIE", "JACOB", "ALFIE", "FREDDIE", "OSCAR", "LEO", "LOGAN", "ARCHIE",
"THEO", "THOMAS", "JAMES", "JOSHUA", "HENRY", "WILLIAM", "MAX", "LUCAS", "ETHAN", "ARTHUR", "MASON", "ISAAC", "HARRISON", "TEDDY", "FINLEY",
"DANIEL", "RILEY", "EDWARD", "JOSEPH", "ALEXANDER", "ADAM", "REGGIE", "SAMUEL", "JAXON", "SEBASTIAN", "ELIJAH", "HARLEY", "TOBY", "ARLO",
"DYLAN", "JUDE", "BENJAMIN", "RORY", "TOMMY", "JAKE", "LOUIE", "CARTER", "JENSON", "HUGO", "BOBBY", "FRANKIE", "OLLIE", "ZACHARY", "DAVID",
"ALBIE", "LEWIS", "LUCA", "RONNIE", "JACKSON", "MATTHEW", "ALEX", "HARVEY", "REUBEN", "JAYDEN", "CALEB", "HUNTER", "THEODORE", "NATHAN",
"BLAKE", "LUKE", "ELLIOT", "ROMAN", "STANLEY", "DEXTER", "MICHAEL", "ELLIOTT", "TYLER", "RYAN", "ELLIS", "FINN", "ALBERT", "KAI", "LIAM",
"CALLUM", "LOUIS", "AARON", "EZRA", "LEON", "CONNOR", "GRAYSON", "JAMIE", "AIDEN", "GABRIEL", "AUSTIN", "LINCOLN", "ELI", "BEN" };

const int MAX_CARDS_IN_PARTY = 12;

Game::Game(Card ** deck, const char* NAME, bool compORperson, int countPlayers, int &countCardsInDeck)
{
	personInGame = compORperson;
	if (countPlayers < 2 || countPlayers > 6)
		exit(1);
	players = new Player*[countPlayers];
	this->countPlayers = countPlayers;
	for (int i = 0; i < countPlayers; i++)
	{
		if (compORperson == true && i == 0)
			players[i] = new Player{ deck, NAME, compORperson, countCardsInDeck };
		else
			players[i] = new Player{ deck, names[rand() % 100], false, countCardsInDeck };
	}
	party = new Card*[MAX_CARDS_IN_PARTY] {nullptr};
	countOfCardInParty = 0;
	beatInGame = true;
	this->deck = deck;
	this->ptrCountCardsInDeck = &countCardsInDeck;
	countExit = 0;
}

Player* Game::ChoiceWhoFirstGo()
{
	Rank smallestTrumps;
	Player* ptr = nullptr;
	for (int i = 0; i < countPlayers; i++)
	{
		for (int j = 0; j < players[i]->GetCountCards(); j++)
		{
			if (players[i]->GetCardsOnhands()[j]->GetTrumps() == true)
			{
				smallestTrumps = players[i]->GetCardsOnhands()[j]->GetRank();
				ptr = players[i];
			}
		}
	}
	for (int i = 0; i < countPlayers; i++)
	{
		for (int j = 0; j < players[i]->GetCountCards(); j++)
		{
			if (ptr != nullptr && smallestTrumps > players[i]->GetCardsOnhands()[j]->GetRank()
				&& players[i]->GetCardsOnhands()[j]->GetTrumps() == true)
			{
				smallestTrumps = players[i]->GetCardsOnhands()[j]->GetRank();
				ptr = players[i];
			}
		}
	}
	if (ptr == nullptr)
		return players[0];
	else
		return ptr;
}

void Game::BetweenTwoPlayers(Player* toss, Player* beat)
{
	if (beatInGame == false)
	{
		while (true)
		{
			if (countTossCards == beat->GetCountCards())
				break;
			if (countTossCards == 6)
				break;

			party[countOfCardInParty] = toss->TossUpCard(party, countOfCardInParty);

			if (party[countOfCardInParty] == nullptr)
			{
				countExit++;
				break;
			}
			cout << toss->GetName() << " tosses a card " << *party[countOfCardInParty] << endl;
			countExit = 0;
			countOfCardInParty++;
			countTossCards++;
		}
	}
	else
	{
		while (true)
		{
			if (countBeatCards == beat->GetCountCards())
			{
				break;
			}

			if (countTossCards == 6)
				break;

			party[countOfCardInParty] = toss->TossUpCard(party, countOfCardInParty);

			if (party[countOfCardInParty] == nullptr)
			{
				countExit++;
				break;
			}

			cout << toss->GetName() << " tosses a card " << *party[countOfCardInParty] << endl;
			countExit = 0;
			countOfCardInParty++;
			countTossCards++;

			party[countOfCardInParty] = beat->BeatCard(party[countOfCardInParty - 1], party, countOfCardInParty);

			if (party[countOfCardInParty] == nullptr)
			{
				cout << "\n" << beat->GetName() << " takes all cards!\n\n";
				beatInGame = false;
				BetweenTwoPlayers(toss, beat);
				break;
			}
			countBeatCards++;
			cout << beat->GetName() << " beats a card by " << *party[countOfCardInParty] << endl;
			countOfCardInParty++;
		}
	}
}

void Game::CheckPlayers()
{
	int temp = countPlayers;
	for (int i = 0; i < countPlayers; i++)
	{
		if (players[i]->GetCountCards() == 0 && beat != players[i])
		{
			cout << "\n" << players[i]->GetName() << " WIN!\n";
			delete players[i];
			players[i] = nullptr;
			temp--;
		}
	}

	for (int i = 0; i < countPlayers; i++)
	{
		for (int j = countPlayers - 1; j > i; j--)
		{
			if (players[j - 1] == nullptr && players[j] != nullptr)
			{
				players[j - 1] = players[j];
				players[j] = nullptr;
			}
		}
	}
	countPlayers = temp;
}

void Game::OneParty(Player* one, Player* beat)
{
	countTossCards = 0;
	countOfCardInParty = 0;
	countBeatCards = 0;
	int positionBeat; // position of player which is beating
	for (int i = 0; i < countPlayers; i++)
	{
		if (beat == players[i])
		{
			positionBeat = i;
			break;
		}
	}

	beatInGame = true;

	party[0] = one->PutCardFirst();
	cout << one->GetName() << " tosses a card " << *party[countOfCardInParty] << endl;
	countOfCardInParty++;
	countTossCards++;

	party[1] = beat->BeatCard(party[0], party, countOfCardInParty);

	if (party[1] == nullptr)
	{
		beatInGame = false;
		cout << "\n" << beat->GetName() << " takes all cards!\n\n";
	}
	else
	{
		cout << beat->GetName() << " beats a card by " << *party[countOfCardInParty] << endl;
		countOfCardInParty++;
		countBeatCards++;
	}

	int positionToss = positionBeat - 1;

	if (positionBeat == 0)
		positionToss = countPlayers - 1;

	countExit = 0;

	while (countExit != countPlayers - 1)
	{
		if (countBeatCards == beat->GetCountCards())
		{
			break;
		}

		if (positionBeat != positionToss)
			BetweenTwoPlayers(players[positionToss], beat);

		if (positionToss == countPlayers - 1)
			positionToss = 0;
		else
			positionToss++;
		if (countOfCardInParty == 12 || countTossCards == 6)
			break;
		if (countTossCards == beat->GetCountCards())
			break;
	}

	if (beatInGame)
		cout << "\n" << beat->GetName() << " beats all cards!\n\n";

	cout << "CARDS ON TABLE: ";
	for (int i = 0; i < countOfCardInParty; i++)
	{
		cout << *party[i] << "  ";
	}
	cout << endl;

	if (beatInGame)
	{
		int index = 0;
		while (index != countOfCardInParty)
		{
			party[index]->SetUse(false);
			party[index]->SetStatus(false);
			index++;
		}
		for (int i = 0; i < countPlayers; i++)
		{
			players[i]->MinusAndDeleteCard();
		}
	}
	else
	{
		int index = 0;
		while (index != countOfCardInParty)
		{
			party[index]->SetUse(false);

			for (int i = 0; i < countPlayers; i++)
			{
				if (players[i] == beat)
					beat->AddCard(party[index]);
				else
					players[i]->MinusNotDeleteCard(party[index]);
			}

			index++;
		}
		for (int i = 0; i < countPlayers; i++)
		{
			players[i]->MinusAndDeleteCard();
		}
	}
	for (int i = 0; i < MAX_CARDS_IN_PARTY; i++)
	{
		party[i] = nullptr;
	}
	for (int i = 0; i < countPlayers; i++)
	{
		players[i]->TakeCardFromDeck(deck, *ptrCountCardsInDeck);
	}
	CheckPlayers();
}

void Game::AllGame()
{
	Player* whoGoFirst = this->ChoiceWhoFirstGo();
	// position of player which is beating
	int positionWhoGo;
	int positionBeat;
	for (int i = 0; i < countPlayers; i++)
	{
		if (whoGoFirst == players[i])
		{
			positionWhoGo = i;
			positionBeat = positionWhoGo + 1;
			if (positionWhoGo == countPlayers - 1)
				positionBeat = 0;
			break;
		}
	}
	bool tempPoint = true;

	while (countPlayers != 1)
	{
		if (countPlayers == 0)
		{
			cout << "\n\nALL WIN!!!\n";
			break;
		}
		
		//для юзера
		if (personInGame == true)
		{
			cout << "PLAYERS NAMES:\n";
			for (int i = 0; i < countPlayers; i++)
			{
				cout << players[i]->GetName() << "\t\t";
			}
			cout << "\n\n";

			if (tempPoint == true)
			{
				tempPoint = false;
				cout << "Player " << whoGoFirst->GetName() << " will be start the first!\n\n";
			}
		}   //для компютера
		else
		{
			for (int i = 0; i < countPlayers; i++)
			{
				cout << *players[i] << "\n\n";
			}
			if (tempPoint == true)
			{
				tempPoint = false;
				cout << "Player " << whoGoFirst->GetName() << " will be start the first!\n\n";
			}
		}

		beat = players[positionBeat];

		cout << players[positionWhoGo]->GetName() << " is going\n";
		cout << players[positionBeat]->GetName() << " is beating\n\n";

		OneParty(players[positionWhoGo], players[positionBeat]);

		//перевірка ігрока який бився і взалежності від його данних виставляємо нові позиції той хто має ходити і битися
		for (int i = 0; i < countPlayers; i++)
		{
			if (beat == players[i] && players[i]->GetCountCards() != 0 && beatInGame == true)
			{
				positionWhoGo = i;
				positionBeat = positionWhoGo + 1;
				if (positionWhoGo == countPlayers - 1)
					positionBeat = 0;
				break;
			}
			if (beat == players[i] && players[i]->GetCountCards() != 0 && beatInGame == false)
			{
				positionWhoGo = i + 1;
				if (i == countPlayers - 1)
					positionWhoGo = 0;
				positionBeat = positionWhoGo + 1;
				if (positionWhoGo == countPlayers - 1)
					positionBeat = 0;
				break;
			}
			if (beat == players[i] && players[i]->GetCountCards() == 0)
			{
				positionWhoGo = i;
				if (positionWhoGo == countPlayers - 1)
					positionWhoGo = 0;
				positionBeat = positionWhoGo + 1;
				if (positionWhoGo == countPlayers - 2)
					positionBeat = 0;
				cout << "\n" << players[i]->GetName() << " WIN!\n";
				delete players[i];
				players[i] = nullptr;

				for (int i = 0; i < countPlayers; i++)
				{
					for (int j = countPlayers - 1; j > i; j--)
					{
						if (players[j - 1] == nullptr && players[j] != nullptr)
						{
							players[j - 1] = players[j];
							players[j] = nullptr;
						}
					}
				}
				countPlayers--;
				break;
			}
		}

		if (countPlayers == 1)
			cout << "\n" << players[0]->GetName() << " LOSE!\n";

		cout << endl;
		system("pause");
		system("cls");
	}
}

Game::~Game()
{
	if (this->deck != nullptr)
	{
		deck = nullptr;
	}
	if (this->party != nullptr)
	{
		delete[] party;
		party = nullptr;
	}
	if (players != nullptr)
	{
		for (int i = 0; players[i] != nullptr; i++)
		{
			delete players[i];
			players[i] = nullptr;
		}
		delete[] players;
		players = nullptr;
	}
}