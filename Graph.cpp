// Owen Dennis
// Spring 2020
// COSC 320-002
//
// Project 3 - Implementation of Graph class
// 5/11/2020

// declare libraries
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "Graph.h"

//copy constructor
Graph::Graph(const Graph& G) {
    directed = G.directed; // copy over bool variable

	std::map<int,std::vector<int>>::const_iterator itr; // map iterator
    for (itr = (G.vertices).begin(); itr != (G.vertices).end(); itr++)
        addVertex(itr->first); // add a vertex to the graph for each vertex in the copied graph

    for (itr = (G.vertices).begin(); itr != (G.vertices).end(); itr++)
        for (int i = 0; i < (itr->second).size(); i++)
            addEdge(itr->first,(itr->second)[i]); // add the edges of the copied graph to this new graph
}

// add a vertex to the graph
void Graph::addVertex(int x) {
	std::vector<int> v; // vreat new vector

	vertices.insert(std::pair<int,std::vector<int>>(x,v)); // add a new pair to the map
}

// add an undirected edge to the edge
void Graph::addEdge(int a, int b) {
	std::map<int,std::vector<int>>::iterator itr = vertices.find(a); // find the pair in the map that had vertex a

	std::vector<int>::iterator edges = std::find((itr->second).begin(),(itr->second).end(),b); // look for vertex b in the vector with key a

	if (edges == (itr->second).end()) { // if the edged is not found
		(itr->second).push_back(b); // add second vertex to first vertex vector
		if (a != b && !directed) { // if the edge is not a self-edge
			itr = vertices.find(b); // find the second vertex
			(itr->second).push_back(a); // add first vertex to second vertex vector
		}
	}
}

// returns the number of edges in the graph
int Graph::numEdges() const {
	int total = 0; // initialize sum

	for (std::map<int,std::vector<int>>::const_iterator itr = vertices.begin(); itr != vertices.end(); itr++)
		total += (itr->second).size(); // add size of current vector

	return total;
}

// prints the adjacency list of each vertex, to show the structure
void Graph::print() {
	for (std::map<int,std::vector<int>>::iterator itr = vertices.begin(); itr != vertices.end(); itr++) {
		std::cout << itr->first << ": "; // print out each vertex

		for (int i = 0; i < (itr->second).size(); i++)
			std::cout << (itr->second)[i] << " "; // print out each element in the vertex's vector
		std::cout << "\n";
	}
}

// == operator overload
bool operator==(const Graph& G1, const Graph& G2) {
	if (G1.vertices.size() != G2.vertices.size()) return false; // if not the same number of vertices

	if (G1.numEdges() != G2.numEdges()) return false; // if not the same numbe rof edges

	std::vector<std::pair<int,std::vector<int>>> vec1, vec2; // vector of map pairs

    for (std::map<int,std::vector<int>>::const_iterator itr = (G1.vertices).begin(); itr != (G1.vertices).end(); itr++)
        vec1.push_back(std::make_pair(itr->first,itr->second)); // get vertices of graph 1

	for (std::map<int,std::vector<int>>::const_iterator itr = (G2.vertices).begin(); itr != (G2.vertices).end(); itr++)
        vec2.push_back(std::make_pair(itr->first,itr->second)); // get vertices of graph 2

    // sorting the vector in ascending order
    std::sort(vec1.begin(),vec1.end(),[](const std::pair<int,std::vector<int>> &a, const std::pair<int,std::vector<int>> &b) { return a.first < b.first; });
	std::sort(vec2.begin(),vec2.end(),[](const std::pair<int,std::vector<int>> &a, const std::pair<int,std::vector<int>> &b) { return a.first < b.first; });

	for (int i = 0; i < vec1.size(); i++)
		if (vec1[i].first != vec2[i].first) return false; // if the vertices are not equal after sorted

	std::map<int,std::vector<int>>::const_iterator edges1, edges2;
	
	for (int i = 0; i < vec1.size(); i++) {
		edges1 = G1.vertices.find(vec1[i].first); // get edges of graph 1
		edges2 = G2.vertices.find(vec1[i].first); // get edges of graph 2

		if ((edges1->second).size() != (edges2->second).size()) return false; // if the number of edges per vertex are not the same

		std::vector<int> v1 (edges1->second), v2 (edges2->second);

		// sort vectors
		std::sort(v1.begin(),v1.end());
		std::sort(v2.begin(),v2.end());

		for (int j = 0; j < v1.size(); j++)
			if (v1[j] != v2[j]) return false; // if edges aren't equal
	}

	return true; // if the graphs pass all of the test, they are equal
}

