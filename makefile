# Owen Dennis
# Spring 2020
# COSC 320 - 002
#
# makefile for Project 3

Project3.exe: Project3.o Graph.o
	g++ Project3.o Graph.o -o Project3.exe

Project3.o: Project3.cpp Graph.h
	g++ -c Project3.cpp

Graph.o: Graph.cpp Graph.h
	g++ -c Graph.cpp

clean:
	rm -f Project3.o Graph.o
