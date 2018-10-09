//
// Created by balmung on 10/09/18.
//

#include <iostream>
#include "math.h"
#include "MaxCutCalc.h"

void initPartition(int partition[], int size){
    for (int i = 0; i < size; i++)
        partition[i] = -1;
}


int *computePartitionPLProbability(int n, const double *probs){
    //computes a partition V1-V2 based on the vector probabilities. n is the number of vertices of the graph
    //probs is an array of probability for each vertex. probs[i] is the probability of vertex i to belong to partition V1

    auto partition = new int[n];//(int*) malloc(sizeof(int)*n);       //for each vertex indicates the partition to which it belongs to
    initPartition(partition, n);

    for(int i = 0; i < n; i++){
        double p = ((double) rand() / (RAND_MAX));
        if (p <= probs[i])
            partition[i] = 1;   //put vertex i into partition V1
        else partition[i] = 0;  //put vertex i into partition V2

    }

    return partition;

}

int *computePartitionPLRounding(int n, const double *plSolution){
    //computes a partition V1-V2 based on the solution to pl. n is the number of vertices of the graph

    auto partition = new int[n];//(int*) malloc(sizeof(int)*n);       //for each vertex indicates the partition to which it belongs to
    initPartition(partition, n);

    for(int i = 0; i < n; i++){
        if (plSolution[i] >= 0.5)
            partition[i] = 1;   //put vertex i into partition V1
        else partition[i] = 0;  //put vertex i into partition V2

    }

    return partition;

}

int *computePartitionFixedProbability(int n, double const probs){
    //computes a partition V1-V2 based on a probability. n is the number of vertices of the graph

    auto partition = new int[n];//(int*) malloc(sizeof(int)*n);       //for each vertex indicates the partition to which it belongs to
    initPartition(partition, n);

    for(int i = 0; i < n; i++){
        double p = ((double) rand() / (RAND_MAX));
        if (p <= probs)
            partition[i] = 1;   //put vertex i into partition V1
        else partition[i] = 0;  //put vertex i into partition V2

    }

    return partition;

}



int *computePartitionGreedy(Graph g, int n){
    //computes a partition V1-V2 based on a greedy assignment. n is the number of vertices of the graph

    auto partition = new int[n];      //for each vertex indicates the partition to which it belongs to
    initPartition(partition, n);
    buildPartitionByRandomEdges(g, n, partition);
    //assign the best partition (in a greedy way) to the vertices which partition is -1
    for(int i = 0; i < n; i++){
        if(partition[i] == -1){
            partition[i] = assignPartitionToVertex(g, i, partition);
        }
    }



    return partition;

}

void buildPartitionByRandomEdges(Graph g, int n, int partition[]){
    //create a partition picking random edges. The partition could be not complete that is some vertices could be not assigned to any partition
    int u, v;           //edge to delete's endpoints
    int position;
    std::unordered_map<int, int> adjU;

    while(g.getM() > 0){
        do {
            u = (rand() % n);                      //pick a random vertex
            adjU = g.getEdgesOfVertex(u);        //adjacent list of u
        }while(adjU.empty());

        position = rand() % (int) adjU.size();      //pick the endpoint of an incident edge in u
        for(auto& vertex : adjU) {
            if (position == 0){
                v = vertex.first;
                break;
            }
            position--;
        }

        //asssing u and v to the current best partition
        if(bestPartition(g, u, v, partition)){
            partition[u] = 1;
            partition[v] = 0;
        } else {
            partition[u] = 0;
            partition[v] = 1;
        }

        //remove u and v from graph
        auto adj = g.getEdgesOfVertex(u);        //adjacent list of u
        for(auto& vertex : adj){
            g.deleteEdge(u, vertex.first);
        }

        adj = g.getEdgesOfVertex(v);        //adjacent list of v
        for(auto& vertex : adj){
            g.deleteEdge(v, vertex.first);
        }

    }
}


int assignPartitionToVertex(Graph g, int u, const int *partition){
    //return the best partition for vertex u
    int cutValuePartition0 = 0;      //amount of incremented cut value if u is in partition 0
    int cutValuePartition1 = 0;      //amount of incremented cut value if u is in partition 1

    auto adj = g.getEdgesOfVertex(u);        //adjacent list of u
    cutValuePartition0 = cutValueForVertex(adj, partition, 0);

    cutValuePartition1 = cutValueForVertex(adj, partition, 1);

    return cutValuePartition1 > cutValuePartition0;

}

