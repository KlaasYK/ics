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

  void doSimulationStep();

private:
  int currentTimestamp;
  QVector<Intersection *> intersections;

  int totalTime;
  int nLanes;

};

#endif // SIMULATION_H
