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
  int getQueued();
  int getWaitTime();
  void doSimulationStep();
  void resetSimulation();

  int stepsGreen;
  int algorithm;

private:
  int carIndex;
  int currentTimestamp;
  int totalTime;
  int nLanes;
  QVector<Intersection *> intersections;
  QVector<Car *> cars;
};

#endif // SIMULATION_H
