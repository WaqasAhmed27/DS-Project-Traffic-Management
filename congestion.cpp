#include "congestion.h"

                                            ///////////Implementation of Vehicles class///////////////////////


// Vehicles;

Vehicles::Vehicles(int num_vertices, node** matrix) {
    this->matrix = matrix;
    this->num_vertices = num_vertices;

}

Vehicles::~Vehicles() {}

void Vehicles::updateRoadUsage(int start, int end, int* pathTaken) {
    int current = end;
    while (pathTaken[current] != -1) {
        int prev = pathTaken[current];
        matrix[prev][current].numofvehicles++;
        current = prev;
    }
}

//Funciton to find the shortest path between two intersections
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

// Function to process the vehicles from the csv file
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


//Print the road usage( Displaying the number of vehicles on each road)
void Vehicles::printRoadUsage() {
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (matrix[i][j].numofvehicles > 0) {
                cout << char('A' + i) << " -> " << char('A' + j)
                          << " : " << matrix[i][j].numofvehicles << " vehicles" << endl;
            }
        }
    }
}


// Function to find the shortest path between two intersections using Dijkstra's algorithm
void Vehicles::findShortestPathDijkstra(int start, int end, int* path_taken, road_closures& road_checker) {
    int* dist = new int[num_vertices];       // Array to store shortest distances
    bool* visited = new bool[num_vertices]; // Array to mark visited nodes

    // Initialize distances to infinity, visited to false, and path_taken to -1
    for (int i = 0; i < num_vertices; i++) {
        dist[i] = INT_MAX; 
        visited[i] = false; 
        path_taken[i] = -1; 
    }

    dist[start] = 0; // Distance to the start node is 0

    for (int count = 0; count < num_vertices - 1; count++) {
        // Find the vertex with the minimum distance value, from the set of vertices not yet visited
        int min_dist = INT_MAX, min_index = -1;
        for (int i = 0; i < num_vertices; i++) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                min_index = i;
            }
        }

        if (min_index == -1) {
            break; // No more reachable nodes
        }

        visited[min_index] = true; // Mark the vertex as visited

        // Update distance value for the adjacent vertices
        for (int i = 0; i < num_vertices; i++) {
            // Skip the paths that are blocked or under repair
            if (!visited[i] && matrix[min_index][i].distance > 0) {
                if (road_checker.is_path_blocked(char(min_index + 'A'), char(i + 'A'))) {
                    cout << "Path from " << char(min_index + 'A') << " to " << char(i + 'A') << " is blocked. Rerouting...\n";
                    continue; // Skip blocked paths
                }
                if (road_checker.is_path_underrepair(char(min_index + 'A'), char(i + 'A'))) {
                    cout << "Path from " << char(min_index + 'A') << " to " << char(i + 'A') << " is under repair. Rerouting...\n";
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
    if (dist[end] == INT_MAX) {
        cout << "No path exists between nodes " << char(start + 'A') << " and " << char(end + 'A') << endl;
    } else {
        cout << "\nShortest distance from " << char(start + 'A') << " to " << char(end + 'A') << " is " << dist[end] << endl;
    }

    delete[] dist;
    delete[] visited;
}



// Function to print the path taken
void Vehicles::printPath(int* pathTaken, int start, int end) {
    if (pathTaken[end] == -1) {
        cout << char(start + 'A') << " ";
        return;
    }
    printPath(pathTaken, start, pathTaken[end]);
    cout << char(end + 'A') << " ";
}

//Function to print vehicles on each road at initial stage
void Vehicles::NumOfVehicles(string csv) {
    ifstream file(csv);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << csv << endl;
        return;
    }

    getline(file, line);

    // Array keeps track of vehicles on each road
    int* vehicleCount = new int[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        vehicleCount[i] = 0;
    }

    while (getline(file, line)) {
        istringstream stream(line);
        string vehicleID, start, end;
        getline(stream, vehicleID, ',');
        getline(stream, start, ',');
        getline(stream, end, ',');

        char start_intersection = start[0];
        int start_index = start_intersection - 65; // Change to indexes

        if (start_index >= 0 && start_index < num_vertices) {
            vehicleCount[start_index]++;
            matrix[start_index][0].numofvehicles++;
        } else {
            cerr << "Warning: Invalid start intersection " << start << endl;
        }
    }

    file.close();
    for (int i = 0; i < num_vertices; i++) {
        char intersection = char(i + 65);  // Convert back to letter
        cout << "Intersection " << intersection << ": " << vehicleCount[i] << " vehicles." << endl;
    }
    delete[] vehicleCount;
}


                                        ////////Implementation of finding all possible paths between two intersections/////////////



// Helper function to find all possible paths between two intersections
void Vehicles::findAllPathsHelper(int current, int end, bool* visited, int* path, int path_index, bool& pathFound, road_closures& roadChecker) {
    visited[current] = true;          // Mark current node as visited
    path[path_index] = current;       // Add current node to path
    path_index++;                   

    if (current == end)
    {
        // Print the current path if it reaches the end

        pathFound = true;             // Path found flag
        for (int i = 0; i < path_index; i++) {
            cout << char(path[i] + 'A') << (i < path_index - 1 ? " -> " : "\n");
        }
    } 
    else 
    {
        for (int i = 0; i < num_vertices; i++) 
        {
            // Check if the edge exists and the node is unvisited
            if (matrix[current][i].distance != 0 && !visited[i]) 
            {   
                // Check if the path is not blocked or under repair
                if (roadChecker.is_path_blocked(char(current + 'A'), char(i + 'A'))) 
                {
                    cout << "Path from " << char(current + 'A') << " to " << char(i + 'A') << " is blocked. Skipping...\n";
                    continue;
                }
                if (roadChecker.is_path_underrepair(char(current + 'A'), char(i + 'A'))) 
                {
                    cout << "Path from " << char(current + 'A') << " to " << char(i + 'A') << " is under repair. Skipping...\n";
                    continue;
                }
                findAllPathsHelper(i, end, visited, path, path_index, pathFound, roadChecker);
            }
        }
    }

    // Backtrack
    visited[current] = false;         // Unmark visited node
}

// Function to find all possible paths between two intersections
void Vehicles::findAllPaths(char startc, char endc, road_closures& roadChecker) 
{
    int start = startc - 'A';       
    int end = endc - 'A';             

    bool* visited = new bool[num_vertices]; // To keep track of visited nodes
    int* path = new int[num_vertices];      // Array to store the current path
    int path_index = 0;
    bool path_found = false;                // Flag to indicate if a path is found  

    // Initialize 
    for (int i = 0; i < num_vertices; i++) 
    {
        visited[i] = false;
    }

    // Call helper function to find all paths
    findAllPathsHelper(start, end, visited, path, path_index, path_found, roadChecker);

    // No path found
    if (!path_found) 
    {
        cout << "No paths exist between " << startc << " and " << endc << endl;
    }

    delete[] visited; 
    delete[] path;   
}


                                            /////////////////////Implementation of Average Travel Time Per Vehicle///////////////////////
                                            

void Vehicles::averageTravelTimePerVehicle(int num_vertices, node** matrix) {
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            if (matrix[i][j].numofvehicles > 0) {  // Print if vehicles present
                cout << "Average travel time per vehicle from " << char(i + 'A') << " to " << char(j + 'A') << " is " 
                     << matrix[i][j].distance / matrix[i][j].numofvehicles << " units." << endl;
            }
        }
    }
}

                                            ////////////Heap Implementation To find the most congested road/////////////////////


