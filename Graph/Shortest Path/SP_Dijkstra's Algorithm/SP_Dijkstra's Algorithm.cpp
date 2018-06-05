#include <iostream>
#include <vector>
#include <list>
#include <memory>           // for std::unique_ptr
#include <utility>          // for std::pair<>
#include <iomanip>          // for std::setw()
#include "Priority_Queue_BinaryHeap.h"

using std::unique_ptr;
using std::vector;
using std::list;
using std::pair;
using std::cout;
using std::endl;

enum Vertex_Color {
    WHITE = 0,
    GRAY = 1,
    BLACK = 2
};

enum Vertex_Predecessor {
    NO_PREDECESSOR = -1
};

const int MAX_DISTANCE = 100;

class Graph_SP {             // SP serves as Shortest Path
private:
    int num_vertex;
    vector< list< pair<int, int> > > adj_list;
    vector<int> visited;
    vector<int> predecessor;
    vector<int> distance;
public:
    Graph_SP() :num_vertex(0) {};
    Graph_SP(int n) :num_vertex(n) {
        adj_list.resize(num_vertex);
    }
    ~Graph_SP() {};

    void addEdge(int from, int to, int weight);
    void printDataArray(vector<int>& array);
    void printIntArray(unique_ptr<int[]>& array);

    void initializeSingleSource(int Start);     // 'Start' is starting point
    void relax(int X, int Y, int weight);       // do relax() to edge(X,Y)

    void Dijkstra(int Start);
};

void Graph_SP::Dijkstra(int Start) {

    initializeSingleSource(Start);

    BinaryHeap minQueue(num_vertex);    // object of min queue
    minQueue.buildMinHeap(distance);

    visited.resize(num_vertex, false);   // initializa visited[] as {0,0,0,...,0}

    while (!minQueue.isHeapEmpty()) {
        int u = minQueue.extractMin();
        for (std::list<std::pair<int, int>>::iterator itr = adj_list[u].begin();
            itr != adj_list[u].end(); ++itr) {

            relax(u, (*itr).first, (*itr).second);
            minQueue.decreaseKey((*itr).first, distance[(*itr).first]);
        }
    }
    cout << "\nprint predecessor:\n";
    printDataArray(predecessor);
    cout << "\nprint distance:\n";
    printDataArray(distance);
}

void Graph_SP::printDataArray(vector<int>& array) {
    for (int i = 0; i < num_vertex; ++i)
        cout << std::setw(4) << i;
    cout << endl;
    for (int i = 0; i < num_vertex; ++i)
        cout << std::setw(4) << array[i];
    cout << endl;
}

void Graph_SP::printIntArray(unique_ptr<int[]>& array) {
    for (int i = 0; i < num_vertex; ++i)
        cout << std::setw(4) << i;
    cout << endl;
    for (int i = 0; i < num_vertex; ++i)
        cout << std::setw(4) << array[i];
    cout << endl;
}

void Graph_SP::initializeSingleSource(int Start) {

    distance.resize(num_vertex);
    predecessor.resize(num_vertex);

    for (int i = 0; i < num_vertex; ++i) {
        distance[i] = MAX_DISTANCE;
        predecessor[i] = NO_PREDECESSOR;
    }
    distance[Start] = 0;          // set the staring point
}

void Graph_SP::relax(int from, int to, int weight) {

    if (distance[to] > distance[from] + weight) {
        distance[to] = distance[from] + weight;
        predecessor[to] = from;
    }
}

void Graph_SP::addEdge(int from, int to, int weight) {
    adj_list[from].push_back(std::make_pair(to, weight));
}

int main() {

    Graph_SP g9(6);
    g9.addEdge(0, 1, 8); g9.addEdge(0, 5, 1);
    g9.addEdge(1, 0, 3); g9.addEdge(1, 2, 1);
    g9.addEdge(2, 0, 5); g9.addEdge(2, 3, 2); g9.addEdge(2, 4, 2);
    g9.addEdge(3, 1, 4); g9.addEdge(3, 2, 6); g9.addEdge(3, 4, 7); g9.addEdge(3, 5, 3);
    g9.addEdge(5, 3, 2); g9.addEdge(5, 4, 8);

    g9.Dijkstra(0);       // set vertex(0) as staring point

    g9.~Graph_SP();

    std::cin.get();
    return 0;
}