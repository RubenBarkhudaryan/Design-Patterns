#include "Factory.hpp"
#include "Product.hpp"

#include <memory>

void	run(const ShapeCreator& creator)
{
	creator.render();
}

int	main()
{
	run(CircleCreator{});
	run(TriangleCreator{});
	run(SquareCreator{});

	return (0);
}
