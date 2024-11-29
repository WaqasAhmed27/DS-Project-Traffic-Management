#ifndef CONGESTION_H
#define CONGESTION_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "trafficNetwork.h"

class Vehicles {
private:
    node** matrix;
    int** roadUsage;
    int num_vertices;

public:
    Vehicles(int num_vertices, node** matrix);
    ~Vehicles();

    void updateRoadUsage(int start, int end, int* pathTaken);
    void findShortestPath(int start, int end, int* pathTaken);
    void processVehicles(std::string csv);
    void printRoadUsage();
};

#endif

