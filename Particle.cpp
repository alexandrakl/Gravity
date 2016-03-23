// Joseph Gunderson & Alexandra Klimenko
// Homework 5
// Completed 10.Mar.2016


#include "Particle.h"
#include "Constants.h"
#include <cmath>


// constructor that takes in a position and mass 
Particle::Particle(Point p, double m)
	: position(p), mass(m), velocity(), radius( ((m/MAX_MASS)*10)+4), alive(true)
{
}



// return position of particle
Point Particle::getPos() const
{
	return position;
}

// set position of particle
void Particle::setPos(double x, double y)
{
	position.setX(x);
	position.setY(y);
}


// changes position of particle based on it's velocity
void Particle::shiftPos(Point v, double dt)
{
	position.setX( (position.getX() + (v.getX()*dt)) );
	position.setY( (position.getY() + (v.getY()*dt)) );
}

// return mass of particle
double Particle::getMass() const
{
	return mass;
}

// return velocity of particle
Point Particle::getVelocity() const
{
	return velocity;
}

// changes velocity in x direction and velocity in y direction of particle
void Particle::setVelocity(Point v)
{
	velocity.setX(v.getX());
	velocity.setY(v.getY());
}

// changes velocity of particle and returns Point object
Point Particle::setVelocity(double x, double y)
{

	velocity.setX(x);
	velocity.setY(y);
	
	return this->getVelocity();
}


// return radius of particle
double Particle::getRadius() const
{
	return radius;
}

// compare two particles
bool Particle::operator==(const Particle& right) const
{
	return ( (this->getPos()==right.getPos()) && (this->getMass() == right.getMass()) ) ? true : false;
}

bool Particle::operator!=(const Particle& right) const
{
	return !(*this == right);
}

bool Particle::isAlive() const
{
	return alive;
}

void Particle::kill()
{
	alive = false;
}










