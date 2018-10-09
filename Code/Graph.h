//
// Created by balmung on 10/09/18.
//

#ifndef UNTITLED1_GRAPH_H
#define UNTITLED1_GRAPH_H


#include <unordered_map>
#include <unordered_set>

class Graph
{
    int N;    // Number of vertices
    int m;    // Number of edges
    std::unordered_map<int, std::unordered_map<int, int> > edges;



public:
    Graph();   // Constructor
    Graph(int N);   // Constructor
    ~Graph();     //destructor

    void setN(int N);
    int getN();

    int getM() const;
    void setM(int m);

    void addVertex(int vertex);
    void addEdge(int u, int v, int weight);   // function to add an edge to graph
    std::unordered_map<int, int> getEdgesOfVertex(int v);
    std::unordered_map<int, std::unordered_map<int, int> > getAllEdges();
    void deleteEdge(int u, int v);
    void deleteVertex(int vertex);


};


#endif //UNTITLED1_GRAPH_H
