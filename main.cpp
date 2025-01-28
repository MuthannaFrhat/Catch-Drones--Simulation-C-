#include "Simulation.h"
#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

//I read the files from argv[] and check if there is errors and then called simulation
int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Error; invalid input" << endl;
        return 1;
    }

    ifstream simFile(argv[1]);
    ifstream drnFile(argv[2]);

    if (!simFile.is_open() || !drnFile.is_open()) {
        cerr << "Error; invalid input" << endl;
        return 1;
    }


    double minX, minY, maxX, maxY;
    if (!(simFile >> minX >> minY >> maxX >> maxY) || minX >= maxX || minY >= maxY) {
        cerr << "Error; invalid input" << endl;
        return 1;
    }


    double goalX, goalY;
    if (!(simFile >> goalX >> goalY)) {
        cerr << "Error; invalid input" << endl;
        return 1;
    }


    int numSteps;
    if (!(simFile >> numSteps) || numSteps < 0) {
        cerr << "Error; invalid input" << endl;
        return 1;
    }


    int droneCount;
    if (!(drnFile >> droneCount) || droneCount <= 0) {
        cerr << "Error; invalid input" << endl;
        return 1;
    }


    char type;
    double px, py, vx, vy;
    for (int i = 0; i < droneCount; ++i) {
        drnFile >> type >> px >> py >> vx >> vy;
        if (drnFile.fail() || !(type == 'S' || type == 'M' || type == 'W' || type == 'H')) {
            cerr << "Error; invalid input" << endl;
            return 1;
        }
    }

    simFile.close();
    drnFile.close();

    Simulation sim(argv[2], argv[1], argv[3]);
    sim.run(argv[3]);

    return 0;
}



