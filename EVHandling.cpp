#include "EVHandling.h"

EVHandling::EVHandling()
{
    this->EV_path = new EV_vehicles*[100];
    for(int i=0;i<100;i++)
    {
        EV_path[i] = new EV_vehicles[100];
    }
}
EVHandling::EVHandling(int num_vertices, node** matrix)
{
    this->num_vertices = num_vertices;
    this->matrix = matrix;
}


void EVHandling::processEVs(string csv, road_closures& road_closures)
{
    ifstream file(csv);
    string line;
    string id;
    string status;
    string start_intersection;
    string end_intersection;

    if (!file.is_open())
    {
        cerr << "Error: Unable to open file " << csv << endl;
        return;
    }

    getline(file, line); // Skip header line
    while (getline(file, line))
    {
        
        
        istringstream stream(line);
        getline(stream, id, ',');
        getline(stream, start_intersection, ',');
        getline(stream, end_intersection, ',');
        getline(stream, status, ',');


        int start_index = start_intersection[0] - 'A';
        int end_index = end_intersection[0] - 'A';

        int* pathTaken = new int[num_vertices];
        for (int i = 0; i < num_vertices; i++) 
        {
            pathTaken[i] = -1;
        }

        //findShortestPathforEV(start_index, end_index, pathTaken, road_closures);
        updateEVPath(start_index, end_index, pathTaken, id, status);

        delete[] pathTaken;
     
    }
    file.close();
}

void EVHandling::printEVs()
{
    cout << "Emergency Vehicles: " << endl;
    for (int i = 0; i < 26; i++)
    {
        if (EV_path[i] != nullptr)
        {
            for (int j = 0; j < 26; j++)
            {
                if (EV_path[i][j].getid() != "")
                {
                    cout << "ID: " << EV_path[i][j].getid() << " Status: " << EV_path[i][j].getstatus() << endl;
                }
            }
        }
    }
    
}

void EVHandling::updateEVPath(int start, int end, int* pathTaken, string id, string status)
{
    int current = end;
    while (pathTaken[current] != -1) 
    {
        int prev = pathTaken[current];
        matrix[prev][current].numofvehicles++;
        current = prev;
    }
}

void EVHandling::findShortestPathforEV(int start, int end, int* path_taken, road_closures& road_checker)
{
    // Function to find the shortest path between two intersections using Dijkstra's algorithm
    int* dist = new int[num_vertices];       // Array to store shortest distances
    bool* visited = new bool[num_vertices]; // Array to mark visited nodes

    // Initialize distances to infinity, visited to false, and path_taken to -1
    for (int i = 0; i < num_vertices; i++) {
        dist[i] = INT_MAX; 
        visited[i] = false; 
        path_taken[i] = -1; 
    }

    dist[start] = 0; // Distance to the start node is 0

    for (int count = 0; count < num_vertices - 1; count++) 
    {
        // Find the vertex with the minimum distance value, from the set of vertices not yet visited
        int min_dist = INT_MAX, min_index = -1;
        for (int i = 0; i < num_vertices; i++) 
        {
            if (!visited[i] && dist[i] < min_dist) 
            {
                min_dist = dist[i];
                min_index = i;
            }
        }

        if (min_index == -1) 
        {
            break; // No more reachable nodes
        }

        visited[min_index] = true; // Mark the vertex as visited

        // Update distance value for the adjacent vertices
        for (int i = 0; i < num_vertices; i++) 
        {
            // Skip the paths that are blocked or under repair
            if (!visited[i] && matrix[min_index][i].distance > 0) 
            {
                if (road_checker.is_path_blocked(char(min_index + 'A'), char(i + 'A'))) 
                {
                    continue; // Skip blocked paths
                }
                if (road_checker.is_path_underrepair(char(min_index + 'A'), char(i + 'A'))) 
                {
                    continue; // Skip paths under repair
                }

                int new_dist = dist[min_index] + matrix[min_index][i].distance;
                if (new_dist < dist[i]) 
                {
                    dist[i] = new_dist;
                    path_taken[i] = min_index; // Update the path
                }
            }
        }
    }

    // Print shortest distance
    if (dist[end] == INT_MAX) 
    {
        cout << "No path exists between nodes " << char(start + 'A') << " and " << char(end + 'A') << endl;
    }

    delete[] dist;
    delete[] visited;
}

void EVHandling::printPathforEV(int* pathTaken, int start, int end) 
{
    if (pathTaken[end] == -1) 
    {
        cout << char(start + 'A') << " ";
        return;
    }
    printPathforEV(pathTaken, start, pathTaken[end]);
    cout << char(end + 'A') << " ";
}

