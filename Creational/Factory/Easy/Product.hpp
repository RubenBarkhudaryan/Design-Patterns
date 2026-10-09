#ifndef	PRODUCT_HPP

# define PRODUCT_HPP

/*Base Interface*/
class	Shape
{
	public:
		virtual ~Shape() = default;
		virtual void	draw() const = 0;
};

class	Circle : public Shape
{
	public:
		~Circle() override = default;
		void	draw() const override;
};

class	Triangle : public Shape
{
	public:
		~Triangle() override = default;
		void	draw() const override;
};

class	Square : public Shape
{
	public:
		~Square() override = default;
		void	draw() const override;
};

#endif //PRODUCT_HPP