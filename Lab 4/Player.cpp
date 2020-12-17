#include "Player.h"
#include "Game.h"
#include <ctime>
Player::Player() {
	credits_ = 10000;
	sum_ = 0;
	splitSum = 0;
}
Player::~Player() {
	hand.clear();
	splitHand.clear();
}
int Player::getCredits() const {
	return credits_;
}
void Player::setCredits(int credits) {
	credits_ = credits;
}
void Player::addNewHand() {
	splitHand.reserve(5);
}
void Player::deleteNewHand() {
	splitHand.clear();
}
int Player::getSum() {
	return sum_;
}
int Player::getSplitSum() {
	return splitSum;
}
