#include <iostream>

class Base {
	void a() { 
		std::cout << "a ";
	}
	void c() {
		std::cout << "c ";
	}
	void e() {
		std::cout << "e ";
	}
	// 2. Для шагов, требующих особенной реализации, определите "замещающие" методы.
	virtual void ph1() = 0;
	virtual void ph2() = 0;
	virtual void ph3() = 0;
public:
	// 1. Стандартизуйте основу алгоритма в шаблонном методе базового класса
	void execute() {
		a();
		ph1();
		c();
		ph2();
		e();
		ph3();
	}
};

class One : public Base {
	// 3. Производные классы реализуют "замещающие" методы.
	/*virtual*/void ph1() override {
		std::cout << "b ";
	}
	/*virtual*/void ph2() override {
		std::cout << "d ";
	}
	/*virtual*/void ph3() override {
		std::cout << "f ";
	}
};

class Two : public Base
{
	/*virtual*/void ph1() override {
		std::cout << "2 ";
	}
	/*virtual*/void ph2() override {
		std::cout << "4 ";
	}
	/*virtual*/void ph3() override {
		std::cout << "6 ";
	}
};

class Three : public Base
{
	/*virtual*/void ph1() override {
		std::cout << "II ";
	}
	/*virtual*/void ph2() override {
		std::cout << "IV ";
	}
	/*virtual*/void ph3() override {
		std::cout << "VI ";
	}
};

int main() {
	Base *array[] = { &One(), &Two(), &Three() };
	
	for (auto& i : array) {
		i->execute();
		std::cout << '\n';
	}

	system("pause");
	return 0;
}
