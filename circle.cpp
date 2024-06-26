#include "circle.hpp"
#include <iostream>
#include <numbers>
using namespace std;

Circle::Circle(Point center, string name, int radius)
	:Shape{center, name}, radius(radius)
{
}

double Circle::area() const
{
	return numbers::pi * radius * radius;
}

void Circle::draw(ostream& out) const
{
	for (int y = -radius; y <= radius; y += 2)
	{
		for (int x = -radius; x <= radius; ++x)
		{
			out << (x * x + y * y <= radius * radius ? '*' : ' ');
		}
		out << '\n';
	}
}

Circle* Circle::clone() const
{
	return new Circle(*this);
}
