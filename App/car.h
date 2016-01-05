#ifndef CAR_H
#define CAR_H

class Car
{
public:
    Car(int carIndex, int currentTimestamp);
    ~Car();

    int index;

    // Position of the car
    int laneIndex;
    int intersectionIndex;
    int queuenumber;

    // Timestamps
    int creationTimestamp;
    int laneTotalWaitTime;
    int nLanes;

};

#endif // CAR_H
