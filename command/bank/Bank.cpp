#include "Bank.hpp"

void Bank::giveMoney() {
	std::cout << "Money to the client" << '\n';
}

void Bank::receiveMoney() {
	std::cout << "Money from the client" << '\n';
}

void Bank::queryBalance() {
	std::cout << "Your balance is positive" << '\n';
}
