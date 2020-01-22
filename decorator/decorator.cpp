#include <iostream>
#include <memory>

class IComponent {
public:
	virtual void operation() = 0;
	virtual ~IComponent() = default;
};

class Component : public IComponent {
public:
	void operation() override {
		std::cout << "World!" << std::endl;
	}
};

class DecoratorOne : public IComponent {
	std::shared_ptr<IComponent> _m_component;

public:
	DecoratorOne(std::shared_ptr<IComponent> component) : _m_component(std::move(component)) {}

	void operation() override {
		std::cout << ", ";
		_m_component->operation();
	}
};

class DecoratorTwo : public IComponent {
	std::shared_ptr<IComponent> _m_component;

public:
	DecoratorTwo(std::shared_ptr<IComponent> component) : _m_component(std::move(component)) {}

	void operation() override {
		std::cout << "Hello";
		_m_component->operation();
	}
};

int main() {
	DecoratorTwo obj(std::make_shared<DecoratorOne>(std::make_shared<Component>()));
	obj.operation(); // prints "Hello, World!\n"

	std::cin.get();
	return 0;
}
