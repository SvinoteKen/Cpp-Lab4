#include "Game.h"
#include "Dealer.h"
#include "OutOfScoreException.h"
#include <stdio.h>
#include <ctime>
Game::Game() {
    amount_=0;
	money = 10000;
	end = false;

	for (int i = 0; i < 4; i++) {
		decks[i] = new Deck();
	}
	players[0] = new Player();
	players[0]->setCredits(money);
	players[1] = new Dealer();
	isSplit_ = false;
}
Game::~Game() {
	delete[] decks;
}
void Game::addCardToPlayer() {
	srand((unsigned)time(0));
	Card card = decks[rand() % 4]->getCard();
    players[0]->hand.push_back(card);
	players[0]->sum_ += card.getValue();
}
void Game::addCardToSplit() {
	srand((unsigned)time(0));
	Card card = decks[rand() % 4]->getCard();
	players[0]->splitHand.push_back(card);
	players[0]->splitSum += card.getValue();
}
void Game::addCardToDealer() 
{
	srand((unsigned)time(0));
	Card card = decks[rand() % 4]->getCard();
	players[1]->hand.push_back(card);
	players[1]->sum_ += card.getValue();
}
void Game::printPlayersHand(bool dealer,bool theEnd) {
	if (dealer) {
		for (int i = 0; i < players[1]->hand.size(); i++)
		{
			std::wcout.width(2);
			std::wcout << players[1]->hand[i];
		}
		if (!theEnd) {
			std::wcout.width(6);
			std::wcout << "??";
		}
		else {};
    }
	else
	{
		if (!isSplit_) {
			for (int i = 0; i < players[0]->hand.size(); i++)
			{
				std::wcout.width(5);
				std::wcout << players[0]->hand[i];
			}
		}
		else {
			for (int i = 0; i < players[0]->hand.size(); i++)
			{
				std::wcout.width(5);
				std::wcout << players[0]->hand[i];
			}
			std::wcout << L"\nÄîïîëíèòåëüíàÿ ðóêà: ";
			for (int i = 0; i < players[0]->splitHand.size(); i++)
			{
				std::wcout.width(5);
				std::wcout << players[0]->splitHand[i];
			}
		}
	}
}
void Game::printDecks() {
	for (int i = 0; i < 4; i++) {
		decks[i]->printCount();
	}
	std::wcout << "\n";
}
void Game::printInfo() {
	std::cout << "Êîëîäû:";
	printDecks();
	std::cout << "\nÄèëåð:";
	printPlayersHand(true,end);
	std::wcout << L"\nÂû:";
	printPlayersHand(false,end);
}
void Game::getAmount() {
	int money = 0;
	std::cout << "Âàøà ñòàâêà?\n";
	std::cin >> money;
	if (money > 0 && money <= players[0]->getCredits()) {
		amount_ = money;
	}
	else
	{
		std::wcout << L"Îøèáêà ñòàâêè\n";
		getAmount();
	}
}
void Game::play() {
	getAmount();
	addCardToDealer();
	addCardToPlayer();
	addCardToPlayer();
	printInfo();
	prompt();
}
void Game::prompt()
{
	if (isSplit_) {
        std::cout << std::endl;
		std::cout << "Äëÿ ïåðâîé ðóêè" << std::endl;
		std::cout << "1. Õâàòèò" << std::endl;
		std::cout << "2. Åùå" << std::endl;
		int action;
		std::cin >> action;
		switch (action) {
		case 1:
			break;
		case 2:
			addCardToPlayer();
			break;
		}
		std::cout << std::endl;
		std::cout << "Äëÿ âòîðîé ðóêè" << std::endl;
		std::cout << "1. Õâàòèò" << std::endl;
		std::cout << "2. Åùå" << std::endl;
		std::cin >> action;
		switch (action) {
		case 1:
			break;
		case 2:
			addCardToSplit();
			printInfo();
			break;
		}
		std::cout << std::endl;
		std::cout << "Çàêîí÷èòü èãðó?" << std::endl;
		std::cout << "1. Äà" << std::endl;
		std::cout << "2. Íåò" << std::endl;
		std::cin >> action;
		switch (action) {
		case 1:
			endGame();
			break;
		case 2:
			prompt();
			break;
		}
	}
	else {
		std::cout << std::endl;
		std::cout << "1. Õâàòèò" << std::endl;
		std::cout << "2. Åùå" << std::endl;
		std::cout << "3. Ñïëèò" << std::endl;
		int action;
		std::cin >> action;
		switch (action) {
		case 1:
			endGame();
			break;
		case 2:
			addCardToPlayer();
			printInfo();
			prompt();
			
			break;
		case 3:
			if (players[0]->hand[0].getContent() != players[0]->hand[1].getContent()) {
				isSplit_ = true;
				amount_ *= 2;
				Card card = players[0]->hand.front();
				players[0]->splitHand.push_back(card);
                players[0]->sum_ -= card.getValue();
				players[0]->splitSum += card.getValue();
				players[0]->hand.erase(players[0]->hand.begin());
				std::cout << "Còàâêà áûëà óäâîåíà, òåïåðü âàøà ñòàâêà " << amount_ << std::endl;
				addCardToPlayer();
				addCardToSplit();
			}
			else {
				std::cout << "Óñëîâèÿ äëÿ ñïëèòà íå âûïîëíåííî" << std::endl;
			}
			printInfo();
			prompt();
			break;
		default:
			std::cout << "Íåâåðíîå äåéñòâèå" << std::endl;
			prompt();
			break;
		}
	}
}
bool Game::nextGame() {
	std::wcout << L"\n1.Ïðîäîëæèòü\n2.Âûõîä\n";
	wchar_t answer;
	std::wcin >> answer;
	switch (answer)
	{
	case L'1':
		isSplit_ = false;
		end = false;
		players[0]->sum_ = 0;
		players[1]->sum_ = 0;
		players[0]->hand.clear();
		players[1]->hand.clear();
		players[0]->splitSum = 0;
		players[0]->deleteNewHand();
		return true;
	default:
		return false;
	}
}
void Game::endGame() {
    end = true;
	std::cout << "Èãðà îêîí÷åíà." << std::endl;
	while (players[1]->sum_ <= 17) { addCardToDealer(); }
	printInfo();
	if (isSplit_) {
		std::cout <<std::endl;
		std::cout << "Ó äèëåðà " << players[1]->sum_ << "." << std::endl;
		std::cout << "Ó âàñ â ïåðâîé ðóêå" << players[0]->sum_ << "," << "âî âòîðîé ðóêå:" << players[0]->splitSum << std::endl;
	}
	else {
		std::cout << std::endl;
		std::cout << "Ó äèëåðà " << players[1]->sum_ << "." << std::endl;
		std::cout << "Ó âàñ â ðóêå" << players[0]->sum_ << std::endl;
	}
	try {
		if (players[0]->sum_ > 21 || players[0]->splitSum > 21) { throw OutOfScoreException(); }
	}
	catch (OutOfScoreException) {
		std::cout << std::endl;
		std::cout << "Вы проиграли у вас перебор" << std::endl;
		money -= amount_;
		players[0]->setCredits(money);
		std::cout << "У вас " << players[0]->getCredits() << std::endl;
		nextGame();
	}
	bool userLost = false;
	bool draw = false;
	if (!isSplit_) {
		if (players[0]->sum_ == 21) {
			std::cout << "Ó âàñ 21 î÷êî. Âû ïîáåäèëè." << std::endl;
            std::cout << "Âû ïîëó÷èëè " << amount_ << "." << std::endl;
		}
		else if (players[1]->sum_ == 21) {
			std::cout << "Ó äèëåðà 21. Âû ïðîèãðàëè. Âû ïîòåðÿëè " << amount_ << "." << std::endl;
			userLost = true;
		}
		else {
			std::cout << "Íè ó êîãî íå âûïàëî 21, íî ";
			if (players[0]->sum_<21 && players[0]->sum_>players[1]->sum_) {
				std::cout << "âû áëèæå ê 21, è ïîýòîìó âûèãðàëè. Âàø âûèãðûø " << amount_ << "." << std::endl;

			}
			else {
				std::cout << "äèëåð áëèæå ê 21, è ïîýòîìó âû ïðîèãðàëè. Âû ïîòåðÿëè " << amount_ << "." << std::endl;
				userLost = true;
			}
		}
	}
	else {
		if (players[0]->sum_ == 21 && players[0]->splitSum == 21 && players[1]->sum_ == 21) {
			std::cout << "Ó âñåõ ïî 21 î÷êó. Íè÷üÿ." << std::endl;
			draw = true;
		}
		else if (players[0]->sum_ == 21 && players[0]->splitSum == 21) {
			std::cout << "Ó âàñ â îáåèõ ðóêàõ ïî 21 î÷êó. Âû ïîáåäèëè." << std::endl;
			amount_ *= 2;
			std::cout << "Âû ïîëó÷èëè óäâîåíûé âûèãðûø" << amount_ << "." << std::endl;
		}
		if (players[0]->sum_ == 21) {
			amount_ /= 2;
			std::cout << "Ó âàñ â ïåðâîé ðóêå 21 î÷êî. Âû ïîáåäèëè." << std::endl;
			std::cout << "Âû ïîëó÷èëè ïåðâîíà÷àëüíóþ ñòàâêó" << amount_ << "." << std::endl;
		}
		else if (players[0]->splitSum == 21) {
			amount_ /= 2;
			std::cout << "Ó âàñ âî âòîðîé ðóêå 21 î÷êî. Âû ïîáåäèëè." << std::endl;
			std::cout << "Âû ïîëó÷èëè ïåðâîíà÷àëüíóþ ñòàâêó " << amount_ << "." << std::endl;
		}
		else if (players[1]->sum_ == 21) {
			std::cout << "Ó äèëåðà 21. Âû ïðîèãðàëè. Âû ïîòåðÿëè " << amount_ << "." << std::endl;
			userLost = true;
		}
		else {
			std::cout << "Íè ó êîãî íå âûïàëî 21, íî ";
			if (players[0]->sum_<21 && players[0]->splitSum<21 && players[0]->sum_>players[1]->sum_&& players[0]->splitSum>players[1]->sum_) {
				std::cout << "â äâóõ ðóêàõ çíà÷åíèå ê 21, è ïîýòîìó âûèãðàëè. Âàø âûèãðûø " << amount_ << "." << std::endl;
			}
			else if (players[0]->sum_<21 && players[0]->splitSum<21 && players[0]->sum_>players[1]->sum_ && players[0]->splitSum<players[1]->sum_) {
				amount_ /= 2;
				std::cout << "ïåðâàÿ ðóêà áëèæå ê 21,íî âòîðàÿ äàëüøå ÷åì îò äèëåðà è ïîýòîìó âû âûèãðàëè ïåðâíà÷àëüíóþ ñòàâêó. Âàø âûèãðûø " << amount_ << "." << std::endl;
			}
			else if (players[0]->sum_ < 21 && players[0]->splitSum<21 && players[0]->sum_<players[1]->sum_ && players[0]->splitSum > players[1]->sum_) {
				amount_ /= 2;
				std::cout << "âòîðàÿ ðóêà áëèæå ê 21,íî ïåðâàÿ äàëüøå ÷åì îò äèëåðà è ïîýòîìó âû âûèãðàëè ïåðâíà÷àëüíóþ ñòàâêó. Âàø âûèãðûø " << amount_ << "." << std::endl;
			}
			else {
				std::cout << "äèëåð áëèæå ê 21, è ïîýòîìó âû ïðîèãðàëè. Âû ïîòåðÿëè " << amount_ << "." << std::endl;
				userLost = true;
			}
		}
	}
	if (userLost) {
		money -= amount_;
		players[0]->setCredits(money);
	}
	else {
		money += amount_;
		players[0]->setCredits(money);
	}
	std::cout << "Ó âàñ " << players[0]->getCredits() << std::endl;
}
