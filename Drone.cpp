#include "Drone.h"
#include <cmath>

Drone::Drone(int id ,double px, double py, double vx, double vy)
        : id(id),position(px, py), velocity(vx, vy), personalBest(px, py) {
    personalBestDistance = getDistanceToGoal(personalBest);
}

Drone::Drone(const Drone& oth)
        : id(oth.id),position(oth.position), velocity(oth.velocity),
          personalBest(oth.personalBest), personalBestDistance(oth.personalBestDistance) {}

Drone& Drone::operator=(const Drone& oth) {
    if (this != &oth) {
        id=oth.id;
        position = oth.position;
        velocity = oth.velocity;
        personalBest = oth.personalBest;
        personalBestDistance = oth.personalBestDistance;
    }
    return *this;
}



void Drone::updatePosition() {
    position.x += velocity.x;
    position.y += velocity.y;
}

double Drone::getDistanceToGoal(const Point& goal) const {
    double dx = goal.x - position.x;
    double dy = goal.y - position.y;
    return std::sqrt(dx * dx + dy * dy);
}



void Drone::checkPersonalBest(const Point& goal) {
    double distance = getDistanceToGoal(goal);
    if (distance < personalBestDistance) {
        personalBest = position;
        personalBestDistance = distance;
    }
}
