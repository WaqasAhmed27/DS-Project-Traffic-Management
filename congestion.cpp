#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "trafficNetwork.h"
using namespace std;

class Vehicles {
private:
    node** matrix;
    int** roadUsage;
    int num_vertices;

public:
    Vehicles(int num_vertices, node** matrix) {
        this->matrix = matrix;
        this->num_vertices = num_vertices;
        roadUsage = new int*[num_vertices];
        for (int i = 0; i < num_vertices; i++) {
            roadUsage[i] = new int[num_vertices];
            for (int j = 0; j < num_vertices; j++) {
                roadUsage[i][j] = 0;
            }
        }
    }

    ~Vehicles() {
        for (int i = 0; i < num_vertices; i++) {
            delete[] roadUsage[i];
        }
        delete[] roadUsage;
    }

    void updateRoadUsage(int start, int end, int* pathTaken) {
        int current = end;
        while (pathTaken[current] != -1) {
            int prev = pathTaken[current];
            roadUsage[prev][current]++;
            current = prev;
        }
    }

    void findShortestPath(int start, int end, int* pathTaken) {
        bool* visited = new bool[num_vertices]();
        int* queue = new int[num_vertices];
        int front = 0, back = 0;

        queue[back++] = start;
        visited[start] = true;
        pathTaken[start] = -1;

        while (front < back) {
            int current = queue[front++];
            for (int i = 0; i < num_vertices; i++) {
                if (matrix[current][i].distance != 0 && !visited[i]) {
                    visited[i] = true;
                    pathTaken[i] = current;
                    queue[back++] = i;
                    if (i == end) {
                        delete[] visited;
                        delete[] queue;
                        return;
                    }
                }
            }
        }

        delete[] visited;
        delete[] queue;
    }

    void processVehicles(string csv) {
        ifstream file(csv);
        string line;
        
        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << csv << endl;
            return;
        }

        getline(file, line);
        while (getline(file, line)) {
            istringstream stream(line);
            string vehicleID, start, end;
            getline(stream, vehicleID, ',');
            getline(stream, start, ',');
            getline(stream, end, ',');

            char start_intersection = start[0];
            char end_intersection = end[0];

            int start_index = start_intersection - 65;
            int end_index = end_intersection - 65;

            int* pathTaken = new int[num_vertices];
            for (int i = 0; i < num_vertices; i++) {
                pathTaken[i] = -1;
            }

            findShortestPath(start_index, end_index, pathTaken);
            updateRoadUsage(start_index, end_index, pathTaken);
            delete[] pathTaken;
        }

        file.close();
    }

    void printRoadUsage() {
        for (int i = 0; i < num_vertices; i++) {
            for (int j = 0; j < num_vertices; j++) {
                if (roadUsage[i][j] > 0) {
                    cout << char('A' + i) << " -> " << char('A' + j)
                         << " : " << roadUsage[i][j] << " vehicles" << endl;
                }
            }
        }
    }
};
