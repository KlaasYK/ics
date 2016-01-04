#ifndef SIMULATION_H
#define SIMULATION_H

#include <QVector>
#include "car.h"
#include "intersection.h"

class Simulation
{
public:
    Simulation();
    ~Simulation();
    QVector<Car*> getCars();
    void doSimulationStep();
private:
    int currentTimestamp;
    QVector<Intersection*> intersections;
};

#endif // SIMULATION_H
