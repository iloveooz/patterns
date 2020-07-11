#include <iostream> 
#include <stack> 

//State 
class Point {
public: 
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
	
	void setX(int x) {
		this->x += x;
	}
	
	void setY(int y) {
		this->y += y;
	}
	
	int getX() const {
		return x;
	}
	
	int getY() const {
		return y;
	}

private:
	int x, y;
};

class Memento {
public: 
	Memento(Point* state) {
		this->state = state;
	}

	Point getState() {
		return *state;
	}

private: 
	Point* state;
};

//Originator 
class Shape {
public: 
	Point position = Point(0, 0);

	void move(int left, int top) {
		position.setX(left);
		position.setY(top);
	}

	Memento getMemento() {
		Point* state = new Point(position.getX(), position.getY());
		return Memento(state);
	}

	void setMemento(Memento memento) {
		position = memento.getState();
	}
};

//Caretaker 
class ShapeHelper {
public: 
	ShapeHelper(Shape* shape) {
		this->shape = shape;
	}

	void move(int left, int top)  {
		stack.push(shape->getMemento());
		shape->move(left, top);
	}

	void undo() {
		if (!stack.empty()) {
			shape->setMemento(stack.top());
			stack.pop();
		}
	}

private: 
	std::stack<Memento> stack;
	Shape* shape;
};

int main() {
	ShapeHelper helper(new Shape);

	helper.move(2, 3); // shape.position is (2, 3) 
	helper.move(-5, 4); // shape.position is (-3, 7) 
	helper.undo(); // shape.position is (2, 3) 
	helper.undo(); // shape.position is (0, 0)
	
	return 0;
}
