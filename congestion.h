#ifndef CONGESTION_H
#define CONGESTION_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "trafficNetwork.h"

#define INT_MAX 2147483647      //Bohot bara number

struct heapNode
{
    int num_of_vehicles;
    heapNode* left;
    heapNode* right;

    heapNode(int num_of_vehicles);
};

class MinHeap
{
private:
    heapNode* root;
    void heapifyup(heapNode* current);
    int countnodes(heapNode* current);
    heapNode* findnode(heapNode* current, int index, int& count);
    heapNode* findnode(heapNode* root, int index);
    heapNode* findParent(heapNode* current, heapNode* child);

public:
    MinHeap();
    void insert(int num_of_vehicles);
    void custructMinHeap(node** matrix, int num_vertices);
    void display();
};

class Vehicles {
private:
    node** matrix;
    int num_vertices;

public:
    Vehicles(int num_vertices, node** matrix);
    ~Vehicles();

    void updateRoadUsage(int start, int end, int* pathTaken);
    void findShortestPath(int start, int end, int* pathTaken);
    void processVehicles(string csv);
    void printRoadUsage();
    void findShortestPathDijkstra(int start, int end, int* pathTaken);
    void printPath(int* pathTaken, int start, int end);
    void NumOfVehicles(string csv);
};

#endif