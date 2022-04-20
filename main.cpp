#include "graph_list.hh"

using namespace std;

int main(){
    graphL graph(4);
    graph.addEdge(0,1,1);
    graph.addEdge(1,2,2);
    graph.addEdge(2,3,3);
    graph.addEdge(1,3,1);
    graph.addEdge(1,4,1);
    graph.printAdjLists();
    return 0;
}