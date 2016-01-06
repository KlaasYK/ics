#include "intersection.h"

#include <QDebug>

Intersection::Intersection()
{
    // All lights are initialised red;
    for (int i = 0; i < 8; ++i) {
        lights.append(Light::RED);
    }
}

// simple traffic light control, it should probably be changeable maybe by putting it in a subclass?
void Intersection::changeLights(int timestamp, int stepsGreen, int type) {
    // Reset first (used when switching while running)
    for (int i = 0; i < 8; ++i) {
        lights[i] = Light::RED;
    }
    switch (type) {
    case 0: simple(timestamp, stepsGreen); break;
    case 1: twoSided(timestamp, stepsGreen); break;
    }

}

void Intersection::simple(int timestamp, int stepsGreen)
{
    int lane = timestamp / stepsGreen % 4;
    lights[lane * 2] = Light::GREEN;
    lights[lane * 2 + 1] = Light::GREEN;
}

void Intersection::twoSided(int timestamp, int stepsGreen)
{
    int lane = timestamp / stepsGreen % 4;
    lights[lane] = Light::GREEN;
    lights[(lane+4)%8] = Light::GREEN;
}


void Intersection::setLights(QVector<Light> nLights)
{
    lights = nLights;
}

int Intersection::getLocalIntersectionIndex(int intersectionIndex, bool outside)
{
    int i;
    for (i = 0; i < 4; ++i)
    {
        if (connectedIntersections[i] == NULL && outside) {
            // Choose the first empy
            return i;
        }
        if (connectedIntersections[i] && connectedIntersections[i]->intersectionIndex == intersectionIndex) {
            return i;
        }
    }
    return -1;
}

// Maybe return a vector of vectors???
QVector2D Intersection::doSimulationStep()
{
    // loop over all lanes
    int i, j, cars = 0, times = 0;
    Intersection *inter;
    for (i = 0; i < 8; ++i)
    {
        int *lane = carsIndicesLane[i];
        if (lane[0] != -1 && lights.at(i) == Light::GREEN)
        {
            // Green light, front row
            if (i%2 == 0) {
                if (rand() % 100 < 50) {
                    // move forward
                    inter = connectedIntersections[(i/2 + 2)%4];
                } else {
                    // turn right
                    inter = connectedIntersections[(i/2 + 3)%4];
                }

            } else {
                // turn left
                inter = connectedIntersections[(i/2 +1)%4];
            }
            if (inter->queueCar(carsInLane[i][0], intersectionIndex))
            {
                times += carsInLane[i][0]->laneTotalWaitTime;
                cars++;
                carsInLane[i][0]->laneTotalWaitTime = 0;
                // Car is on the next lane, remove it here
                carsIndicesLane[i][0] = -1;
                carsInLane[i][0] = NULL;

            } else {
                 carsInLane[i][0]->laneTotalWaitTime++;
            }
        } else {
            if (lane[0] != -1) {
                carsInLane[i][0]->laneTotalWaitTime++;
            }
        }

        // Processs all cars further in the lane
        for (j = 1; j < LANE_LENGTH; ++j)
        {
            if (lane[j] != -1 ) {
                if ( lane[j-1] == -1) {
                    // if there is no car in front, move car
                    carsIndicesLane[i][j-1] = carsIndicesLane[i][j];
                    carsIndicesLane[i][j] = -1;
                    carsInLane[i][j]->queuenumber = j-1;
                    carsInLane[i][j-1] = carsInLane[i][j];
                    carsInLane[i][j] = NULL;
                } else {
                    // Else wait time increases
                    carsInLane[i][j]->laneTotalWaitTime++;
                }
            }
        } // Lane for loop
    }

    return QVector2D(times, cars);
}


bool Intersection::queueCar(Car *car, int sourceIntersection) {
    bool fromOutside = sourceIntersection == -1 ? true : false;
    int lane, inter = getLocalIntersectionIndex(sourceIntersection, fromOutside);

    lane = inter * 2;

    if (carsIndicesLane[lane][LANE_LENGTH-1] == -1) {
        // Can join the right/forward lane
        if (carsIndicesLane[lane+1][LANE_LENGTH-1] == -1) {
            // Can join the left lane, choose randomly 50/50
            if (rand() % 100 < 50) {
                carsIndicesLane[lane][LANE_LENGTH-1] = car->index;
                carsInLane[lane][LANE_LENGTH-1] = car;
                car->laneIndex = lane;
                car->intersectionIndex = intersectionIndex;
                car->queuenumber = LANE_LENGTH-1;
                return true;
            }
        } else {
            carsIndicesLane[lane][LANE_LENGTH-1] = car->index;
            carsInLane[lane][LANE_LENGTH-1] = car;
            car->laneIndex = lane;
            car->intersectionIndex = intersectionIndex;
            car->queuenumber = LANE_LENGTH-1;
            return true;
        }
    }
    if (carsIndicesLane[lane+1][LANE_LENGTH-1] == -1) {
        // Can join the left lane
        carsIndicesLane[lane+1][LANE_LENGTH-1] = car->index;
        carsInLane[lane+1][LANE_LENGTH-1] = car;
        car->laneIndex = lane+1;
        car->intersectionIndex = intersectionIndex;
        car->queuenumber = LANE_LENGTH-1;
        return true;
    }
    // Could not join any lane
    return false;
}


QVector<Car*> Intersection::getCars()
{
    QVector<Car*> cars;
    int lane,queue;

    for (lane = 0; lane < 8; ++lane)
    {
        for (queue = 0; queue < LANE_LENGTH; ++queue) {
            if (carsIndicesLane[lane][queue] != -1)
            {
                cars.append(carsInLane[lane][queue]);
            }
        }
    }

    return cars;
}

void Intersection::clearAllLanes()
{
    int i,j;
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < LANE_LENGTH; ++j)
        {
            carsIndicesLane[i][j] = -1;
        }
    }
    // All lights are initialised red;
    for (int i = 0; i < 8; ++i) {
        lights[i]=Light::RED;
    }
}



