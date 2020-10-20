#pragma once
#include "Player.h"

class Game
{
	Player** players;			//поле для наших іграків
	Card ** deck;				//вказівник на колоду карт
	Card** party;				//вказівник на карти які в активній ігрі-партії "на столі"
	Player* beat;				//вказівник на іграка який бється
	int* ptrCountCardsInDeck;	//вказівник на залишок карт у колоді
	bool beatInGame;			//змінна яка показує чи ігрок який бється таки побився чи ні і забиратиме карти
	bool personInGame;			//змінна яка показує чи юзер в ігрі
	int countExit;				//для виходу із циклу
	int countPlayers;			//кількість іграків
	int countOfCardInParty;		//кількість карт які активні в партії
	int countTossCards;			//кількість підкинутих карт
	int countBeatCards;			//кількість побитих карт
public:
	//конструкто з параметрами
	Game(Card ** deck, const char* NAME, bool compORperson, int countPlayers, int &countCardsInDeck);
	//повертає вказівник на вказівники з іграками
	Player** GetPlayers() { return players; }
	//повертає вказівник на ігрока який ходить перший так як має найменший козирь
	Player* ChoiceWhoFirstGo();
	//імітує ігру між двома ігроками 
	void BetweenTwoPlayers(Player* toss, Player* beat);
	//перевірка чи ігрок не виграв
	void CheckPlayers();
	//ціла одна партія
	void OneParty(Player* one, Player* next);
	//ціла одна ігра
	void AllGame();
	//деструктор
	~Game();
};