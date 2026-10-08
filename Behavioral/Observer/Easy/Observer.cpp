#include "Observer.hpp"

#include <iostream>
#include <cfloat>

#include "Subject.hpp"

CurrentConditionsDisplay::CurrentConditionsDisplay() :
	temperature(0.0),
	humidity(0.0),
	pressure(0.0)
{}

void	CurrentConditionsDisplay::update(const WeatherData& data)
{
	this->temperature = data.temperature;
	this->humidity = data.humidity;
	this->pressure = data.pressure;

	display();
}

void	CurrentConditionsDisplay::display() const
{
	std::cout << temperature << "°C, "
				<< humidity << "% humidity, "
				<< pressure << "hPa pressure" << std::endl;
}


StatisticsDisplay::StatisticsDisplay() :
	max(-DBL_MAX),
	min(DBL_MAX),
	sum(0.0),
	count_of_updates(0)
{}

void	StatisticsDisplay::update(const WeatherData& data)
{
	double	temp = data.temperature;

	if (max < temp)
		max = temp;

	if (temp < min)
		min = temp;

	sum += temp;
	++count_of_updates;

	display();
}

void	StatisticsDisplay::display() const
{
	std::cout << "Statistics for today:" << std::endl;

	std::cout << "Max temperature: " << max << std::endl;
	std::cout << "Min temperature: " << min << std::endl;
	std::cout << "Average temperature: " << sum / count_of_updates << std::endl;
}


ForecastDisplay::ForecastDisplay() :
	has_previous(false),
	last_pressure(0.0),
	delta(0.0)
{}

void	ForecastDisplay::update(const WeatherData& data)
{
	if (has_previous)
	{
		delta = data.pressure - last_pressure;
		display();
	}
	else
		has_previous = true;
	last_pressure = data.pressure;
}

void	ForecastDisplay::display() const
{
	if (delta > 0.2)
		std::cout << "Forecast: Pressure is RISING 📈 (Weather clearing up/getting colder)" << std::endl;
	else if (delta < -0.2)
		std::cout << "Forecast: Pressure is DROPPING 📉 (Warmth/precipitation approaching)" << std::endl;
	else
		std::cout << "Forecast: Pressure STABLE ➡️" << std::endl;
}