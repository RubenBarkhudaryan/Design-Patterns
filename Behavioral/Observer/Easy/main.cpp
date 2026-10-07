#include "Observer.hpp"
#include "Subject.hpp"

int	main()
{
	WeatherStation	station;

	CurrentConditionsDisplay	current;
	StatisticsDisplay			stats;
	ForecastDisplay				forecast;

	station.attach(&current);
	station.attach(&stats);
	station.attach(&forecast);

	station.setMeasurements(25.0f, 60.0f, 1013.0f);

	station.detach(&forecast);
	station.setMeasurements(27.0f, 55.0f, 1010.0f);

	station.attach(&forecast);
	station.setMeasurements(22.0f, 70.0f, 1015.0f);
}