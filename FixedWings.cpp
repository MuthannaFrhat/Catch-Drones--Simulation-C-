#include "FixedWings.h"
#include <cstdlib>
//update speed for this type of drone
void FixedWings::updateVelocity(const Point& globalBest, const Point& goal) {
    double a = 0.25, b = 1.0, c = 1.0;
    double R1 = static_cast<double>(std::rand()) / RAND_MAX;
    double R2 = static_cast<double>(std::rand()) / RAND_MAX;

    velocity.x = a * velocity.x + b * R1 * (personalBest.x - position.x)
                 + c * R2 * (globalBest.x - position.x);
    velocity.y = a * velocity.y + b * R1 * (personalBest.y - position.y)
                 + c * R2 * (globalBest.y - position.y);
}
