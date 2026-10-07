#ifndef	SUBJECT_HPP

# define SUBJECT_HPP

# include <vector>

class	IObserver;

class	ISubject
{
	public:
		virtual void	notify() = 0;
		virtual void	attach(IObserver *observer) = 0;
		virtual void	detach(IObserver *observer) = 0;
		virtual ~ISubject() {}
};

struct	WeatherData
{
	double	temperature;
	double	humidity;
	double	pressure;
};

class	WeatherStation : public ISubject
{
	double						temperature;
	double						humidity;
	double						pressure;
	std::vector<IObserver *>	observers;

	public:
		WeatherStation();
		~WeatherStation() override {}

		void	setMeasurements(double new_temperature, double new_humidity, double new_pressure);

		void	notify() override;
		void	attach(IObserver *observer) override;
		void	detach(IObserver *observer) override;
};

#endif //SUBJECT_HPP