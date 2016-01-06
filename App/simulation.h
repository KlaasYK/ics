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

private:
  int currentTimestamp;
  int totalTime;
  int nLanes;
  QVector<Intersection *> intersections;
};

#endif // SIMULATION_H
