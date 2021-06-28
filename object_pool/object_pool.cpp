#include <string>
#include <iostream>
#include <list>

class Resource {
	int value;
public:
	Resource() {
		value = 0;
	}
	void reset() {
		value = 0;
	}
	int getValue() {
		return value;
	}
	void setValue(int number) {
		value = number;
	}
};

class ObjectPool {
private:
	std::list<Resource*> resources;

	static ObjectPool* instance;
	ObjectPool() {}
public:
	static ObjectPool* getInstance() {
		if (instance == 0) {
			instance = new ObjectPool;
		}
		return instance;
	}

	Resource* getResource() {
		if (resources.empty()) {
			std::cout << "Creating new." << std::endl;
			return new Resource;
		} else {
			std::cout << "Reusing existing." << std::endl;
			Resource* resource = resources.front();
			resources.pop_front();
			return resource;
		}
	}

	void returnResource(Resource* object)
	{
		object->reset();
		resources.push_back(object);
	}
};

ObjectPool* ObjectPool::instance = 0;

int main() {
	ObjectPool* pool = ObjectPool::getInstance();
	
	Resource* one;
	Resource* two;
	
	/* Resources will be created. */
	
	one = pool->getResource();
	one->setValue(10);
	std::cout << "one = " << one->getValue() << " [" << one << "]" << std::endl;
	two = pool->getResource();
	two->setValue(20);
	std::cout << "two = " << two->getValue() << " [" << two << "]" << std::endl;
	pool->returnResource(one);
	pool->returnResource(two);
	
	/* Resources will be reused.
	 * Notice that the value of both resources were reset back to zero. */

	one = pool->getResource();
	std::cout << "one = " << one->getValue() << " [" << one << "]" << std::endl;
	two = pool->getResource();
	std::cout << "two = " << two->getValue() << " [" << two << "]" << std::endl;

	system("pause");
	return 0;
}
