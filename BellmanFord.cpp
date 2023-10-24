#include<iostream>
using namespace std;

void printArr(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

struct Edge
{
	int src , dest , weight;
};

class Graph
{
	int Vertices , Edges;
	Edge* edge;
	public:
		Graph* createGraph(int V , int E);
		void BellmanFord(Graph* graph , int src);
};

Graph* Graph::createGraph(int V, int E)
{
	Graph* graph = new Graph;
	graph->Vertices = V;
	graph->Edges = E;
	graph->edge = new Edge[E];
	
	for(int i = 0 ; i < graph->Edges ; i++)
	{
		printf("Enter the source of edge %d: " , i+1);
		scanf("%d" , &graph->edge[i].src);
		printf("Enter the destination of edge %d: " , i+1);
		scanf("%d" , &graph->edge[i].dest);
		printf("Enter the weight of edge %d: " , i+1);
		scanf("%d" , &graph->edge[i].weight);
		printf("\n");
	}
	printf("Graph created successfully!!\n");
	return graph;
}

void Graph::BellmanFord(Graph* graph , int src)
{
	int V = graph->Vertices;
	int E = graph->Edges;
	int distance[V];
	
	for(int i = 0 ; i <  V ; i++)
		distance[i] = 999;
	
	distance[src-1] = 0;
	
	for(int i = 0 ; i < V ; i++)
	{
		for(int j = 0 ; j < E ; j++)
		{
			int u = graph->edge[j].src;
			int v = graph->edge[j].dest;
			int wt = graph->edge[j].weight;
			if((distance[u] != 999) && (distance[u] + wt < distance[v]))
			{
				distance[v] = distance[u] + wt;
			}	
		}
	}  	
	
	for(int j = 0 ; j < E ; j++)
	{
		int u = graph->edge[j].src;
		int v = graph->edge[j].dest;
		int wt = graph->edge[j].weight;
		if((distance[u] != 999) && (distance[u] + wt < distance[v]))
		{
			printf("\n This Graph cannot be solved by \"BELLMAN-FORD Algorithnm!!\"\n");
			return;
		}	
	}
	
	printArr(distance , V);
	
	return;
}

int main()
{
	int V , E;
	printf("Enter the number of vertices : ");
	scanf("%d" , &V);
	printf("Enter the number of edges : ");
	scanf("%d" , &E);
	
	Graph G;
	Graph* inputGraph = G.createGraph(V , E);
	
	G.BellmanFord(inputGraph , 1);
	return 0;
}
