
#ifndef EX3_FIXEDWINGS_H
#define EX3_FIXEDWINGS_H
#include "Drone.h"
class FixedWings : virtual public Drone {
public:
    FixedWings(int id,double px, double py, double vx, double vy) : Drone(id,px, py, vx, vy) {}
    void updateVelocity(const Point& globalBest, const Point& goal) override;
    const char* getType() const override { return "W"; }

    Drone* clone() const override {
        return new FixedWings(*this);  // Custom clone for this derived class
    }
};
#endif //EX3_FIXEDWINGS_H
