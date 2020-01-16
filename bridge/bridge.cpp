#include <iostream>

class Drawer {
public:
	virtual ~Drawer() = default;
	virtual void drawCircle(int x, int y, int radius) = 0;
    virtual void drawPoint(int x, int y) = 0;
};

class SmallCircleDrawer : public Drawer {
    const double radiusMultiplier = 0.25;
public:
    void drawCircle(int x, int y, int radius) override {
	    std::cout << "Small circle center " << x << ", " << y << " radius = " << radius * radiusMultiplier << std::endl;
    }

    void drawPoint(int x, int y) override {}
};

class LargeCircleDrawer : public Drawer {
    const double radiusMultiplier = 10;
public:
    void drawCircle(int x, int y, int radius) override {
	    std::cout << "Large circle center " << x << ", " << y << " radius = " << radius * radiusMultiplier  << std::endl;
    }
    void drawPoint(int x, int y) override {}
};

class PointDrawer : public Drawer {
public:
    void drawCircle(int x, int y, int radius) override {}

    void drawPoint(int x, int y) override {
        std::cout << "Point center " << x << ", " << y << std::endl;
    }
};

class SmallSquareDrawer : public Drawer {
    const double sideMultiplier = 0.25;
public:

};

class LargeSquareDrawer : public Drawer {
    const double sideMultiplier = 0.25;
public:

};

class Shape {
protected:
    Drawer* drawer;

public:
    Shape(Drawer* drw) {
        drawer = drw;
    }

    Shape() {}

    virtual void draw() = 0;
    virtual void enlargeRadius(int multiplier) = 0;
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

int main(int argc, char* argv[])
{
    Shape* shapes[3] = { new Circle(5,10,10, new LargeCircleDrawer()),
                         new Circle(20,30,1, new SmallCircleDrawer()), 
						 new Point(100, 100, new PointDrawer()) };

    for (Shape* shape : shapes) {
	    shape->draw();
    }

    system("pause");
    return 0;
}
