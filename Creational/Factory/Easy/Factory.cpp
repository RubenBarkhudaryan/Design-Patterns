#include "Factory.hpp"

void	ShapeCreator::render() const
{
	std::unique_ptr<Shape>	shape = createShape();
	shape->draw();
}

std::unique_ptr<Shape>	CircleCreator::createShape() const
{
	return std::make_unique<Circle>();
}

std::unique_ptr<Shape>	TriangleCreator::createShape() const
{
	return std::make_unique<Triangle>();
}

std::unique_ptr<Shape>	SquareCreator::createShape() const
{
	return std::make_unique<Square>();
}
