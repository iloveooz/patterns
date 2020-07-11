#include "BalanceCommand.hpp"

BalanceCommand::BalanceCommand(Bank bank) {
	this->bank = bank;
} 

void BalanceCommand::execute() {
	bank.queryBalance();
}
