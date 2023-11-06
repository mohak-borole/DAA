#include<iostream>
#include<climits>

// Define infinity as a large value
int inf = 9999;

using namespace std;

class TSP {
    int cities;
    int edges;
    int adj[50][50], rm[50][50], temp[50][50];

public:
    // Constructor to initialize the TSP instance
    TSP() {
        cout << "Enter the number of cities: ";
        cin >> cities;

        // Initialize adjacency matrix with infinity values
        for (int i = 0; i < cities; i++) {
            for (int j = 0; j < cities; j++) {
                adj[i][j] = inf;
            }
        }

        cout << "\nEnter Number of edges" << endl;
        cin >> edges;

        // Input the edges and their weights
        for (int i = 0; i < edges; i++) {
            int u, v, wt;
            cout << "\nEnter Source Vertex" << endl;
            cin >> u;
            cout << "\nEnter Destination Vertex" << endl;
            cin >> v;
            cout << "\nEnter Weight of this edge" << endl;
            cin >> wt;
            adj[u][v] = wt;
        }
    }

    // Function to perform the Traveling Salesman Problem calculation
    void TSPCall();

    // Function for row and column minimization
    int minimization(int inf, int c);

    // Function to check if an element is present in an array
    int check(int arr[], int size, int ch);

    // Function to make certain elements of a matrix as infinity
    void make_inf(int arr[], int size, int inf, int col);
};

void TSP::TSPCall() {
    // Row & column minimization
    int cost = 0;
    for (int i = 0; i < cities; i++) {
        int min = adj[i][0];
        // Find the minimum element in each row
        for (int j = 1; j < cities; j++) {
            if (min > adj[i][j]) {
                min = adj[i][j];
            }
        }
        // Update cost and minimize the row
        cost = cost + min;
        for (int k = 0; k < cities; k++) {
            if (adj[i][k] != inf) {
                rm[i][k] = adj[i][k] - min;
            } else {
                rm[i][k] = inf;
            }
        }
    }

    // Repeat the process for columns
    for (int i = 0; i < cities; i++) {
        int min = rm[0][i];
        for (int j = 1; j < cities; j++) {
            if (min > rm[j][i]) {
                min = rm[j][i];
            }
        }
        cost = cost + min;
        for (int k = 0; k < cities; k++) {
            if (rm[k][i] != inf) {
                rm[k][i] = rm[k][i] - min;
            } else {
                rm[k][i] = inf;
            }
        }
    }

    // Array to keep track of visited vertices
    int visited[cities];
    int size = 0;
    visited[size] = 0;
    size++;
    int ans = cost;

    // Continue until all cities are visited
    while (true) {
        int min = INT_MAX;
        int min_ind = 0;

        // Find the next city to visit with the minimum cost
        for (int j = 1; j < cities; j++) {
            int ch = check(visited, size, j);
            if (ch == 0) {
                int c1 = 0;
                for (int p = 0; p < cities; p++) {
                    for (int q = 0; q < cities; q++) {
                        temp[p][q] = rm[p][q];
                    }
                }
                make_inf(visited, size, inf, j);
                c1 = minimization(inf, cost);
                c1 = c1 + rm[visited[size - 1]][j];
                if (c1 < min) {
                    min = c1;
                    min_ind = j;
                }
            }
        }

        // Update matrices based on the selected city
        for (int p = 0; p < cities; p++) {
            for (int q = 0; q < cities; q++) {
                temp[p][q] = rm[p][q];
            }
        }
        make_inf(visited, size, inf, min_ind);
        int tpp = minimization(inf, cost);
        for (int p = 0; p < cities; p++) {
            for (int q = 0; q < cities; q++) {
                rm[p][q] = temp[p][q];
            }
        }

        // Update visited array and cost
        visited[size] = min_ind;
        size++;
        cost = min;

        // Break if all cities are visited
        if (size == cities) {
            break;
        }
    }

    // Output the result
    cout << "\nPath :-" << endl;
    for (int k = 0; k < size; k++) {
        cout << visited[k] << " --> ";
    }
    cout << visited[0] << endl;
    cout << "\nMinimum cost " << cost << endl;
}

int TSP::minimization(int inf, int c) {
    int cost = c;
    for (int i = 0; i < cities; i++) {
        int min = temp[i][0];
        for (int j = 1; j < cities; j++) {
            if (min > temp[i][j]) {
                min = temp[i][j];
            }
        }
        if (min != inf) {
            cost = cost + min;
            for (int k = 0; k < cities; k++) {
                if (temp[i][k] != inf) {
                    temp[i][k] = temp[i][k] - min;
                } else {
                    temp[i][k] = inf;
                }
            }
        }
    }

    for (int i = 0; i < cities; i++) {
        int min = temp[0][i];
        for (int j = 1; j < cities; j++) {
            if (min > temp[j][i]) {
                min = temp[j][i];
            }
        }
        if (min != inf) {
            cost = cost + min;
            for (int k = 0; k < cities; k++) {
                if (temp[k][i] != inf) {
                    temp[k][i] = temp[k][i] - min;
                } else {
                    temp[k][i] = inf;
                }
            }
        }
    }
    return cost;
}

int TSP::check(int arr[], int size, int ch) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == ch) {
            return 1;
        }
    }
    return 0;
}

void TSP::make_inf(int arr[], int size, int inf, int col) {
    for (int i = 0; i < size; i++) {
        int r = arr[i];
        for (int p = 0; p < cities; p++) {
            temp[r][p] = inf;
        }
    }

    for (int i = 0; i < cities; i++) {
        temp[i][col] = inf;
    }

    int first = arr[0];
    temp[col][first] = inf;
    for (int i = 1; i < size; i++) {
        int t = arr[i];
        temp[t][first] = inf;
    }
}

int main() {
    // Create an instance of the TSP class
    TSP tsp;

    // Call the TSP calculation function
    tsp.TSPCall();

    return 0;
}
