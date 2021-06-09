#include <iostream>
#include <vector>
#include <string>

using Text = std::vector<std::string>;

class Quest {
public:
	Quest() {
		m_text.reserve(100);
	}

	void Insert(int line, const std::string& str) {
		if (line <= m_text.size())
			m_text.insert(m_text.begin() + line, str);
		else
			std::cout << "Insert Error!" << std::endl;
	}
	
	void Remove(int line) {
		if (!(line > m_text.size()))
			m_text.erase(m_text.begin() + line);
		else
			std::cout << "Remove Error!" << std::endl;
	}

	std::string& operator [] (int x) {
		return m_text[x];
	}

	void ShowText() {
		int i = 1;
		for (auto& piece : m_text) {
			std::cout << i++ << '.' << piece << std::endl;
		}
	}
private:
	Text m_text;
};

class Game {
public:
	Game() : line(0), m_quest(new Quest) {}
	
	void create() {
		std::cout << "Create game " << std::endl;
	}

	void open(const std::string& file) {
		std::cout << "Open game from " << file << std::endl;
	}

	void save(const std::string& file) {
		std::cout << "Save game in " << file << std::endl;
		m_quest->ShowText();
	}

	void make_edit(const std::string& str) {
		std::cout << "Add: " << str << std::endl;
		m_quest->Insert(line++, str);
	}

	void undo_edit(int number) {
		std::cout << "Undo: " << number << std::endl;
		m_quest->Remove(number);
	}

	void close() {
		std::cout << "Close game" << std::endl;
	}

	void setQuest(Quest* pQuest) {
		m_quest = pQuest;
	}
	
	Quest* getQuest() {
		return m_quest;
	}

private:
	int line;
	Quest* m_quest;
};

template <typename OutType>
OutType getPlayerInput(const std::string& value = "") {
	OutType out;
	std::cout << value;
	if constexpr (std::is_same_v<OutType, std::string>)
		std::getline(std::cin, out, '\n');
	else {
		std::cin >> out;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return out;
}

// Базовый класс
class Command {
public:
	virtual ~Command() = default;
	virtual void execute() = 0;

protected:
	Command(Game* pGame) : m_pGame(pGame) {}
	Game* m_pGame;
};

class CreateGameCommand : public Command {
public:
	CreateGameCommand(Game* pGame) : Command(pGame) {}

	void execute() override {
		m_pGame->create();
	}
};

class OpenGameCommand : public Command {
public:
	OpenGameCommand(Game* pGame) : Command(pGame) {}
	
	void execute() override {
		const auto file_name = getPlayerInput<std::string>("Enter open file name: ");
		m_pGame->open(file_name);
	}
};

class SaveGameCommand : public Command {
public:
	SaveGameCommand(Game* pGame) : Command(pGame) {}

	void execute() override {
		const auto file_name = getPlayerInput<std::string>("Enter save file name: ");
		m_pGame->save(file_name);
	}
};

class CloseGameCommand : public Command {
public:
	CloseGameCommand(Game* pGame) : Command(pGame) {}

	void execute() override {
		m_pGame->close();
	}
};

class MakeEditCommand : public Command {
public:
	MakeEditCommand(Game* pGame) : Command(pGame) {}

	void execute() override {
		const auto str = getPlayerInput<std::string>("Enter your string: ");
		m_pGame->make_edit(str);
	}
};

class UndoEditCommand : public Command {
public:
	UndoEditCommand(Game* pGame) : Command(pGame) {}

	void execute() override {
		const int number = getPlayerInput<int>("Enter your line number: ");
		m_pGame->undo_edit(number);
	}
};


int main() {
	Game* pGame = new Game();
	
	std::vector <Command*> v; // Имитация действий игрока
	
	v.push_back(new CreateGameCommand(pGame));	// Создаем новую игру
	v.push_back(new OpenGameCommand(pGame));	// Открываем игру

	v.push_back(new MakeEditCommand(pGame));	// Делаем несколько ходов
	v.push_back(new MakeEditCommand(pGame));
	v.push_back(new MakeEditCommand(pGame));
	v.push_back(new MakeEditCommand(pGame));
	v.push_back(new MakeEditCommand(pGame));
	
	v.push_back(new UndoEditCommand(pGame));		// Последний ход отменяем
	v.push_back(new SaveGameCommand(pGame));	// Сохраняем игру
	v.push_back(new CloseGameCommand(pGame));	// Закрываем игру

	for (auto& i : v)
		i->execute();

	for (auto& i : v)
		delete i;

	delete pGame;

	system("pause");
	return 0;
}
