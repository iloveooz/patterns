#include <iostream>
#include <tgmath.h>

class Interface {
public:
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
    // Конструктор
    C() : m_i ( new A() ) { }
    // Деструктор
    virtual ~C() {
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
private:
    // Объявляем объект методы которого будем делегировать
    Interface * m_i;
};

int main() {
    C c;

    c.f();
    c.g();
    c.toB();
    c.f();
    c.g();

    return 0;
}
