#include "car.h"

#include <QDebug>

Car::Car(int carIndex, int inLane, int outLane, int currentTimestamp, int numberOfLanes)
{
    index = carIndex;
    creationTimestamp = currentTimestamp;
    laneIndex = inLane;
    //queueNumber to be set by the Intersection
    calculatePath(outLane);

    laneWaitTimes = new int[numberOfLanes];
    nLanes = numberOfLanes;
}

Car::~Car()
{
    delete laneWaitTimes;
}

int Car::getNextLane() {
    if (!pathIndices.isEmpty())
    {
        return pathIndices.takeFirst();
    }
    qDebug() << "Car is lost... Please advise";
    return -1;
}

int Car::getTotalWaitTime()
{
    int totalTime = 0, index;
    for (index = 0; index < nLanes; ++index)
    {
        totalTime += laneWaitTimes[index];
    }
    return totalTime;
}

void Car::calculatePath(int destinationIndex)
{
    // TODO: implement A* and store indices in pathIndices
    // Can this be done here???
}

