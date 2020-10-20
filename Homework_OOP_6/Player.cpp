#include "Player.h"
// ����������� � �����������: ������ ������ ���, �� �� "�����"(����) �� �� �����(����)
Player::Player(Card ** deck, const char* NAME, bool compORperson, int &countCardsInDeck)
{
	if (countCardsInDeck == 0)
		exit(1);
	ptrCountCardsInDeck = &countCardsInDeck;
	countCards = 6;
	cardsOnhands = new Card*[countCards];
	for (int i = 0; i < countCards; i++)
	{
		int index = rand() % countCardsInDeck;
		cardsOnhands[i] = deck[index];
		DeleteCardFromDeck(deck, index, countCardsInDeck);
	}
	this->compORperson = compORperson;
	name = new char[strlen(NAME) + 1];
	strcpy_s(name, strlen(NAME) + 1, NAME);
	SortCart();

}
//������ ����� �� ������
void Player::AddCard(Card* card)
{
	//���������� �� ����� ����� � ������ �� �� �����
	for (int i = 0; i < countCards; i++)
	{
		if (cardsOnhands[i] == card)
			return;
	}
	//������ ������
	Card** newCards = new Card*[countCards + 1];
	for (int i = 0; i < countCards; i++)
	{
		newCards[i] = cardsOnhands[i];
	}
	delete[] cardsOnhands;
	newCards[countCards] = card;
	cardsOnhands = newCards;
	//�������� ������� � �������
	countCards++;
	SortCart();
}

//��� ��������� ����� (� �����)
void Player::MinusAndDeleteCard()
{
	int temp = countCards;
	//��������� ����� ������ ��� "�� ����"
	for (int i = 0; i < countCards; i++)
	{
		if (cardsOnhands[i]->GetStatus() == false)
		{
			delete cardsOnhands[i];
			cardsOnhands[i] = nullptr;
			temp--;
		}
	}
	//��������� �� ��������� �� ���� � ����� 
	for (int i = 0; i < countCards; i++)
	{
		for (int j = countCards - 1; j > i; j--)
		{
			if (cardsOnhands[j - 1] == nullptr && cardsOnhands[j] != nullptr)
			{
				cardsOnhands[j - 1] = cardsOnhands[j];
				cardsOnhands[j] = nullptr;
			}
		}
	}
	//�������� ������� ���� �� �����
	countCards = temp;
	//�������
	SortCart();
}

//�������� ����� �� ���� �� �� �����
void Player::MinusNotDeleteCard(Card *card)
{
	for (int i = 0; i < countCards; i++)
	{
		if (cardsOnhands[i] == card)
		{
			cardsOnhands[i] = cardsOnhands[countCards - 1];
			cardsOnhands[countCards - 1] = nullptr;
			countCards--;
			SortCart();
			break;
		}
	}
}

//����� ���� ������ ����� ����� � ��������� �� �� �� ���� �� ����
Card* Player::PutCardFirst()
{
	int index = 0;

	if (compORperson == true)
	{
		cout << "You are starting. Put first card!\n";
		index = EnterChoice();
		if (index == -1)
			index = 0;
		cardsOnhands[index]->SetUse(true);
		return cardsOnhands[index];
	}

	Card* ptrSmallest = cardsOnhands[index];
	while (cardsOnhands[index]->GetTrumps() == true)
	{
		if (index == countCards - 1)
		{
			ptrSmallest = cardsOnhands[0];
			break;
		}
		index++;
		ptrSmallest = cardsOnhands[index];
	}
	ptrSmallest->SetUse(true);
	return ptrSmallest;
}


//����� ���� ���� ���������� ����� � ��������� �� ��� � ���
Card* Player::TossUpCard(Card** roundGame, int count)
{
	// ��� �����������
	if (compORperson == true)
	{
		cout << "\nCARDS ON TABLE: ";
		for (int i = 0; i < count; i++)
		{
			cout << *roundGame[i] << "  ";
		}
		cout << endl;
		cout << "\nIf you have a card. You can toss up!\n";
		int position = EnterChoice();
		if (position == -1)
			return nullptr;
		for (int i = 0; i < count; i++)
		{
			if (roundGame[i]->GetRank() == cardsOnhands[position]->GetRank() && cardsOnhands[position]->GetUse() == false)
			{
				cardsOnhands[position]->SetUse(true);
				return cardsOnhands[position];
			}
		}
		cout << "You are cheating!\n";
		return nullptr;
	}
	//��� ���������
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < countCards; j++)
		{
			if (roundGame[i]->GetRank() == cardsOnhands[j]->GetRank() && cardsOnhands[j]->GetTrumps() == false
				&& cardsOnhands[j]->GetUse() == false)
			{
				cardsOnhands[j]->SetUse(true);
				return cardsOnhands[j];
			}
		}
	}
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < countCards; j++)
		{
			if (roundGame[i]->GetRank() == cardsOnhands[j]->GetRank() && cardsOnhands[j]->GetTrumps() == true
				&& cardsOnhands[j]->GetUse() == false)
			{
				if (cardsOnhands[j]->GetRank() <= Ten && *ptrCountCardsInDeck >= 6)
				{
					cardsOnhands[j]->SetUse(true);
					return cardsOnhands[j];
				}
				if (*ptrCountCardsInDeck < 6)
				{
					cardsOnhands[j]->SetUse(true);
					return cardsOnhands[j];
				}
			}
		}
	}
	//���� ����� ���� ��������� ����
	return nullptr;
}

