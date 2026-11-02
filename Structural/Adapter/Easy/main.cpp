#include <iostream>
#include <iomanip>
#include <string>

#include "TemperatureSensor.hpp"

/* A native sensor that already speaks Celsius: no adapter needed. */
class	CelsiusSensor : public ITemperatureSensor
{
	private:
		double	celsius;

	public:
		explicit CelsiusSensor(double celsius) : celsius(celsius) {}
		double	getCelsius() const override { return celsius; }
};

/* The client: knows only the target interface, nothing about Fahrenheit. */
void	printTemperature(const std::string& name, const ITemperatureSensor& sensor)
{
	std::cout << std::left << std::setw(28) << name
				<< std::right << std::setw(8) << sensor.getCelsius() << " C" << std::endl;
}

int	main()
{
	std::cout << std::fixed << std::setprecision(2);

	std::cout << "=== 1. Native Celsius sensor and adapted Fahrenheit sensor, same client ===" << std::endl;
	CelsiusSensor			native(21.5);
	FahrenheitSensor		adaptee;
	FahrenheitSensorAdapter	adapter(adaptee);

	adaptee.setF(70.7f);

	printTemperature("Native Celsius sensor", native);
	printTemperature("Fahrenheit sensor (adapted)", adapter);

	std::cout << std::endl << "=== 2. Known conversion values ===" << std::endl;

	struct	Reading
	{
		const char*	label;
		float		fahrenheit;
	};

	const Reading	readings[] = {
		{"32 F (freezing point)", 32.0f},
		{"212 F (boiling point)", 212.0f},
		{"-40 F (scales meet)", -40.0f},
		{"98.6 F (body temperature)", 98.6f}
	};

	for (const Reading& r : readings)
	{
		adaptee.setF(r.fahrenheit);
		printTemperature(r.label, adapter);
	}

	std::cout << std::endl << "=== 3. The adapter reads the adaptee live ===" << std::endl;
	adaptee.setF(32.0f);
	printTemperature("Before change (32 F)", adapter);
	adaptee.setF(212.0f);
	printTemperature("After change (212 F)", adapter);

	std::cout << std::endl << "=== 4. Both sensor kinds through one interface ===" << std::endl;
	const ITemperatureSensor*	sensors[] = {&native, &adapter};
	double						sum = 0.0;

	for (const ITemperatureSensor* sensor : sensors)
		sum += sensor->getCelsius();
	std::cout << "Average of both sensors: " << sum / 2 << " C" << std::endl;

	return (0);
}
