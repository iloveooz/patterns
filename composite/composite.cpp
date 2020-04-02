#include <iostream>
#include <list>
#include <memory>

class IShape {
public:
    typedef std::shared_ptr<IShape> SPtr;

    virtual void draw() = 0;

    virtual void addComponent(const SPtr&) {
        throw std::runtime_error("SPtr: Can't add to a leaf");
    }

    virtual void removeComponent(const SPtr&) {
        throw std::runtime_error("SPtr: Can't remove from a leaf");
    }
};

class Square : public IShape {
    virtual void draw() {
        std::cout << "I'm a square" << std::endl;
    }
};

class Circle : public IShape {
    virtual void draw() {
        std::cout << "I'm a circle" << std::endl;
    }
};

class Triangle : public IShape {
    virtual void draw() {
        std::cout << "I'm a triangle" << std::endl;
    }
};

class Point : public IShape {
    virtual void draw() {
        std::cout << "I'm a square" << std::endl;
    }
};

class Composite : public IShape {
public:
    virtual void draw() {
        for (SPtr& shape : components_) {
            shape->draw();
        }
    }

    void addComponent(const SPtr& sptr) {
        components_.push_back(sptr);
    }

    void removeComponent(const SPtr& sptr) {
        components_.remove(sptr);
    }

private:
    std::list <SPtr> components_;
};

int main() {
    std::cout << "Hello, World!" << std::endl;

    Composite comp;

    IShape::SPtr shape1(new Square);
    IShape::SPtr shape2(new Circle);
    IShape::SPtr shape3(new Triangle);
    IShape::SPtr shape4(new Point);

    IShape::SPtr comp2(new Composite);
    IShape::SPtr comp3(new Composite);

    comp2->addComponent(shape1);
    comp2->addComponent(shape2);
    comp2->addComponent(shape3);

    comp3->addComponent(shape4);

    comp.addComponent(comp2);
    comp.addComponent(comp3);

    comp.draw();

    return 0;
}
