#pragma once
#include "IFormattable.h"
#include <string>
#include "Deck.h"
class Adapted :public IFormattable
{
public:
	Adapted(Deck* deck);
	std::wstring format() override;
	void prettyPrint(const IFormattable& object) override;
private:
	Deck* deck_;
};
