#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <QVector>
#include "car.h"

// Amount of cars able to queue in lane
#define LANE_LENGTH 8

#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3

class Intersection
{
public:
    Intersection();
    QVector<Car*> getCars();
    void doSimulationStep();

    // TODO: traffic ligths

    bool queueCar(Car* car, int sourceIntersection);
    void clearAllLanes();
    void setLights(QVector<int> nLights);

    int intersectionIndex;
    Intersection *connectedIntersections[4];

    // Car indices, use -1 for empty cell
    int carsIndicesLane[8][LANE_LENGTH];
    Car* carsInLane[8][LANE_LENGTH];

    QVector<int> lights;

private:
    int getLocalIntersectionIndex(int intersectionIndex, bool outside);
};

#endif // INTERSECTION_H