// function to say if the graph is isomorphic to another given one
bool Graph::isIsomorphic(const Graph& G) {
	if (vertices.size() != G.vertices.size()) return false; // if not the same number of vertices

    if (numEdges() != G.numEdges()) return false; // if not the same numbe rof edges

	std::vector<int> perm;
	int index;

	std::map<int,std::vector<int>>::iterator itr, itr2;
	std::map<int,std::vector<int>>::const_iterator c_itr;
	for (c_itr = G.vertices.begin(); c_itr != G.vertices.end(); c_itr++)
		perm.push_back(c_itr->first); // get vertices of graph 1 to run permutations of

	std::sort(perm.begin(),perm.end()); // sort the permutation vector

	do {
		std::map<int,int> mapping;

		index = 0;
		for (itr = vertices.begin(); itr != vertices.end(); itr++) {
			mapping.insert(std::pair<int,int>(itr->first,perm[index]));
			index++;
		} // get the mapping of one vertex to the next depending on what permutation is being used
		
		Graph temp(directed); // declare temporary graph

		for (c_itr = G.vertices.begin(); c_itr != G.vertices.end(); c_itr++)
			temp.addVertex(c_itr->first); // add vertices of graph 1 to the temp graph

		std::map<int,int>::iterator itr3, itr4;
		for (itr = vertices.begin(); itr != vertices.end(); itr++) {
			itr3 = mapping.find(itr->first); // get the mapping of the vertices

			for (int i = 0; i < (itr->second).size(); i++) {
				itr4 = mapping.find((itr->second)[i]); // get mapping of edge from current vertex
				temp.addEdge(itr3->second,itr4->second); // create mapped graph from original based on mapping
			}
		}

		if (temp == G) { // see if the temp graph is equal to graph 2
			std::cout << "Mapping:\n"; // if equal, show the mapping
			for (std::map<int,int>::iterator i = mapping.begin(); i != mapping.end(); i++)
				std::cout << i->first << " --> " << i->second << "\n";
			std::cout << "\n";
			return true;
		}

	} while (std::next_permutation(perm.begin(),perm.end())); // for each permutation

	return false; // if no mapping is found, they are not isomorphic
}

// function to return the subvectors of a given size of a given vector
void Graph::getSubsets(std::vector<std::vector<int>>& subsets, int n, int start, int length, bool* used) {
	if (length == n) { // the length of the current subvector is the desired value
		std::vector<int> set;
		int i = 0, m = 0;

		for (std::map<int,std::vector<int>>::iterator itr = vertices.begin(); itr != vertices.end(); itr++) // for each vertex
			if (used[i++] == true) // if the vertex is to be used
				if (m++ < n) // if the number of indeces added is less than the length
					set.push_back(itr->first); // add the vertex to the subvector
		subsets.push_back(set); // add the subvector to the list of subvectors
	} else if (start == vertices.size()) { // if we are at the end of the vertex list
		return;
	} else {
		used[start] = true; // current value is to be used
		getSubsets(subsets,n,start+1,length+1,used); // run function with new condition

		used[start] = false; // current value is not to be used
		getSubsets(subsets,n,start+1,length,used); // run function with new condition
	}
}

// function to see if the current graph has subgraphs isomorphic to a given graph
bool Graph::isSubIsomorphic(int& count, const Graph& G) {
	if (vertices.size() <= G.vertices.size()) return false; // if all subgraph's number of vertices are less than the number of vertices in G

	if (numEdges() <= G.numEdges()) return false; // if number of edges in current graph is less than the number of edges in given one

	bool subiso = false;
	bool used[vertices.size()]; // setting up variables for subset function
	
	for (int i = 0; i < vertices.size(); i++)
		used[i] = true;

	std::vector<std::vector<int>> subsets; // to hold all subsets

	getSubsets(subsets,G.vertices.size(),0,0,used); // get all subsets of size "number of vertices in G"

/*	for (int i = 0; i < subsets.size(); i++) { // print out all of the subsets
		for (int j = 0; j < subsets[i].size(); j++)
			std::cout << subsets[i][j] << " ";
		std::cout << "\n";
	} */

	for (int i = 0; i < subsets.size(); i++) { // for each subset
		Graph temp(directed); // create templated graph

		for (int j = 0; j < subsets[i].size(); j++) // add each value in the subset as a vertex of the temp graph
			temp.addVertex(subsets[i][j]);

		for (std::map<int,std::vector<int>>::iterator itr1 = temp.vertices.begin(); itr1 != temp.vertices.end(); itr1++) { // for each vertex in the temp graph
			std::map<int,std::vector<int>>::iterator itr2 = vertices.find(itr1->first); // find the verex in the original graph

			for (int j = 0; j < (itr2->second).size(); j++) { // for each of the found vertex's edges
				std::map<int,std::vector<int>>::iterator itr3 = temp.vertices.find((itr2->second)[j]); // see if the edges second pairing has a corresponding verex
				if (itr3 != temp.vertices.end()) temp.addEdge(itr1->first,(itr2->second)[j]); // if the vertex exists, add the edge
			}
		}

		if (temp.isIsomorphic(G)) { // check to see if the temp graph is isomorphic to G
			subiso = true;
			count++; // count how many sub graphs are isomorphic to G
		}
	}

	return subiso; // retrun if there are subgraphs isomorphic to G
}




















