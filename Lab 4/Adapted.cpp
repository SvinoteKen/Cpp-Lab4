#include "Adapted.h"
#include "IFormattable.h"
#include <io.h>
#include <fcntl.h>
Adapted::Adapted(Deck* deck) {
	deck_ = deck;
}
std::wstring Adapted::format() {
	std::wstring formatted_line = L"";
	for (int i = 0; i < deck_->getCount(); i++) {
		Card card = deck_->getCardPerIndex(i);
		if (card.getSuit() == Suit::Club || card.getSuit() == Suit::Spades) {

			formatted_line += card.getPrintInterpretation()+L'=';
			for (int j = 0; j < card.getValue(); j++) {
				formatted_line += L"\x1b[34m";
				formatted_line += card.getSuitInSymbol();
				formatted_line += L"\x1b[0m";
			}
			formatted_line += L"\n";
		}
		else {
			formatted_line += card.getPrintInterpretation() + L'=';
			for (int j = 0; j < card.getValue(); j++) {
				formatted_line += L"\x1b[31m";
				formatted_line += card.getSuitInSymbol();
				formatted_line += L"\x1b[0m";

			}
			formatted_line += L"\n";
		}
	}
	return formatted_line;
}
void Adapted::prettyPrint(const IFormattable& object) {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	std::wcout << format();
}
