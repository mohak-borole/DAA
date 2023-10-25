#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;

const int MAX = 10;

int n;
int graph[MAX][MAX];
int finalPath[MAX]; // To store the final Hamiltonian cycle
int finalCost = INT_MAX; // To store the minimum cost of the Hamiltonian cycle

// Function to copy the current path to the final path
void copyToFinalPath(int currentPath[]) {
    for (int i = 0; i < n; i++)
        finalPath[i] = currentPath[i];
    finalPath[n] = currentPath[0]; // Completing the cycle by going back to the starting city
}

// Function to find the minimum edge cost from vertex i
int firstMin(int i) {
    int min = INT_MAX;
    for (int k = 0; k < n; k++)
        if (graph[i][k] < min && i != k)
            min = graph[i][k];
    return min;
}

// Function to find the second minimum edge cost from vertex i
int secondMin(int i) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < n; j++) {
        if (i == j)
            continue;
        if (graph[i][j] <= first) {
            second = first;
            first = graph[i][j];
        } else if (graph[i][j] <= second && graph[i][j] != first) {
            second = graph[i][j];
        }
    }
    return second;
}

// Recursive function to solve the TSP problem
void TSPRec(int curr_bound, int curr_weight, int level, int currentPath[]) {
    // Base case: if all cities are visited
    if (level == n) {
        if (graph[currentPath[level - 1]][currentPath[0]] != 0) {
            // Update the final path and cost if a better solution is found
            int curr_cost = curr_weight + graph[currentPath[level - 1]][currentPath[0]];
            if (curr_cost < finalCost) {
                copyToFinalPath(currentPath);
                finalCost = curr_cost;
            }
        }
        return;
    }

    // Explore each unvisited city
    for (int i = 0; i < n; i++) {
        if (graph[currentPath[level - 1]][i] != 0 &&
            find(currentPath, currentPath + level, i) == currentPath + level) {
            int temp = curr_bound;
            curr_weight += graph[currentPath[level - 1]][i];

            // Update the current bound based on the selected edges
            if (level == 1)
                curr_bound -= (firstMin(currentPath[level - 1]) + firstMin(i)) / 2;
            else
                curr_bound -= (secondMin(currentPath[level - 1]) + firstMin(i)) / 2;

            // If the current bound + current weight is less than the final cost,
            // explore the node further
            if (curr_bound + curr_weight < finalCost) {
                currentPath[level] = i;
                TSPRec(curr_bound, curr_weight, level + 1, currentPath);
            }

            // Backtrack: undo the changes
            curr_weight -= graph[currentPath[level - 1]][i];
            curr_bound = temp;

            // Reset the path for backtracking
            fill(currentPath + level, currentPath + n, -1);
        }
    }
}

bool visited[MAX];

// Function to initialize and start the TSP solution
void TSP() {
    int currentPath[MAX];
    int curr_bound = 0;
    fill(currentPath, currentPath + MAX, -1);
    fill(visited, visited + MAX, false);

    // Calculate the initial bound
    for (int i = 0; i < n; i++)
        curr_bound += (firstMin(i) + secondMin(i));

    curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;

    currentPath[0] = 0; // Start from city 0
    visited[0] = true;
    TSPRec(curr_bound, 0, 1, currentPath);
}

int main() {
    cout << "Enter the number of cities: ";
    cin >> n;

    cout << "Enter the adjacency matrix representing the graph:" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];

    TSP();

    cout << "Optimal Path: ";
    for (int i = 0; i <= n; i++)
        cout << finalPath[i] << " ";
    cout << endl;

    cout << "Minimum Cost: " << finalCost << endl;

    return 0;
}


/*OUTPUT
./a.out 
Enter the number of cities: 4
Enter the adjacency matrix representing the graph:
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0
Optimal Path: 0 1 3 2 0 
Minimum Cost: 80
*/