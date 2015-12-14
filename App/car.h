#ifndef CAR_H
#define CAR_H

#include <QVector>

class Car
{
public:
    Car(int carIndex, int inLane, int outLane, int currentTimestamp, int numberOfLanes);
    ~Car();

    int index;

    // Position of the car
    int laneIndex;
    int queueNumber;

    // A vector to represent the path this car is going to take
    QVector<int> pathIndices;

    // Timestamps
    int creationTimestamp;
    int* laneWaitTimes;

    int getTotalWaitTime();
private:
    int nLanes;
};

#endif // CAR_H
