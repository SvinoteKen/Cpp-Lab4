#include <string>
#include <iostream>
enum class Suit
{
	Club,
	Spades,
	Hearts,
	Diamond
};
#pragma once
class Card
{
public:
	Card(std::wstring content, int value, Suit suit);
	~Card();
	int getValue() const;
	std::wstring getContent() const;
	std::wstring print() const;
	Suit getSuit() const;
	wchar_t getSuitInSymbol() const;
	std::wstring getPrintInterpretation() const;
	friend std::wostream& operator<<(std::wostream& out, const Card& card);
private:
	std::wstring content_;
	int value_;
	wchar_t suit_in_symbol_;
	Suit suit_;
};

