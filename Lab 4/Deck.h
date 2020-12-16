#pragma once
#include<vector>
#include<stdlib.h>
#include<time.h>
#include "Card.h"
class Deck
{
public:
	Deck();
	~Deck();
	void printCount();
	int getDeckSum();
	int getCount();
	Card getCard();
	Card getCardPerIndex(int idx) const;
private:
	std::vector<Card*> deck;
   
};

