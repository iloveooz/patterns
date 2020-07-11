#pragma once

#include "iCommand.hpp"
#include "Bank.hpp"

//ConcreteCommand
class BalanceCommand : public iCommand {
private:
	Bank bank;
	
public:
	BalanceCommand(Bank bank);
	
	void execute();
	
};
