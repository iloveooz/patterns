#pragma once

#include "iCommand.hpp"
#include "Bank.hpp"

//ConcreteCommand
class PutCommand: public iCommand {
private:
	Bank bank;

public:
	PutCommand(Bank bank);

	void execute();
};
