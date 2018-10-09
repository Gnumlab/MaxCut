//
// Created by balmung on 10/09/18.
//

#ifndef UNTITLED1_MAXCUTCALC_H
#define UNTITLED1_MAXCUTCALC_H

#include "Graph.h"
void initPartition(int partition[], int size);

int *computePartitionPLProbability(int n, const double *probs);
int *computePartitionPLRounding(int n, const double *plSolution);
int *computePartitionFixedProbability(int n, double probs);
int *computePartitionGreedy(Graph g, int n);
int *computePartitionGreedyProb(Graph g, int n);


void buildPartitionByRandomEdges(Graph g, int n, int partition[]);
int assignPartitionToVertex(Graph g, int u, const int *partition);
int bestPartition(Graph g, int u, int v, int const partition[]);
int cutValueForVertex(std::unordered_map<int, int> adj, int const partition[], int tmpPartition);

void buildPartitionByRandomEdgesProb(Graph g, int n, int partition[]);
int assignPartitionToVertexProb(Graph g, int u, const int *partition);
int bestPartitionProb(Graph g, int u, int v, int const partition[]);

int *computePartitionGreedyProbFixed(Graph g, int n);
void buildPartitionByRandomEdgesProbFixed(Graph g, int n, int partition[]);
int assignPartitionToVertexProbFixed();

int computeCutValue(Graph g, int const partition[]);  //compute the number of edges between two partitions

#endif //UNTITLED1_MAXCUTCALC_H
