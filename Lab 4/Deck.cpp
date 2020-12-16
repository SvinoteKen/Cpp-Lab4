#include "Deck.h"
#include <ctime>
Deck::Deck() {
	std::wstring names[3] = { L"J", L"Q" , L"K" };
	deck.reserve(52);
    for (int i = 2; i <= 10; i++) {
		deck.push_back(new Card(std::to_wstring(i), i, Suit::Club));
		deck.push_back(new Card(std::to_wstring(i), i, Suit::Diamond));
		deck.push_back(new Card(std::to_wstring(i), i, Suit::Hearts));
		deck.push_back(new Card(std::to_wstring(i), i, Suit::Spades));
	}
	for (int i = 0; i < 3; i++) {
		deck.push_back(new Card(names[i], 10, Suit::Club));
		deck.push_back(new Card(names[i], 10, Suit::Diamond));
		deck.push_back(new Card(names[i], 10, Suit::Hearts));
		deck.push_back(new Card(names[i], 10, Suit::Spades));
	}
	deck.push_back(new Card(L"A", 11, Suit::Club));
	deck.push_back(new Card(L"A", 11, Suit::Diamond));
	deck.push_back(new Card(L"A", 11, Suit::Hearts));
	deck.push_back(new Card(L"A", 11, Suit::Spades));
	srand((unsigned)time(0));
	for (int i = 0; i < 52; i++) {
		std::swap(deck[i], deck[rand() % 52]);
	}
}
Deck::~Deck() {
	deck.clear();
}
void Deck::printCount() {
	std::wcout.width(5);
	std::wcout << "[" << deck.size() << "]";
}
int Deck::getDeckSum() {
	int sum = 0;
	for (int i = 0; i < deck.size(); i++) {
		sum += deck[i]->getValue();
	}
	return sum;
}
int Deck::getCount() {
	return deck.size();
}
Card Deck::getCard() {
	srand(time(NULL));
	int i = rand() % deck.size();
	Card card = *deck[i];
	deck.erase(deck.begin()+i);
	return card;
}
Card Deck::getCardPerIndex(int idx) const {
	return *deck[idx];
}
