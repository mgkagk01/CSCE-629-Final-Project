#include "Kruskal.h"
#include<iostream>
#include<queue>
#include<chrono>
Kruskal::Kruskal(int Edges) {
	numEdges = Edges;

	maxHeap = new KruskalHeap(Edges);
	for (size_t i = 0; i < nNodes; i++){
		color[i] =0;
		parent[i] = -1;
		rank[i] = 0;
		maxTree[i] = NULL;
		daddy[i] = -1;
		capacityInTree[i] = 0;
	}
}

void Kruskal::maxBandwidth(vertex* adj[], int s, int t) {

	// Step 1: Collect and Sort the edges
	collectAndSort(adj);

	
	// Step 2: Make Set
	for (size_t i = 0; i < nNodes; i++)
		makeSet(i);
	
	// Step 3: For all edges
	int pos = 0;
	int e;
	int r1, r2;
	for (int i = 0; i < numEdges; i++) {

		// Step 3.1: Pick the edge with the largest weight
		e = maxHeap->sortedArray[pos].weight;

		// Step 3.2:  Find the roots of the two vertices connected using e
		r1 = find(maxHeap->sortedArray[pos].nodes.first);
		r2 = find(maxHeap->sortedArray[pos].nodes.second);

		// Step 3.3: Check if the nodes are in the same tree, if not => connect
		if (r1 != r2) {
			unionFuc(r1, r2);
			addPair(maxHeap->sortedArray[pos].nodes.first, maxHeap->sortedArray[pos].nodes.second, maxHeap->sortedArray[pos].weight);
		}

		pos++;
	}
	
	// Step 4: Find the maximum Bandwidth and the path
	findMaxAndPath(s, t);

	
}

void Kruskal::collectAndSort(vertex* adj[]) {

	
	// Step 1: Collect, use BFS to collect the edges of the graph
	auto start = std::chrono::high_resolution_clock::now();
	collect(adj);
	auto end = std::chrono::high_resolution_clock::now();
	//std::cout << "\nCollect Delete Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	// Step 2: Delete duplicates
	maxHeap->deleteDuplicates();

	// Step 3: sort Edges
	start = std::chrono::high_resolution_clock::now();
 	maxHeap->heapSort();
	end = std::chrono::high_resolution_clock::now();
	//std::cout << "\nSort Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();


}


void Kruskal::collect(vertex* adj[]) {

	
	// Initialize the values to zero
	for (size_t i = 0; i < nNodes; i++) 
		color[i] = 0;
	

	// Step 1: Create a queue and push node to queue
	std::queue<int> q;
	q.push(0);

	// Step 2: set the value of the node to be black
	color[0] = 2;

	int u;
	// Iterate
	while (!q.empty()) {
		u = q.front();
		q.pop();


		vertex* temp = adj[u];
		while (temp != NULL) {

			// Add this edge to the array
			maxHeap->insertEdge(temp->id, u, temp->weight);

			if (color[temp->id] == 0){
				q.push(temp->id);
				color[temp->id] = 2;
			}
			temp = temp->next;
		}

	}

}

void Kruskal::addPair(int node1, int node2, int weight) {

	// Initialize nodes
	vertex* v1 = initNode(node1, weight);
	vertex* v2 = initNode(node2, weight);

	//Connect node1 -> node2
	vertex* temp = maxTree[node1];
	v2->next = temp;
	maxTree[node1] = v2;

	//Connect node2 -> node1
	vertex* temp2 = maxTree[node2];
	v1->next = temp2;
	maxTree[node2] = v1;
}

vertex* Kruskal::initNode(int node, int weight) {

	vertex* newNode = new vertex();
	newNode->id = node;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;

}


// === Functions for disjoint sets
void Kruskal::makeSet(int node) {
	rank[node] = 0;
	parent[node] = -1;
}

int Kruskal::find(int node) {

	int w = node;

	while (parent[w] != -1)
		w = parent[w];

	return w;
}

void Kruskal::unionFuc(int r1, int r2) {

	if (rank[r1] > rank[r2]) // The rank of the first tree is greater
		parent[r2] = r1;
	else if (rank[r2] > rank[r1]) // The rank of the second tree is greater
		parent[r1] = r2;
	else {  // The ranks are the same
		parent[r2] = r1;
		rank[r1]++;
	}
}

// === Functions for spanning Tree
void Kruskal::findMaxAndPath(int s, int t) {
	// Initialize the values to zero
	for (size_t i = 0; i < nNodes; i++) {
		color[i] = 0;
		daddy[i] = -1;
	}
	
	// BFS on the spanning tree
	
	bfs(s);
	//return;
	int min = 100000000;

	while (daddy[t] != -1) {
		if (min > capacityInTree[t])
			min = capacityInTree[t];
		t = daddy[t];

	}
	std::cout << "\nMaximum Bandwidth is: " << min;

}

void Kruskal::bfs(int node) {
	// Step 1: Create a queue and push node to queue
	std::queue<int> q;
	q.push(node);

	// Step 2: set the value of the node to be black
	color[node] = 2;

	int u;
	// Iterate
	while (!q.empty()) {
		u = q.front();
		q.pop();
		vertex* temp = maxTree[u];
		while (temp != NULL) {
			if (color[temp->id] == 0) {
				q.push(temp->id);
				color[temp->id] = 2;
				daddy[temp->id] = u;
				capacityInTree[temp->id] = temp->weight;
			}
			temp = temp->next;
		}
	}
}



