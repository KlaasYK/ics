#include "intersection.h"

Intersection::Intersection()
{

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
}

void Intersection::doSimulationStep()
{
    // loop over all lanes

}


bool Intersection::queueCar(Car *car, int sourceIntersection) {
    bool fromOutside = sourceIntersection == -1 ? true : false;
    int lane, inter = getLocalIntersectionIndex(sourceIntersection, fromOutside);

    lane = inter * 2;

    if (carsIndicesLane[lane][LANE_LENGTH] == -1) {
        // Can join the right/forward lane
        if (carsIndicesLane[lane+1][LANE_LENGTH] == -1) {
            // Can join the left lane, choose randomly
            if (rand() % 100 < 50) {
                carsIndicesLane[lane][LANE_LENGTH] = car->index;
                carsInLane[lane][LANE_LENGTH] = car;
                car->laneIndex = lane;
                car->intersectionIndex = intersectionIndex;
                return true;
            }
        } else {
            carsIndicesLane[lane][LANE_LENGTH] = car->index;
            carsInLane[lane][LANE_LENGTH] = car;
            car->laneIndex = lane;
            car->intersectionIndex = intersectionIndex;
            return true;
        }
    }
    if (carsIndicesLane[lane+1][LANE_LENGTH] == -1) {
        // Can join the left lane
        carsIndicesLane[lane+1][LANE_LENGTH] = car->index;
        carsInLane[lane+1][LANE_LENGTH] = car;
        car->laneIndex = lane+1;
        car->intersectionIndex = intersectionIndex;
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



