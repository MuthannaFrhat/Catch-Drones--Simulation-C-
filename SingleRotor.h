
#ifndef EX3_SINGLEROTOR_H
#define EX3_SINGLEROTOR_H
#include "Drone.h"

class SingleRotor : virtual public Drone {
public:
    SingleRotor(int id,double px, double py, double vx, double vy) : Drone(id,px, py, vx, vy) {}
    void updateVelocity(const Point& globalBest, const Point& goal) override;
    const char * getType() const override { return "S"; }


    Drone* clone() const override {
        return new SingleRotor(*this);  // Custom clone for this derived class
    }


};


#endif //EX3_SINGLEROTOR_H
