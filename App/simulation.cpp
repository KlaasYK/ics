#include "simulation.h"

#include <QVector2D>

void Simulation::resetSimulation() {
    currentTimestamp = 0;
    totalTime = 0;
    carsMovedTotal = 0;
    carIndex = 0;
    for (int i = 0; i < 9; ++i)
    {
        intersections[i]->clearAllLanes();
    }
    cars.clear();
    srand(42);
}

Simulation::Simulation() {
  intersections = QVector<Intersection *>();

  currentTimestamp = 0;
  totalTime = 0;
  carsMovedTotal = 0;
  carIndex = 0;
  algorithm = LightType::SIMPLE;
  stepsGreen = 4;

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

  intersections.at(0)->connectedIntersections[TOP] = intersections.at(6);
  intersections.at(0)->connectedIntersections[RIGHT] = intersections.at(1);
  intersections.at(0)->connectedIntersections[BOTTOM] = intersections.at(3);
  intersections.at(0)->connectedIntersections[LEFT] = intersections.at(2);

  intersections.at(1)->connectedIntersections[TOP] = intersections.at(7);
  intersections.at(1)->connectedIntersections[RIGHT] = intersections.at(2);
  intersections.at(1)->connectedIntersections[BOTTOM] = intersections.at(4);
  intersections.at(1)->connectedIntersections[LEFT] = intersections.at(0);

  intersections.at(2)->connectedIntersections[TOP] = intersections.at(8);
  intersections.at(2)->connectedIntersections[RIGHT] = intersections.at(0);
  intersections.at(2)->connectedIntersections[BOTTOM] = intersections.at(5);
  intersections.at(2)->connectedIntersections[LEFT] = intersections.at(1);

  intersections.at(3)->connectedIntersections[TOP] = intersections.at(0);
  intersections.at(3)->connectedIntersections[RIGHT] = intersections.at(4);
  intersections.at(3)->connectedIntersections[BOTTOM] = intersections.at(6);
  intersections.at(3)->connectedIntersections[LEFT] = intersections.at(5);

  intersections.at(4)->connectedIntersections[TOP] = intersections.at(1);
  intersections.at(4)->connectedIntersections[RIGHT] = intersections.at(5);
  intersections.at(4)->connectedIntersections[BOTTOM] = intersections.at(7);
  intersections.at(4)->connectedIntersections[LEFT] = intersections.at(3);

  intersections.at(5)->connectedIntersections[TOP] = intersections.at(2);
  intersections.at(5)->connectedIntersections[RIGHT] = intersections.at(3);
  intersections.at(5)->connectedIntersections[BOTTOM] = intersections.at(8);
  intersections.at(5)->connectedIntersections[LEFT] = intersections.at(4);

  intersections.at(6)->connectedIntersections[TOP] = intersections.at(3);
  intersections.at(6)->connectedIntersections[RIGHT] = intersections.at(7);
  intersections.at(6)->connectedIntersections[BOTTOM] = intersections.at(0);
  intersections.at(6)->connectedIntersections[LEFT] = intersections.at(8);

  intersections.at(7)->connectedIntersections[TOP] = intersections.at(4);
  intersections.at(7)->connectedIntersections[RIGHT] = intersections.at(8);
  intersections.at(7)->connectedIntersections[BOTTOM] = intersections.at(1);
  intersections.at(7)->connectedIntersections[LEFT] = intersections.at(6);

  intersections.at(8)->connectedIntersections[TOP] = intersections.at(5);
  intersections.at(8)->connectedIntersections[RIGHT] = intersections.at(6);
  intersections.at(8)->connectedIntersections[BOTTOM] = intersections.at(2);
  intersections.at(8)->connectedIntersections[LEFT] = intersections.at(7);

  srand(42);
}

int Simulation::getStepNumber() { return currentTimestamp; }

int Simulation::getCarsTotal() { return cars.size(); }

int Simulation::getCarsMoved() {
    if (currentTimestamp > 0) {
        return carsMovedTotal / currentTimestamp;
    } else {
        return 0;
    }}

int Simulation::getWaitTime() {
    if (carsMovedTotal > 0) {
        return totalTime / carsMovedTotal;
    } else {
        return 0;
    }
}

QVector<Intersection *> Simulation::getIntersections() { return intersections; }

void Simulation::doSimulationStep() {

    if (currentTimestamp < 200) {
        int inter, prev,r;
        Car *c = new Car(carIndex++,currentTimestamp);
        cars.append(c);
        do {
            inter = rand() % 9;
            r = rand()%100;
            if (r < 25) {
                prev = (inter + 3) % 9; // Bottom
            } else if (r < 50) {
                prev = (inter - 3) % 9; // Top
            } else if (r < 75) {
                prev = (inter%3 + 1)%3+inter/3*3; // Right
            } else {
                prev = (inter%3 - 1)%3+inter/3*3; // Right
            }
        } while (!intersections.at(inter)->queueCar(c,prev));
    }


    // TODO: implement detection (or something similar), currently only timed

    for (Intersection *inter : intersections) {
        inter->changeLights(currentTimestamp,stepsGreen, algorithm);
        QVector2D q2d = inter->doSimulationStep();
        totalTime += q2d.x();
        carsMovedTotal += q2d.y();
    }

    currentTimestamp++;
}

Simulation::~Simulation() {
    cars.clear();
    intersections.clear();
}