// Constructor
heapNode::heapNode(int num_of_vehicles, char start_intersection, char end_intersection) 
{
    this->num_of_vehicles = num_of_vehicles;
    this->start_intersection = start_intersection;
    this->end_intersection = end_intersection;
    left = right = nullptr;
}

heapNode::heapNode() 
{
    this->num_of_vehicles=0;
    this->start_intersection = 'A';
    this->end_intersection = 'A';
    left = right = nullptr;
}
// Constructor
MinHeap::MinHeap()
{
    root = nullptr;
}

// Function to count the number of nodes in the heap
int MinHeap::countnodes(heapNode* current)
{
    if(current ==nullptr)
        return 0;
    
    return 1 + countnodes(current->left) + countnodes(current->right);  
}

// Helper function to find the node at a given index
heapNode* MinHeap::findnode(heapNode* root, int index, int& count)
{
    if(root == nullptr)
        return nullptr;

    if(count == index)
        return root;

    count++;

    heapNode* left = findnode(root->left, index, count);
    
    if(left)
        return left;
    
    return findnode(root->right, index, count);

}

// Function to find the node at a given index
heapNode* MinHeap:: findnode(heapNode* root, int index)
{
    int count =0;
    return findnode(root, index, count);    
}

//Findinf the parent of the given child 
heapNode* MinHeap:: findParent(heapNode* current, heapNode* child)
{
    if(current == nullptr || (current->left == nullptr && current->right == nullptr))
    {
        return nullptr;
    }

    if(child == current->left || child == current->right)
    {
        return current;
    }

    heapNode* left = findParent(current->left, child);
    if(left)
        return left;
    return findParent(current->right, child);
}

