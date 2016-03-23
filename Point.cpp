// Joseph Gunderson & Alexandra Klimenko
// Homework 5
// Completed 10.Mar.2016


#include "Point.h"

// default constructor that sets point at origin
Point::Point()
	: x(0), y(0)
{
}

// constructor that sets point at a specific location
Point::Point(double a, double b)
	: x(a), y(b)
{
}


// return value of x
double Point::getX() const
{
	return x;
}

// change value of x
void Point::setX(double d)
{
	x = d;
}

// return value of y
double Point::getY() const
{
	return y;
}

// change value of y
void Point::setY(double d)
{
	y = d;
}



// compare two Points
bool Point::operator==(const Point& right) const
{
	return (this->getX() ==  right.getX() && this->getY() ==  right.getY() ) ? true : false;
}

bool Point::operator!=(const Point& right) const
{
	return !(*this == right);
}







