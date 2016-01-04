#include "simulation.h"

Simulation::Simulation() {
  intersections = QVector<Intersection *>();
  cars = QVector<Car *>();

  int i;
  Intersection *inter;

  // Create the 9 intersections
  // Form left to right top to bottom

  for (i = 0; i < 9; ++i)
  {
      inter = new Intersection();
      inter->intersectionIndex = i;
      inter->clearAllLanes();
      intersections.append(inter);
  }

  intersections.at(0)->connectedIntersections[TOP] = NULL;
  intersections.at(0)->connectedIntersections[RIGHT] = intersections.at(1);
  intersections.at(0)->connectedIntersections[BOTTOM] = intersections.at(3);
  intersections.at(0)->connectedIntersections[LEFT] = NULL;

  intersections.at(1)->connectedIntersections[TOP] = NULL;
  intersections.at(1)->connectedIntersections[RIGHT] = intersections.at(2);
  intersections.at(1)->connectedIntersections[BOTTOM] = intersections.at(4);
  intersections.at(1)->connectedIntersections[LEFT] = intersections.at(0);

  intersections.at(2)->connectedIntersections[TOP] = NULL;
  intersections.at(2)->connectedIntersections[RIGHT] = NULL;
  intersections.at(2)->connectedIntersections[BOTTOM] = intersections.at(5);
  intersections.at(2)->connectedIntersections[LEFT] = intersections.at(1);

  intersections.at(3)->connectedIntersections[TOP] = intersections.at(0);
  intersections.at(3)->connectedIntersections[RIGHT] = intersections.at(4);
  intersections.at(3)->connectedIntersections[BOTTOM] = intersections.at(6);
  intersections.at(3)->connectedIntersections[LEFT] = NULL;

  intersections.at(4)->connectedIntersections[TOP] = intersections.at(1);
  intersections.at(4)->connectedIntersections[RIGHT] = intersections.at(5);
  intersections.at(4)->connectedIntersections[BOTTOM] = intersections.at(7);
  intersections.at(4)->connectedIntersections[LEFT] = intersections.at(3);

  intersections.at(5)->connectedIntersections[TOP] = intersections.at(2);
  intersections.at(5)->connectedIntersections[RIGHT] = NULL;
  intersections.at(5)->connectedIntersections[BOTTOM] = intersections.at(8);
  intersections.at(5)->connectedIntersections[LEFT] = intersections.at(4);

  intersections.at(6)->connectedIntersections[TOP] = intersections.at(3);
  intersections.at(6)->connectedIntersections[RIGHT] = intersections.at(7);
  intersections.at(6)->connectedIntersections[BOTTOM] = NULL;
  intersections.at(6)->connectedIntersections[LEFT] = NULL;

  intersections.at(7)->connectedIntersections[TOP] = intersections.at(4);
  intersections.at(7)->connectedIntersections[RIGHT] = intersections.at(8);
  intersections.at(7)->connectedIntersections[BOTTOM] = NULL;
  intersections.at(7)->connectedIntersections[LEFT] = NULL;

  intersections.at(8)->connectedIntersections[TOP] = intersections.at(5);
  intersections.at(8)->connectedIntersections[RIGHT] = NULL;
  intersections.at(8)->connectedIntersections[BOTTOM] = NULL;
  intersections.at(8)->connectedIntersections[LEFT] = intersections.at(7);

}



QVector<Intersection *> Simulation::getIntersections() { return intersections; }

QVector<Car *> Simulation::getCars()
{
    // TODO: read all cars from all lanes from each intersection
    return cars;
}

void Simulation::doSimulationStep() { currentTimestamp++; }

Simulation::~Simulation() {
  int i;
  for (i = 0; i < intersections.size(); ++i) {
    Intersection *in = intersections.at(i);
    delete in;
  }
  for (Car *car : cars) {
    delete car;
  }
}
