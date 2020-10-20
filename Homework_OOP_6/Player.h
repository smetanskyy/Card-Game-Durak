#pragma once
#include "Card.h"

class Player
{
	Card ** cardsOnhands;
	char* name;
	int* ptrCountCardsInDeck;
	bool compORperson;
	int countCards;

public:
	// конструктор з параметрами
	Player(Card ** deck, const char* NAME, bool compORperson, int &countCardsInDeck);

	//метод для вибору першої карти, щоб походити
	Card* PutCardFirst();

	//метод який повертає карту якою бються
	Card* BeatCard(Card* card, Card** roundGame, int count);

	//метод який повертає карту щоб підкинути
	Card* TossUpCard(Card** roundGame, int count);

	//повертає вказівник на усі карти які є на руках у іграка
	Card** GetCardsOnhands() { return cardsOnhands; }

	//додає карту до іграка
	void AddCard(Card* card);

	//заберає карту в ігрока і викидає в атбой
	void MinusAndDeleteCard();

	//тільки забирає карту в ігрока, але карта ще в ігрі
	void MinusNotDeleteCard(Card *card);

	//беремо карту із колоди
	void TakeCardFromDeck(Card ** deck, int &countCardsInDeck);

	//сортуємо карти на руках
	void SortCart();

	//метод для повернення імя іграка
	const char* GetName() const { return name; }

	//повертає кількість карт на руках
	int GetCountCards() { return countCards; }

	//повертає позицію карти на руках яку обрав користувач
	int EnterChoice();

	//дружня ф-ція для виводу ігрока на екран
	friend ostream& operator << (ostream &show, const Player &obj);

	//деструктор
	~Player();
};