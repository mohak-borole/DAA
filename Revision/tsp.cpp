#include<iostream>
#include <bits/stdc++.h>
#include<limits.h>
using namespace std;

int final_path[10];
int visited[10];
int final_res = INT_MAX;

void copyToFinal(int curr_path[] , int size)
{
	for (int i=0; i<size; i++)
		final_path[i] = curr_path[i];
	final_path[size] = curr_path[0];
}

int firstMin(int adj[10][10], int i , int size)
{
	int min = INT_MAX;
	for (int k=0; k<size; k++)
		if (adj[i][k]<min && i != k)
			min = adj[i][k];
	return min;
}

int secondMin(int adj[10][10], int i , int size)
{
	int first = INT_MAX, second = INT_MAX;
	for (int j=0; j<size; j++)
	{
		if (i == j)
			continue;

		if (adj[i][j] <= first)
		{
			second = first;
			first = adj[i][j];
		}
		else if (adj[i][j] <= second &&
				adj[i][j] != first)
			second = adj[i][j];
	}
	return second;
}

void TSPRec(int adj[10][10], int curr_bound, int curr_weight,
			int level, int curr_path[] ,int size)
{
	// base case is whesize we have reached level size which
	// means we have covered all the nodes once
	if (level==size)
	{
		// check if there is an edge from last vertex in
		// path back to the first vertex
		if (adj[curr_path[level-1]][curr_path[0]] != 0)
		{
			// curr_res has the total weight of the
			// solution we got
			int curr_res = curr_weight +
					adj[curr_path[level-1]][curr_path[0]];

			// Update final result and final path if
			// current result is better.
			if (curr_res < final_res)
			{
				copyToFinal(curr_path , size);
				final_res = curr_res;
			}
		}
		return;
	}

	// for any other level iterate for all vertices to
	// build the search space tree recursively
	for (int i=0; i<size; i++)
	{
		// Consider next vertex if it is not same (diagonal
		// entry in adjacency matrix and not visited
		// already)
		if (adj[curr_path[level-1]][i] != 0 &&
			visited[i] == false)
		{
			int temp = curr_bound;
			curr_weight += adj[curr_path[level-1]][i];

			// different computation of curr_bound for
			// level 2 from the other levels
			if (level==1)
			curr_bound -= ((firstMin(adj, curr_path[level-1] , size) +
							firstMin(adj, i , size))/2);
			else
			curr_bound -= ((secondMin(adj, curr_path[level-1] , size) +
							firstMin(adj, i , size))/2);

			// curr_bound + curr_weight is the actual lower bound
			// for the node that we have arrived on
			// If current lower bound < final_res, we need to explore
			// the node further
			if (curr_bound + curr_weight < final_res)
			{
				curr_path[level] = i;
				visited[i] = true;

				// call TSPRec for the next level
				TSPRec(adj, curr_bound, curr_weight, level+1,
					curr_path , size);
			}

			// Else we have to prune the node by resetting
			// all changes to curr_weight and curr_bound
			curr_weight -= adj[curr_path[level-1]][i];
			curr_bound = temp;

			// Also reset the visited array
			memset(visited, false, sizeof(visited));
			for (int j=0; j<=level-1; j++)
				visited[curr_path[j]] = true;
		}
	}
}

void TSP(int adj[10][10] , int size)
{
	int curr_path[size+1];

	// Calculate initial lower bound for the root node
	// using the formula 1/2 * (sum of first min +
	// second min) for all edges.
	// Also initialize the curr_path and visited array
	int curr_bound = 0;
	memset(curr_path, -1, sizeof(curr_path));
	memset(visited, 0, sizeof(curr_path));

	// Compute initial bound
	for (int i=0; i<size; i++)
		curr_bound += (firstMin(adj, i , size) +
					secondMin(adj, i , size));

	// Rounding off the lower bound to an integer
	curr_bound = (curr_bound&1)? curr_bound/2 + 1 :
								curr_bound/2;

	// We start at vertex 1 so the first vertex
	// in curr_path[] is 0
	visited[0] = true;
	curr_path[0] = 0;

	// Call to TSPRec for curr_weight equal to
	// 0 and level 1
	TSPRec(adj, curr_bound, 0, 1, curr_path , size);
}

int main()
{
	int size = 4;
	//Adjacency matrix for the given graph
	int adj[10][10] = { {0, 10, 15, 20},
		{10, 0, 35, 25},
		{15, 35, 0, 30},
		{20, 25, 30, 0}
	};

	TSP(adj , size);

	printf("Minimum cost : %d\n", final_res);
	printf("Path Taken : ");
	for (int i=0; i<=size; i++)
		printf("%d ", final_path[i]);

	return 0;
}