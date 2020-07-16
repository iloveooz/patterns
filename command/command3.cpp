#include <iostream>
#include <vector>
#include <string>

class Game {
public:
	static void create() {
		std::cout << "Create game " << std::endl;
	}

	static void open(const std::string& file) {
		std::cout << "Open game from " << file << std::endl;
	}

	static void save(const std::string& file) {
		std::cout << "Save game in " << file << std::endl;
	}

	static void make_move(const std::string& move) {
		std::cout << "Make move " << move << std::endl;
	}
};

std::string getPlayerInput(const std::string& prompt) {
	std::string input;
	std::cout << prompt;
	std::cin >> input;
	return input;
}

// Базовый класс
class command {
public:
	virtual ~command() = default;
	virtual void execute() = 0;
protected:
	command() = default;
};

class CreateGameCommand : public command {
public:
	CreateGameCommand() = default;

	void execute() override {
		Game::create();
	}
};

class OpenGameCommand : public command {
public:
	OpenGameCommand() = default;
	
	void execute() override {
		const std::string file_name = getPlayerInput("Enter file name:");
		Game::open(file_name);
	}
};

class SaveGameCommand : public command {
public:
	SaveGameCommand() = default;
	
	void execute() override {
		const std::string file_name = getPlayerInput("Enter file name:");
		Game::save(file_name);
	}
};

class MakeMoveCommand : public command {
public:
	MakeMoveCommand() = default;
	
	void execute() override {
		// Сохраним игру для возможного последующего отката
		Game::save("TEMP_FILE");
		const std::string move = getPlayerInput("Enter your move:");
		Game::make_move(move);
	}
};

class UndoCommand : public command {
public:
	UndoCommand() = default;

	void execute() override {
		// Восстановим игру из временного файла
		Game::open("TEMP_FILE");
	}
};


int main() {
	std::vector <command*> v; // Имитация действий игрока
	v.push_back(new CreateGameCommand());	// Создаем новую игру 

	v.push_back(new MakeMoveCommand());	// Делаем несколько ходов
	v.push_back(new MakeMoveCommand());
	
	v.push_back(new UndoCommand());		// Последний ход отменяем
	v.push_back(new SaveGameCommand());	// Сохраняем игру

	for (auto& i : v)
		i->execute();

	for (auto& i : v)
		delete i;

	system("pause");
	return 0;
}
