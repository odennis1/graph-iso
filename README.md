# graph-iso
### Introduction
I had to complete a project in my school's COSC 320 class and chose graph isomorphisms as my topic.  I found out that computer scientists are unaware if the problem of graph isomorphism is P or NP-complete (although we are getting closer and closer to P).

I decided to create brute force algorithms to solve both the Graph Isomorphism Problem and the Induced Subgraph Isomorphism Problem.  These algorthims run in factorial time, which is awful.  However, my goal was to solve the problem by any way necessary.

### Guide
The code is very easy to use.  It takes in two graphs by reading two separate text files containing adjacency matrices.  For example:

    4
    0 1 0 1
    0 0 0 0
    0 1 0 1
    1 0 1 0

The program checks to see if the teo graphs are isomorphic to one another.  if they are, the output will say so and list the mapping from the first to second set of vertices.  For example:

    G1 is isomorphic to G2
    
    Mapping:
    1 -> 3
    2 -> 2
    3 -> 4
    4 -> 1

The second algorithm tries to find every subgraph of the first graph that is isomorphic to the second graph.  The second graph must have less vertices and edges as the first graph.  The output will list every subgraph isomorphism mapping.  For example:

    Mapping:
    1 -> 3
    2 -> 2
    3 -> 4
    4 -> 1
    
    Mapping:
    1 -> 1
    2 -> 4
    3 -> 3
    4 -> 2
    
    Mapping:
    1 -> 2
    2 -> 1
    3 -> 4
    4 -> 3
    
    G1 has 3 subgraph isomorphism(s) to G2
 
 I am also adding the paper I had to write for the project for a much more in depth explaination.
 
 ### Good luck and have fun with it!
