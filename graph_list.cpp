#include "graph_list.hh"

using namespace std;

node::node(int vert, int cost){
    next = NULL;
    vertex = vert;
    weight = cost;
}

void node::add(int vert, int cost){
    node* current = this;
    while(current->next != NULL){
        current = current->next;
    }
    node* newNode = new node(vert, cost);
    current->next = newNode;
}

void node::printList(){
    node* current = this;
    do{
        cout << current->vertex << '\t' << current->weight << endl;
        current = current->next;
    }while(current != NULL);
}

void list::add(int vert, int cost){
    if(head == NULL){
        node* newNode = new node(vert, cost);
        head = newNode;
    }
    else{
        head->add(vert, cost);
    }
}

void list::printList(){
    if(head != NULL)
        head->printList();
}

graphL::graphL(int vertNum){
    num_of_vertex = vertNum;
    // tyle list ile wierzchołkow
    array = new list[vertNum];
}

bool graphL::addEdge(int start, int end, int weight){
    // krawedzie nie moga byc ujemnie indeksowane
    if(start < 0 || end < 0) return false;

    // nie mozna dodac polaczenia z krawedzia ktora nei istneije
    if(start < num_of_vertex && end < num_of_vertex){
        array[start].add(end, weight);
        array[end].add(start, weight);
        return true;
    }
    return false;
}

void graphL::printAdjLists(){
    cout << "Sasiad | waga" << endl;
    for(int i = 0; i < num_of_vertex; i++){
        cout << "Lista sasiedztwa dla wiercholka "
         << i << ":" <<endl;
        array[i].printList();
    }
}