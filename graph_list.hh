#ifndef GRAPH_L
#define GRAPH_L
#include <iostream>

class node {
    int vertex, weight;
    node* next;
    public:
    node(int vert, int cost);
    void add(int vert, int cost);
    bool isNextNull(){return next == NULL;}
    void printList();
    void getAdjVert(int *result);
    void getAdjWeights(int *result);
};

class list {
    node* head;
    public:
    list(){head = NULL;}
    void add(int vert, int cost);
    void printList();
    void getAdjVert(int result[]);
    void getAdjWeights(int result[]);
};

class graphL {
    // ilość wierzchołków w grafie
    int num_of_vertex;
    // lista sąsiedztwa w grafie
    list* array;
    public:
    graphL(int vertNum);
    bool addEdge(int start, int end, int weight);
    // dla testów
    void printAdjLists();
    void dijkstra(int src);
    void getAdjVert(int vert, int *result);
    void getAdjWeights(int vert, int *result);
};

#endif