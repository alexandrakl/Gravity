// Joseph Gunderson & Alexandra Klimenko
// Homework 5
// Completed 10.Mar.2016


#ifndef PARTICLE_H
#define	PARTICLE_H

#include <iostream>

#include "Constants.h"
#include "Point.h"


class Particle : public Point
{
private:
	Point position;
	double mass;
	Point velocity; // velocity in x and y direction
	double radius;
	bool alive;
	
public:
	Particle(Point p, double m);
	Point getPos() const;
	void setPos(double x, double y);
	void shiftPos(Point v, double dt);
	Point getVelocity() const;
	void setVelocity(Point v);
	Point setVelocity(double x, double y);
	double getRadius() const;
	double getMass() const;
	bool operator==(const Particle& right) const;
	bool operator!=(const Particle& right) const;
	bool isAlive() const;
	void kill();
	
	
	
};

#endif
