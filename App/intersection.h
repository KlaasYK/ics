#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <QVector>

#include "car.h"
#include "stepstats.h"

// Amount of cars able to queue in lane
#define LANE_LENGTH 8

#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3

enum class Light {GREEN, RED};
enum class LightType {SIMPLE, TWOSIDED, SIMPLELOOP, TWOSIDEDLOOP};

class Intersection
{
public:
    Intersection();
    QVector<Car*> getCars();
    void doSimulationStep(StepStats &stat);

    void changeLights(int timestamp, int stepsGreen, LightType type);

    bool queueCar(Car* car, int sourceIntersection);
    void clearAllLanes();

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
    void simpleLoop(int timestamp, int stepsGreen);
    void twoSidedLoop(int timestamp, int stepsGreen);

    int loopStamp;
    int loopLane;

};

#endif // INTERSECTION_H
