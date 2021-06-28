#pragma warning(disable : 4996)
#include <iostream>
#include <string>

class Thousand;
class Hundred;
class Ten;
class One;

class RNInterpreter {
public:
	
	RNInterpreter(); // ctor for client
	RNInterpreter(int) {}
	// ctor for subclasses, avoids infinite loop

	virtual ~RNInterpreter() = default;
	
	int interpret(char*) const; // interpret() for client
	
	virtual void interpret(char* input, int &total)
	{
		// for internal use
		int index = 0;
		if (!strncmp(input, nine(), 2))
		{
			total += 9 * multiplier();
			index += 2;
		}
		else if (!strncmp(input, four(), 2))
		{
			total += 4 * multiplier();
			index += 2;
		}
		else
		{
			if (input[0] == five())
			{
				total += 5 * multiplier();
				index = 1;
			}
			else
				index = 0;
			for (int end = index + 3; index < end; index++)
				if (input[index] == one())
					total += 1 * multiplier();
				else
					break;
		}
		strcpy(input, &(input[index]));
	} // remove leading chars processed
protected:
	// cannot be pure virtual because client asks for instance
	virtual char one() { return '\0'; }
	virtual const char* four() { return ""; }
	virtual char five() { return '\0'; }
	virtual const char* nine() { return ""; }
	
	virtual int multiplier() { return 0; }
private:
	RNInterpreter *thousands;
	RNInterpreter *hundreds;
	RNInterpreter *tens;
	RNInterpreter *ones;
};

class Thousand : public RNInterpreter {
public:
	// provide 1-arg ctor to avoid infinite loop in base class ctor
	Thousand(int) : RNInterpreter(1) {}
protected:
	char one() override {
		return 'M';
	}
	const char* four() override {
		return "";
	}
	char five() override {
		return '\0';
	}
	const char* nine() override {
		return "";
	}
	
	int multiplier() override {
		return 1000;
	}
};

class Hundred : public RNInterpreter {
public:
	Hundred(int) : RNInterpreter(1) {}
protected:
	 char one() override {
		return 'C';
	}
	const char* four() override {
		return "CD";
	}
	char five() override {
		return 'D';
	}
	const char* nine() override {
		return "CM";
	}
	
	int multiplier() override {
		return 100;
	}
};

class Ten : public RNInterpreter {
public:
	Ten(int) : RNInterpreter(1) {}
protected:
	char one() override {
		return 'X';
	}
	const char* four() override {
		return "XL";
	}
	char five() override {
		return 'L';
	}
	const char* nine() override {
		return "XC";
	}
	
	int multiplier() override {
		return 10;
	}
};

class One : public RNInterpreter {
public:
	One(int) : RNInterpreter(1) {}
protected:
	char one() override {
		return 'I';
	}
	const char* four() override {
		return "IV";
	}
	char five() override {
		return 'V';
	}
	const char* nine() override {
		return "IX";
	}
	
	int multiplier() override {
		return 1;
	}
};

RNInterpreter::RNInterpreter() {
	// use 1-arg ctor to avoid infinite loop
	thousands = new Thousand(1);
	hundreds = new Hundred(1);
	tens = new Ten(1);
	ones = new One(1);
}

int RNInterpreter::interpret(char* input) const {
	int total = 0;
	
	thousands->interpret(input, total);
	hundreds->interpret(input, total);
	tens->interpret(input, total);
	ones->interpret(input, total);
	
	if (strcmp(input, "") != 0)
		// if input was invalid, return 0
		return 0;
	return total;
}

int main() {
	const RNInterpreter interpreter;
	char input[20];
	
	std::cout << "Enter Roman Numeral: ";
	
	while (std::cin >> input) {
		std::cout << "   interpretation is "
			<< interpreter.interpret(input) << std::endl;
		std::cout << "Enter Roman Numeral: ";
	}
}
