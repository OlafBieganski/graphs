#ifndef PQUEUE
#define PQUEUE

struct heapNode {
    int vert;
    int distance = 0;
    heapNode(int vert, int dist): vert(vert), distance(dist) {}
    heapNode();
};


class priority_queue{
    heapNode *array = nullptr;
    // index in position array represents vertex
    // and its assigned value is idx in heap array
    int *position = nullptr;
    int heapSize = 0; // how many elems is curr in heap
    int heapCapacity = 0;
    void bubbleUp(int idx);
    void bubbleDown();
    public:
    priority_queue(int capacity);
    void add(int vert, int dist);
    heapNode poll();
    void swapNodes(int a, int b);
    bool isEmpty();
    bool isInHeap(int vert);
    void changeDist(int vert,int newDist);
};

#endif