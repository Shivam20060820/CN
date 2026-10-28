/*
 * Assignment 4: Distance Vector Routing Algorithm
 * This program simulates the Distance Vector Routing Algorithm
 * to compute shortest paths and minimum routing costs between nodes
 */

#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>

using namespace std;

#define INF 99999  // Represents infinity (no direct link)
#define MAX_NODES 10

class DistanceVectorRouting {
private:
    int numNodes;
    int costMatrix[MAX_NODES][MAX_NODES];           // Cost matrix for the network
    int routingTable[MAX_NODES][MAX_NODES];         // Routing table: routingTable[i][j] = cost from node i to j
    int nextHop[MAX_NODES][MAX_NODES];              // Next hop: nextHop[i][j] = next node from i to reach j

public:
    DistanceVectorRouting(int n) : numNodes(n) {
        // Initialize all matrices
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                costMatrix[i][j] = (i == j) ? 0 : INF;
                routingTable[i][j] = (i == j) ? 0 : INF;
                nextHop[i][j] = (i == j) ? i : -1;
            }
        }
    }

    // Set the cost between two nodes
    void setCost(int from, int to, int cost) {
        costMatrix[from][to] = cost;
        routingTable[from][to] = cost;
        nextHop[from][to] = to;
    }

    // Display the cost matrix
    void displayCostMatrix() {
        cout << "\n========================================" << endl;
        cout << "         INITIAL COST MATRIX" << endl;
        cout << "========================================" << endl;
        cout << "\n     ";
        for (int i = 0; i < numNodes; i++) {
            cout << "N" << i << "    ";
        }
        cout << endl;
        cout << "   " << string(numNodes * 7, '-') << endl;

        for (int i = 0; i < numNodes; i++) {
            cout << "N" << i << " | ";
            for (int j = 0; j < numNodes; j++) {
                if (costMatrix[i][j] == INF)
                    cout << setw(4) << "INF" << "  ";
                else
                    cout << setw(4) << costMatrix[i][j] << "  ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // Display routing table for all nodes
    void displayRoutingTables(string title = "ROUTING TABLES") {
        cout << "\n========================================" << endl;
        cout << "           " << title << endl;
        cout << "========================================" << endl;

        for (int i = 0; i < numNodes; i++) {
            cout << "\nRouting Table for Node N" << i << ":" << endl;
            cout << "Destination | Cost | Next Hop" << endl;
            cout << "------------|------|----------" << endl;
            for (int j = 0; j < numNodes; j++) {
                cout << "     N" << j << "     | ";
                if (routingTable[i][j] == INF)
                    cout << " INF | ";
                else
                    cout << setw(4) << routingTable[i][j] << " | ";

                if (nextHop[i][j] == -1)
                    cout << "   -" << endl;
                else
                    cout << "   N" << nextHop[i][j] << endl;
            }
        }
        cout << endl;
    }

    // Bellman-Ford algorithm for Distance Vector Routing
    bool updateRoutingTables() {
        bool updated = false;

        // For each node
        for (int i = 0; i < numNodes; i++) {
            // For each destination
            for (int j = 0; j < numNodes; j++) {
                // For each neighbor
                for (int k = 0; k < numNodes; k++) {
                    // If there's a link from i to k
                    if (costMatrix[i][k] != INF && k != i) {
                        // Calculate new cost: cost(i->k) + cost(k->j)
                        int newCost = costMatrix[i][k] + routingTable[k][j];

                        // If new cost is better, update
                        if (newCost < routingTable[i][j]) {
                            routingTable[i][j] = newCost;
                            nextHop[i][j] = k;  // Route through k
                            updated = true;
                        }
                    }
                }
            }
        }
        return updated;
    }

    // Run the Distance Vector Routing algorithm
    void runAlgorithm() {
        cout << "\n========================================" << endl;
        cout << "  RUNNING DISTANCE VECTOR ALGORITHM" << endl;
        cout << "========================================" << endl;

        displayCostMatrix();
        displayRoutingTables("INITIAL ROUTING TABLES");

        int iteration = 1;
        bool updated = true;

        // Keep updating until convergence
        while (updated) {
            cout << "\n--- Iteration " << iteration << " ---" << endl;
            updated = updateRoutingTables();

            if (updated) {
                cout << "Routing tables updated in iteration " << iteration << endl;
            } else {
                cout << "No updates in iteration " << iteration << " - Algorithm converged!" << endl;
            }
            iteration++;

            // Prevent infinite loops (shouldn't happen in valid networks)
            if (iteration > numNodes * numNodes) {
                cout << "\nWarning: Maximum iterations reached. Possible routing loop!" << endl;
                break;
            }
        }

        displayRoutingTables("FINAL ROUTING TABLES");
    }

    // Display shortest path between two nodes
    void displayShortestPath(int source, int destination) {
        cout << "\n========================================" << endl;
        cout << "          SHORTEST PATH RESULT" << endl;
        cout << "========================================" << endl;

        if (routingTable[source][destination] == INF) {
            cout << "\nNo path exists from N" << source << " to N" << destination << endl;
            return;
        }

        cout << "\nFrom Node N" << source << " to Node N" << destination << ":" << endl;
        cout << "Minimum Cost: " << routingTable[source][destination] << endl;
        cout << "Path: N" << source;

        int current = source;
        while (current != destination) {
            current = nextHop[current][destination];
            cout << " -> N" << current;
        }
        cout << endl << endl;
    }

    // Display all shortest paths from a source node
    void displayAllPaths(int source) {
        cout << "\n========================================" << endl;
        cout << "    ALL SHORTEST PATHS FROM N" << source << endl;
        cout << "========================================" << endl;

        for (int dest = 0; dest < numNodes; dest++) {
            if (dest != source) {
                displayShortestPath(source, dest);
            }
        }
    }
};

int main() {
    int numNodes, numEdges;
    int choice;

    cout << "\n**************************************" << endl;
    cout << "  DISTANCE VECTOR ROUTING SIMULATOR" << endl;
    cout << "**************************************" << endl;

    cout << "\nEnter number of nodes in the network: ";
    cin >> numNodes;

    if (numNodes <= 0 || numNodes > MAX_NODES) {
        cout << "Invalid number of nodes! Must be between 1 and " << MAX_NODES << endl;
        return 1;
    }

    DistanceVectorRouting dvr(numNodes);

    cout << "\nChoose input method:" << endl;
    cout << "1. Manual input" << endl;
    cout << "2. Use default example network" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "\nEnter number of edges (links): ";
        cin >> numEdges;

        cout << "\nEnter edges in format: from_node to_node cost" << endl;
        cout << "(Node numbers should be from 0 to " << (numNodes - 1) << ")" << endl;
        cout << "(Use " << INF << " or any large number for no direct connection)" << endl;

        for (int i = 0; i < numEdges; i++) {
            int from, to, cost;
            cout << "Edge " << (i + 1) << ": ";
            cin >> from >> to >> cost;

            if (from >= 0 && from < numNodes && to >= 0 && to < numNodes) {
                dvr.setCost(from, to, cost);
                // For undirected graph, set both directions
                dvr.setCost(to, from, cost);
            } else {
                cout << "Invalid node numbers! Skipping this edge." << endl;
                i--;
            }
        }
    } else {
        // Default example network (4 nodes)
        cout << "\nUsing default example network with 4 nodes..." << endl;

        // Example topology:
        // N0 -- 1 -- N1
        // |          |
        // 4          2
        // |          |
        // N3 -- 1 -- N2

        dvr.setCost(0, 1, 1);
        dvr.setCost(1, 0, 1);

        dvr.setCost(1, 2, 2);
        dvr.setCost(2, 1, 2);

        dvr.setCost(2, 3, 1);
        dvr.setCost(3, 2, 1);

        dvr.setCost(3, 0, 4);
        dvr.setCost(0, 3, 4);
    }

    // Run the Distance Vector Routing algorithm
    dvr.runAlgorithm();

    // Display shortest paths
    int source, destination;
    char continueChoice;

    do {
        cout << "\nEnter source node (0 to " << (numNodes - 1) << "): ";
        cin >> source;

        if (source < 0 || source >= numNodes) {
            cout << "Invalid source node!" << endl;
            continue;
        }

        cout << "Options:" << endl;
        cout << "1. Show path to specific destination" << endl;
        cout << "2. Show all paths from source" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter destination node (0 to " << (numNodes - 1) << "): ";
            cin >> destination;

            if (destination >= 0 && destination < numNodes) {
                dvr.displayShortestPath(source, destination);
            } else {
                cout << "Invalid destination node!" << endl;
            }
        } else {
            dvr.displayAllPaths(source);
        }

        cout << "\nDo you want to check another path? (y/n): ";
        cin >> continueChoice;

    } while (continueChoice == 'y' || continueChoice == 'Y');

    cout << "\n**************************************" << endl;
    cout << "     Program completed successfully!" << endl;
    cout << "**************************************" << endl;

    return 0;
}
