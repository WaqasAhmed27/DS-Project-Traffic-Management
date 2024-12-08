#ifndef EVHANDLING_H
#define EVHANDLING_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "trafficNetwork.h"
#include "roadClosures.h"
using namespace std;


#define INT_MAX 2147483647      //Bohot bara number

class EVHandling
{
private:
    int num_vertices;
    node** matrix;
    EV_vehicles** EV_path;
public:

    EVHandling();
    EVHandling(int num_vertices,node** matrix);
    void findShortestPathforEV(int start, int end, int* pathTaken, road_closures& roadChecker);
    void updateEVPath(int start, int end, int* pathTaken, string id, string status);
    void printPathforEV(int* pathTaken, int start, int end);
    void processEVs(string csv, road_closures& roadChecker);
    void printEVs();

};








#endif