#include "Subject.hpp"

#include <algorithm>
#include "Observer.hpp"

WeatherStation::WeatherStation() :
	temperature(0.0),
	humidity(0.0),
	pressure(0.0)
{}

void	WeatherStation::setMeasurements(double new_temperature, double new_humidity, double new_pressure)
{
	temperature = new_temperature;
	humidity = new_humidity;
	pressure = new_pressure;

	notify();
}

void	WeatherStation::notify()
{
	for (IObserver *observer : observers)
		observer->update({temperature, humidity, pressure});
}

void	WeatherStation::attach(IObserver *observer)
{
	if (observer == nullptr)
		return ;

	observers.push_back(observer);
}

void	WeatherStation::detach(IObserver *observer)
{
	observers.erase(std::remove(
					observers.begin(),
					observers.end(),
					observer), observers.end());
}
