#include <iostream>
#include <vector>

enum class Shape_ID {
	SmallCircle_ID,
    LargeCircle_ID,
    Point_ID,
    Square_ID
};

class Drawer {
public:
	virtual ~Drawer() = default;
	virtual void drawCircle(int x, int y, int radius) = 0;
    virtual void drawPoint(int x, int y) = 0;
    virtual void drawSquare(int x, int y, int edge) = 0;
};

class SmallCircleDrawer : public Drawer {
    const double radiusMultiplier = 0.25;
public:
    void drawCircle(int x, int y, int radius) override {
	    std::cout << "Small circle center (" << x << ", " << y << ") radius = " << radius * radiusMultiplier << std::endl;
    }

    void drawPoint(int x, int y) override {}

    void drawSquare(int x, int y, int edge) override {}
};

class LargeCircleDrawer : public Drawer {
    const double radiusMultiplier = 10;
public:
    void drawCircle(int x, int y, int radius) override {
	    std::cout << "Large circle center (" << x << ", " << y << ") radius = " << radius * radiusMultiplier  << std::endl;
    }
    void drawPoint(int x, int y) override {}

    void drawSquare(int x, int y, int edge) override {}
};

class PointDrawer : public Drawer {
public:
    void drawCircle(int x, int y, int radius) override {}

    void drawPoint(int x, int y) override {
        std::cout << "Point center (" << x << ", " << y << ")" << std::endl;
    }

    void drawSquare(int x, int y, int edge) override {}
};

class SquareDrawer final : public Drawer {
public:
    void drawCircle(int x, int y, int radius) override {}

    void drawPoint(int x, int y) override {}

    void drawSquare(int x, int y, int edge) override {
        std::cout << "Square upper corner (" << x << ", " << y << ") edge = " << edge << std::endl;
    }
};

class Shape {
protected:
    Drawer* drawer;

public:
    Shape(Drawer* drw) {
        drawer = drw;
    }

    Shape(): drawer(nullptr) {
    }

    virtual ~Shape() {}

    virtual void draw() = 0;
    virtual void enlargeRadius(int multiplier) = 0;

    static Shape* createShape(Shape_ID, int x, int y, int edge, int radius);
};

class Circle : public Shape {
    int x, y, radius;
public:
    Circle(int _x, int _y, int _radius, Drawer* drw) {
        drawer = drw;
        setX(_x);
        setY(_y);
        setRadius(_radius);
    }

    void draw() override {
        drawer->drawCircle(x, y, radius);
    }

    void enlargeRadius(int multiplier) override {
        radius *= multiplier;
    }

    void setX(int _x) {
        x = _x;
    }

    void setY(int _y) {
        y = _y;
    }

    void setRadius(int _radius) {
        radius = _radius;
    }
};

class Point : public Shape {
    int x, y;
public:
    Point(int _x, int _y, Drawer* drw) {
        drawer = drw;
        setX(_x);
        setY(_y);
    }

    void draw() override {
        drawer->drawPoint(x, y);
    }

    void setX(int _x) {
        x = _x;
    }

    void setY(int _y) {
        y = _y;
    }

    void enlargeRadius(int multiplier) override {}
};

class Square : public Shape {
    int x, y, edge;
public:
    Square(int _x, int _y, int _edge, Drawer* drw) {
        drawer = drw;
        setX(_x);
        setY(_y);
        setEdge(_edge);
    }

    void draw() override {
        drawer->drawSquare(x, y, edge);
    }

    void setX(int _x) {
        x = _x;
    }

    void setY(int _y) {
        y = _y;
    }

    void setEdge(int _edge) {
        edge = _edge;
    }

    void enlargeRadius(int multiplier) override {}
};

Shape* Shape::createShape(Shape_ID id, int x, int y, int edge, int radius) {
    Shape* sh = nullptr;

    switch(id) {
    case Shape_ID::LargeCircle_ID:
        sh = new Circle(x, y, radius, new LargeCircleDrawer());
        break;
    case Shape_ID::SmallCircle_ID:
        sh = new Circle(x, y, radius, new SmallCircleDrawer());
        break;
    case Shape_ID::Point_ID:
        sh = new Point(x, y, new PointDrawer());
    	break;
    case Shape_ID::Square_ID:
        sh = new Square(x, y, edge, new SquareDrawer());
    	break;
    default:
        break;
    }
    return sh;
}

class ShapeFactory {
public:
    virtual Shape* createShape() = 0;
};

int main(int argc, char* argv[])
{
    std::vector<Shape*> shapes = { 
		new Circle(5,10,10, new LargeCircleDrawer()),
		new Circle(20,30,1, new SmallCircleDrawer()), 
		new Point(100, 100, new PointDrawer()),
		new Point(1000, 1000, new PointDrawer())
    };

    shapes.push_back(new Square(100, 100, 100, new SquareDrawer()));
    shapes.push_back(new Square(1000, 1000, 100, new SquareDrawer()));

    shapes.push_back(Shape::createShape(Shape_ID::LargeCircle_ID, 55, 55, 55, 55));
    shapes.push_back(Shape::createShape(Shape_ID::Square_ID, 55, 55, 55, 55));

    for (Shape* shape : shapes) {
	    shape->draw();
    }

    system("pause");
    return 0;
}


