#include "Dealer.h"
#include "Deck.h"
Dealer::Dealer() {
	sum_ = 0;
	hand.reserve(5);
}
Dealer::~Dealer() {
	hand.clear();
}
