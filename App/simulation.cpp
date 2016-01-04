#include "simulation.h"

Simulation::Simulation() {
  intersections = QVector<Intersection *>();
  cars = QVector<Car *>();
}

QVector<Intersection *> Simulation::getIntersections() { return intersections; }

QVector<Car *> Simulation::getCars() { return cars; }

void Simulation::doSimulationStep() { currentTimestamp++; }

Simulation::~Simulation() {
  int i;
  for (i = 0; i < intersections.size(); ++i) {
    // I know, just popping leaves the intersections vector empty...
    Intersection *in = intersections.at(i);
    delete in;
  }
  for (Car *car : cars) {
    // I know, just popping leaves the intersections vector empty...
    delete car;
  }
}
