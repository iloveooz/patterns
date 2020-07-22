#include <iostream>

// класс, описывающий некоторое блюдо
class Dish {
public:
    Dish(int complexity, const char* description): m_complexity(complexity), m_description(description) {}
private:
	friend class Cook;			// Повар имеют доступ к блюду
    int m_complexity;			// Сложность блюда
    const char* m_description;	// Краткое описание блюда
};

// Абстрактный повар, который может заниматься приготовлением блюда
class Cook {
public:
    Cook(int skill) : m_skill(skill), next(nullptr) {}

    virtual ~Cook() {
        delete next;
    }

     // Добавляет в цепочку ответственности более опытного повара, который сможет принять на себя приготовление блюда, если текущий не справится
    Cook* setNext(Cook* cook) {
        next = cook;
        return next;
    }

    // Повар начинает приготовление или, если блюдо слишком сложное, передает его более опытному коллеге
    void cooking(Dish* dish) {
        if (m_skill < dish->m_complexity) {
            if (next) {
                next->cooking(dish);
            } else {
                std::cout << dish->m_description << " - это блюдо никто не может приготовить." << std::endl;
            }
        } else {
            cookingConcrete(dish->m_description);
        }
    }
protected:
    int m_skill; // опыт (умение готовить сложные блюда) у данного повара
    Cook* next;  // более умелый повар, который получит блюдо, если для текущего оно слишком сложное в плане приготовления
    virtual void cookingConcrete(const char* description) {}    // собственно приготовление
};

class JuniorCook: public Cook {
protected:
    void cookingConcrete(const char* description) {
        std::cout << "Блюдо \"" << description << "\" готовит поварёнок Риггс" << std::endl;
    }

public:
    JuniorCook(int skill): Cook(skill) {}
};

class MiddleCook: public Cook {
protected:
    void cookingConcrete(const char* description) {
        std::cout << "Блюдо \"" << description << "\" готовит повар Джон Макклейн" << std::endl;
    }

public:
    MiddleCook(int skill): Cook(skill) {}
};

class SeniorCook: public Cook {
protected:
    void cookingConcrete(const char* description) {
        std::cout << "Блюдо \"" << description << "\" готовит сеньор-повар Ханна" << std::endl;
    }

public:
    SeniorCook(int skill): Cook(skill) {}
};

class SuperCook : public Cook {
protected:
	void cookingConcrete(const char* description) {
		std::cout << "Блюдо \"" << description << "\" готовит супер-повар Марио" << std::endl;
	}
public:
	SuperCook(int skill) : Cook(skill) {}
};

int main() {
	setlocale(LC_ALL, "Russian");
	Cook* cook = new JuniorCook(3); // повар с наименьшим опытом приготовления блюд
	cook->setNext(new MiddleCook(5))->setNext(new SeniorCook(8))->setNext(new SuperCook(16)); // добавляем ему трёх опытных коллег

	cook->cooking(new Dish(2, "Блинчики"));
	cook->cooking(new Dish(7, "Тортик"));
	cook->cooking(new Dish(5, "Борщец"));
	cook->cooking(new Dish(15, "Дранички"));

	return 0;
}
