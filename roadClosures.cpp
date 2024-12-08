#include "roadClosures.h"

road_closures::road_closures(node** matrix, int num_vertices) 
{
    this->matrix = matrix;
    this->num_vertices = num_vertices;
}

void road_closures::block_road(char start_intersection, char end_intersection)
{
    int start_index = start_intersection - 'A';
    int end_index = end_intersection - 'A';
    
    if(matrix[start_index][end_index].distance == 0)
    {
        cout<<"Error: Road does not exist between "<<start_intersection<<" and "<<end_intersection<<endl;
        return;
    }

    if(matrix[start_index][end_index].status == "Blocked")
    {
        cout<<"Error: Road is already blocked"<<endl;
        return;
    }  

    else
    {
        cout<<"Blocking road from "<<start_intersection<<" to "<<end_intersection<<endl;
         matrix[start_index][end_index].status = "Blocked";
    }
}

void road_closures::clear_road(char start_intersection, char end_intersection)
{
    int start_index = start_intersection - 'A';
    int end_index = end_intersection - 'A';

    if(matrix[start_index][end_index].status == "Clear")
    {
        cout<<"Error: Road is already clear"<<endl;
        return;
    }
    else
    {
        cout<<"Clearing road from "<<start_intersection<<" to "<<end_intersection<<endl;
        matrix[start_index][end_index].status = "Clear";
    }
   
}

void road_closures::processRoadClosures(string csv)
{
    ifstream file(csv);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << csv << endl;
        return;
    }

    getline(file, line); // Skip the header
    while (getline(file, line)) 
    {
        istringstream stream(line);
        string status, start, end;
        getline(stream, start, ',');
        getline(stream, end, ',');
        getline(stream, status, ',');

        char start_intersection = start[0];
        char end_intersection = end[0];

        int start_index = start_intersection - 'A';
        int end_index = end_intersection - 'A';

        matrix[start_index][end_index].status = status;
    }


    file.close();
}

void road_closures::display_blocked_roads()
{
    cout << "\nRoad Closures:" << endl;
    cout << "Start -> End -> Status" << endl;
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            if(matrix[i][j].status == "Blocked" && matrix[i][j].distance != 0)
                cout << char(i + 'A') << " -> " << char(j + 'A') << " -> " << matrix[i][j].status << endl;
        }
    }
}

void road_closures::display_underrepair_roads()
{
    cout << "\nUnder Repair Roads" << endl;
    cout << "Start -> End -> Status" << endl;
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            if(matrix[i][j].status == "Under Repair" && matrix[i][j].distance != 0)
                cout << char(i + 'A') << " -> " << char(j + 'A') << " -> " << matrix[i][j].status << endl;
        }
    }
}

void road_closures::display_clear_roads()
{
    cout<<"\nClear Roads:"<<endl;
    cout << "Start -> End -> Status" << endl;
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            if(matrix[i][j].status == "Clear" && matrix[i][j].distance != 0)
                cout << char(i + 'A') << " -> " << char(j + 'A') << " -> " << matrix[i][j].status << endl;
        }
    }
}

void road_closures::display_all_roads()
{
    cout << "\nRoads Status:" << endl;
    cout << "Start -> End -> Status" << endl;
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            if(matrix[i][j].distance != 0 && matrix[i][j].status != "open")
                cout << char(i + 'A') << " -> " << char(j + 'A') << " -> " << matrix[i][j].status << endl;
        }
    }
}

bool road_closures::is_path_blocked(char start_intersection, char end_intersection) {
    int start_index = start_intersection - 'A';
    int end_index = end_intersection - 'A';

    if (start_index < 0 || start_index >= num_vertices ||  end_index < 0 || end_index >= num_vertices) {
        cout << "Error: Invalid intersections provided." << endl;
        return false; // Returning false if invalid indices are provided
    }

    // Check the status of the path
    if (matrix[start_index][end_index].status == "Blocked") 
    {
        return true; // Path is blocked
    }

    return false; // Path is not blocked
}


bool road_closures::is_path_underrepair(char start_intersection, char end_intersection) {
    int start_index = start_intersection - 'A';
    int end_index = end_intersection - 'A';

    //input validation
    if (start_index < 0 || start_index >= num_vertices ||  end_index < 0 || end_index >= num_vertices) {
        cout << "Error: Invalid intersections provided." << endl;
        return false; // Returning false if invalid indices are provided
    }

    // Check the status of the path
    if(matrix[start_index][end_index].status == "Under Repair")
    {
        return true; // Path is under repair
    }

    return false; // Path is not under repair
}