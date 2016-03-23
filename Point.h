// Joseph Gunderson & Alexandra Klimenko
// Homework 5
// Completed 10.Mar.2016


#ifndef POINT_H
#define	POINT_H

#include <iostream>


class Point 
{
private:
	double x;
	double y;

public:
	Point();
	Point(double a, double b);
	double getX() const;
	double getY() const;
	void setX(double d);
	void setY(double d);
	bool operator==(const Point& right) const;
	bool operator!=(const Point& right) const;

	
};

#endif
