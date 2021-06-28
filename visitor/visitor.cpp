#include <iostream>
#include <string>

// 1. Добавьте метод accept(Visitor) иерархию "элемент"
class Element {
public:
	virtual void accept(class Visitor &v) = 0;
};

class This : public Element {
public:
	/*virtual*/void accept(Visitor &v) override;

	std::string thiss() {
		return "This";
	}
};

class That : public Element {
public:
	/*virtual*/void accept(Visitor &v);

	std::string that() {
		return "That";
	}
};

class TheOther : public Element {
public:
	/*virtual*/void accept(Visitor &v);

	std::string theOther() {
		return "TheOther";
	}
};

// 2. Создайте базовый класс Visitor и определите 
// методы visit()для каждого типа "элемента"
class Visitor {
public:
	virtual void visit(This *e) = 0;
	virtual void visit(That *e) = 0;
	virtual void visit(TheOther *e) = 0;
};

/*virtual*/void This::accept(Visitor &v) {
	v.visit(this);
}

/*virtual*/void That::accept(Visitor &v) {
	v.visit(this);
}

/*virtual*/void TheOther::accept(Visitor &v) {
	v.visit(this);
}

// 3. Создайте производные классы Visitor для каждой 
// "операции", исполняемой над "элементами"
class UpVisitor : public Visitor {
	/*virtual*/void visit(This *e) {
		std::cout << "do Up on " + e->thiss() << '\n';
	}
	/*virtual*/void visit(That *e) {
		std::cout << "do Up on " + e->that() << '\n';
	}
	/*virtual*/void visit(TheOther *e) {
		std::cout << "do Up on " + e->theOther() << '\n';
	}
};

class DownVisitor : public Visitor {
	/*virtual*/void visit(This *e) {
		std::cout << "do Down on " + e->thiss() << '\n';
	}
	/*virtual*/void visit(That *e) {
		std::cout << "do Down on " + e->that() << '\n';
	}
	/*virtual*/void visit(TheOther *e) {
		std::cout << "do Down on " + e->theOther() << '\n';
	}
};

int main() {
	Element *list[] = { new This(), new That(), new TheOther() };

	UpVisitor up;      // 4. Клиент создает 
	DownVisitor down;  //    объекты Visitor
	
	for (auto& i : list)
		// и передает каждый 
		i->accept(up);
	
	for (auto& i : list)
		// в вызываемый метод accept()
		i->accept(down);

	system("pause");
	return 0;
}
