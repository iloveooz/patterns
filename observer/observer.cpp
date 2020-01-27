#include <iostream>
#include <string>
#include <list>

class SupervisedString;

class IObserver {
public:
	virtual void handleEvent(const SupervisedString&) = 0;
};

class SupervisedString { // Observable class
	std::string _str;
	std::list<IObserver*> _observers;

	void _Notify() {
		for (auto& observer : _observers) {
			observer->handleEvent(*this);
		}
	}

	public:
	void add(IObserver& ref) {
		_observers.push_back(&ref);
	}

	void remove(IObserver& ref) {
		_observers.remove(&ref);
	}

	const std::string& get() const {
		return _str;
	}

	void reset(std::string str) {
		_str = str;
		_Notify();
	}
};

class Reflector : public IObserver { // Prints the observed string into cout
public:
	virtual void handleEvent(const SupervisedString& ref) {
		std::cout << ref.get() << std::endl;
	}
};

class Counter : public IObserver { // Prints the length of observed string into cout
public:
	virtual void handleEvent(const SupervisedString& ref) {
		std::cout << "length = " << ref.get().length() << std::endl;
	}
};

int main() {
	SupervisedString str;
	Reflector refl;
	Counter cnt;

	str.add(refl);
	str.reset("Hello, World!");
	std::cout << std::endl;

	str.remove(refl);
	str.add(cnt);
	str.reset("World, Hello!");
	std::cout << std::endl;

	system("pause");
	return 0;
}
