#pragma once
#include<utility>
#include "KruskalHeap.h"
#include "Graph.h"

class Kruskal{
	
	int  numEdges;


public:
	KruskalHeap *maxHeap;
	Kruskal(int  Edges);
	
	vertex* maxTree[nNodes];
	
	int lastElement = 0;
	int color[nNodes];
	int parent[nNodes];
	int rank[nNodes];
	int daddy[nNodes];
	int capacityInTree[nNodes];


	// Function to find the Maximum Spanning Tree using Kruskal's
	void maxBandwidth(vertex* adj[], int s, int t);

	// For collecting and Sorting the edges
	void collectAndSort(vertex* adj[]);
	void collect(vertex* adj[]);
	void addPair(int node1, int node2, int weight);
	vertex* initNode(int node, int weight);
	
	// For disjoint sets
	int find(int node);
	void unionFuc(int r1, int r2);
	void makeSet(int node);

	// To find the maximum bandwidth in the maximum spanning tree	
	void findMaxAndPath(int s, int t);
	void bfs(int node);

};

