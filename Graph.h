#pragma once
#include<queue>


const int nNodes = 5000;

// Struct to create the Neigbors of each node
typedef struct node {

	int id;
	int weight;
	node* next;

}vertex;

class Graph{

	bool type;
	int seed;
public:
	// Constructor
	Graph(bool type, int seed);
	int nEdges;
	
	// Adjecency List
	vertex *adj[nNodes];

	// Use During the Graph construction
	int maxNeighbors; // Depends on the type of the graph
	int numNeighbors[nNodes];
	bool connections[nNodes];
	
	// Add the edge on the graph
	void addPair(int node1, int node2, int weight);
	vertex* initNode(int node, int weight);

	// --- BFS
	int color[nNodes];
	void bfs(int node);

	// --- To check if the graph is connected
	void isConnected();

	// --- Print the graph (Recomendend only for graphs with small number of vertices)
	void printGraph();
	void printNeighbors(int node);

};

