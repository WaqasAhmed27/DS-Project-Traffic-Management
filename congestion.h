#ifndef CONGESTION_H
#define CONGESTION_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "trafficNetwork.h"
#include "roadClosures.h"

#define INT_MAX 2147483647      //Bohot bara number

struct heapNode
{
    int num_of_vehicles;
    heapNode* left;
    heapNode* right;
    char start_intersection;
    char end_intersection;
    heapNode();
    heapNode(int num_of_vehicles, char start_intersection, char end_intersection);
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
    void insert(int num_of_vehicles, char start_intersection, char end_intersection);
    void constructMinHeap(node** matrix, int num_vertices);
    heapNode* exractMaxNode(heapNode*& root);
    heapNode* FindMostCongestedRoad();
    void display();
};

struct VehicleDetails {
    string StartIntersection;
    int vehicleCount;
    bool isOccupied;
};

class Vehicles {
private:
    node** matrix;
    int** roadUsage;
    int num_vertices;
    VehicleDetails* hashTable;  // Hash table to store vehicle details
    int tableSize;

    // Simple hash function to map start-end pair to an index
    int hashFunction(string StartIntersection);

    // Handle collisions using linear probing
    void insertToHashTable(string StartIntersection);
public:
    void printRoadUsage();
    void printRoadUsageHT();
    void printVehicleDetails();
    void NumOfVehicles(string csv);
    void processVehicles(string csv);
    void printPath(int* pathTaken, int start, int end);
    void updateRoadUsage(int start, int end, int* pathTaken);
    void findShortestPath(int start, int end, int* pathTaken);
    void averageTravelTimePerVehicle(int num_vertices, node** matrix);
    void findAllPaths(char startc, char endc, road_closures& roadChecker);
    void findShortestPathDijkstra(int start, int end, int* pathTaken, road_closures& roadChecker);
    void findAllPathsHelper(int current, int end, bool* visited, int* path, int path_index, bool& pathFound, road_closures& roadChecker);
};
#endif
