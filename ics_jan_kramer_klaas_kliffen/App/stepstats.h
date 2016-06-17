#ifndef STEPSTATS_H
#define STEPSTATS_H

class StepStats {
public:
    StepStats(int step, int cars, int dequeued, int minTime, int maxTime, int sumTime): time(step), numCars(cars), dequeuedCars(dequeued), minQueueTime(minTime), maxQueueTime(maxTime), sumQueueTime(sumTime) {}
    int time;

    int numCars;
    int dequeuedCars;

    bool validMin = false;
    bool validMax = false;
    int minQueueTime;
    int maxQueueTime;
    int sumQueueTime;
};

#endif // STEPSTATS_H
