
#ifndef EX3_MULTIROTOR_H
#define EX3_MULTIROTOR_H

#include "Drone.h"
class MultiRotor :virtual public Drone {
public:
    MultiRotor(int id,double px, double py, double vx, double vy) : Drone(id,px, py, vx, vy) {}
    void updateVelocity(const Point& globalBest, const Point& goal) override;
    const char* getType() const override { return "M"; }
    Drone* clone() const override {
        return new MultiRotor(*this);  // Custom clone for this derived class
    }

};


#endif //EX3_MULTIROTOR_H
