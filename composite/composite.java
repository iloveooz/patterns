package test;

import java.util.ArrayList;
import java.util.List;

interface Shape {
	public void print();
}

class Square implements Shape {
	@Override
	public void print() {
		System.out.println("I'm Square");
	}	
}

class Circle implements Shape {
	@Override
	public void print() {
		System.out.println("I'm Circle");
	}
}

class Triangle implements Shape {
	@Override
	public void print() {
		System.out.println("I'm Triangle");
	}
}

class Point implements Shape {
	@Override
	public void print() {
		System.out.println("I'm Point");
	}
}

class Composite implements Shape {
	private List<Shape> components = new ArrayList<Shape>();
	@Override
	public void print() {
		for (Shape shape : components) {
			shape.print();
		}
	}
	
	public void addComponent(Shape c) {
		components.add(c);
	}
	
	public void removeComponent(Shape c) {
		components.remove(c);
	}
}

public class CompositeTest {

	public static void main(String[] args) {
	       //Initialize four ellipses
		Shape sh1 = new Square();
		Shape sh2 = new Circle();
		Shape sh3 = new Triangle();
		Shape sh4 = new Point();

        //Initialize three composite graphics
		Composite c1 = new Composite();
		Composite c2 = new Composite();
		Composite c3 = new Composite();

        //Composes the graphics
        c2.addComponent(sh1);
        c2.addComponent(sh2);
        c2.addComponent(sh3);

        c3.addComponent(sh4);

        c1.addComponent(c2);
        c1.addComponent(c3);

        //Prints the complete graphic (four times the string "Ellipse").
        c1.print();
	}
}
