#pragma once
#include <iostream>
#include <ctime>
using namespace std;

// ��������� ��� ��������� ������ ����
const int CARDS_IN_DECK = 36;

// ������������ ��� ����� ����
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

//������������ ��� ���� ����
enum Suit
{
	Diamonds,
	Hearts,
	Spades,
	Clubs
};

// ���� �����
class Card
{
	Suit suit;		// ���� ��� ����
	Rank rank;		// ���� ��� �����
	bool trumps;	// ���� �� ����� ��������
	bool status;	// ���� �� ����� ���� ������ �� � �����
	bool use;		// ���� �� ����� �� ���������� ���� ���� � ������� ��� �� �� �����

public:
	Card(Suit suit, Rank rank, Suit trumps);		// ����������� � �����������

	bool GetTrumps() const { return trumps; }		// ������� �� ����� ������� �� �
	bool GetStatus() const { return status; }		// ������� ������ �����
	bool GetUse() const { return use; }				// ������� �� ����� � ���
	void SetStatus(bool status) { this->status = status; }	// ��� ������������ ������� 
	void SetUse(bool use) { this->use = use; }		// ��� ������������ �� ����� ���������������

	Suit GetSuit() const { return suit; }			// ������� ����� �����
	Rank GetRank() const { return rank; }			// ������� ���� �����
	friend ostream& operator << (ostream &show, const Card &card); // ������ �-��� ��� ������ �� ����� �����
};

Card** CreateDeck(Suit trumps); // �������� ��� ��������� ������ ���� 
void DeleteCardFromDeck(Card** deck, int index, int &countRemainCardsInDeck); // ��������, ��� ����� ����� � ������