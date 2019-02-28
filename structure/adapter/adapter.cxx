	#include <iostream>

	// уже существующий класс, написанный кем-то
	class FahrenheitSensor {
	public:
		// получить показания температуры в гр. Фаренгейта
		float getFahrenheitTemperature() {
			float t = 32.0;
			return t;
		}
	protected:
		void adjustFahrenheit() {}
	};

	class KelvinSensor {
	public:
		// получаем показания температуры в градусах Кельвина
		double getKelvinTemperature() {
			double t = 300;
			return t;
		}
	protected:
		void adjustKelvin() {}
	};

	class Sensor {
	public:
		virtual ~Sensor() {}
		virtual float getTemperatureFromFahrenheit() = 0;
		virtual float getTemperatureFromKelvin() = 0;
		
		virtual void adjustFahrenheit() = 0;
		virtual void adjustKelvin() = 0;
	};

	class Adapter : public Sensor, private FahrenheitSensor, KelvinSensor {
	public:
		Adapter (FahrenheitSensor *p1, KelvinSensor *p2) : p_fsensor(p1), p_ksensor(p2) {}
		
		~Adapter() {
			delete p_fsensor;
			delete p_ksensor;
		}
		
		float getTemperatureFromFahrenheit() {
			return (p_fsensor->getFahrenheitTemperature() - 32.0) * 5.0 / 9.0;
		}

		float getTemperatureFromKelvin() {
			return (p_ksensor->getKelvinTemperature() - 273.15);
		}
		
		void adjustFahrenheit () {
			FahrenheitSensor::adjustFahrenheit();
		}

		void adjustKelvin () {
			KelvinSensor::adjustKelvin();
		}
		
	private:
		FahrenheitSensor* p_fsensor;
		KelvinSensor* p_ksensor;
	};

	int main() {
		Sensor* p = new Adapter(new FahrenheitSensor, new KelvinSensor);
		std::cout << "от Фаренгейта к Цельсию = " << p->getTemperatureFromFahrenheit() << '\n';	
		std::cout << "от Кельвина к Цельсию = " << p->getTemperatureFromKelvin() << '\n';	
		delete p;
		return 0;
	}
