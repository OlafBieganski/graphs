#include <iostream>

class node {
    int vertex, weight;
    node* next;
    public:
    node(int vert, int cost);
    node();
    void add(int vert, int cost);
    bool isNextNull(){if(next == NULL){return true;}else{return false;}}
    void printList();
};



class graphL {
    // ilość wierzchołków w grafie
    int num_of_vertex;
    // lista sąsiedztwa w grafie
    node* array;
    public:
    graphL(int vertNum);
    void addEdge(int start, int end, int weight);
    // dla testów
    void printAdjLists();
};