int bestPartition(Graph g, int u, int v, int const partition[]){
    //return the best partition for vertex u given the edge uv crossing the cut
    int cutValuePartition0 = 0;      //amount of incremented cut value if u is in partition 0 and v in 1
    int cutValuePartition1 = 0;      //amount of incremented cut value if u is in partition 1 and v in 0

    auto adj = g.getEdgesOfVertex(u);        //adjacent list of u
    cutValuePartition0 = cutValueForVertex(adj, partition, 0);
    adj = g.getEdgesOfVertex(v);        //adjacent list of v
    cutValuePartition0 += cutValueForVertex(adj, partition, 1);

    adj = g.getEdgesOfVertex(u);        //adjacent list of u
    cutValuePartition1 = cutValueForVertex(adj, partition, 1);
    adj = g.getEdgesOfVertex(v);        //adjacent list of v
    cutValuePartition1 += cutValueForVertex(adj, partition, 0);

    return cutValuePartition1 > cutValuePartition0;

}

int cutValueForVertex(std::unordered_map<int, int> adj, int const partition[], int tmpPartition) {
    //return the number of adjacent edges to u crossing the cut supposing u belongs to partition tmpPartition

    int cutValueIncrement = 0;      //amount of incremented cut value
    for(auto& w : adj){
        if(partition[w.first] == 1 - tmpPartition)
            cutValueIncrement += w.second;
    }
    return  cutValueIncrement;
}


int computeCutValue(Graph g, int const partition[]){
    int cutValue = 0;

    //std::cout << "numero " << g.getAllEdges().size()<<std::endl;
    for(auto& vertex : g.getAllEdges()){

        int u = vertex.first;       //map's key
        for(auto& v : vertex.second){
            if(partition[u] != partition[v.first]) cutValue += v.second;        //each edge is counted 2 times because the graph is non directed
        }
    }

    return cutValue/2;

}




//PROBABILISTIC VERSION OF GREEDY ALGORITHM


int *computePartitionGreedyProb(Graph g, int n){
    //computes a partition V1-V2 based on the vector probabilities. n is the number of vertices of the graph
    //probs is the probability of each vertex to belong to partition V1

    auto partition = new int[n];//(int*) malloc(sizeof(int)*n);       //for each vertex indicates the partition to which it belongs to
    initPartition(partition, n);
    buildPartitionByRandomEdgesProb(g, n, partition);

    //assign the best partition (in a greedy way) to the vertices which partition is -1
    for(int i = 0; i < n; i++){
        if(partition[i] == -1){
            partition[i] = assignPartitionToVertexProb(g, i, partition);
        }
    }



    return partition;

}

void buildPartitionByRandomEdgesProb(Graph g, int n, int partition[]){
    //create a partition picking random edges. The partition could be not complete that is some vertices could be not assigned to any partition
    int u, v;           //edge to delete's endpoints
    int position;
    std::unordered_map<int, int> adjU;

    while(g.getM() > 0){
        //std::cout << g.getM() << std::endl;
        do {
            u = (rand() % n);
            adjU = g.getEdgesOfVertex(u);        //adjacent list of u
        }while(adjU.empty());

        position = rand() % (int) adjU.size();
        for(auto& vertex : adjU) {
            if (position == 0){
                v = vertex.first;
                break;
            }
            position--;
        }

        //asssing u and v to the current best partition
        if(bestPartitionProb(g, u, v, partition)){
            partition[u] = 1;
            partition[v] = 0;
        } else {
            partition[u] = 0;
            partition[v] = 1;
        }

        //remove u and v from graph
        auto adj = g.getEdgesOfVertex(u);        //adjacent list of u
        for(auto& vertex : adj){
            g.deleteEdge(u, vertex.first);
        }

        adj = g.getEdgesOfVertex(v);        //adjacent list of v
        for(auto& vertex : adj){
            g.deleteEdge(v, vertex.first);
        }

    }
}


int assignPartitionToVertexProb(Graph g, int u, const int *partition){
    //return the best partition for vertex u
    int cutValuePartition0 = 0;      //amount of incremented cut value if u is in partition 0
    int cutValuePartition1 = 0;      //amount of incremented cut value if u is in partition 1

    auto adj = g.getEdgesOfVertex(u);        //adjacent list of u
    cutValuePartition0 = cutValueForVertex(adj, partition, 0);

    cutValuePartition1 = cutValueForVertex(adj, partition, 1);

    if(cutValuePartition0 + cutValuePartition1 == 0)
        return 0;

    double p = ((double) rand() / (RAND_MAX));

    if(cutValuePartition0 < 0 && cutValuePartition1 < 0)
        return p <= (cutValuePartition0/((cutValuePartition0 + cutValuePartition1)*1.0));

    if(cutValuePartition0 < 0)      //we want partition 1 with higher probability than partition 0
        return p >= (1/(sqrt((cutValuePartition0*(-1) + cutValuePartition1)) ));

    if(cutValuePartition1 < 0)      //we want partition 0 with higher probability than partition 1
        return p <= (1/(sqrt((cutValuePartition0 + cutValuePartition1*(-1)))));

    return p <= (cutValuePartition0/((cutValuePartition0 + cutValuePartition1)*1.0));


}

