#include <iostream>
#include <vector>
#include <ctime>
 
class Base {
  public:
    virtual ~Base() {}

    Base() {
        next = nullptr;
    }
    void setNext(Base* n) {
        next = n;
    }
    void add(Base *n) {
        if (next)
          next->add(n);
        else
          next = n;
    }
    // 2. Метод базового класса, делегирующий запрос next-объекту
    virtual void handle(int i, int year) {
        next->handle(i, year);
    }
private:
	    // 1. Указатель "next" в базовом классе
    Base* next;
};
 
class Handler1_32: public Base {
public:
     /*virtual*/void handle(int i, int year) {
        if (rand() % 2) {
            // 3. 3 из 4 запросов не обрабатываем
            std::cout << "1/32 won - ";
            // 3. и делегируем базовому классу
            Base::handle(i, year);
        }
        else
	        std::cout << "1/32 lost.";
    }
};
 
class Handler1_16: public Base {
public:
     /*virtual*/void handle(int i, int year) {
        if (rand() % 2) {
	        std::cout << "1/16 won - ";
            Base::handle(i, year);
        }
        else
	        std::cout << "1/16 lost.";
    }
};
 
class Handler1_8: public Base {
public:
     /*virtual*/void handle(int i, int year) {
        if (rand() % 2)  {
	        std::cout << "1/8 won - ";
            Base::handle(i, year);
        }
        else
	        std::cout << "1/8 lost.";
    }
};

class Handler1_4: public Base {
public:
     /*virtual*/void handle(int i, int year) {
        if (rand() % 2)  {
	        std::cout << "1/4 won - ";
            Base::handle(i, year);
        }
        else
	        std::cout << "1/4 lost.";
    }
};

class Handler1_2: public Base {
public:
     /*virtual*/void handle(int i, int year) {
        if (rand() % 2)  {
	        std::cout << "1/2 won - ";
            Base::handle(i, year);
        }
        else
	        std::cout << "1/2 lost.";
    }
};

class Handler1_1: public Base {
public:
     /*virtual*/void handle(int i, int year) {
        if (rand() % 2)  {
	        std::cout << "FINAL won! " << year << '\n';
        }
        else
	        std::cout << "FINAL lost. " << year;
    }
};

int main() {
	srand(time(nullptr));

	int year = 1950;
	
	Handler1_32 far;
	Handler1_16 sixteen;
	Handler1_8 eight;
	Handler1_4 four;
	Handler1_2 semifinal;
	Handler1_1 final;
	
	far.add(&sixteen);
	far.add(&eight);
	far.add(&four);
	far.add(&semifinal);
	far.add(&final);
	
	final.setNext(&far);
	
	for (int i = 1; i <= 71; i++, year++) {
		std::cout << year << ": ";
		far.handle(i, year);
		std::cout << '\n';
	}
	
	system("pause");
	return 0;
}
