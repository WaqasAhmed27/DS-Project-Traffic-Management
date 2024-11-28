#ifndef TRAFFIC_NETWORK_H
#define TRAFFIC_NETWORK_H

#include <iostream>
#include <fstream>
using namespace std;

class node
{
public:
    int distance;
    char intersection;

    node();
    node(int distance, char intersection);
};

class TrafficNetwork
{
private:
    node** matrix;
    int num_vertices;

public:
    TrafficNetwork(int num_vertices);
    ~TrafficNetwork();
    void Mapping_Roads(string csv);
    void Display();
};

#endif // TRAFFIC_NETWORK_H
