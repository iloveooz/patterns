#include<iostream>
#include<vector>
#include<string>

class Game {
public:
	void create() {
		std::cout << "Create game " << std::endl;
	}

	void open(std::string file) {
		std::cout << "Open game from " << file << std::endl;
	}

	void save(std::string file) {
		std::cout << "Save game in " << file << std::endl;
	}

	void make_move(std::string move) {
		std::cout << "Make move " << move << std::endl;
	}
};

std::string getPlayerInput(std::string prompt) {
	std::string input;
	std::cout << prompt;
	std::cin >> input;
	return input;
}

// Базовый класс
class Command {
public:
	virtual ~Command() {}
	virtual void execute() = 0;
	
protected:
	Command(Game* p): pgame(p) {}
	Game* pgame;
};

class CreateGameCommand: public Command {
public:
	CreateGameCommand(Game* p) : Command(p) {}
	
	void execute() {
		pgame->create();
	}
};

class OpenGameCommand: public Command {
public:
	OpenGameCommand(Game* p) : Command(p) {}
	
	void execute() {
		std::string file_name;
		file_name = getPlayerInput("Enter file name:");
		pgame->open(file_name);
	}
};

class SaveGameCommand: public Command {
public:
	SaveGameCommand(Game* p) : Command(p) {}
	
	void execute() {
		std::string file_name;
		file_name = getPlayerInput("Enter file name:");
		pgame->save(file_name);
	}
};

class MakeMoveCommand: public Command {
public:
	MakeMoveCommand(Game* p) : Command(p) {}
	
	void execute() { 
		// Сохраним игру для возможного последующего отката
		pgame->save("TEMP_FILE");
		std::string move;
		move = getPlayerInput("Enter your move:");
		pgame->make_move(move);
	}
};

class UndoCommand: public Command {
public:
	UndoCommand(Game* p) : Command(p) {}
	
	void execute() { 
		pgame->open("TEMP_FILE"); // Восстановим игру из временного файла
	}
};


int main() {
	Game game;
	std::vector<Command* > v; // Имитация действий игрока
	
	v.push_back(new CreateGameCommand(&game));	// Создаем новую игру 
	v.push_back(new MakeMoveCommand(&game));	// Делаем несколько ходов
	v.push_back(new MakeMoveCommand(&game));
	v.push_back(new UndoCommand(&game));		// Последний ход отменяем
	v.push_back(new SaveGameCommand(&game));	// Сохраняем игру

	for (size_t i = 0; i < v.size(); ++i)
		v[i]->execute();

	for (size_t i = 0; i < v.size(); ++i)
		delete v[i];

	return 0;
}
