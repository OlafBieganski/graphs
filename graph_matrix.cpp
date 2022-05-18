#include "graph_matrix.hh"
#include <iostream>
#include <limits.h>

#define INFINITY INT_MAX

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

// additional utility functions used in dijkstra algorithm

int minDistance(int distance[], bool includedSTP[], int numVert){
    int min = INFINITY, min_idx;
    for(int i = 0; i < numVert; i++){
        if(includedSTP[i] == false && distance[i] <= min){
            min = distance[i], min_idx = i;
        }
    }
    return min_idx;
}

void printSolution(int distance[], int vertNum)
{
    std::cout <<"Vertex \t Distance from Source" << std::endl;
    for (int i = 0; i < vertNum; i++)
        std::cout  << i << " \t\t"<<distance[i]<< std::endl;
}

void graphM::dijkstra(int source){

    int distance[numVert]; // it will hold the sum of distances (shortest possible)
    bool includedSPT[numVert]; // true for the vertex that has already been included to spt
    
    for(int i = 0; i < numVert; i++){
        distance[i] = INFINITY, includedSPT[i] = false;
    }
    distance[source] = 0; // initial vertex marked as included to spt

    for(int i = 0; i < numVert-1; i++){
        int picked = minDistance(distance, includedSPT, numVert);
        includedSPT[picked] = true;
        for(int j = 0; j < numVert; j++){
            if(!includedSPT[j] && adj_matrix[picked][j] && distance[picked] != INFINITY
            && distance[picked] + adj_matrix[picked][j] < distance[j]){
                distance[j] = distance[picked] + adj_matrix[picked][j];
            }
        }
    }
    printSolution(distance, numVert);
}