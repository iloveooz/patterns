#include <iostream>
#include <tgmath.h>

class Interface {
public:
	virtual ~Interface() {}
    virtual void f() = 0;
    virtual void g() = 0;
};

class A : public Interface {
public:
    void f() { std::cout << "A: вызываем метод f()" << std::endl; }
    void g() { std::cout << "A: вызываем метод g()" << std::endl; }
};

class B : public Interface {
public:
    void f() { std::cout << "B: вызываем метод f()" << std::endl; }
    void g() { std::cout << "B: вызываем метод g()" << std::endl; }
};

class C : public Interface {
public:
	void f() { std::cout << "C: вызываем метод f()" << std::endl; }
    void g() { std::cout << "C: вызываем метод g()" << std::endl; }
};

class User : public Interface {
public:
    // Конструктор
    User() : m_i ( new A() ) { }
    // Деструктор
    virtual ~User() {
        delete m_i;
    }
    void f() { m_i->f(); }
    void g() { m_i->g(); }
    // Этими методами меняем поле-объект, чьи методы будем делегировать
    void toA() {
        delete m_i;
        m_i = new A();
    }
    void toB() {
        delete m_i;
        m_i = new B();
    }
    void toC() {
		delete m_i;
		m_i = new C();
	}
private:
    // Объявляем объект методы которого будем делегировать
    Interface * m_i;
};

int main() {
    User user;

    user.f();
    user.g();
    user.toB();
    user.f();
    user.g();
    user.toC();
    user.f();
    user.g();

    return 0;
}
