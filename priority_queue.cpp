#include "priority_queue.hh"
#include <cstdlib>
#include <iostream>

#define NOT_INCLUDED -1

using namespace std;

priority_queue::priority_queue(int capacity){
    if(capacity <= 0){
        cout << "Error in priority_queue::priority_queue(int capacity). Incorrect param."
        << endl;
        exit(1);
    }
    heapSize = 0;
    heapCapacity = capacity;
    array = new heapNode[heapCapacity];
    position = new int[heapCapacity];
    for(int i = 0; i < heapCapacity; i++){
        position[i] = NOT_INCLUDED;
    }
}

// true if queue is empty
bool priority_queue::isEmpty(){
    return !heapSize; // if heapSize 0 returns true
}

// swap two nodes in heap
void  priority_queue::swapNodes(int a, int b){
    heapNode temp = array[a];
    position[array[a].vert] = position[array[b].vert];
    array[a] = array[b];
    position[array[b].vert] = position[temp.vert];
    array[b] = temp;
}

// bubbles up the node if possible and necessary
void priority_queue::bubbleUp(int idx){
    if(isEmpty() || heapSize == 1) return;
    int child = idx, parent = (idx-1)/2;
    // check if child is lesser than parent and child is not zero idx or less
    while(less(child, parent) && child > 0){
        swapNodes(child, parent);
        child = parent;
        parent = (child - 1)/2;
    }
}

// bubbles down the node if possible and necessary
void priority_queue::bubbleDown(int idx){
    if(isEmpty() || heapSize == 1) return;
    int node = idx, child = idx;
    int leftChild = 2*node + 1;
    int rightChild = 2*node + 2;
    // check which child is suitable for swap if any at all
    if(leftChild < heapSize && less(leftChild, child)){
        child = leftChild;
    }
    if(rightChild < heapSize && less(rightChild, child)){
        child = rightChild;
    }
    // perform bubbling down
    if(child != idx){
        swapNodes(node, child);
        bubbleDown(child); // continue bubbling 
    }
}

// adds new node to heap with with given data and sorts heap
void priority_queue::add(int vert, int dist){
    if(heapSize >= heapCapacity) // check if queue is full
        return;
    // if empty
    if(this->isEmpty()){ 
        array[0] = heapNode(vert, dist);
        position[vert] = 0;    
    }
    else{
        array[heapSize] = heapNode(vert, dist);
        position[vert] = heapSize;
        bubbleUp(heapSize);
    }
    heapSize++;
}

// returns true if node at idx 'a' is lesser than at 'b'
bool priority_queue::less(int a, int b){
    if(!(a < heapSize && b < heapSize)){
        cout << "Error in bool priority_queue::less(int a, int b). Out of scope."
        << endl;
        exit(1);
    }
    return array[a].distance < array[b].distance;
}

// finds vertex in minHeap and changes its distance
void priority_queue::changeDist(int vert,int newDist){
    if(!isInHeap(vert)) return;
    int node = position[vert];
    int parent = (node-1)/2;
    array[node].distance = newDist;
    bubbleUp(node);
    bubbleDown(node);
}

// check if vertex is in queue
bool priority_queue::isInHeap(int vert){
    return position[vert] != NOT_INCLUDED;
}

heapNode priority_queue::poll(){
    return removeNode(0);
}

heapNode priority_queue::removeNode(int idx){
    heapNode result;
    int last_index = heapSize - 1;
    if(isEmpty() || idx > last_index || idx < 0){
        cerr << "Error in remove(int idx)." << endl;
        exit(1);
    }
    swapNodes(idx, last_index);
    heapSize--;
    result = array[last_index];
    array[last_index] = heapNode();
    bubbleDown(0);
    return result;
}