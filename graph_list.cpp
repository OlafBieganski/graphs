#include "graph_list.hh"
#include "priority_queue.hh"
#include <limits.h>

#define INF INT_MAX
#define NO_PARENT -1
#define END -10

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

void node::getAdjVert(int *result){
    int i = 0;
    // count howy many adj verticies
    do{
        i++;
    }while(next != NULL);
    // create array of sufficient size
    int *arr = new int[i+1];
    i = 0;
    node* current = this;
    do{
        arr[i] = current->vertex;
        i++;
        current = current->next;
    }while(current->next != NULL);
    arr[i+1] = END;
    result = arr;
}

void node::getAdjWeights(int *result){
    int i = 0;
    // count howy many adj verticies
    do{
        i++;
    }while(next != NULL);
    // create array of sufficient size
    int *arr = new int[i+1];
    i = 0;
    node* current = this;
    do{
        arr[i] = current->weight;
        i++;
        current = current->next;
    }while(current->next != NULL);
    arr[i+1] = END;
    result = arr;
}

void list::getAdjVert(int result[]){
    head->getAdjVert(result);
}

void list::getAdjWeights(int result[]){
    head->getAdjWeights(result);
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

// adds an egde between two nodes
// params: start node, end node, weight
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

void graphL::getAdjVert(int vert, int *result){
    array[vert].getAdjVert(result);
}

void graphL::getAdjWeights(int vert, int *result){
    array[vert].getAdjWeights(result);
}

void graphL::dijkstra(int src){
    // check if src in scope
    if(src >= num_of_vertex) return;
    // arrays for final dist and for path to every vert
    int cost[num_of_vertex], parent[num_of_vertex];
    // create priority queue
    priority_queue minHeap(num_of_vertex);
    // set all dist as INF
    for(int i = 0; i < num_of_vertex; i++){
        minHeap.add(i, INF);
        cost[i] = INF;
    }
    // set source distance as 0
    minHeap.changeDist(src, 0);
    // src has no parent vertex
    parent[src] = NO_PARENT;
    // arrays for adjacent verticies and weights for every checked node
    int *adjVert, *adjCost;
    // upadate distances of adjacent verticies as long as
    // queue is not empty. At each iteration we poll one node with min dist
    // and update dist of its adj vert
    while(!minHeap.isEmpty()){
        heapNode node = minHeap.poll();
        int currVert = node.vert;
        int minDist = node.distance;
        cost[currVert] = minDist;
        getAdjVert(currVert, adjVert);
        getAdjWeights(currVert, adjCost);
        int i = 0;
        while(adjVert[i] != END){
            // check if new dist is lower than currently saved and if adj vert is still in queue
            if(cost[adjVert[i]] > adjCost[i] + cost[currVert] && minHeap.isInHeap(adjVert[i])){
                minHeap.changeDist(adjVert[i], adjCost[i] + cost[currVert]);
                parent[adjVert[i]] = currVert;
            }
            i++;
        }
    }
}