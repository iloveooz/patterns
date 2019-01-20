	#include <iostream>

	// уже существующий класс, написанный кем-то
	class FahrenheitSensor {
	public:
		// получить показания температуры в гр. Фаренгейта
		float getFahrenheitTemp() {
			float t = 32.0;
			return t;
		}
	};

	class Sensor {
	public:
		virtual ~Sensor() {}
		virtual float getTemperature() = 0;
	};

	class Adapter : public Sensor {
	public:
		Adapter (FahrenheitSensor* p) : p_fsensor(p) {}
		~Adapter() {
			delete p_fsensor;
		}
		float getTemperature() {
			return (p_fsensor->getFahrenheitTemp() - 32.0) * 5.0 / 9.0;
		}
	private:
		FahrenheitSensor* p_fsensor;
	};

	int main() {
		Sensor* p = new Adapter(new FahrenheitSensor);
		std::cout << "по Цельсию = " << p->getTemperature() << '\n';	
		delete p;
		return 0;
	}
