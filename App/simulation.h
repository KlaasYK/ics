#ifndef SIMULATION_H
#define SIMULATION_H

#include <QVector>
#include "car.h"
#include "intersection.h"

class Simulation {
public:
  Simulation();
  ~Simulation();

  QVector<Intersection *> getIntersections();


  int getStepNumber();
  int getCarsTotal();
  int getCarsMoved();
  int getWaitTime();

  void doSimulationStep();
  void resetSimulation();

  int stepsGreen;
  LightType algorithm;

private:
  int carIndex;
  int currentTimestamp;
  int totalTime;
  int carsMovedTotal;
  QVector<Intersection *> intersections;
  QVector<Car *> cars;
};

#endif // SIMULATION_H
