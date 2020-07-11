#include "PutCommand.hpp"

PutCommand::PutCommand(Bank bank) {
	this->bank = bank;
}

void PutCommand::execute() {
	bank.receiveMoney();
}
