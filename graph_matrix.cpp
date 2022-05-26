#include "graph_matrix.hh"
#include <iostream>
#include <limits.h>
#include <time.h>
#include<sys/time.h>

using namespace std;

#define INFINITY INT_MAX
#define NO_PARENT -1

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
// creates graph with given density. Connections are random.
// density between 0-100 (%)
graphM::graphM(int vertNum, int density){
    if(density < 0 || density > 100){
        cerr << "Error in graphM(density)." << endl;
        exit(1);
    }
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

    // evaluate edges
    int edges = 0.5*density/100*numVert*(numVert-1);
    // initial values for connections
    int weight = 0, conNum = numVert -1, conNum2 = 0;
    // for rand()
    struct timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    // calculate how many initial concetions and random
    if(edges - (numVert-1) <= 0){
        conNum = edges;
    } else if(edges - (numVert-1) > 0){
        conNum2 = edges - (numVert-1);
    }
    // first we connect all verticies
    for(int i = 0; i < conNum; i++){
        weight = (rand() % 100) + 1;
        addEdge(i, i+1, weight);
    }
    // then we make random connections between verts not connected
    int x, y;
    for(int i = 0; i < conNum2; i++){
        x = rand() % vertNum;
        y = rand() % vertNum;
        weight = (rand() % 100) + 1;
        // check if not connected and not connecting with itself
        if(!isEdge(x,y) && x != y){
            addEdge(x, y, weight);
        }
        else i--;
    }
}

// check if connections between two given idx exists
bool graphM::isEdge(int start, int end){
    if(start < 0 || end < 0 || start >= numVert || end >= numVert){
        cerr << "Error in isEgde()." << endl;
        exit(1);
    }
    // second check redundant
    return (adj_matrix[start][end] || adj_matrix[end][start]);
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

void printPath(int parent[], int vert){
    if(parent[vert] == NO_PARENT)
        return;
    printPath(parent, parent[vert]);
    std::cout << " " << vert;
}

void printSolution(int distance[], int parent[], int vertNum, int source)
{
    std::cout <<"Vertex \t Distance from Source \t Path" << std::endl;
    for (int i = 0; i < vertNum; i++){
        std::cout  << source << "->" << i << " \t\t"<< distance[i] << "\t\t" << source;
        printPath(parent, i);
        std::cout << std::endl;
    }
}

void graphM::dijkstra(int source, bool print){

    int distance[numVert]; // it will hold the sum of distances (shortest possible)
    bool includedSPT[numVert]; // true for the vertex that has already been included to spt
    int parent[numVert]; // index is a vertex and value assigned is parent vertex
    
    for(int i = 0; i < numVert; i++){
        distance[i] = INFINITY, includedSPT[i] = false;
        parent[i] = NO_PARENT; // at first no parents
    }
    distance[source] = 0; // initial vertex marked as included to spt

    for(int i = 0; i < numVert-1; i++){
        int picked = minDistance(distance, includedSPT, numVert);
        includedSPT[picked] = true;

        for(int j = 0; j < numVert; j++){
            if(!includedSPT[j] && adj_matrix[picked][j] && distance[picked] != INFINITY
            && distance[picked] + adj_matrix[picked][j] < distance[j]){
                parent[j] = picked; // the last update will be parent
                distance[j] = distance[picked] + adj_matrix[picked][j]; // upadating distance for adjacent verticies
            }
        }
    }
    if(print == true)
        printSolution(distance, parent, numVert, source);
}

// performs dijkstra for given src and returns its run-time 
double graphM::dijkstraTime(int src){
    // Start measuring time
    struct timespec begin, end; 
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);

    // perform dijkstra algorithm
    dijkstra(src, false);

    // Stop measuring time and calculate the elapsed time
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    return elapsed;
}

void printPathTF(int parent[], int vert, std::fstream & file){
    if(parent[vert] == NO_PARENT)
        return;
    printPathTF(parent, parent[vert], file);
    file << " " << vert;
}

void printToFile(int distance[], int parent[], int vertNum, int source, std::fstream & file)
{
    file <<"Vertex \t Distance from Source \t Path" << std::endl;
    for (int i = 0; i < vertNum; i++){
        file  << source << "->" << i << " \t\t"<< distance[i] << "\t\t" << source;
        printPathTF(parent, i, file);
        file << std::endl;
    }
}

void graphM::dijkstraToFile(int source, std::fstream & file){

    int distance[numVert]; // it will hold the sum of distances (shortest possible)
    bool includedSPT[numVert]; // true for the vertex that has already been included to spt
    int parent[numVert]; // index is a vertex and value assigned is parent vertex
    
    for(int i = 0; i < numVert; i++){
        distance[i] = INFINITY, includedSPT[i] = false;
        parent[i] = NO_PARENT; // at first no parents
    }
    distance[source] = 0; // initial vertex marked as included to spt

    for(int i = 0; i < numVert-1; i++){
        int picked = minDistance(distance, includedSPT, numVert);
        includedSPT[picked] = true;

        for(int j = 0; j < numVert; j++){
            if(!includedSPT[j] && adj_matrix[picked][j] && distance[picked] != INFINITY
            && distance[picked] + adj_matrix[picked][j] < distance[j]){
                parent[j] = picked; // the last update will be parent
                distance[j] = distance[picked] + adj_matrix[picked][j]; // upadating distance for adjacent verticies
            }
        }
    }
    printToFile(distance, parent, numVert, source, file);
}