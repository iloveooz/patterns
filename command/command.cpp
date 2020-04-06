#include <iostream>
#include <vector>
#include <string>

class Document {
	std::vector<std::string> data;
public:
	Document() {
		data.reserve(100); // at least for 100 lines
	}

	void Insert(int line, const std::string & str) {
		if (line <= data.size())
			data.insert(data.begin() + line, str);
		else
			std::cout << "Error!" << std::endl;
	}

	void Remove(int line) {
		if (!(line>data.size()))
			data.erase(data.begin() + line);
		else
			std::cout << "Error!" << std::endl;
	}

	std::string & operator [] (int x) {
		return data[x];
	}

	void Show() {
		for (int i = 0; i<data.size(); ++i) {
			std::cout << i + 1 << ". " << data[i] << std::endl;
		}
	}
};

class Command {
protected:
	Document * doc;
public:
	virtual ~Command() {}
	virtual void Execute() = 0;
	virtual void unExecute() = 0;

	void setDocument(Document * _doc) {
		doc = _doc;
	}
};

class InsertCommand : public Command {
	int line;
	std::string str;
public:
	InsertCommand(int _line, const std::string & _str) : line(_line), str(_str) {}

	void Execute() {
		doc->Insert(line, str);
	}

	void unExecute() {
		doc->Remove(line);
	}
};

class Invoker {
	std::vector<Command *> DoneCommands;
	Document doc;
	Command* command;
public:
	void Insert(int line, std::string str) {
		command = new InsertCommand(line, str);
		command->setDocument(&doc);
		command->Execute();
		DoneCommands.push_back(command);
	}

	void Undo() {
		if (DoneCommands.size() == 0) {
			std::cout << "There is nothing to undo!" << std::endl;
		} else {
			command = DoneCommands.back();
			DoneCommands.pop_back();
			command->unExecute();
			// Don't forget to delete command!!!
			delete command;
		}
	}

	void Show() {
		doc.Show();
	}
};

int main() {
	char s = '1';
	int line, line_b;
	std::string str;
	Invoker inv;
	while (s != 'e') {
		std::cout << "What to do: \n1. Add a line\n2. Undo last command" << std::endl;
		std::cin >> s;

		switch (s) {
		case '1':
			std::cout << "What line to insert: ";
			std::cin >> line;
			--line;
			std::cout << "What to insert: ";
			std::cin >> str;
			inv.Insert(line, str);
			break;
		case '2':
			inv.Undo();
			break;
		}
		std::cout << "$$$DOCUMENT$$$" << std::endl;
		inv.Show();
		std::cout << "$$$DOCUMENT$$$" << std::endl;
	}

	system("pause");
	return 0;
}
