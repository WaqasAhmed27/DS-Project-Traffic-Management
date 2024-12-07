#include "trafficNetwork.h"
#include "trafficSignal.h"
#include "congestion.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


    TrafficSignal::TrafficSignal() {
        totalSignals = 0;
    }

    // Function to load up signal timing
    void TrafficSignal::readTrafficSignalData(string csv) {
        ifstream file(csv);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << csv << endl;
            return;
        }

        string line;
        getline(file, line);

        while (getline(file, line)) {
            char intersection = line[0];
            int green_time = stoi(line.substr(2));

            intersections[totalSignals] = intersection;
            greenTimes[totalSignals] = green_time;
            totalSignals++;
        }

        file.close();
    }

// Function to adjust timings
void TrafficSignal::adjustGreenTimes(TrafficNetwork& network, string vehiclesCSV, int vertices, Vehicles vehicles) {

    int num_vertices = vertices;

    ifstream file(vehiclesCSV);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << vehiclesCSV << endl;
        return;
    }

    string line;
    getline(file, line);

    while (getline(file, line)) {
        istringstream stream(line);
        string vehicleID, start, end;
        getline(stream, vehicleID, ',');
        getline(stream, start, ',');
        getline(stream, end, ',');

        char start_intersection = start[0];
        int start_index = start_intersection - 65;
    }
    file.close();

    // Adjustment
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            int additionalTime = network.getmatrix()[i][j].numofvehicles * 5;
            greenTimes[i] = greenTimes[i] + additionalTime;
        }
    }
}

// Function for Display
    void TrafficSignal::displayGreenTimes(int a, TrafficNetwork& network) {
        if (a == 0) {
            cout << "\nOriginal Green Light Times:\n";
        } else {
            cout << "\nUpdated Green Light Times:\n";
        }
        for (int i = 0; i < totalSignals; i++) {  // Use totalSignals to ensure we don't exceed bounds
                if (greenTimes[i] != 0 && intersections[i] >= 65 && intersections[i] <= 90) {
                    cout << "Intersection " << intersections[i] << ": " << greenTimes[i] << " seconds" << endl;
                }
        }
        cout << endl;
        
    }


    void TrafficSignal::OverrideTiming(int seconds, TrafficNetwork& network, char vertice) {
        if (vertice >= 'a' && vertice<= 'z') {
            vertice -= 32;
        }
        for (int i = 0; i < totalSignals; i++) {
            if (intersections[i] == vertice) {
                greenTimes[i] = seconds;
                cout << "Green light at Intersection " << vertice << " will now be open for " << seconds << " seconds.\n";
                displayGreenTimes(1,network);
                return;
            }
        }

            cout << "Intersection " << vertice << " not found." << endl;
    }

