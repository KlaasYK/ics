#ifndef SIMULATION_H
#define SIMULATION_H

#include <QVector>
#include "car.h"

class Simulation
{
public:
    Simulation();
    QVector<Car*> getCars();
    void doSimulationStep();
private:
    int currentTimestamp;
};

#endif // SIMULATION_H
