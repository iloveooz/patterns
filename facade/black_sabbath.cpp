#include <iostream>
#include <string>
#include <memory>

/** Абстрактный музыкант - не является обязательной составляющей паттерна, введен для упрощения кода */
class Musician {

	std::string name;

public:
	Musician(const std::string &name) {
		this->name = name.data();
	}

	virtual ~Musician() = default;

protected:
	void output(const std::string &text) {
		std::cout << this->name << " " << text << "." << std::endl;
	}
};

/** Конкретные музыканты */
class Vocalist : public Musician {

public:
	Vocalist(const std::string &name) : Musician(name) {}

	void singCouplet(int coupletNumber) {
		std::string text = "спел куплет №";
		text += std::to_string(coupletNumber);
		output(text);
	}

	void singChorus() {
		std::string text = "спел припев";
		output(text);
	}
};

class Guitarist : public Musician {

public:
	Guitarist(const std::string &name) : Musician(name) {}

	void playCoolOpening() {
		std::string text = "начинает с крутого вступления";
		output(text);
	}

	void playCoolRiffs() {
		std::string text = "играет крутые риффы";
		output(text);
	}

	void playAnotherCoolRiffs() {
		std::string text = "играет другие крутые риффы";
		output(text);
	}

	void playIncrediblyCoolSolo() {
		std::string text = "выдает невероятно крутое соло";
		output(text);
	}

	void playFinalAccord() {
		std::string text = "заканчивает песню мощным аккордом";
		output(text);
	}
};

class Bassist : public Musician {

public:
	Bassist(const std::string &name) : Musician(name) {}

	void followTheDrums() {
		std::string text = "следует за барабанами";
		output(text);
	}

	void changeRhythm(const std::string type) {
		std::string text = ("перешел на ритм ");
		text += type;
		text += "a";
		output(text);
	}

	void stopPlaying() {
		std::string text = "заканчивает играть";
		output(text);
	}
};

class Drummer : public Musician {

public:
	Drummer(const std::string &name) : Musician(name) {}

	void startPlaying() {
		std::string text = "начинает играть";
		output(text);
	}

	void stopPlaying() {
		std::string text = "заканчивает играть";
		output(text);
	}
};

/** Фасад, в данном случае - знаменитая рок-группа */
class BlackSabbath {

	std::unique_ptr<Vocalist> vocalist;
	std::unique_ptr<Guitarist> guitarist;
	std::unique_ptr<Bassist> bassist;
	std::unique_ptr<Drummer> drummer;

public:

	BlackSabbath() {
		vocalist = std::make_unique<Vocalist>("Оззи Осборн");
		guitarist = std::make_unique<Guitarist>("Тони Айомми");
		bassist = std::make_unique<Bassist>("Гизер Батлер");
		drummer = std::make_unique<Drummer>("Билл Уорд");
	}

	void playCoolSong() {
		guitarist->playCoolOpening();
		drummer->startPlaying();
		bassist->followTheDrums();
		guitarist->playCoolRiffs();
		vocalist->singCouplet(1);

		std::string chorus("припев");
		std::string couplet("куплет");

		bassist->changeRhythm(std::string(chorus));
		guitarist->playAnotherCoolRiffs();
		vocalist->singChorus();

		bassist->changeRhythm(std::string(couplet));
		guitarist->playCoolRiffs();
		vocalist->singCouplet(2);

		bassist->changeRhythm(std::string(chorus));
		guitarist->playAnotherCoolRiffs();
		vocalist->singChorus();

		bassist->changeRhythm(std::string(couplet));
		guitarist->playIncrediblyCoolSolo();
		guitarist->playCoolRiffs();
		vocalist->singCouplet(3);

		bassist->changeRhythm(std::string(chorus));
		guitarist->playAnotherCoolRiffs();
		vocalist->singChorus();

		bassist->changeRhythm(std::string(couplet));
		guitarist->playCoolRiffs();
		bassist->stopPlaying();
		drummer->stopPlaying();
		guitarist->playFinalAccord();
	}
};

int main() {
	setlocale(LC_ALL, "Russian");
	std::cout << "OUTPUT:" << std::endl;
	BlackSabbath band;
	band.playCoolSong();

	std::cout << std::endl;
	system("pause");
	return 0;
}
