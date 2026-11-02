#ifndef	TEMPERATURE_SENSOR_HPP

# define TEMPERATURE_SENSOR_HPP

class	FahrenheitSensor
{
	private:
		float	fahrenheit {32.0f};

	public:
		float	readF() const;
		void	setF(float fahrenheit);
};

class	ITemperatureSensor
{
	public:
		virtual ~ITemperatureSensor() {}
		virtual double	getCelsius() const = 0;
};

class	FahrenheitSensorAdapter : public ITemperatureSensor
{
	private:
		const FahrenheitSensor&	sensor;

	public:
		explicit FahrenheitSensorAdapter(const FahrenheitSensor& sensor);
		double	getCelsius() const override;
};

#endif //TEMPERATURE_SENSOR_HPP