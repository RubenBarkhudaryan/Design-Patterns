#ifndef	STATE_HPP

# define STATE_HPP

# include <memory>

class	TrafficLightContext;

class	TrafficLightState
{
	public:
		virtual ~TrafficLightState(){}

		virtual void	handle(TrafficLightContext& ctx) = 0;
		virtual void	pressPedestrianButton(TrafficLightContext&) {}
};

class	RedLightState : public TrafficLightState
{
	private:
		int	light_time;

	public:
		explicit RedLightState(int time);
		~RedLightState() override {}

		void	handle(TrafficLightContext& ctx) override;
		void	pressPedestrianButton(TrafficLightContext&) override;
};

class	GreenLightState : public TrafficLightState
{
	private:
		int		light_time;
		bool	shortened;

	public:
		explicit GreenLightState(int time);
		~GreenLightState() override {}

		void	handle(TrafficLightContext& ctx) override;
		void	pressPedestrianButton(TrafficLightContext&) override;
};

class	YellowLightState : public TrafficLightState
{
	private:
		int	light_time;

	public:
		explicit YellowLightState(int time);
		~YellowLightState() override {}

		void	handle(TrafficLightContext& ctx) override;
		void	pressPedestrianButton(TrafficLightContext&) override;
};

class	TrafficLightContext
{
	private:
		std::unique_ptr<TrafficLightState>	state;

	public:
		TrafficLightContext();
		~TrafficLightContext() {}

		void	next();
		void	pressPedestrianButton();
		void	updateState(std::unique_ptr<TrafficLightState> new_state);
};

#endif //STATE_HPP