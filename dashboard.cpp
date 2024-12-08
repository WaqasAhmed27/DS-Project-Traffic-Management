#include "dashboard.h"
#include <iostream>
#include <fstream>

void Dashboard::Simulate() {
    const int NUM_VERTICES = 26;
    TrafficNetwork network(NUM_VERTICES);
    network.Mapping_Roads("road_network.csv");

    TrafficSignal signals;
    signals.readTrafficSignalData("traffic_signals.csv");

    road_closures closures(network.getmatrix(), NUM_VERTICES);
    closures.processRoadClosures("road_closures.csv");

    EVHandling ev(NUM_VERTICES, network.getmatrix());
    Vehicles vehicles(NUM_VERTICES, network.getmatrix());
    vehicles.processVehicles("vehicles.csv");

    MinHeap heap;
    heap.constructMinHeap(network.getmatrix(), NUM_VERTICES);
            

    int choice = 0;
    while (choice != 13) 
    {
        cout << "\nWELCOME TO TRAFFIC MANAGEMENT SYSTEM\n";
        cout << "------------------------------------\n";
        cout << "SIMULATION DASHBOARD\n";
        cout << "1. Display Road Network\n";
        cout << "2. Display Traffic Signal Timings\n";
        cout << "3. Adjust Traffic Signal Timings\n";
        cout << "4. Display Road Closures\n";
        cout << "5. Handle Emergency Vehicle Routing\n";
        cout << "6. Block Road Due To Accident\n";
        cout << "7. Simulate Vehicle Routing\n";
        cout << "8. Display Most Congested Road\n";
        cout << "9. Display Shortest Path Between Two Intersections\n";
        cout << "10. Display Number Of Vehicles On Each Road\n";
        cout << "11. Display Average Travel Time Per Vehicle\n";
        cout<<"12. Reduce congestion\n";
        cout << "13. Exit\n";
        cout<<"Enter Choice: ";
        cin >> choice;

        if (choice == 13) 
        {
            //quit
            cout << "Exiting...\n";
            break;
        } 
        else if (choice == 1) 
        {
            cout << "\nRoad Network:\n";
            network.Display();
        }
        else if (choice == 2) 
        {
            signals.displayGreenTimes(0, network);
        } 
        else if (choice == 3) 
        {
            char id;
            int time;
            cout << "Enter Intersection ID: ";
            cin >> id;
            if(id >= 'a' && id <= 'z')
            {
                id -= 32;
            }
            else if(id < 'A' || id > 'Z')
            {
                cout << "Invalid Intersection ID\n";
                continue;
            }

            cout << "New timing (in seconds): ";
            cin >> time;

            if (time <= 0) 
            {
                cout << "Invalid time entered\n";
                continue;
            } 
            else 
            {
                signals.OverrideTiming(time, network, id);
            }
        } 
        else if (choice == 4) 
        {
            cout << "Blocked Roads:\n";
            closures.display_blocked_roads();
        } 
        else if (choice == 5) 
        {
            char start, end;
            cout << "Enter Start And End Intersection For Emergency Vehicles\n";
            cout << "Start: ";
            cin >> start;
            if(start >= 'a' && start <= 'z')
            {
                start -= 32;
            }
            else if(start < 'A' || start > 'Z')
            {
                cout << "Invalid Start Intersection ID\n";
                continue;
            }
            cout << "End: ";
            cin >> end;
            if(end >= 'a' && end <= 'z')
            {
                end -= 32;
            }
            if(end < 'A' || end > 'Z')
            {
                cout << "Invalid End Intersection ID\n";
                continue;
            }
            int start_index = start - 'A';
            int end_index = end - 'A';
            int pathTakenEV[NUM_VERTICES];
            ev.findShortestPathforEV(start_index, end_index, pathTakenEV, closures);
            cout << "Shortest Path For EV From Intersection " << char(start_index + 'A') << " to Intersection " << char(end_index + 'A') << ":\n";
            ev.printPathforEV(pathTakenEV, start_index, end_index);
        } 
        else if (choice == 6) 
        {
            char start, end;
            cout << "Enter Start And End Intersection For Road Closure\n";
            cout << "Start: ";
            cin >> start;
            if(start >= 'a' && start <= 'z')
            {
                start -= 32;
            }
            if(start < 'A' || start > 'Z')
            {
                cout << "Invalid Start Intersection ID\n";
                continue;
            }
            cout << "End: ";
            cin >> end;
            if(end >= 'a' && end <= 'z')
            {
                end -= 32;
            }
            if(end < 'A' || end > 'Z')
            {
                cout << "Invalid End Intersection ID\n";
                continue;
            }
            closures.block_road(start, end);
        } 
        else if (choice == 7) 
        {
            char start, end;
            cout << "Enter Start And End Intersection For Vehicle Routing\n";
            cout << "Start: ";
            cin >> start;
            if(start >= 'a' && start <= 'z')
            {
                start -= 32;
            }
            if(start < 'A' || start > 'Z')
            {
                cout << "Invalid Start Intersection ID\n";
                continue;
            }
            cout << "End: ";
            cin >> end;
            if(end >= 'a' && end <= 'z')
            {
                end -= 32;
            }
            if(end < 'A' || end > 'Z')
            {
                cout << "Invalid End Intersection ID\n";
                continue;
            }
            vehicles.findAllPaths(start, end, closures);
        } 
        else if (choice == 8) 
        {
            heapNode* mostCongestedRoad = heap.FindMostCongestedRoad();
        } 
        else if (choice == 9) 
        {
            char start, end;
            cout << "Enter Start And End Intersection For Shortest Path\n";
            cout << "Start: ";
            cin >> start;
            if(start >= 'a' && start <= 'z')
            {
                start -= 32;
            }
            if(start < 'A' || start > 'Z')
            {
                cout << "Invalid Start Intersection ID\n";
                continue;
            }
            cout << "End: ";
            cin >> end;
            if(end >= 'a' && end <= 'z')
            {
                end -= 32;
            }
            if(end < 'A' || end > 'Z')
            {
                cout << "Invalid End Intersection ID\n";
                continue;
            }
            int start_index = start - 'A';
            int end_index = end - 'A';
            int pathTaken[NUM_VERTICES];
            vehicles.findShortestPathDijkstra(start_index, end_index, pathTaken, closures);
            cout << "Path " << char(start_index + 'A') << " to " << char(end_index + 'A') << ": ";
            vehicles.printPath(pathTaken, start_index, end_index);
        } 
        else if (choice == 10) 
        {
            vehicles.printRoadUsage();
        } 
        else if (choice == 11) 
        {
            cout<<"Number of vehicles on each road: "<<endl;
            vehicles.averageTravelTimePerVehicle(NUM_VERTICES, network.getmatrix());
        }
        else if(choice == 12)
        {
            court << "Average Travel Time Per Vehicle: "<<endl;
            heap.reduceCongestion(heap.FindMostCongestedRoad(), network.getmatrix(), NUM_VERTICES, closures, vehicles);   
        } 
        else 
        {
            cout << "Invalid Choice\n";
        }
    }
}
