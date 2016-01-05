#include "simulation.h"

#include <QVector2D>

Simulation::Simulation() {
  intersections = QVector<Intersection *>();

  totalTime = 0;
  nLanes = 0;

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

  // Create the first car
  Car *c = new Car(0,0);
  // Put it in the left midle intersection
  intersections.at(3)->queueCar(c,-1);

}



QVector<Intersection *> Simulation::getIntersections() { return intersections; }

void Simulation::doSimulationStep() {
    // TODO: add cars (every x steps, until timestamp == x ...)


    // TODO: Change lights, depending on currentTimeStamp

    // TODO: implement detection (or something similar), currently only timed

    for (Intersection *inter : intersections) {
        QVector2D q2d = inter->doSimulationStep();
        totalTime = q2d.x();
        nLanes = q2d.y();
    }

    // TODO Write statistics?

    currentTimestamp++;
}

Simulation::~Simulation() {
  int i;
  for (i = 0; i < intersections.size(); ++i) {
    Intersection *in = intersections.at(i);
    delete in;
  }
}
