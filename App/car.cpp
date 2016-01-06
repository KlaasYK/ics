#include "car.h"

#include <QDebug>

Car::Car(int carIndex, int currentTimestamp)
{
    index = carIndex;
    creationTimestamp = currentTimestamp;

    // TODO: make an array of all possible lanes (currently only using mean)
    laneTotalWaitTime = 0;
}

Car::~Car()
{

}
