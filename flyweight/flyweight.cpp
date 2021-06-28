#include <iostream>
#include <string>

class Icon {
public:
	Icon(const char *fileName) {
		strcpy_s(_name, fileName);
		
		if (!strcmp(fileName, "go")) {
			_width = 20;
			_height = 20;
		}
		
		if (!strcmp(fileName, "stop")) {
			_width = 40;
			_height = 40;
		}
		
		if (!strcmp(fileName, "select")) {
			_width = 60;
			_height = 60;
		}
		
		if (!strcmp(fileName, "undo")) {
			_width = 30;
			_height = 30;
		}

		if (!strcmp(fileName, "redo")) {
			_width = 10;
			_height = 10;
		}
	}
	
	const char *getName() const {
		return _name;
	}
	
	void draw(int x, int y) const {
		std::cout << "   drawing " << _name << ": upper left (" << x << "," << y << ") - lower right (" << x + _width << "," << y + _height << ")" << std::endl;
	}
	
private:
	char _name[20];
	int _width;
	int _height;
};

class FlyweightFactory {
public:
	static Icon *getIcon(const char *name) {
		for (int i = 0; i < _numIcons; i++)
			if (!strcmp(name, _icons[i]->getName()))
				return _icons[i];
		_icons[_numIcons] = new Icon(name);
		return _icons[_numIcons++];
	}
	
	static void reportTheIcons() {
		std::cout << "Active Flyweights: ";
		for (int i = 0; i < _numIcons; i++)
			std::cout << _icons[i]->getName() << " ";
		std::cout << std::endl;
	}
private:
	enum {
		MAX_ICONS = 5
	};
	
	static int _numIcons;
	static Icon *_icons[MAX_ICONS];
};

int FlyweightFactory::_numIcons = 0;
Icon *FlyweightFactory::_icons[];

class DialogBox {
public:
	DialogBox(int x, int y, int incr) : _iconsOriginX(x), _iconsOriginY(y), _iconsXIncrement(incr) {}
	virtual ~DialogBox() = default;
	virtual void draw() = 0;
protected:
	Icon* _icons[3] {};
	int _iconsOriginX;
	int _iconsOriginY;
	int _iconsXIncrement;
};

class FileSelection : public DialogBox {
public:
	FileSelection(Icon *first, Icon *second, Icon *third) : DialogBox(100, 100, 100) {
		_icons[0] = first;
		_icons[1] = second;
		_icons[2] = third;
	}
	
	void draw() override {
		std::cout << "drawing FileSelection:" << std::endl;
		for (int i = 0; i < 3; i++)
			_icons[i]->draw(_iconsOriginX +
			(i *_iconsXIncrement), _iconsOriginY);
	}
};

class CommitTransaction : public DialogBox {
public:
	CommitTransaction(Icon *first, Icon *second, Icon *third) : DialogBox(150, 150, 150) {
		_icons[0] = first;
		_icons[1] = second;
		_icons[2] = third;
	}
	
	void draw() override {
		std::cout << "drawing CommitTransaction:" << std::endl;
		for (int i = 0; i < 3; i++)
			_icons[i]->draw(_iconsOriginX +
			(i *_iconsXIncrement), _iconsOriginY);
	}
};

class RedoMaking : public DialogBox {
public:
	RedoMaking(Icon *first, Icon *second, Icon *third) : DialogBox(150, 150, 150) {
		_icons[0] = first;
		_icons[1] = second;
		_icons[2] = third;
	}

	void draw() override {
		std::cout << "drawing RedoMaking:" << std::endl;
		for (int i = 0; i < 3; i++)
			_icons[i]->draw(_iconsOriginX +
			(i *_iconsXIncrement), _iconsOriginY);
	}
};

int main() {
	DialogBox *dialogs[3];
	
	dialogs[0] = new FileSelection(FlyweightFactory::getIcon("go"),FlyweightFactory::getIcon("stop"),FlyweightFactory::getIcon("select"));

	dialogs[1] = new CommitTransaction(FlyweightFactory::getIcon("select"),FlyweightFactory::getIcon("stop"),FlyweightFactory::getIcon("undo"));
	
	dialogs[2] = new RedoMaking(FlyweightFactory::getIcon("stop"), FlyweightFactory::getIcon("select"), FlyweightFactory::getIcon("redo"));

	for (auto& dialog : dialogs)
		dialog->draw();

	FlyweightFactory::reportTheIcons();

	system("pause");
}
