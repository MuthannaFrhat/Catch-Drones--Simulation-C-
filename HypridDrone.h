#ifndef HYBRIDDRONE_H
#define HYBRIDDRONE_H

#include "SingleRotor.h"
#include "MultiRotor.h"
#include "FixedWings.h"

class HybridDrone : public SingleRotor, public MultiRotor, public FixedWings {
public:
    HybridDrone(int id,double px, double py, double vx, double vy)
            : Drone(id,px, py, vx, vy), SingleRotor(id,px, py, vx, vy),
              MultiRotor(id,px, py, vx, vy), FixedWings(id,px, py, vx, vy) {}

    void updateVelocity(const Point& globalBest, const Point& goal) override ;

    const char* getType() const override {
        return "H";
    }

    Drone* clone() const override {
        return new HybridDrone(*this);
    }
};


#endif // HYBRIDDRONE_H
