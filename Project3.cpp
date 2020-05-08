// Owen Dennis
// Spring 2020
// COSC 320-002
//
// Project 3 - Main File
// 5/11/2020

// declare libraries
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include "stdlib.h"
#include "Graph.h"

const int SIZE = 7; // number of vertices

int main(int argc, char* argv[]) {
	if (argc != 3) { // if thee are not two graph files
		std::cout << "You need to have two files added to the command line! Exitting...\n";
		return 1;
	}
	
    bool directed = false;
	int count = 0;

    Graph G1(directed), G2(directed); // declare graphs

	std::fstream graph1(argv[1]), graph2(argv[2]); // get two graph files
	std::string str, edge;
	int n, j;

	if (graph1.is_open()) { // if the first graph file is found
		getline(graph1,str); // get the number of vertices
		n = std::stoi(str); // convert from string to int

		for (int i = 0; i < n; i++) // add vertices
			G1.addVertex(i+1);
	
		for (int i = 0; i < n; i++) { // for each vertex
			getline(graph1,str); // get the line in adjacency matrix
			std::istringstream iss(str); // parse out 0's and 1's

			j = 1;

			while (iss >> edge) { // for each 0 or 1
				if (edge == "1") G1.addEdge(i+1,j); // if there is an edge, make it
				j++;
			}
		}

		graph1.close();
	}

	if (graph2.is_open()) { // if the second graph file is found
        getline(graph2,str); // get the number of vertices
		n = std::stoi(str); // convert from string to int

        for (int i = 0; i < n; i++) // add vertices
            G2.addVertex(i+1);

        for (int i = 0; i < n; i++) { // for each vertex
            getline(graph2,str); // get line in adjacency list
            std::istringstream iss(str); // parse out 0's and 1's

			j = 1;

            while (iss >> edge) { // for each 0 or 1
				if (edge == "1") G2.addEdge(i+1,j); // if there is an edge, make it
				j++;
			}
        }

        graph2.close();
    }

	// display graphs
    std::cout << "\nG1:\n";
    G1.print();

    std::cout << "\nG2:\n";
    G2.print();
	std::cout << "\n";

	auto start = std::chrono::system_clock::now();

	// run isomorphism check an show mapping if they are
   	if (G1.isIsomorphic(G2)) std::cout << "Isomorphic";
   	else std::cout << "Not Isomorphic";

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "\n\nTime elapsed for isomorphism check: " << elapsed_seconds.count() << " s\n\n\n";

	auto start2 = std::chrono::system_clock::now();

	// run subisomorphism check and show mappings if there are any
	if (G1.isSubIsomorphic(count,G2)) std::cout << "G1 has " << count << " subgraph(s) isomorphic to G2... the mappings are above";
    else std::cout << "No subgraph of G1 is isomorphic to G2";

    auto end2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = end2 - start2;
    std::cout << "\n\nTime elapsed for sub-isomorphism check: " << elapsed_seconds2.count() << " s\n\n";

    return 0;
}







