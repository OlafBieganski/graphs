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
    int* getAdjVert();
    int* getAdjWeights();
};

class list {
    node* head;
    public:
    list(){head = NULL;}
    void add(int vert, int cost);
    void printList();
    int* getAdjVert();
    int* getAdjWeights();
};

class graphL {
    // ilość wierzchołków w grafie
    int num_of_vertex;
    // lista sąsiedztwa w grafie
    list* array;
    public:
    graphL(int vertNum);
    graphL(int vertNum, int density);
    graphL(): num_of_vertex(0), array(nullptr) {};
    bool addEdge(int start, int end, int weight);
    // for tests
    void printAdjLists();
    void dijkstra(int src, bool print = true);
    int* getAdjVert(int vert);
    int* getAdjWeights(int vert);
    bool isEdge(int start, int end);
    double dijkstraTime(int src);
};

#endif