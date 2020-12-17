#pragma once
#include "deck.h"
#include <iostream>
class Player
{
public:
	Player();
	~Player();
	void setCredits(int credits);
	int getCredits() const;
	void addNewHand();
	void deleteNewHand();
	int getSum();
	int getSplitSum();
	friend class Game;
protected:
	int sum_;
	int splitSum;
	std::vector<Card>hand;
private:
	std::vector<Card> splitHand;
	bool new_hand_;
	int credits_;
};


