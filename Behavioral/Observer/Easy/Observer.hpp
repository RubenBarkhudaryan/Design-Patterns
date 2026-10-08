#ifndef	OBSERVER_HPP

# define OBSERVER_HPP

#include "Subject.hpp"

class	IObserver
{
	public:
		virtual void	update(const WeatherData& data) = 0;
		virtual ~IObserver() {};
};

class	CurrentConditionsDisplay : public IObserver
{
	private:
		double	temperature;
		double	humidity;
		double	pressure;

	public:
		CurrentConditionsDisplay();
		~CurrentConditionsDisplay() override {}
		void	update(const WeatherData& data) override;
		void	display() const;
};

class	StatisticsDisplay : public IObserver
{
	private:

		double	max;
		double	min;
		double	sum;

		int		count_of_updates;

	public:
		StatisticsDisplay();
		~StatisticsDisplay() override {}
		void	update(const WeatherData& data) override;
		void	display() const;
};

class	ForecastDisplay : public IObserver
{
	private:
		bool	has_previous;
		double	last_pressure;
		double	delta;

	public:
		ForecastDisplay();
		~ForecastDisplay() override {}
		void	update(const WeatherData& data) override;
		void	display() const;
};

#endif //OBSERVER_HPP