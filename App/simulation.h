#ifndef SIMULATION_H
#define SIMULATION_H

#include <QVector>
class Simulation
{
public:
    Simulation();
    QVector<Car> getCars();
    void doSimulationStep();
private:
    int currentTimestamp;
};

#endif // SIMULATION_H
