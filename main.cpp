#include <iostream>
#include "Graph.h"
#include "MaxHeap.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include<chrono>
#include <random>


int main(){

	// --- Initialize the random generator
	int seed = 0;
	int seed2 = 1;
	std::mt19937 generator(seed);
	std::uniform_int_distribution<int> sourceDesti(0, 5000 - 1);

	// --- Pick at random the source and destination vertices
	int s = sourceDesti(generator);
	int t = sourceDesti(generator);

	std::cout << "Problem MaxBand from: " << s << " to " << t << ", using seed: " << seed << std::endl;

	// --- Creater Graph, Dijkstra's and Kruskal's objects
	Graph G(0, seed2);
	Dijkstra dAlgo;
	Kruskal kAlgo(G.nEdges);
	
	// --- Kruskal 
	std::cout << "\n=== Kruskal ===";
	auto start = std::chrono::high_resolution_clock::now();
	kAlgo.maxBandwidth(G.adj, s, t);
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "\nTotal Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	// --- Dijkstra, array based
	std::cout << "\n\n=== Simple ===\n";
	start = std::chrono::high_resolution_clock::now();
	dAlgo.arrayBased(s, t, G.adj);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "Total Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	// --- Dijkstra, heap based
	std::cout << "\n\n=== Heap based ===\n";
	start = std::chrono::high_resolution_clock::now();
	dAlgo.heapBased(s, t, G.adj);
	end = std::chrono::high_resolution_clock::now();
	std::cout << "Total Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
	

	return 0;
}