// Function to heapify up to maintain the min heap property  
void MinHeap::heapifyup(heapNode* node)
{
    if(node == nullptr || root == nullptr)
        return;
    
    heapNode* parent = findParent(root, node);

    if (parent != nullptr && parent->num_of_vehicles > node->num_of_vehicles) {
        swap(parent->num_of_vehicles, node->num_of_vehicles);
        swap(parent->start_intersection, node->start_intersection);
        swap(parent->end_intersection, node->end_intersection);
        heapifyup(parent);
    }
}


// Function to insert a new node into the heap while maintaining the min heap property and structure property
void MinHeap::insert(int num_of_vehicles, char start_intersection, char end_intersection) 
{
    if (root == nullptr) 
    {
        root = new heapNode(num_of_vehicles, start_intersection, end_intersection);
    } 
    else 
    {
        int no_of_nodes = countnodes(root);// Count the number of nodes in the heap
        heapNode* point = findnode(root, (no_of_nodes - 1)); //Finding the point at which the new node is to be inserted

        // Insert the new node as the left child if the left child is empty and if not insert as the right child
        if (point->left == nullptr) 
        {
            point->left = new heapNode(num_of_vehicles, start_intersection, end_intersection);
            heapifyup(point->left);
        }             
        else             
        {
            point->right = new heapNode(num_of_vehicles, start_intersection, end_intersection);
            heapifyup(point->right);
        }
         
    }
}

// Function to construct the min heap from the given num of vehicles on each road in the matrix 
void MinHeap::constructMinHeap(node** matrix, int num_vertices)
{
    for(int i =0; i<num_vertices; i++)
    {
        for(int j =0; j<num_vertices; j++)
        {
            if(matrix[i][j].numofvehicles > 0)
            {
                insert(matrix[i][j].numofvehicles, i+'A', j+'A');//Converting the indexes i and j to corresponding intersections   
            }
        }
    }
}   

// Function to display the heap
void MinHeap::display()
{
    if(root == nullptr)
    {
        cout<<"Heap is empty!"<<endl;
        return;
    }
    cout<<"Heap: "<<endl;

    int no_of_nodes = countnodes(root);
    for(int i =0; i<no_of_nodes; i++)
    {
        heapNode* current = findnode(root, i);
        cout<<current->num_of_vehicles<<" ";
    }
    cout<<endl;
}

// Helper function to extract the node with the maximum number of vehicles from the heap
heapNode* MinHeap::exractMaxNode(heapNode*& root)
{
    if(root == nullptr)
    {
        return nullptr;
    }

    if(root->left == nullptr && root->right == nullptr)
    {
        return root;
    }

    heapNode* left = exractMaxNode(root->left);// Finding max node in the left subtree
    heapNode* right = exractMaxNode(root->right);// Finding max node in the right subtree

    heapNode* max = root;

    if(left!= nullptr && left->num_of_vehicles > max->num_of_vehicles)// Comparing the max node in the left subtree with the root
    {
        max = left;
    }
    if(right != nullptr && right->num_of_vehicles > max->num_of_vehicles)// Comparing the max node in the right subtree with the root
    {
        max = right;
    }

    return max;
}

