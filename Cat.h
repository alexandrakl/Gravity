// Joseph Gunderson & Alexandra Klimenko
// Homework 5
// Completed 10.Mar.2016


#ifndef CAT_H
#define	CAT_H

#include "Point.h"
#include "Constants.h"

//The cat dimensions
const int CAT_WIDTH = 50;
const int CAT_HEIGHT = 50;


class Cat : public Point
{
    private:
    Point position;
    Point velocity;
    
    public:
    Cat();
    Point getPos() const;
    void setPos(double x, double y);
    void shiftPos(Point v, double dt);
    Point getVelocity() const;
    void setVelocity(Point v);
    Point setVelocity(double x, double y);


};

#endif
