#include "intersection.h"

#include <QDebug>

#define LIGHT_GREEN 1
#define LIGHT_RED 0

Intersection::Intersection()
{
    // All lights are initialised red;
    for (int i = 0; i < 8; ++i) {
        lights.append(0);
    }
}

void Intersection::setLights(QVector<int> nLights)
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
        if (connectedIntersections[i]->intersectionIndex == intersectionIndex) {
            return i;
        }
    }
    return -1;
}

// Maybe return a vector of vectors???
QVector2D Intersection::doSimulationStep()
{
    // loop over all lanes
    int i, j, lanes = 0, times = 0;
    Intersection *inter;
    for (i = 0; i < 8; ++i)
    {
        int *lane = carsIndicesLane[i];
        if (lane[0] != -1 && lights.at(i) == LIGHT_GREEN)
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
            if (inter == NULL) {
                // Car is done, delete it
                times += carsInLane[i][0]->laneTotalWaitTime;
                lanes += carsInLane[i][0]->nLanes;
                carsIndicesLane[i][0] = -1;
                Car *car = carsInLane[i][0];
                carsInLane[i][0] = NULL;
                delete car;
            } else {
                if (inter->queueCar(carsInLane[i][0], intersectionIndex))
                {
                    // Car is on the next lane, remove it here
                    carsIndicesLane[i][0] = -1;
                    carsInLane[i][0] = NULL;
                } else {
                     carsInLane[i][0]->laneTotalWaitTime++;
                }
            }

        } else {
            if (lane[0] != -1) {
                qDebug() << "Waiting...";
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

    return QVector2D(times, lanes);
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
                car->nLanes++;
                car->queuenumber = LANE_LENGTH-1;
                return true;
            }
        } else {
            carsIndicesLane[lane][LANE_LENGTH-1] = car->index;
            carsInLane[lane][LANE_LENGTH-1] = car;
            car->laneIndex = lane;
            car->intersectionIndex = intersectionIndex;
            car->nLanes++;
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
        car->nLanes++;
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
}



