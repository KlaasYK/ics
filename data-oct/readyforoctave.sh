#!/bin/bash
for file in ./*.txt;
do
  sed -i 's/step\ numCars\ dequeuedCars\ minQueueTime\ maxQueueTime\ sumQueueTime\n//g' ${file};
  sed -i 's/?/NaN/g' ${file};
done