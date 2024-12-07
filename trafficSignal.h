#ifndef TRAFFICSIGNAL_H
#define TRAFFICSIGNAL_H

#include "trafficNetwork.h"
#include "congestion.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class TrafficSignal {
private:
    char intersections[1000] = {};  // Contains intersections
    int greenTimes[1000] = {};       // Contains green light timings
    int totalSignals;

public:
    TrafficSignal();
    void readTrafficSignalData(string csv);
    void adjustGreenTimes(TrafficNetwork& network, string vehiclesCSV, int vertices, Vehicles vehicles);
    void displayGreenTimes(int a, TrafficNetwork& network);
    void OverrideTiming(int timing, TrafficNetwork& network, char vertice);
};

#endif