// Function to find the most congested road in the heap
heapNode* MinHeap::FindMostCongestedRoad()
{
    if(root == nullptr)
    {
        return nullptr;
    }

    heapNode* max = exractMaxNode(root);

    cout<<"Most Congested Road: "<<max->start_intersection<<" -> "<<max->end_intersection<<" : "<<max->num_of_vehicles<<" vehicles"<<endl;
    return max;
}

// This function is used to find the alternative path for traffic congestion to re-route it
int* Vehicles::findAlternativePath(char startc, char endc, road_closures& roadChecker) 
{
    int start = startc - 'A'; 
    int end = endc - 'A';    
    
    bool* visited = new bool[num_vertices];  // To track visited nodes
    int* path_taken = new int[num_vertices]; // To store the path
    int path_index = 0;  // Index to track the current position in the path
    bool path_found = false;  // Flag to indicate if we found a path

    // Initialize visited array
    for (int i = 0; i < num_vertices; i++) 
    {
        visited[i] = false;  //marked as unvisited
        path_taken[i] = -1;   // Marked as not part of the path
    }

    int* stack = new int[num_vertices];
    int stack_size = 0;

    stack[stack_size++] = start;
    visited[start] = true;

    while (stack_size > 0 && !path_found) 
    {
        int current = stack[stack_size - 1];
        stack_size--;  //pop

        // Add the current node to the path
        path_taken[path_index++] = current;

        // If we've reached the destination, we found a path
        if (current == end) 
        {
            path_found = true;
            break;
        }

        // Explore all adjacent nodes
        bool moved = false;
        for (int i = 0; i < num_vertices; i++) 
        {
            if (matrix[current][i].distance != 0 && !visited[i]) 
            {
                // Check if the path is not blocked or under repair
                if (roadChecker.is_path_blocked(char(current + 'A'), char(i + 'A'))) 
                {
                    continue;  // Skip blocked paths
                }
                if (roadChecker.is_path_underrepair(char(current + 'A'), char(i + 'A'))) 
                {
                    continue;  // Skip under-repair paths
                }

                // Push the adjacent node onto the stack for DFS
                stack[stack_size++] = i;
                visited[i] = true;
                moved = true;
                break;  // Only move to one unvisited adjacent node at a time
            }
        }

        // If we didn't move to any adjacent node, remove the current node from the path
        if (!moved) 
        {
            path_index--;  //removing the current node
            visited[current] = false;  //Marked as unvisited
        }
    }

    // If no path was found, set path_taken to -1 for all nodes
    if (!path_found) 
    {
        delete[] visited;
        delete[] stack;
        delete[] path_taken;
        return nullptr;  // No path exists
    }

    delete[] visited;
    delete[] stack;
    return path_taken;  // Return the path 
}

void MinHeap::reduceCongestion(heapNode* congested_road, node** matrix, int num_vertices, road_closures& road_closures, Vehicles& vehicles) {     
    if (congested_road == nullptr) {        
        cout << "No road to reduce congestion!" << endl;
        return;
    }
    int* path_taken = vehicles.findAlternativePath(congested_road->start_intersection, congested_road->end_intersection, road_closures);

    if(path_taken == nullptr)
    {
        cout<<"There is no alternative path between "<< congested_road->start_intersection <<"->"<<congested_road->end_intersection<<" to divert traffic"<<endl;
        return;
    }

    int start = congested_road->start_intersection - 'A';
    int end = congested_road->end_intersection - 'A';

    while (congested_road->num_of_vehicles > 3) {         
        congested_road->num_of_vehicles--;         
        matrix[start][end].numofvehicles--;         
        vehicles.updateRoadUsage(start, end, path_taken);      
    }

    if (congested_road->num_of_vehicles <= 3) {        
        cout << "Congestion reduced to acceptable level on road from " 
             << congested_road->start_intersection << " to " 
             << congested_road->end_intersection << endl;
    }

    // Free the path_taken memory if dynamically allocated
    delete[] path_taken;
}
