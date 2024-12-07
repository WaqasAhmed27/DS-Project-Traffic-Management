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
        for (int i = 0; i <= 26; i++) {
            for (int j = 0; j <= 26; j++){
                if (network.getmatrix()[i][j].numofvehicles > 0 && greenTimes[i] != 0 && intersections[i] >= 65 && intersections[i] <= 90) {
                    cout << "Intersection " << intersections[i] << ": " << greenTimes[i] << " seconds" << endl;
                    i++;
                }
            }   
        }
        cout << endl;
    }
