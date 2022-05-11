#ifndef GRAPH_M
#define GRAPH_M

class graphM {
    int numVert;
    int** adj_matrix;
    public:
    graphM(int vertNum);
    bool addEdge(int start, int end, int weight);
    void printAdjList();
};

#endif