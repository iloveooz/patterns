#include <iostream>
#include <string>

class Colleague;
class Mediator;
class ConcreteMediator;
class ConcreteColleague1;
class ConcreteColleague2;

class Mediator {
public:
	virtual ~Mediator() = default;
	virtual void Send(std::string const& message, Colleague* colleague) const = 0;
};

class Colleague {
protected:
	Mediator* _mediator;

public:
	explicit Colleague(Mediator* mediator) : _mediator(mediator) {}
};

class ConcreteColleague1 : public Colleague {
public:
	explicit ConcreteColleague1(Mediator* mediator) : Colleague(mediator) {}

	void Send(std::string const& message) {
		_mediator->Send(message, this);
	}

	void Notify(std::string const& message) {
		std::cout << "Colleague1 gets message '" << message << "'" << std::endl;
	}
private:
	std::string _name;
};

class ConcreteColleague2 :public Colleague {
public:
	explicit ConcreteColleague2(Mediator* mediator) : Colleague(mediator) {}

	void Send(std::string const& message) {
		_mediator->Send(message, this);
	}

	void Notify(std::string const& message) {
		std::cout << "Colleague2 gets message '" << message << "'" << std::endl;
	}
};

class ConcreteMediator :public Mediator {
public:
	void SetColleague1(ConcreteColleague1* c) {
		_m_Colleague1 = c;
	}

	void SetColleague2(ConcreteColleague2* c) {
		_m_Colleague2 = c;
	}

	void Send(std::string const& message, Colleague* colleague) const override {
		if (colleague == _m_Colleague1) {
			_m_Colleague2->Notify(message);
		}
		else if (colleague == _m_Colleague2) {
			_m_Colleague1->Notify(message);
		}
	}
protected:
	ConcreteColleague1* _m_Colleague1 = nullptr;
	ConcreteColleague2* _m_Colleague2 = nullptr;
};

int main() {
	ConcreteMediator mediator;

	ConcreteColleague1 c1(&mediator);
	ConcreteColleague2 c2(&mediator);

	mediator.SetColleague1(&c1);
	mediator.SetColleague2(&c2);

	c1.Send("How are you?");
	c2.Send("Fine, thanks");

	std::cin.get();
	return 0;
}
