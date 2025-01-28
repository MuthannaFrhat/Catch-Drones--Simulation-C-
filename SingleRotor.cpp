#include "SingleRotor.h"
#include <cstdlib>
//update speed for this type of drone
void SingleRotor::updateVelocity(const Point& globalBest, const Point& goal) {
    double a = 0.01, b = -0.1, c = -0.25;
    double R1 = static_cast<double>(std::rand()) / RAND_MAX;
    double R2 = static_cast<double>(std::rand()) / RAND_MAX;

    velocity.x = a * velocity.x + b * R1 * (personalBest.x - position.x)
                 + c * R2 * (globalBest.x - position.x);
    velocity.y = a * velocity.y + b * R1 * (personalBest.y - position.y)
                 + c * R2 * (globalBest.y - position.y);
}
