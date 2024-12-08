#ifndef TRAFFIC_NETWORK_H
#define TRAFFIC_NETWORK_H

#include <iostream>
#include <fstream>
using namespace std;


class EV_vehicles
{
private:
    string id;
    string status;

public:
    EV_vehicles();
    ~EV_vehicles();
    EV_vehicles(string id, string status);
    string getid();
    string getstatus();
};


class node
{
public:
    int distance;       //Distance between two intersections
    char intersection;  //Intersection
    string status;      //Road status
    int numofvehicles; //Number of vehicles on the road

    node();
    node(int distance, char intersection, string status);
};

class TrafficNetwork
{
private:
    node** matrix;
    int num_vertices;

public:
    TrafficNetwork(int num_vertices);
    ~TrafficNetwork();
    node** getmatrix();
    void Mapping_Roads(string csv);
    void addnewroad(char start_intersection, char end_intersection, int distance);
    void removeRoad(char start_intersection, char end_intersection);
    void Display();
};

#endif // TRAFFIC_NETWORK_H
