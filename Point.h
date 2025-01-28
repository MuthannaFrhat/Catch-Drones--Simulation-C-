//
// Created by Admin on 12/24/2024.
//

#ifndef EX3_POINT_H
#define EX3_POINT_H
#include "math.h"
#include "iostream"
struct Point {
    double x, y;
    int dronesCount;

    Point(double x = 0, double y = 0, int dronesCount = 0)
            : x(x), y(y), dronesCount(dronesCount) {}

    double distanceTo(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }

    // Prefix ++: Increment dronesCount
    Point& operator++() {
        ++dronesCount;
        return *this;
    }
    Point(const Point& oth){
        x=oth.x;
        y=oth.y;
        dronesCount=oth.dronesCount;
    }
    ~Point()
    {

    }
    Point& operator=(const Point& oth)
    {
        x=oth.x;
        y=oth.y;
        dronesCount=oth.dronesCount;
        return *this;
    }
    Point (Point&& oth)
    {
        x=oth.x;
        y=oth.y;
        dronesCount=oth.dronesCount;
    }
    Point& operator=(const Point&& oth)
    {
        x=oth.x;
        y=oth.y;
        dronesCount=oth.dronesCount;
        return *this;
    }
    // Postfix ++: Increment dronesCount (return original state)
    Point operator++(int) {
        Point temp = *this;
        ++(*this);
        return temp;
    }

    // Prefix --: Decrement dronesCount (ensure it doesn't go below 0)
    Point& operator--() {
        if (dronesCount > 0) {
            --dronesCount;
        } else {
             std::cerr<<"Drones count cannot be negative";
        }
        return *this;
    }

    // Postfix --: Decrement dronesCount (return original state, ensure it doesn't go below 0)
    Point operator--(int) {
        Point temp = *this;
        --(*this); // This will throw an exception if dronesCount < 0
        return temp;
    }
};



#endif //EX3_POINT_H
