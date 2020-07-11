#include "Bank.hpp"
#include "BankClient.hpp"

#include "PutCommand.hpp"
#include "GetCommand.hpp"

#include "BalanceCommand.hpp"

int main() {
	Bank bank; // client 

	PutCommand cPut(bank);
	GetCommand cGet(bank);
	BalanceCommand cBalance(bank);

	BankClient client(&cPut, &cGet, &cBalance);

	client.getMoney(); // printed: money to the client
	client.putMoney(); // printed: money from the client
	client.balanceMoney(); // printed: query client's balance

	return 0;
}
