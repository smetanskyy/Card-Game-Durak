#pragma once
#include "Player.h"

class Game
{
	Player** players;			//���� ��� ����� ������
	Card ** deck;				//�������� �� ������ ����
	Card** party;				//�������� �� ����� �� � ������� ���-���� "�� ����"
	Player* beat;				//�������� �� ������ ���� �����
	int* ptrCountCardsInDeck;	//�������� �� ������� ���� � �����
	bool beatInGame;			//����� ��� ������ �� ����� ���� ����� ���� ������� �� � � ���������� �����
	bool personInGame;			//����� ��� ������ �� ���� � ���
	int countExit;				//��� ������ �� �����
	int countPlayers;			//������� ������
	int countOfCardInParty;		//������� ���� �� ������ � ����
	int countTossCards;			//������� ��������� ����
	int countBeatCards;			//������� ������� ����
public:
	//���������� � �����������
	Game(Card ** deck, const char* NAME, bool compORperson, int countPlayers, int &countCardsInDeck);
	//������� �������� �� ��������� � ��������
	Player** GetPlayers() { return players; }
	//������� �������� �� ������ ���� ������ ������ ��� �� �� ��������� ������
	Player* ChoiceWhoFirstGo();
	//���� ���� �� ����� �������� 
	void BetweenTwoPlayers(Player* toss, Player* beat);
	//�������� �� ����� �� ������
	void CheckPlayers();
	//���� ���� �����
	void OneParty(Player* one, Player* next);
	//���� ���� ����
	void AllGame();
	//����������
	~Game();
};