#include "graph_list.hh"
#include "graph_matrix.hh"

using namespace std;

int main(){
    cout << "Graph implemented on adjacency list." << endl;
    graphL graph(4);
    graph.addEdge(0,1,1);
    graph.addEdge(1,2,2);
    graph.addEdge(2,3,3);
    graph.addEdge(1,3,1);
    graph.addEdge(1,4,1);
    graph.printAdjLists();

    cout << "Graph implemented on adjacency matrix." << endl;
    graphM graphM(4);
    graphM.addEdge(0,1,1);
    graphM.addEdge(1,2,2);
    graphM.addEdge(2,3,3);
    graphM.addEdge(1,3,1);
    graphM.addEdge(1,4,1);
    graphM.printAdjLists();

    return 0;
}