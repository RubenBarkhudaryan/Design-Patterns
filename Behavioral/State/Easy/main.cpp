#include "State.hpp"

int	main()
{
	TrafficLightContext	trafficLightContext;

	while (true)
	{
		trafficLightContext.next();
		trafficLightContext.pressPedestrianButton();
	}

	return (0);
}