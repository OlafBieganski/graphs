#ifndef PQUEUE
#define PQUEUE

#define UNDEF_VERT -2
#define UNDEF_DIST -3

struct heapNode {
    int vert;
    int distance;
    heapNode(int vert, int dist): vert(vert), distance(dist) {}
    heapNode(): vert(UNDEF_VERT), distance(UNDEF_DIST) {}
};


class priority_queue{
    heapNode *array = nullptr;
    // index in position array represents vertex
    // and its assigned value is idx in heap array
    int *position = nullptr;
    int heapSize = 0; // how many elems is curr in heap
    int heapCapacity = 0;
    void bubbleUp(int idx);
    void bubbleDown(int idx);
    void swapNodes(int a, int b);
    heapNode removeNode(int idx);
    public:
    priority_queue(int capacity);
    void add(int vert, int dist);
    heapNode poll();
    bool isEmpty();
    bool isInHeap(int vert);
    void changeDist(int vert,int newDist);
    bool less(int a, int b);
};

#endif