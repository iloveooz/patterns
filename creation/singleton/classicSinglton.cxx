
	#include <iostream>
	
	class Singleton {
	private:
		static Singleton *p_instance;
		
		// конструкторы и операторы присваивания закрыты
		Singleton() {}
		Singleton(const Singleton&) {}
		Singleton& operator = (Singleton& );
	public:
		static Singleton * getInstance() {
			if (!p_instance) {
				p_instance = new Singleton();
			}
			return p_instance;
		}
	};
	
	int main() {
		
		// Singleton A;
		Singleton * Singleton::p_instance = 0;
				
		
		return 0;
	}
