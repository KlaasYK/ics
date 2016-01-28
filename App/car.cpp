#include "car.h"

#include <QDebug>

Car::Car(int carIndex, int currentTimestamp)
{
    index = carIndex;
    creationTimestamp = currentTimestamp;

    // TODO: make an array of all possible lanes (currently only using mean)
    laneTotalWaitTime = 0;
    color.setRgb(rand()%256,rand()%256,rand()%256);
    colorRoof.setRgb(rand()%256,rand()%256,rand()%256);

}

Car::~Car()
{

}
