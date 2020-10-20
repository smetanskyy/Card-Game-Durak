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
	// ����������� � �����������
	Player(Card ** deck, const char* NAME, bool compORperson, int &countCardsInDeck);

	//����� ��� ������ ����� �����, ��� ��������
	Card* PutCardFirst();

	//����� ���� ������� ����� ���� ������
	Card* BeatCard(Card* card, Card** roundGame, int count);

	//����� ���� ������� ����� ��� ��������
	Card* TossUpCard(Card** roundGame, int count);

	//������� �������� �� �� ����� �� � �� ����� � ������
	Card** GetCardsOnhands() { return cardsOnhands; }

	//���� ����� �� ������
	void AddCard(Card* card);

	//������ ����� � ������ � ������ � �����
	void MinusAndDeleteCard();

	//����� ������ ����� � ������, ��� ����� �� � ���
	void MinusNotDeleteCard(Card *card);

	//������ ����� �� ������
	void TakeCardFromDeck(Card ** deck, int &countCardsInDeck);

	//������� ����� �� �����
	void SortCart();

	//����� ��� ���������� ��� ������
	const char* GetName() const { return name; }

	//������� ������� ���� �� �����
	int GetCountCards() { return countCards; }

	//������� ������� ����� �� ����� ��� ����� ����������
	int EnterChoice();

	//������ �-��� ��� ������ ������ �� �����
	friend ostream& operator << (ostream &show, const Player &obj);

	//����������
	~Player();
};