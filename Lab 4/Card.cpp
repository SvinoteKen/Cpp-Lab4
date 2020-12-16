#include "Card.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
Card::Card(std::wstring content, int value, Suit suit) {
	content_ = content;
	value_ = value;
	suit_ = suit;
	switch (suit_) {
	case Suit::Club:
		suit_in_symbol_ = L'\u2663';
		break;
	case Suit::Diamond:
		suit_in_symbol_ = L'\u2666';
		break;
	case Suit::Spades:
		suit_in_symbol_ = L'\u2660';
		break;
	case Suit::Hearts:
		suit_in_symbol_ = L'\u2665';
		break;
	}
}
Card::~Card() {

}
int Card::getValue() const {
	return value_;
}
std::wstring Card::getContent() const {
	return content_;
}
std::wostream& operator<<(std::wostream& out, const Card& card) {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	out <<card.content_<<card.suit_in_symbol_<<" ";
	_setmode(_fileno(stdout), _O_TEXT);
	_setmode(_fileno(stdin), _O_TEXT);
	return out;
}
std::wstring Card::getPrintInterpretation() const {
	std::wstring ws = L"";
	ws += content_;
	ws += suit_in_symbol_;
	return ws;
}
std::wstring Card::print() const {
	std::wstring ws = L"";
	ws += content_;
	ws += suit_in_symbol_;
	return ws;
}
Suit Card::getSuit() const {
	return suit_;
}
wchar_t Card::getSuitInSymbol() const {
	return suit_in_symbol_;
}