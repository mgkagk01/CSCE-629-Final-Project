#pragma once
#include <iostream>


// Struct to be a node of the heap
typedef struct edge {

	std::pair<int, int> nodes;
	int weight;
	int position;

}edge;

class KruskalHeap{

	int enEdges;
public:

	// Constructor
	KruskalHeap(int nEdges);
	
	int lastElementPos;
	int countDuplEdges;

	edge* heapArray; // heap array
	edge* sortedArray; // sorted array, we can use the heap array to reduce the space complexity
	edge* collectorArray; // Two times the heap array since we collect an edge two times
	void deleteDuplicates(); // Delete the duplicates

	// For the functionalities of the heap
	void insertEdge(int node1, int node2, int capacity);
	void heapify(bool up, edge node);
	void heapSort();
	void deleteRoot();

	// Functions for Debugging
	void printHeap();
	bool isSorted();
	void printColle();

};

