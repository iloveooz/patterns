#pragma once

#include "iCommand.hpp"
#include "Bank.hpp"

//ConcreteCommand
class GetCommand: public iCommand {
private:
	Bank bank;

public: 
	GetCommand(Bank bank);

	void execute();
};
