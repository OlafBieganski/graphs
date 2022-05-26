#ifndef GRAPH_M
#define GRAPH_M
#include <fstream>

class graphM {
    int numVert;
    int** adj_matrix;
    public:
    graphM(int vertNum);
    graphM(int vertNum, int density);
    graphM(): numVert(0), adj_matrix(nullptr) {};
    bool addEdge(int start, int end, int weight);
    void printAdjLists();
    void dijkstra(int source, bool print = true);
    bool isEdge(int start, int end);
    double dijkstraTime(int src);
    void dijkstraToFile(int source, std::fstream & file);
};

#endif