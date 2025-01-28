#ifndef SIMULATION_H
#define SIMULATION_H

#include "Drone.h"
#include "Point.h"
#include "BinarySearchTree.h"

using namespace std;
class Simulation {
private:
    Point goal;
    int maxIterations;
    BinarySearchTree<Drone>* drones;

    basic_string<char> outputFileName;


public:
    Simulation(string dronesFile,string imulationFile, string outputFile);
    ~Simulation();
    Simulation(const Simulation& oth);
    Simulation(Simulation && oth);
    Simulation& operator=(Simulation& oth);
    Simulation& operator=(Simulation&& oth);
    std::string formatDouble(double value) const;
    void run(string outputFile);
    void printResults() const;
};

#endif // SIMULATION_H
