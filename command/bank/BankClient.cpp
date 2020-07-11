#include "BankClient.hpp"

BankClient::BankClient(iCommand* cPut, iCommand* cGet) {
	putCommand = cPut;
	getCommand = cGet;
}

void BankClient::putMoney() {
	putCommand->execute();
}

void BankClient::getMoney() {
	getCommand->execute();
}