Card* Player::BeatCard(Card* card, Card** roundGame, int count)
{
	if (compORperson == true)
	{
		cout << "\nCARDS ON TABLE: ";
		for (int i = 0; i < count; i++)
		{
			cout << *roundGame[i] << "  ";
		}
		cout << endl;
		cout << "\nYou are beating!\n";
		int position = EnterChoice();
		if (position == -1)
			return nullptr;
		if (card->GetTrumps() == false)
		{
			if (card->GetRank() < cardsOnhands[position]->GetRank() && card->GetSuit() == cardsOnhands[position]->GetSuit()
				&& cardsOnhands[position]->GetUse() == false)
			{
				cardsOnhands[position]->SetUse(true);
				return cardsOnhands[position];
			}
			else if (cardsOnhands[position]->GetTrumps() == true && cardsOnhands[position]->GetUse() == false)
			{
				cardsOnhands[position]->SetUse(true);
				return cardsOnhands[position];
			}
			else
			{
				cout << "\nYou play foul\n";
				return nullptr;
			}
		}
		else
		{
			if (cardsOnhands[position]->GetRank() > card->GetRank() && cardsOnhands[position]->GetTrumps() == true
				&& cardsOnhands[position]->GetUse() == false)
			{
				cardsOnhands[position]->SetUse(true);
				return cardsOnhands[position];
			}
			else
			{
				cout << "\nYou play foul\n";
				return nullptr;
			}
		}

	}

	if (card->GetTrumps() == false)
	{
		for (int i = 0; i < countCards; i++)
		{
			if (cardsOnhands[i]->GetRank() > card->GetRank() && card->GetSuit() == cardsOnhands[i]->GetSuit()
				&& cardsOnhands[i]->GetUse() == false)
			{
				cardsOnhands[i]->SetUse(true);
				return cardsOnhands[i];
			}
		}
		for (int i = 0; i < countCards; i++)
		{
			if (cardsOnhands[i]->GetTrumps() == true && cardsOnhands[i]->GetUse() == false)
			{
				cardsOnhands[i]->SetUse(true);
				return cardsOnhands[i];
			}
		}
	}
	else
	{
		for (int i = 0; i < countCards; i++)
		{
			if (cardsOnhands[i]->GetRank() > card->GetRank() && cardsOnhands[i]->GetTrumps() == true && cardsOnhands[i]->GetUse() == false)
			{
				cardsOnhands[i]->SetUse(true);
				return cardsOnhands[i];
			}
		}
	}
	return nullptr;
}

void Player::TakeCardFromDeck(Card ** deck, int &countCardsInDeck)
{
	while (countCards < 6)
	{
		if (countCardsInDeck != 0)
		{

			Card** tempCardsOnhands = new Card*[countCards + 1];
			for (int i = 0; i < countCards; i++)
			{
				tempCardsOnhands[i] = cardsOnhands[i];
			}
			int index = rand() % countCardsInDeck;
			tempCardsOnhands[countCards] = deck[index];
			DeleteCardFromDeck(deck, index, countCardsInDeck);
			delete[] cardsOnhands;
			cardsOnhands = tempCardsOnhands;
			tempCardsOnhands = nullptr;
			countCards++;
			SortCart();
		}
		else
			break;
	}
}

Player::~Player()
{
	if (name != nullptr)
	{
		delete[] name;
		name = nullptr;
	}
	if (cardsOnhands != nullptr)
	{
		for (int i = 0; i < countCards && cardsOnhands[i] != nullptr; i++)
		{
			delete cardsOnhands[i];
			cardsOnhands[i] = nullptr;
		}
		delete[] cardsOnhands;
		cardsOnhands = nullptr;
	}
}

void Player::SortCart()
{
	Card* temp = nullptr;
	for (int i = 0; i < countCards; i++)
	{
		for (int j = countCards - 1; j > i; j--)
		{
			if (cardsOnhands[j]->GetRank() < cardsOnhands[j - 1]->GetRank())
			{
				temp = cardsOnhands[j - 1];
				cardsOnhands[j - 1] = cardsOnhands[j];
				cardsOnhands[j] = temp;
			}
		}
	}
}

int Player::EnterChoice()
{
	cout << "Please enter the ordinal number of the card you want to select ";
	cout << " or input 0 - do nothing!\n";
	for (int i = 0; i < countCards; i++)
	{
		if (cardsOnhands[i]->GetUse() == false && cardsOnhands[i]->GetTrumps() == true)
		{
			cout << i + 1 << ") " << *cardsOnhands[i] << "*  ";
		}
		else if (cardsOnhands[i]->GetUse() == false)
		{
			cout << i + 1 << ") " << *cardsOnhands[i] << "  ";
		}
		else
		{
			cout << i + 1 << ") [ ]  ";
		}
	}
	cout << endl;
	int choice;
	while (true)
	{
		cin >> choice;
		if (choice < 0 || choice > countCards)
		{
			cout << "Try again: ";
		}
		else
		{
			system("cls");
			return choice - 1;
		}
	}
}