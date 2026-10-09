#include "Product.hpp"

#include <cmath>
#include <iostream>

void	Circle::draw() const
{
	const int	radius = 5;
	const int	pixelAspect = 2;

	for (int y = -radius / pixelAspect; y <= radius / pixelAspect; y++)
	{
		for (int x = -radius; x <= radius; x++)
		{
			float	dist = std::sqrt(static_cast<float>(x * x + (y * pixelAspect) * (y * pixelAspect)));

			if (std::abs(dist - radius) < 0.5f)
				std::cout << "*";
			else
				std::cout << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


void	Triangle::draw() const
{
	int	height = 5;

	for (int i = 1; i <= height; i++)
	{
		for (int j = 0; j < height - i; j++)
			std::cout << " ";

		for (int k = 0; k < (2 * i - 1); k++)
			std::cout << "*";

		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void	Square::draw() const
{
	int	size = 5;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			std::cout << "* ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}