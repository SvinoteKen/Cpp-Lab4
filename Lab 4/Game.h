#pragma once
#include "Deck.h"
#include "Player.h"
class Game
{
public:
	Game();
	~Game();
	void addCardToPlayer();
	void addCardToDealer();
	void printDecks();
	void play();
	void getAmount();
	void printPlayersHand(bool dealer,bool theEnd);
	void printInfo();
	void endGame();
	void addCardToSplit();
	void prompt();
	bool nextGame();

private:
	Deck* decks[4];
	Player* players[2];
	int amount_;
	bool isSplit_;
	int money;
    bool end ;
};

