//
// Created by balmung on 10/09/18.
//

#include "graphReader.h"



Graph *readGraph(std::string filename){

    std::fstream file(filename, std::ios_base::in);

    Graph *g = new Graph();

    int from, to, weight;
    file >> from;
    file >> to;
    g->setN(from);
    //g->setM(to);
    int i = 0;
    while (file >> from)
    {
        i++;
        g->addVertex(from);
        file >> to;
        g->addVertex(to);
        file >> weight;
        weight = 1;
        g->addEdge(from, to, weight);

    }
    std::cout<<i<<std::endl;
    file.close();
    return g;

}


Graph *readGraphRandomWeights(std::string filename){

    std::fstream file(filename, std::ios_base::in);

    Graph *g = new Graph();

    int from, to, weight;
    file >> from;
    file >> to;
    g->setN(from);
    //g->setM(to);

    while (file >> from)
    {

        g->addVertex(from);
        file >> to;
        g->addVertex(to);
        weight = rand() % 10 + 1;
        g->addEdge(from, to, weight);

    }

    file.close();
    return g;

}

void writeGraph(Graph g, std::string filename){

    std::fstream file(filename, std::ios_base::out);

    file << g.getN() << "\n";
    file << g.getM() << "\n";

    //write all edges
    for(auto& u : g.getAllEdges()){
        for(auto& v : u.second){
            file << u.first << " " << v.first << " " << v.second<< "\n";
        }
    }



    file.close();

}

int *readPLSolution(std::string filename, int n){

    std::fstream file(filename, std::ios_base::in);

    auto pl = new int[n];

    for(int i = 0; i < n; i++){
        file >> pl[i];
    }

    file.close();
    return pl;

}

void writeResults(std::list<int> results, std::string filename){

    std::fstream file(filename, std::ios_base::out);
    int max = 0, min = INT32_MAX;

    std::cout<<"Max int "<<min<< std::endl;

    for(auto& value : results){
        if(min > value) min = value;
        if(max < value) max = value;
        file << value << "\n";
    }
    std::cout<<"Max power "<<max<<" Min power " << min <<std::endl;

    file.close();

}