int bestPartitionProb(Graph g, int u, int v, int const partition[]){
    //return the best partition for vertex u given the edge uv crossing the cut
    int cutValuePartition0 = 0;      //amount of incremented cut value if u is in partition 0 and v in 1
    int cutValuePartition1 = 0;      //amount of incremented cut value if u is in partition 1 and v in 0

    auto adj = g.getEdgesOfVertex(u);        //adjacent list of u
    cutValuePartition0 = cutValueForVertex(adj, partition, 0);
    adj = g.getEdgesOfVertex(v);        //adjacent list of v
    cutValuePartition0 += cutValueForVertex(adj, partition, 1);

    adj = g.getEdgesOfVertex(u);        //adjacent list of u
    cutValuePartition1 = cutValueForVertex(adj, partition, 1);
    adj = g.getEdgesOfVertex(v);        //adjacent list of v
    cutValuePartition1 += cutValueForVertex(adj, partition, 0);

    if(cutValuePartition0 + cutValuePartition1 == 0)
        return 0;

    double p = ((double) rand() / (RAND_MAX));

    if(cutValuePartition0 < 0 && cutValuePartition1 < 0)
        return p >= (cutValuePartition0/((cutValuePartition0 + cutValuePartition1)*1.0));

    if(cutValuePartition0 < 0)
        return p >= (1/(sqrt((cutValuePartition0*(-1) + cutValuePartition1)) ));

    if(cutValuePartition1 < 0)
        return p <= (1/(sqrt((cutValuePartition0 + cutValuePartition1*(-1)))));

    return p <= (cutValuePartition0/((cutValuePartition0 + cutValuePartition1)*1.0));

}


//PROBABILISTIC VERSION OF GREEDY ALGORITHM WITH FIXED PROBABILITY = 0.5


int *computePartitionGreedyProbFixed(Graph g, int n){
    //computes a partition V1-V2 based on the vector probabilities. n is the number of vertices of the graph
    //probs is the probability of each vertex to belong to partition V1

    auto partition = new int[n];//(int*) malloc(sizeof(int)*n);       //for each vertex indicates the partition to which it belongs to
    initPartition(partition, n);
    buildPartitionByRandomEdgesProbFixed(g, n, partition);

    //assign the best partition (in a greedy way) to the vertices which partition is -1
    for(int i = 0; i < n; i++){
        if(partition[i] == -1){
            partition[i] = assignPartitionToVertexProbFixed();
        }
    }



    return partition;

}

void buildPartitionByRandomEdgesProbFixed(Graph g, int n, int partition[]){
    //create a partition picking random edges. The partition could be not complete that is some vertices could be not assigned to any partition
    int u, v;           //edge to delete's endpoints
    int position;
    std::unordered_map<int, int> adjU;

    while(g.getM() > 0){
        //std::cout << g.getM() << std::endl;
        do {
            u = (rand() % n);
            adjU = g.getEdgesOfVertex(u);        //adjacent list of u
        }while(adjU.empty());

        position = rand() % (int) adjU.size();
        for(auto& vertex : adjU) {
            if (position == 0){
                v = vertex.first;
                break;
            }
            position--;
        }

        //asssing u and v to the current best partition
        if(assignPartitionToVertexProbFixed()){
            partition[u] = 1;
            partition[v] = 0;
        } else {
            partition[u] = 0;
            partition[v] = 1;
        }

        //remove u and v from graph
        auto adj = g.getEdgesOfVertex(u);        //adjacent list of u
        for(auto& vertex : adj){
            g.deleteEdge(u, vertex.first);
        }

        adj = g.getEdgesOfVertex(v);        //adjacent list of v
        for(auto& vertex : adj){
            g.deleteEdge(v, vertex.first);
        }

    }
}


int assignPartitionToVertexProbFixed(){

    double p = ((double) rand() / (RAND_MAX));

    return p <= 0.5;

}
