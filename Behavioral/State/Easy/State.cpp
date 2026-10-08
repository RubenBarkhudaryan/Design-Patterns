#include "State.hpp"

#include <iostream>
#include <thread>
#include <chrono>

constexpr int RED_DURATION = 5;
constexpr int GREEN_DURATION = 10;
constexpr int YELLOW_DURATION = 5;

RedLightState::RedLightState(int time) :
	light_time(time)
{}

void	RedLightState::handle(TrafficLightContext& ctx)
{
	std::cout << "Red light on. Duration "
				<< light_time <<" sec" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(light_time));

	ctx.updateState(std::make_unique<GreenLightState>(GREEN_DURATION));
}

void	RedLightState::pressPedestrianButton(TrafficLightContext&)
{
	std::cout << "No effect on red light duration" << std::endl << std::endl;
}


GreenLightState::GreenLightState(int time) :
	light_time(time),
	shortened(false)
{}

void	GreenLightState::pressPedestrianButton(TrafficLightContext&)
{
	if (!shortened)
	{
		shortened = true;

		if (light_time - 5 > 0)
		{
			light_time -= 5;

			std::cout << "Green light duration shortened: "
						<< light_time + 5 << " -> "
						<< light_time << std::endl << std::endl;
		}
		else
			std::cout << "No effect on green light duration" << std::endl << std::endl;
	}
}

void	GreenLightState::handle(TrafficLightContext& ctx)
{
	std::cout << "Green light on. Duration "
				<< light_time <<" sec" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(light_time));

	ctx.updateState(std::make_unique<YellowLightState>(YELLOW_DURATION));
}


YellowLightState::YellowLightState(int time) :
	light_time(time)
{}

void	YellowLightState::handle(TrafficLightContext& ctx)
{
	std::cout << "Yellow light on. Duration "
				<< light_time <<" sec" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(light_time));

	ctx.updateState(std::make_unique<RedLightState>(RED_DURATION));
}

void	YellowLightState::pressPedestrianButton(TrafficLightContext&)
{
	std::cout << "No effect on yellow light duration" << std::endl << std::endl;
}


TrafficLightContext::TrafficLightContext() :
	state(std::make_unique<RedLightState>(RED_DURATION))
{}

void	TrafficLightContext::updateState(std::unique_ptr<TrafficLightState> new_state)
{
	if (!new_state)
		return ;

	state.swap(new_state);
}

void	TrafficLightContext::pressPedestrianButton()
{
	state->pressPedestrianButton(*this);
}

void	TrafficLightContext::next()
{
	state->handle(*this);
}
