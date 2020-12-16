#include "Player.h"
#include "Game.h"
#include <ctime>
Player::Player() {
	credits_ = 10000;
	sum_ = 0;
	new_hand_ = false;
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
void Player::openHand() {
	hand.reserve(5);
}
void Player::addNewHand() {
	splitHand.reserve(5);
	new_hand_ = true;
}
void Player::deleteNewHand() {
	splitHand.clear();
	new_hand_ = false;
}
int Player::getSum() {
	return sum_;
}
int Player::getSplitSum() {
	return splitSum;
}
