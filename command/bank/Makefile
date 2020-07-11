CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=
SOURCES=main.cpp Bank.cpp BankClient.cpp PutCommand.cpp GetCommand.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bank.exe
PREFIX=/usr/local/bin

all: $(EXECUTABLE)

$(EXECUTABLE): main.o Bank.o BankClient.o PutCommand.o GetCommand.o
	$(CC) main.o Bank.o BankClient.o PutCommand.o GetCommand.o -o $(EXECUTABLE)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Bank.o: Bank.cpp
	$(CC) $(CFLAGS) Bank.cpp

BankClient.o: BankClient.cpp
	$(CC) $(CFLAGS) BankClient.cpp

PutCommand.o: PutCommand.cpp
	$(CC) $(CFLAGS) PutCommand.cpp

GetCommand.o: GetCommand.cpp
	$(CC) $(CFLAGS) GetCommand.cpp

install:
	install ./$(EXECUTABLE) $(PREFIX)
	
uninstall:
	rm -rf $(PREFIX)/$(EXECUTABLE)

clean-o:
	rm -rf *.o

clean:
	rm -rf *.o $(EXECUTABLE)
