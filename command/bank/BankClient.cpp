#include "BankClient.hpp"

BankClient::BankClient(iCommand* cPut, iCommand* cGet, iCommand* cBalance) {
	putCommand = cPut;
	getCommand = cGet;
	balanceCommand = cBalance;
}

void BankClient::putMoney() {
	putCommand->execute();
}

void BankClient::getMoney() {
	getCommand->execute();
}

void BankClient::balanceMoney() {
	balanceCommand->execute();
}

