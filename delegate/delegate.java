package test;

interface Graphics {
	void draw();
}

class Spot implements Graphics {
	public void draw() {
		System.out.println("Рисую пятно");
	}
}

class Line implements Graphics {
	public void draw() {
		System.out.println("Рисую линию");
	}
}

class Pentagon implements Graphics {
	public void draw() {
		System.out.println("Рисую пятиугольник");
	}
}

class Painter {
	private Graphics graph;
	public void setGraphics(Graphics g) {
		graph = g;
	}
	public void draw() {
		graph.draw();
	}
}

public class DelegateTest {
	public static void main(String[] args) {
		Painter painter = new Painter();
		
		painter.setGraphics(new Spot());
		painter.draw();
		
		painter.setGraphics(new Line());
		painter.draw();
		
		painter.setGraphics(new Pentagon());
		painter.draw();
	}
}
