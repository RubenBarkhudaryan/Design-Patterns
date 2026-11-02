#include "TemperatureSensor.hpp"

float	FahrenheitSensor::readF() const
{
	return fahrenheit;
}

void	FahrenheitSensor::setF(float fahrenheit)
{
	this->fahrenheit = fahrenheit;
}

FahrenheitSensorAdapter::FahrenheitSensorAdapter(const FahrenheitSensor& sensor)
	: sensor(sensor)
{
}


double	FahrenheitSensorAdapter::getCelsius() const
{
	return ((sensor.readF() - 32.0) * 5.0 / 9.0);
}