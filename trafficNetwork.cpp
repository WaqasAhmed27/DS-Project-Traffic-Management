#include "trafficNetwork.h"

EV_vehicles::EV_vehicles()
{
    id = "";
    status = "";
}

EV_vehicles::EV_vehicles(string id, string status)
{
    this->id = id;
    this->status = status;
}

EV_vehicles::~EV_vehicles()
{

}
string EV_vehicles::getid()
{
    return id;
}

string EV_vehicles::getstatus()
{
    return status;
}


// Constructor for node
node::node() : distance(0), intersection(' ') {}

node::node(int distance, char intersection, string status)
{
    this->distance = distance;
    this->intersection = intersection;
    this->status = status;
    this->numofvehicles=0;

}

// Constructor for TrafficNetwork
TrafficNetwork::TrafficNetwork(int num_vertices)
{
    this->num_vertices = num_vertices;
    matrix = new node*[num_vertices];

    for (int i = 0; i < num_vertices; i++)
    {
        matrix[i] = new node[num_vertices];
        for (int j = 0; j < num_vertices; j++)
        {
            matrix[i][j].distance = 0;
            matrix[i][j].intersection = ' ';
            matrix[i][j].status = "Clear";
            matrix[i][j].numofvehicles = 0;
        }
    }
}

// Destructor for TrafficNetwork
TrafficNetwork::~TrafficNetwork()
{
    for (int i = 0; i < num_vertices; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

//Function to map the roads
void TrafficNetwork::Mapping_Roads(string csv)
{
    ifstream file(csv);
    string line;
    char start_intersection;
    char end_intersection;
    int distance;

    if (!file.is_open())
    {
        cerr << "Error: Unable to open file " << csv << endl;
        return;
    }

    getline(file, line); // Skip header line
    while (getline(file, line))
    {
        int commapos = line.find(',');
        if (commapos != string::npos)
        {
            start_intersection = line[0];
        }

        line = line.substr(commapos + 1);
        commapos = line.find(',');
        if (commapos != string::npos)
        {
            end_intersection = line[0];
        }

        line = line.substr(commapos + 1);
        distance = stoi(line);

        int start_index = start_intersection - 'A';
        int end_index = end_intersection - 'A';

        matrix[start_index][end_index].distance = distance;
        matrix[start_index][end_index].intersection = end_intersection;
        matrix[start_index][end_index].status = "open";
    }

    file.close();
}

// Function to display the road network
void TrafficNetwork::Display()
{
    for (int i = 0; i < num_vertices; i++)
    {
        cout << char(i + 'A') << " -> ";
        for (int j = 0; j < num_vertices; j++)
        {
            if (matrix[i][j].distance != 0)
            {
                cout << " (" << matrix[i][j].intersection << "," << matrix[i][j].distance << ") ";
            }
        }
        cout << endl;
    }
}

//Getter function for matrix
node** TrafficNetwork::getmatrix()
{
    return matrix;
}

// Function to add a new road
void TrafficNetwork::addnewroad(char start_intersection, char end_intersection, int distance)
{
    int start_index = start_intersection - 'A';
    int end_index = end_intersection - 'A';

    matrix[start_index][end_index].distance = distance;
    matrix[start_index][end_index].intersection = end_intersection;
}

// Function to remove a road
void TrafficNetwork::removeRoad(char start_intersection, char end_intersection)
{
    int start_index = start_intersection - 'A';
    int end_index = end_intersection - 'A';

    matrix[start_index][end_index].distance = 0;
    matrix[start_index][end_index].intersection = ' ';
}
