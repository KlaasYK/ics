#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <QVector>
#include "car.h"

// Amount of cars able to queue in lane
#define LANE_LENGTH 8

class Intersection
{
public:
    Intersection();
    QVector<Car> getCars();
    void doSimulationStep();

    // Check wheter a car can enter the lane
    bool canQueue(int sourceLaneIndex,int destinationLaneIndex);
    void queueCar(Car* car, int sourceLaneIndex, int destinationLaneIndex);

    int laneIndices[8];
    // Index of the next lane (or -1 for end)
    int destinationLaneIndices[8];
    int sourceLaneIndices[8][3];
    Intersection *connectedIntersections[4];

    // Car indices, use -1 for empty cell
    int carsIndicesLane[8][LANE_LENGTH];
    Car* carsInLane[8][LANE_LENGTH];

};

#endif // INTERSECTION_H
