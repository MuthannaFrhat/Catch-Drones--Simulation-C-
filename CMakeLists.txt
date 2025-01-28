cmake_minimum_required(VERSION 3.28)
project(ex3)

set(CMAKE_CXX_STANDARD 11)

add_executable(ex3 main.cpp
        Point.h
        Point.h
        Simulation.h
        Drone.cpp
        Simulation.cpp
        SingleRotor.h
        MultiRotor.h
        FixedWings.h
        HypridDrone.h
        SingleRotor.cpp
        MultiRotor.cpp
        FixedWings.cpp
        HypridDrone.cpp
        BinarySearchTree.h
)
