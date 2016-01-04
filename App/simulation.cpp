#include "simulation.h"

Simulation::Simulation()
{
    intersections = QVector();

}

void Simulation::doSimulationStep()
{


    currentTimestamp++;
}

Simulation::~Simulation()
{
    int i;
    for (i = 0; i < intersections.size(); ++i) {
        // I know, just popping leaves the intersections vector empty...
        Intersection *in = intersections.at(i);
        delete in;
    }
}




