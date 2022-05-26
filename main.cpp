#include "graph_list.hh"
#include "graph_matrix.hh"
#include "priority_queue.hh"
#include <fstream>

#define LOG(x) std::cout << x << std::endl

using namespace std;

void genereteTimeFile();
void readGraph();
void writeGraph();

int main(){
    while(true){
        LOG("MENU:");
        LOG("1. Generate file with algorithm runtime.");
        LOG("2. Read graph from file.");
        LOG("3. Save dijkstra algorith output to file.");
        LOG("4. Terminate program.");
        LOG("Input number from 1 to 4:");
        int userInput = 0;
        cin >> userInput;
        switch(userInput){
            case 1:
                genereteTimeFile();
                return 0;
            case 2:
                readGraph();
                break;
            case 3:
                writeGraph();
                break;
            case 4:
                return 0;
            default:
                LOG("Invalid option.");
                break;
        }
    }
    return 0;
}


void genereteTimeFile(){
    int vertNumbers[5] = {10, 20, 50, 75, 100};
    int density[4] = {25, 50, 75, 100};
    string names[4] = {"25%", "50%", "75%", "100%"};
    graphL graphList[4][5][100];
    graphM graphMatrix[4][5][100];
    string filename;

    // type name of file
    LOG("Type output file name:");
    cin >> filename;
    cout << "Are sure sure you want to write to file " << filename << " ?" << endl;
    cin.get();
    cin.get();

    // fill array with proper graphs
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++){
            LOG("Work in progress:");
            LOG(j);
            for(int k = 0; k < 100; k++){
                graphList[i][j][k] = graphL(vertNumbers[j], density[i]);
                graphMatrix[i][j][k] = graphM(vertNumbers[j], density[i]);
            }
        }
    }

    // open file
    fstream File;
    File.open(filename, ios::app);
    if(!File.is_open()){
        LOG("File opening error.");
        exit(1);
    }

    // do dijkstra for list and save time for each case
    double elapsedTime = 0;

    File << "Adjacency List" << '\n';
    File << "\t10" << "\t20"<< "\t50"<< "\t75"<< "\t100" << '\n';
    for(int i = 0; i < 4; i++){
        File << names[i] << '\t';
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 100; k++){
                elapsedTime += graphList[i][j][k].dijkstraTime(0);
            }
            File << fixed << elapsedTime/100 << '\t';
        }
        File << '\n';
        elapsedTime = 0;
    }

    File << '\n';
    elapsedTime = 0;

    File << "Adjacency Matrix" << '\n';
    File << "\t10" << "\t20"<< "\t50"<< "\t75"<< "\t100" << '\n';
    for(int i = 0; i < 4; i++){
        File << names[i] << '\t';
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 100; k++){
                elapsedTime += graphMatrix[i][j][k].dijkstraTime(0);
            }
            File << fixed << elapsedTime/100 << '\t';
        }
        File << '\n';
        elapsedTime = 0;
    }

    File.close();
}

void readGraph(){
    // type name of input file
    string filename;
    LOG("Type graph data file name:");
    cin >> filename;

    ifstream File;
    File.open(filename, ios::in);
    if(!File.is_open()){
        LOG("File opening error.");
        exit(1);
    }

    int E, V, src, start, end, cost;
    File >> E >> V >> src;
    graphL graph(V);
    for(int i = 0; i < E; i++){
        File >> start >> end >> cost;
        graph.addEdge(start, end, cost);
    }
    graph.printAdjLists();
    graph.dijkstra(src);
    File.close();
}

void writeGraph(){
    string filename;
    LOG("Type dijkstra output data file name:");
    cin >> filename;

    fstream File;
    File.open(filename, ios::out);
    if(!File.is_open()){
        LOG("File opening error.");
        exit(1);
    }

    int vertNum, density;
    LOG("Type number of verticies:");
    cin >> vertNum;
    LOG("Type density value:");
    cin >> density;
    graphM graph(vertNum, density);
    graph.dijkstraToFile(0, File);
    File.close();
}