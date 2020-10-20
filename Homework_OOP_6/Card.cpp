#include "Card.h"

// беремо одну карту з колоди і зменшуємо залишок карт на 1, якщо карт в колоді 0 видаляємо колоду
void DeleteCardFromDeck(Card** deck, int index, int &countRemainCardsInDeck)
{
	deck[index] = nullptr;
	for (int i = index; i < countRemainCardsInDeck - 1; i++)
	{
		deck[i] = deck[i + 1];
		deck[i + 1] = nullptr;
	}
	countRemainCardsInDeck--;
	if (countRemainCardsInDeck == 0)
	{
		delete[] deck;
		deck = nullptr;
	}
}

// конструктор з параметрами, який встановлює ранг, масть, і чи карта козирна
Card::Card(Suit suit, Rank rank, Suit trumps)
{
	this->suit = suit;
	this->rank = rank;
	if (suit == trumps)
		this->trumps = true;
	else
		this->trumps = false;
	//карта не в атбої, тобто "жива"
	status = true;
	//і не використовуєть активно
	use = false;
}

// ф-ція для створення колоди з урахуванням козиря
Card** CreateDeck(Suit trumps)
{
	Card** deck = new Card*[CARDS_IN_DECK];
	Suit suit;
	for (int i = Diamonds; i <= Clubs; i++)
	{
		switch (i)
		{
		case Diamonds:
			suit = Diamonds;
			break;
		case Hearts:
			suit = Hearts;
			break;
		case Spades:
			suit = Spades;
			break;
		case Clubs:
			suit = Clubs;
			break;
		}
		Rank rank;
		for (int j = Six; j <= Ace; j++)
		{
			switch (j)
			{
			case Six:
				rank = Six;
				break;
			case Seven:
				rank = Seven;
				break;
			case Eight:
				rank = Eight;
				break;
			case Nine:
				rank = Nine;
				break;
			case Ten:
				rank = Ten;
				break;
			case Jack:
				rank = Jack;
				break;
			case Queen:
				rank = Queen;
				break;
			case King:
				rank = King;
				break;
			case Ace:
				rank = Ace;
				break;
			}
			deck[i * 9 + j] = new Card{ suit, rank, trumps };
		}
	}
	return deck;
}