#include "car.h"

#include <QDebug>

Car::Car(int carIndex, int currentTimestamp)
{
    index = carIndex;
    creationTimestamp = currentTimestamp;
    laneTotalWaitTime = 0;
    color.setRgb(rand()%256,rand()%256,rand()%256);
    colorRoof.setRgb(rand()%256,rand()%256,rand()%256);

}
