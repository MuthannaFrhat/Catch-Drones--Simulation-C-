#include "Simulation.h"
#include "SingleRotor.h"
#include "MultiRotor.h"
#include "FixedWings.h"
#include "HypridDrone.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <utility>
#include "BinarySearchTree.h"



struct Area {
    double minX, minY, maxX, maxY;
} area;



Simulation::Simulation(string dronesFile, string simulationFile, string outputFile)
        : outputFileName(outputFile) {
    std::ifstream simFile(simulationFile);
    std::ifstream drnFile(dronesFile);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    simFile >> area.minX >> area.minY >> area.maxX >> area.maxY;
    simFile >> goal.x >> goal.y;
    simFile >> maxIterations;

    int droneCount;
    drnFile >> droneCount;

    drones = new BinarySearchTree<Drone>();

    char type;
    double px, py, vx, vy;


    for (int i = 0; i < droneCount; ++i) {
        drnFile  >> type >> px >> py >> vx >> vy;

        Drone* drone = nullptr;
        switch (type) {
            case 'S': drone = new SingleRotor(i, px, py, vx, vy); break;
            case 'M': drone = new MultiRotor(i, px, py, vx, vy); break;
            case 'W': drone = new FixedWings(i, px, py, vx, vy); break;
            case 'H': drone = new HybridDrone(i, px, py, vx, vy); break;
        }

        if (drone) {
            drones->insert(drone);
        }
    }
}

Simulation::~Simulation() {
    delete drones;
}

void Simulation::run(string outputFile) {
    std::ofstream out(outputFile);
    if (!out.is_open()) {
        std::cerr << "Error; invalid input" << std::endl;
        std::exit(1);
    }

    Point globalBest;
    if (drones)
    {
        globalBest = drones->findMin()->getPosition();
    }
    else {
        globalBest = {0, 0};  // In case the drones are not available
    }

    double globalBestDistance = globalBest.distanceTo(goal);

    bool goalReached = false;
    int t = 0;

    if (maxIterations == 0) {
        out << t << std::endl;
        drones->inOrderTraversalAndPrint(out);
        return;
    }

    while (t < maxIterations) {
        for (int i = 0; i < drones->size(); ++i) {
            Drone* drone = drones->findMin();
            drone->checkPersonalBest(goal);
            double distance = drone->getDistanceToGoal(goal);
            if (distance < globalBestDistance) {
                globalBest = drone->getPosition();
                globalBestDistance = distance;
            }

            if (drone->getPosition().x >= goal.x && drone->getPosition().y >= goal.y) {
                goalReached = true;
                break;
            }
        }

        if (goalReached) {
            out << t << std::endl;
            drones->inOrderTraversalAndPrint(out);
            break;
        }

        for (int i = 0; i < drones->size(); ++i) {
            Drone* drone = drones->search(i);

            drone->updateVelocity(globalBest, goal);
            drone->updatePosition();

            if (drone->getPosition().x < area.minX) drone->UpdateX(area.minX);
            if (drone->getPosition().x > area.maxX) drone->UpdateX(area.maxX);
            if (drone->getPosition().y < area.minY) drone->UpdateY(area.minY);
            if (drone->getPosition().y > area.maxY) drone->UpdateY(area.maxY);
        }

        ++t;
    }

    if (!goalReached) {
        out << t << std::endl;
        drones->inOrderTraversalAndPrint(out);
    }
}




// Copy Constructor
Simulation::Simulation(const Simulation& oth)
        : goal(oth.goal), maxIterations(oth.maxIterations), drones(nullptr) {
    if (oth.drones) {
        drones = new BinarySearchTree<Drone>(*oth.drones);
    }
}

// Move Constructor
Simulation::Simulation(Simulation&& oth)
        : goal(std::move(oth.goal)), maxIterations(oth.maxIterations), drones(oth.drones) {
    oth.drones = nullptr;
}

// Copy Assignment Operator
Simulation& Simulation::operator=(Simulation& oth) {
    if (this != &oth) {
        goal = oth.goal;
        maxIterations = oth.maxIterations;
        delete drones;
        drones = new BinarySearchTree<Drone>(*oth.drones);
    }
    return *this;
}

// Move Assignment Operator
Simulation& Simulation::operator=(Simulation&& oth) {
    if (this != &oth) {
        goal = std::move(oth.goal);
        maxIterations = oth.maxIterations;
        delete drones;
        drones = oth.drones;
        oth.drones = nullptr;
    }
    return *this;
}
