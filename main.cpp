#include "graph_list.hh"
#include "graph_matrix.hh"
#include "priority_queue.hh"

using namespace std;

int main(){

    priority_queue minHeap(7);
    for(int i = 0; i < 5; i++){
        minHeap.add(i, 10);
    }

    minHeap.add(5, 1);
    minHeap.add(6, 4);
    minHeap.changeDist(4,0);
    minHeap.changeDist(2,2);
    minHeap.poll();
    minHeap.poll();
    minHeap.print();

    /*
    cout << "Graph implemented on adjacency list." << endl;
    graphL graph(7);
    graph.addEdge(0,1,1);
    graph.addEdge(1,2,2);
    graph.addEdge(2,3,3);
    graph.addEdge(1,3,1);
    graph.addEdge(0,3,3);
    graph.addEdge(3,6,1);
    graph.addEdge(6,2,4);
    graph.addEdge(1,4,5);
    graph.addEdge(4,2,1);
    graph.addEdge(2,5,3);
    graph.addEdge(5,4,1);
    graph.printAdjLists();
    graph.dijkstra(1);

    cout << "Graph implemented on adjacency matrix." << endl;
    graphM graphM(7);
    graphM.addEdge(0,1,1);
    graphM.addEdge(1,2,2);
    graphM.addEdge(2,3,3);
    graphM.addEdge(1,3,1);
    graphM.addEdge(1,4,1);
    graphM.addEdge(0,3,3);
    graphM.addEdge(3,6,1);
    graphM.addEdge(6,2,4);
    graphM.addEdge(1,4,5);
    graphM.addEdge(4,2,1);
    graphM.addEdge(2,5,3);
    graphM.addEdge(5,4,1);
    graphM.printAdjLists();

    cout << "Dijkstra algorithm:" << endl;
    graphM.dijkstra(0);
*/
    return 0;
}