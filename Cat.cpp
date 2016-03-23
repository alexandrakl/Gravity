// Joseph Gunderson & Alexandra Klimenko
// Homework 5
// Completed 10.Mar.2016


#include "Cat.h"


Cat::Cat()
	: position(CAT_WIDTH,CAT_HEIGHT), velocity()
{
}


// return position of cat
Point Cat::getPos() const
{
	return position;
}

// set position of cat
void Cat::setPos(double x, double y)
{
	position.setX(x);
	position.setY(y);
}


// changes position of cat based on it's velocity
void Cat::shiftPos(Point v, double dt)
{
	position.setX( (position.getX() + (v.getX()*dt)) );
	position.setY( (position.getY() + (v.getY()*dt)) );
}


// return velocity of cat
Point Cat::getVelocity() const
{
	return velocity;
}

// changes velocity in x direction and velocity in y direction of cat
void Cat::setVelocity(Point v)
{
	velocity.setX(v.getX());
	velocity.setY(v.getY());
}

// changes velocity of cat and returns Point object
Point Cat::setVelocity(double x, double y)
{

	velocity.setX(x);
	velocity.setY(y);
	
	return this->getVelocity();
}


