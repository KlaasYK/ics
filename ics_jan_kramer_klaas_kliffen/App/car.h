#ifndef CAR_H
#define CAR_H

#include <QColor>

class Car
{
public:
    Car(int carIndex, int currentTimestamp);

    int index;

    // Position of the car
    int laneIndex;
    int intersectionIndex;
    int queuenumber;

    // Timestamps
    int creationTimestamp;
    int laneTotalWaitTime;

    QColor color;
    QColor colorRoof;

};

#endif // CAR_H
