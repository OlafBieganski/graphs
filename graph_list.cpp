#include "graph_list.hh"
#include "priority_queue.hh"
#include <limits.h>
#include <time.h>
#include<sys/time.h>

#define INF INT_MAX
#define NO_PARENT -1
#define END -10

using namespace std;

node::node(int vert, int cost){
    next = NULL;
    vertex = vert;
    weight = cost;
}

//node::node(const node &another){}

/*void node::operator = (const node& another){
    this->vertex = another.vertex;
    this->weight = another.weight;
    next = new node(another.next->vertex, another.next->weight);
}*/

/*node::~node(){
    // probably not necessary to check for null
    if(this->next != NULL) delete this->next;
}*/

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

/*list::~list(){
    delete head;
}*/

void list::add(int vert, int cost){
    if(head == NULL){
        node* newNode = new node(vert, cost);
        head = newNode;
    }
    else{
        head->add(vert, cost);
    }
}

int* node::getAdjVert(){
    int i = 0;
    // count howy many adj verticies
    node* current = this;
    do{
        i++;
        current = current->next;
    }while(current != NULL);
    // create array of sufficient size
    int* result = new int[i+1];
    i = 0;
    current = this;
    do{
        result[i] = current->vertex;
        i++;
        current = current->next;
    }while(current != NULL);
    result[i] = END;
    return result;
}

int* node::getAdjWeights(){
    int i = 0;
    // count howy many adj verticies
    node* current = this;
    do{
        i++;
        current = current->next;
    }while(current != NULL);
    // create array of sufficient size
    int* result = new int[i+1];
    i = 0;
    current = this;
    do{
        result[i] = current->weight;
        i++;
        current = current->next;
    }while(current != NULL);
    result[i] = END;
    return result;
}

// returns ptr to arr of adjacent verticies. Last elem in returned arr is taged as const 'END' 
int* list::getAdjVert(){
    if(head == NULL){
        int *result = new int[1];
        result[0] = END;
        return result;
    }
    return head->getAdjVert();
}

int* list::getAdjWeights(){
    if(head == NULL){
        int *result = new int[1];
        result[0] = END;
        return result;
    }
    return head->getAdjWeights();
}

void list::printList(){
    if(head != NULL)
        head->printList();
}

/*graphL::~graphL(){
    delete[] array;
}*/

graphL::graphL(int vertNum){
    num_of_vertex = vertNum;
    // as many lists as the num of verticies
    array = new list[vertNum];
}

// creates a graph of given verticies number and density
// density ranges between 0-100 (%)
graphL::graphL(int vertNum, int density){
    num_of_vertex = vertNum;
    // as many lists as the num of verticies
    array = new list[vertNum];
    //----part for edges creation----
    // evaluate edges
    int edges = 0.5*density/100*num_of_vertex*(num_of_vertex-1);
    // initial values for connections
    int weight = 0, conNum = num_of_vertex -1, conNum2 = 0;
    // for rand()
    struct timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
    // calculate how many initial concetions and random
    if(edges - conNum < 0){
        conNum = edges;
    } else if(edges - (num_of_vertex-1) > 0){
        conNum2 = edges - (num_of_vertex-1);
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

// returns true if two verts of given idx connected
bool graphL::isEdge(int start, int end){
    if(start < 0 || end < 0 || start >= num_of_vertex || end >= num_of_vertex){
        cerr << "Error in isEgde()." << endl;
        exit(1);
    }
    int *adjVerts = getAdjVert(start);
    // iterate through adj verts and check if end is one of them
    int i = 0;
    while(adjVerts[i] != END){
        if(adjVerts[i] == end) return true;
        i++;
    }
    return false;
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

int* graphL::getAdjVert(int vert){
    return array[vert].getAdjVert();
}

int* graphL::getAdjWeights(int vert){
    return array[vert].getAdjWeights();
}

void printPath1(int parent[], int vert){
    if(parent[vert] == NO_PARENT)
        return;
    printPath1(parent, parent[vert]);
    std::cout << " " << vert;
}

void printSolution1(int distance[], int parent[], int vertNum, int source)
{
    std::cout <<"Vertex \t Distance from Source \t Path" << std::endl;
    for (int i = 0; i < vertNum; i++){
        std::cout  << source << "->" << i << " \t\t"<< distance[i] << "\t\t" << source;
        printPath1(parent, i);
        std::cout << std::endl;
    }
}

void graphL::dijkstra(int src, bool print){
    // check if src in scope
    if(src >= num_of_vertex) return;
    // arrays for final dist and for path to every vert
    int cost[num_of_vertex], parent[num_of_vertex];
    // create priority queue
    priority_queue minHeap(num_of_vertex);
    // set all dist as INF
    for(int i = 0; i < num_of_vertex; i++){
        minHeap.add(i, INF);
        cost[i] = INF; // will be updated in while loop
        parent[i] = NO_PARENT; // at this moment no parent
    }
    //minHeap.print();
    // set source distance as 0
    minHeap.changeDist(src, 0);
    // arrays for adjacent verticies and weights for every checked node
    int *adjVert, *adjCost;
    // upadate distances of adjacent verticies as long as
    // queue is not empty. At each iteration we poll one node with min dist
    // and update dist of its adj vert
    while(!minHeap.isEmpty()){
        //cout << "----------" << endl;
        //minHeap.print();
        heapNode node = minHeap.poll();
        int currVert = node.vert;
        int minDist = node.distance;
        //std::cout << "Picked: " << currVert << std::endl;
        cost[currVert] = minDist;
        adjVert = getAdjVert(currVert);
        adjCost = getAdjWeights(currVert);
        //cout << "ADJACENT VERTICIES" << endl;
        int i = 0;
        /*while(adjVert[i] != END){
            cout << adjVert[i] << '\t' << adjCost[i] << endl;
            i++;
        }
        i = 0;*/
        while(adjVert[i] != END){
            // check if new dist is lower than currently saved and if adj vert is still in queue
            if(cost[adjVert[i]] > adjCost[i] + cost[currVert] && minHeap.isInHeap(adjVert[i])){
                minHeap.changeDist(adjVert[i], adjCost[i] + cost[currVert]);
                cost[adjVert[i]] = adjCost[i] + cost[currVert];
                parent[adjVert[i]] = currVert;
            }
            i++;
        }
        // free memory allocated inside getAdjVert(), getAdjWeights()
        delete[] adjCost;
        delete[] adjVert;
    }
    if(print == true)
        printSolution1(cost, parent, num_of_vertex, src);
}

// performs dijkstra for given src and returns its run-time 
double graphL::dijkstraTime(int src){
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