#include "priority_queue.hh"
#include <cstdlib>

priority_queue::priority_queue(int capacity){
    if(capacity <= 0) exit(0);
    heapSize = 0;
    heapCapacity = capacity;
    array = new heapNode[heapCapacity];
    position = new int[heapCapacity];
}

bool priority_queue::isEmpty(){
    return !heapSize; // if heapSize 0 returns true
}

void  priority_queue::swapNodes(int a, int b){
    heapNode temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

void priority_queue::bubbleUp(int idx){
    if(this->isEmpty() || heapSize == 1) return;
    int i =idx;
    // check if child is greater than parent and child is not zero or less
    while(array[i].distance < array[(i-1)/2].distance && i){
        swapNodes(i, (i-1)/2);
        i = (i-1)/2;
    }
}

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

