#pragma once
#include <iostream>
#include <ctime>
using namespace std;

// константа для створення колоди карт
const int CARDS_IN_DECK = 36;

// перечислення для рангу карт
enum Rank
{
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
	Ace
};

//перечислення для масті карт
enum Suit
{
	Diamonds,
	Hearts,
	Spades,
	Clubs
};

// клас карта
class Card
{
	Suit suit;		// поле для масті
	Rank rank;		// поле для рангу
	bool trumps;	// поле чи карта козирана
	bool status;	// поле чи карта може іграти чи в атбой
	bool use;		// поле чи карта на відповідному етапі ігри в активній ігрі чи на руках

public:
	Card(Suit suit, Rank rank, Suit trumps);		// конструктор з параметрами

	bool GetTrumps() const { return trumps; }		// повертає чи карта козирна чи ні
	bool GetStatus() const { return status; }		// повертає статус карти
	bool GetUse() const { return use; }				// повертає чи карта в ігрі
	void SetStatus(bool status) { this->status = status; }	// для встановлення статусу 
	void SetUse(bool use) { this->use = use; }		// для встановлення чи карта використовується

	Suit GetSuit() const { return suit; }			// повертає масть карти
	Rank GetRank() const { return rank; }			// повертає ранг карти
	friend ostream& operator << (ostream &show, const Card &card); // дружня ф-ція для виводу на екран карти
};

Card** CreateDeck(Suit trumps); // прототип для створення колоди карт 
void DeleteCardFromDeck(Card** deck, int index, int &countRemainCardsInDeck); // прототип, щоб брати карти з колоди