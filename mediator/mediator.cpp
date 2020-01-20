#include <iostream>
#include <string>
#include <vector>

class Colleague;

class Mediator {
public:
	virtual ~Mediator() = default;
	virtual void Send(std::string const& message, Colleague* colleague) const = 0;
};

class Colleague {
public:
	explicit Colleague(Mediator* mediator) : _mediator(mediator) {}
protected:
	Mediator* _mediator;
};

class ConcreteColleague : public Colleague {
public:
	explicit ConcreteColleague(Mediator* mediator, const std::string &name) : Colleague(mediator) {
		_name = name;
	}

	void Send(std::string const &message) {
		_mediator->Send(message, this);
	}

	void Notify(std::string const &message) {
		std::cout << "Colleague " << _name.data() << " gets message '" << message << "'" << std::endl;
		Answer();
	}

	void Answer() {
		std::cout << "Colleague " << _name.data() << " answered Bless You!" << std::endl;
	}

	std::string& getName() {
		return _name;
	}
private:
	std::string _name;
};

class ConcreteMediator :public Mediator {
public:
	void AddColleague(ConcreteColleague* c) {
		_m_Colleagues.push_back(c);
	}

	void Send(std::string const& message, Colleague* colleague) const override {
		for (ConcreteColleague* colleague : _m_Colleagues)
			colleague->Notify(message);
	}

	void Traverse() {
		for (ConcreteColleague* colleague : _m_Colleagues)
			std::cout << colleague->getName().data() << std::endl;
	}

protected:
	std::vector<ConcreteColleague*> _m_Colleagues;
};

int main() {
	ConcreteMediator mediator;

	std::vector <ConcreteColleague *> colleagues;

	colleagues.push_back(new ConcreteColleague(&mediator, "Vasya"));
	colleagues.push_back(new ConcreteColleague(&mediator, "Petya"));
	colleagues.push_back(new ConcreteColleague(&mediator, "Kolya"));
	colleagues.push_back(new ConcreteColleague(&mediator, "Tolya"));
	colleagues.push_back(new ConcreteColleague(&mediator, "Roma"));
	colleagues.push_back(new ConcreteColleague(&mediator, "Filya"));
	colleagues.push_back(new ConcreteColleague(&mediator, "Alesha"));
	colleagues.push_back(new ConcreteColleague(&mediator, "Gulya"));
	colleagues.push_back(new ConcreteColleague(&mediator, "Sereja"));
	colleagues.push_back(new ConcreteColleague(&mediator, "Nulya"));

	for (auto colleague : colleagues)
		mediator.AddColleague(colleague);

	colleagues[0]->Send("How are you?");
	std::cout << std::endl;

	mediator.Traverse();

	std::cin.get();
	return 0;
}
