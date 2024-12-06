#include "congestion.h"

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
            if (matrix[i][j].numofvehicles > 0) {
                cout << char('A' + i) << " -> " << char('A' + j)
                          << " : " << matrix[i][j].numofvehicles << " vehicles" << endl;
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

// Constructor
heapNode::heapNode(int num_of_vehicles) 
{
    this->num_of_vehicles = num_of_vehicles;
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

    if (parent != nullptr && parent->num_of_vehicles > node->num_of_vehicles)
    {
        swap(parent->num_of_vehicles, node->num_of_vehicles);
        heapifyup(parent);
    }
}


// Function to insert a new node into the heap while maintaining the min heap property and structure property
void MinHeap::insert(int num_of_vehicles) 
{
    if (root == nullptr) 
    {
        root = new heapNode(num_of_vehicles);
    } 
    else 
    {
        int no_of_nodes = countnodes(root);// Count the number of nodes in the heap
        heapNode* point = findnode(root, no_of_nodes - 1); //Finding the point at which the new node is to be inserted

        // Insert the new node as the left child if the left child is empty and if not insert as the right child
        if (point->left == nullptr) 
        {
            point->left = new heapNode(num_of_vehicles);
            heapifyup(point->left);
        }             
        else             
        {
            point->right = new heapNode(num_of_vehicles);
            heapifyup(point->right);
        }
         
    }
}

// Function to construct the min heap from the given num of vehicles on each road in the matrix 
void MinHeap::custructMinHeap(node** matrix, int num_vertices)
{
    for(int i =0; i<num_vertices; i++)
    {
        for(int j =0; j<num_vertices; j++)
        {
            if(matrix[i][j].numofvehicles > 0)
            {
                insert(matrix[i][j].numofvehicles);
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
