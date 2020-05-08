// Owen Dennis
// Spring 2020
// COSC 320-002
//
// Project 3 - Declaration of Graph class
// 5/11/2020

// declaring libraries
#include <map>
#include <vector>

class Graph {
	std::map<int, std::vector<int>> vertices; // map of vertices to vector of vertices
	bool directed;

  public:
	Graph(bool dir) : directed(dir) {}
	Graph(const Graph& G); // copy constructor

	void addVertex(int x); // add a vertex to the graph
	void addEdge(int a, int b); // add an undirected edge to the graph
	int numEdges() const; // return the number of edges in the graph

	void print(); // prints the adjacency list of each vertex, to show the structure

	friend bool operator==(const Graph& G1, const Graph& G2); // operator overload for the == comparison operator

	bool isIsomorphic(const Graph& G); // function to return if the given graph is isomorphic to this one and lists its mapping if so

	void getSubsets(std::vector<std::vector<int>>& subsets, int n, int start, int length, bool* used); // return all subvectors of a given size of a vector
	bool isSubIsomorphic(int& count, const Graph& G); // function to return if the given graph is isomorphic to subgraphs of this graph and lists the mappings
};



