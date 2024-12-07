#include "congestion.h"

Vehicles::Vehicles(int num_vertices, node** matrix) {
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

Vehicles::~Vehicles() {
    for (int i = 0; i < num_vertices; i++) {
        delete[] roadUsage[i];
    }
    delete[] roadUsage;
}

void Vehicles::updateRoadUsage(int start, int end, int* pathTaken) {
    int current = end;
    while (pathTaken[current] != -1) {
        int prev = pathTaken[current];
        roadUsage[prev][current]++;
        current = prev;
    }
}

void Vehicles::findShortestPath(int start, int end, int* pathTaken) {
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

void Vehicles::processVehicles(string csv) {
    ifstream file(csv);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << csv << endl;
        return;
    }

    getline(file, line); // Skip the header
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

void Vehicles::printRoadUsage() {
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (roadUsage[i][j] > 0) {
                cout << char('A' + i) << " -> " << char('A' + j)
                          << " : " << roadUsage[i][j] << " vehicles" << endl;
            }
        }
    }
}

void Vehicles::findShortestPathDijkstra(int start, int end, int* path_taken) {
    int* dist = new int[num_vertices];       // Array to store shortest distances
    bool* visited = new bool[num_vertices]; 

    int i = 0;

    while (i < num_vertices) {
        dist[i] = INT_MAX;  // Setting weights to MAX
        visited[i] = false; //Marked Unvisited
        path_taken[i] = -1; 
        i++;
    }

    dist[start] = 0; // Setting start node distance to 0

    int count = 0;
    while (count < num_vertices - 1) {
        int min_dist = INT_MAX;
        int min_index = -1;

        i = 0;
        while (i < num_vertices) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                min_index = i;
            }
            i++;
        }

        if (min_index == -1) {
            break;
        }

        visited[min_index] = true;

        i = 0;
        while (i < num_vertices) {
            if (!visited[i] && matrix[min_index][i].distance > 0) { // If neighbor exists
                int new_dist = dist[min_index] + matrix[min_index][i].distance;
                if (new_dist < dist[i]) {
                    dist[i] = new_dist;
                    path_taken[i] = min_index; // Update
                }
            }
            i++;
        }
        count++;
    }

    // Print shortest distance
    if (dist[end] == INT_MAX) {
        cout << "No path exists between nodes " << char(start + 'A') << " and " << char(end + 'A') << endl;
    } else {
        cout << "\nShortest distance from " << char(start + 'A') << " to " << char(end + 'A') << " is " << dist[end] << endl;
    }

    delete[] dist;
    delete[] visited;
}


void Vehicles::printPath(int* pathTaken, int start, int end) {
    if (pathTaken[end] == -1) {
        cout << char(start + 'A') << " ";
        return;
    }
    printPath(pathTaken, start, pathTaken[end]);
    cout << char(end + 'A') << " ";
}

void Vehicles::findAllPathsHelper(int current, int end, bool* visited, int* path, int path_index, bool& pathFound) {
    visited[current] = true;          // vist marked
    path[path_index] = current;       // adding current node to path
    path_index++;                  

    if (current == end)
    {
        // Print the current path
        pathFound = true;             //path found
        for (int i = 0; i < path_index; i++) {
            cout << char(path[i] + 'A') << (i < path_index - 1 ? " -> " : "\n");
        }
    } 
    else 
    {
        // Recurse for all adjacent nodes
        for (int i = 0; i < num_vertices; i++) 
        {
            if (matrix[current][i].distance != 0 && !visited[i]) 
            {   
                //visit only unvisited nodes
                findAllPathsHelper(i, end, visited, path, path_index, pathFound);
            }
        }
    }

    // Backtracking
    visited[current] = false;         //unmarking visited node
}

void Vehicles::findAllPaths(char startc, char endc) 
{
    int start = startc - 'A';       
    int end = endc - 'A';             

    bool* visited = new bool[num_vertices]; // To keep track of visited nodes
    int* path = new int[num_vertices];      // Array to store the current path
    int path_index = 0;
    bool path_found = false;                // Flag to indicate if a path is found  

    // Initialize visited array
    for (int i = 0; i < num_vertices; i++) {
        visited[i] = false;
    }

    //helper call
    findAllPathsHelper(start, end, visited, path, path_index, path_found);

    //no path found
    if (!path_found) 
    {
        cout << "No paths exist between " << startc << " and " << endc << endl;
    }

    delete[] visited; 
    delete[] path;   
}
