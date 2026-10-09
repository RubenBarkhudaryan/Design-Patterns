#ifndef	FACTORY_HPP

# define FACTORY_HPP

# include <memory>

# include "Product.hpp"

/*Base Abstract class*/
class	ShapeCreator
{
	private:
		virtual std::unique_ptr<Shape>	createShape() const = 0;

	public:
		virtual ~ShapeCreator() = default;
		void	render() const;
};


/*Circle factory declaration*/
class	CircleCreator : public ShapeCreator
{
	private:
		std::unique_ptr<Shape>	createShape() const override;
};


/*Triangle factory declaration*/
class	TriangleCreator : public ShapeCreator
{
	private:
		std::unique_ptr<Shape>	createShape() const override;
};


/*Square factory declaration*/
class	SquareCreator : public ShapeCreator
{
	private:
		std::unique_ptr<Shape>	createShape() const override;
};

#endif //FACTORY_HPP