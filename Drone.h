#ifndef DRONE_H
#define DRONE_H

#include "Point.h"
#include <iostream>
#include <string>

class Drone {
protected:
    int id;
    Point position;
    Point velocity;
    Point personalBest;
    double personalBestDistance;

public:
    Drone(int id ,double px, double py, double vx, double vy);
    Drone(const Drone& oth);
    Drone& operator=(const Drone& oth);
    virtual ~Drone()=default;
    virtual Drone* clone() const =0;
    virtual void updateVelocity(const Point& globalBest, const Point& goal) = 0;
    void updatePosition();
    double getDistanceToGoal(const Point& goal) const;

    virtual Point getPosition() const {
        return position;
    }
    void checkPersonalBest(const Point& goal);
    virtual const char* getType() const = 0;

    void UpdateX(double n)
    {
        position.x=n;
    }
    void UpdateY(double n)
    {
        position.y=n;
    }
    int getId() const {
        return id;
    }




};









#endif // DRONE_H
