#ifndef ROAD_CLOSURES_H
#define ROAD_CLOSURES_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "trafficNetwork.h"
using namespace std;

class road_closures
{
    private:
        node** matrix;
        int num_vertices;
    public:

        road_closures(node** matrix, int num_vertices);
        void block_road(char start_intersection, char end_intersection);
        void clear_road(char start_intersection, char end_intersection);
        void processRoadClosures(string csv);
        void display_blocked_roads();
        void display_underrepair_roads();
        void display_clear_roads();
        void display_all_roads();
        bool is_path_blocked(char start_intersection, char end_intersection);
        bool is_path_underrepair(char start_intersection, char end_intersection);

};



#endif