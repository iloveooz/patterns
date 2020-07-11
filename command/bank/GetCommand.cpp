#include "GetCommand.hpp"

GetCommand::GetCommand(Bank bank) {
	this->bank = bank;
} 

void GetCommand::execute() {
	bank.giveMoney();
}
