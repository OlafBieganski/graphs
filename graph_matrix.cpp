#include "graph_matrix.hh"
#include <iostream>

// creates a graph instance
// params: number of verticies in graph
graphM::graphM(int vertNum){
    if(vertNum > 0){
        numVert = vertNum;
        // allocating rows
        adj_matrix = new int*[vertNum];
        // allocating colums
        for(int i = 0; i < vertNum; i++)
            adj_matrix[i] = new int[vertNum];
        // filling matrix with 0s (we have no edges yet)
        for(int i = 0; i < vertNum; i++){
            for(int j = 0; j < vertNum; j++){
                adj_matrix[i][j] = 0;
            }
        }
    }
}

// adds an egde beetwen two verticies with given weight
// params: start vert, end vert, weight value
bool graphM::addEdge(int start, int end, int weight){
    if(start < 0 || end < 0) return false;

    if(start < numVert && end < numVert){
        adj_matrix[start][end] = weight;
        adj_matrix[end][start] = weight;
        return true;
    }
    return false;
}

void graphM::printAdjLists(){
    std::cout << "Sasiad | waga" << std::endl;
    for(int i = 0; i < numVert; i++){
        std::cout << "Lista sasiedztwa dla wiercholka "
            << i << ":" << std::endl;
        for(int j = 0; j < numVert; j++){
            if(adj_matrix[i][j] != 0)
                std::cout << j << '\t' << adj_matrix[i][j] << std::endl;
        }
    }
}