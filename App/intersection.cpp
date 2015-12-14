#include "intersection.h"

Intersection::Intersection()
{

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



