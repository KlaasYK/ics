#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <QVector>
#include <QVector2D>

#include "car.h"

// Amount of cars able to queue in lane
#define LANE_LENGTH 8

#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3

enum class Light {GREEN, RED};

class Intersection
{
public:
    Intersection();
    QVector<Car*> getCars();
    QVector2D doSimulationStep();

    void changeLights(int timestamp, int stepsGreen, int type);

    bool queueCar(Car* car, int sourceIntersection);
    void clearAllLanes();
    void setLights(QVector<Light> nLights);

    int intersectionIndex;
    Intersection *connectedIntersections[4];

    // Car indices, use -1 for empty cell
    int carsIndicesLane[8][LANE_LENGTH];
    Car* carsInLane[8][LANE_LENGTH];

    QVector<Light> lights;

private:
    int getLocalIntersectionIndex(int intersectionIndex, bool outside);
    void simple(int timestamp, int stepsGreen);
    void twoSided(int timestamp, int stepsGreen);
};

#endif // INTERSECTION_H
