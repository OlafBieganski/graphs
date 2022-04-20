#include "graph_list.hh"

using namespace std;

node::node(int vert, int cost){
    next = NULL;
    vertex = vert;
    weight = cost;
}

node::node(){
    
}

void node::add(int vert, int cost){
    node* current = this;
    while(current->next != NULL){
        current = current->next;
    }
    node* newNode = new node();
    newNode->next = NULL;
    newNode->vertex = vert;
    newNode->weight = cost;
    current->next = newNode;
}

void node::printList(){
    node* current = this;
    do{
        cout << current->vertex << '\t' << current->weight << endl;
        current = current->next;
    }while(current != NULL);
}

graphL::graphL(int vertNum){
    num_of_vertex = vertNum;
    // tyle list ile wierzchołkow
    array = new node[vertNum];
}

void graphL::addEdge(int start, int end, int weight){
    array[start].add(end, weight);
    array[end].add(start, weight);
}

void graphL::printAdjLists(){
    for(int i = 0; i < num_of_vertex; i++){
        array[i].printList();
    }
}