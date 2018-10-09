//
// Created by balmung on 10/09/18.
//

#include "Graph.h"

#include <queue>


Graph::Graph()
{
    this->N = -1;
    this->m = 0;
    edges = std::unordered_map<int, std::unordered_map<int, int> >();
}


Graph::Graph(int N)
{
    this->N = N;
    this->m = 0;
    edges = std::unordered_map<int, std::unordered_map<int, int> >();
}

Graph::~Graph()
{
    //edges.~unordered_map();

}

int Graph::getN() {return this->N;}
void Graph::setN(int N) {this->N = N;}


void Graph::addVertex(int vertex)
{
    edges.insert({vertex, std::unordered_map<int, int>()});

    this->N = std::max(vertex, this-> N);
}

void Graph::addEdge(int u, int v, int weight)
{
    if(u == v) return;      //avoid self loop

    this->m += 2;

    edges[u].erase(v);
    edges[v].erase(u);

    edges[u].insert({v, weight});
    edges[v].insert({u, weight});
}


std::unordered_map<int, int> Graph::getEdgesOfVertex(int v) {
    return this->edges[v];
}

std::unordered_map<int, std::unordered_map<int, int> > Graph::getAllEdges(){
    return this->edges;
};




void Graph::deleteEdge(int u, int v){
    edges[u].erase(v);
    edges[v].erase(u);
    this->m -= 2;
}

void Graph::deleteVertex(int vertex) {
    //remove vertex from the graph. It is supposed there are not edges where vertex is one of the endpoints
    edges.erase(vertex);
}

int Graph::getM() const {
    return m;
}

void Graph::setM(int m) {
    Graph::m = m;
}
