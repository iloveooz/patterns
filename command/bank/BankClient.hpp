#pragma once

#include "iCommand.hpp"

//Invoker
class BankClient {
private:
	iCommand* putCommand;
	iCommand* getCommand;

public:
	BankClient(iCommand* cPut, iCommand* cGet);

	void putMoney();
	void getMoney();
};
