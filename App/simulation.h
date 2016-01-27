#ifndef SIMULATION_H
#define SIMULATION_H

#include <QVector>
#include "car.h"
#include "intersection.h"
#include "stepstats.h"

class Simulation {
public:
  Simulation();
  ~Simulation();

  QVector<Intersection *> getIntersections();


  int getStepNumber();
  int getCarsTotal();
  int getCarsMoved();
  int getWaitTime();
  QVector<StepStats *> getStats();

  void doSimulationStep();
  void resetSimulation();

  int numCars;

  int stepsGreen;
  LightType algorithm;

private:
  int carIndex;
  int currentTimestamp;
  int sumQueueTime;
  int dequeuedTotal;
  QVector<Intersection *> intersections;
  QVector<Car *> cars;
  QVector<StepStats *> stats;
};

#endif // SIMULATION_H
