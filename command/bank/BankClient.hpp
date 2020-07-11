#pragma once

#include "iCommand.hpp"

//Invoker
class BankClient {
private:
	iCommand* putCommand;
	iCommand* getCommand;
	iCommand* balanceCommand;

public:
	BankClient(iCommand* cPut, iCommand* cGet, iCommand* cBalance);

	void putMoney();
	void getMoney();
	void balanceMoney();
};
