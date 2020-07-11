#include "Bank.hpp"
#include "BankClient.hpp"

#include "PutCommand.hpp"
#include "GetCommand.hpp"

int main() {
	Bank bank; // client 

	PutCommand cPut(bank);
	GetCommand cGet(bank);

	BankClient client(&cPut, &cGet);

	client.getMoney(); // printed: money to the client
	client.putMoney(); // printed: money from the client

	return 0;
}
