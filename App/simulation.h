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

  int totalTime;
  int nLanes;
private:
  int currentTimestamp;
  QVector<Intersection *> intersections;
};

#endif // SIMULATION_H
