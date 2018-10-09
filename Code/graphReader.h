//
// Created by balmung on 10/09/18.
//

#ifndef UNTITLED1_GRAPHREADER_H
#define UNTITLED1_GRAPHREADER_H

#include <iostream>
#include <string>
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <list>

Graph *readGraph(std::string filename);
Graph *readGraphRandomWeights(std::string filename);
void writeGraph(Graph g, std::string filename);
void writeResults(std::list<int> results, std::string filename);
int *readPLSolution(std::string filename, int n);


#endif //UNTITLED1_GRAPHREADER_H
