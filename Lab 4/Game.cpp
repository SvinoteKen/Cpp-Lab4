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
			std::wcout << L"\nДополнительная рука: ";
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
	std::cout << "Колоды:";
	printDecks();
	std::cout << "\nДилер:";
	printPlayersHand(true,end);
	std::wcout << L"\nВы:";
	printPlayersHand(false,end);
}
void Game::getAmount() {
	int money = 0;
	std::cout << "Ваша ставка?\n";
	std::cin >> money;
	if (money > 0 && money <= players[0]->getCredits()) {
		amount_ = money;
	}
	else
	{
		std::wcout << L"Ошибка ставки\n";
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
		std::cout << "Для первой руки" << std::endl;
		std::cout << "1. Хватит" << std::endl;
		std::cout << "2. Еще" << std::endl;
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
		std::cout << "Для второй руки" << std::endl;
		std::cout << "1. Хватит" << std::endl;
		std::cout << "2. Еще" << std::endl;
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
		std::cout << "Закончить игру?" << std::endl;
		std::cout << "1. Да" << std::endl;
		std::cout << "2. Нет" << std::endl;
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
		std::cout << "1. Хватит" << std::endl;
		std::cout << "2. Еще" << std::endl;
		std::cout << "3. Сплит" << std::endl;
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
				players[0]->addNewHand();
				isSplit_ = true;
				amount_ *= 2;
				Card card = players[0]->hand.front();
				players[0]->splitHand.push_back(card);
                players[0]->sum_ -= card.getValue();
				players[0]->splitSum += card.getValue();
				players[0]->hand.erase(players[0]->hand.begin());
				std::cout << "Cтавка была удвоена, теперь ваша ставка " << amount_ << std::endl;
				addCardToPlayer();
				addCardToSplit();
			}
			else {
				std::cout << "Условия для сплита не выполненно" << std::endl;
			}
			printInfo();
			prompt();
			break;
		default:
			std::cout << "Неверное действие" << std::endl;
			prompt();
			break;
		}
	}
}
bool Game::nextGame() {
	std::wcout << L"\n1.Продолжить\n2.Выход\n";
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
	std::cout << "Игра окончена." << std::endl;
	while (players[1]->sum_ <= 17) { addCardToDealer(); }
	printInfo();
	if (isSplit_) {
		std::cout <<std::endl;
		std::cout << "У дилера " << players[1]->sum_ << "." << std::endl;
		std::cout << "У вас в первой руке" << players[0]->sum_ << "," << "во второй руке:" << players[0]->splitSum << std::endl;
	}
	else {
		std::cout << std::endl;
		std::cout << "У дилера " << players[1]->sum_ << "." << std::endl;
		std::cout << "У вас в руке" << players[0]->sum_ << std::endl;
	}
	bool userLost = false;
	bool draw = false;
	if (!isSplit_) {
		if (players[0]->sum_ == 21) {
			std::cout << "У вас 21 очко. Вы победили." << std::endl;
            std::cout << "Вы получили " << amount_ << "." << std::endl;
		}
		else if (players[1]->sum_ == 21) {
			std::cout << "У дилера 21. Вы проиграли. Вы потеряли " << amount_ << "." << std::endl;
			userLost = true;
		}
		else {
			std::cout << "Ни у кого не выпало 21, но ";
			if (players[0]->sum_<21 && players[0]->sum_>players[1]->sum_) {
				std::cout << "вы ближе к 21, и поэтому выиграли. Ваш выигрыш " << amount_ << "." << std::endl;

			}
			else {
				std::cout << "дилер ближе к 21, и поэтому вы проиграли. Вы потеряли " << amount_ << "." << std::endl;
				userLost = true;
			}
		}
	}
	else {
		if (players[0]->sum_ == 21 && players[0]->splitSum == 21 && players[1]->sum_ == 21) {
			std::cout << "У всех по 21 очку. Ничья." << std::endl;
			draw = true;
		}
		else if (players[0]->sum_ == 21 && players[0]->splitSum == 21) {
			std::cout << "У вас в обеих руках по 21 очку. Вы победили." << std::endl;
			amount_ *= 2;
			std::cout << "Вы получили удвоеный выигрыш" << amount_ << "." << std::endl;
		}
		if (players[0]->sum_ == 21) {
			amount_ /= 2;
			std::cout << "У вас в первой руке 21 очко. Вы победили." << std::endl;
			std::cout << "Вы получили первоначальную ставку" << amount_ << "." << std::endl;
		}
		else if (players[0]->splitSum == 21) {
			amount_ /= 2;
			std::cout << "У вас во второй руке 21 очко. Вы победили." << std::endl;
			std::cout << "Вы получили первоначальную ставку " << amount_ << "." << std::endl;
		}
		else if (players[1]->sum_ == 21) {
			std::cout << "У дилера 21. Вы проиграли. Вы потеряли " << amount_ << "." << std::endl;
			userLost = true;
		}
		else {
			std::cout << "Ни у кого не выпало 21, но ";
			if (players[0]->sum_<21 && players[0]->splitSum<21 && players[0]->sum_>players[1]->sum_&& players[0]->splitSum>players[1]->sum_) {
				std::cout << "в двух руках значение к 21, и поэтому выиграли. Ваш выигрыш " << amount_ << "." << std::endl;
			}
			else if (players[0]->sum_<21 && players[0]->splitSum<21 && players[0]->sum_>players[1]->sum_ && players[0]->splitSum<players[1]->sum_) {
				amount_ /= 2;
				std::cout << "первая рука ближе к 21,но вторая дальше чем от дилера и поэтому вы выиграли первначальную ставку. Ваш выигрыш " << amount_ << "." << std::endl;
			}
			else if (players[0]->sum_ < 21 && players[0]->splitSum<21 && players[0]->sum_<players[1]->sum_ && players[0]->splitSum > players[1]->sum_) {
				amount_ /= 2;
				std::cout << "вторая рука ближе к 21,но первая дальше чем от дилера и поэтому вы выиграли первначальную ставку. Ваш выигрыш " << amount_ << "." << std::endl;
			}
			else {
				std::cout << "дилер ближе к 21, и поэтому вы проиграли. Вы потеряли " << amount_ << "." << std::endl;
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
	std::cout << "У вас " << players[0]->getCredits() << std::endl;
}