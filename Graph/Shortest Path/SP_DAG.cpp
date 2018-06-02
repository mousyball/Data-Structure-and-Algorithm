#include <iostream>
#include <vector>
#include <list>
#include <memory>           // for std::unique_ptr
#include <utility>          // for std::pair<>
#include <iomanip>          // for std::setw()

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
    vector<int> predecessor;
    vector<int> distance;
public:
    Graph_SP() :num_vertex(0) {};
    Graph_SP(int n) :num_vertex(n) {
        adj_list.resize(num_vertex);
    }
    ~Graph_SP() {};

    void addEdge(int from, int to, int weight);
    void printDataArray(vector<int> array);
    void printIntArray(unique_ptr<int[]>& array);

    void initializeSingleSource(int Start);     // 'Start' is starting point
    void relax(int X, int Y, int weight);       // do relax() to edge(X,Y)

    void DAG_SP(int Start = 0);                 // DFS + topological sort
    void getTopologicalSort(unique_ptr<int[]>& array, int Start);
    void DFSVisit_TS(unique_ptr<int[]>& array, unique_ptr<int[]>& color, unique_ptr<int[]>& discover,
        unique_ptr<int[]>& finish, int vertex, int &time, int &count);

};

void Graph_SP::getTopologicalSort(unique_ptr<int[]>& array, int Start) {

    //int color[num_vertex], discover[num_vertex], finish[num_vertex];
    unique_ptr<int[]> color (new int[num_vertex]);
    unique_ptr<int[]> discover(new int[num_vertex]);
    unique_ptr<int[]> finish(new int[num_vertex]);

    for (int i = 0; i < num_vertex; ++i) {
        color[i] = WHITE;
        discover[i] = 0;
        finish[i] = 0;
        predecessor[i] = NO_PREDECESSOR;
    }

    int time = 0;
    int count = num_vertex - 1;        // 'count' is the index of topologicalsort[]
    int i = Start;

    // DFS algorithm
    for (int j = 0; j < num_vertex; ++j) {
        if (color[i] == WHITE) {
            DFSVisit_TS(array, color, discover, finish, i, time, count);
        }
        i = j;
    }
    cout << "\nprint discover time:\n";
    printIntArray(discover);
    cout << "\nprint finish time:\n";
    printIntArray(finish);
}

void Graph_SP::DFSVisit_TS(unique_ptr<int[]>& array, unique_ptr<int[]>& color, unique_ptr<int[]>& discover,
    unique_ptr<int[]>& finish, int vertex, int &time, int &count) {

    color[vertex] = GRAY;         // set gray
    discover[vertex] = ++time;

    // DFS algorithm
    for (list< pair<int, int> >::iterator itr = adj_list[vertex].begin();
        itr != adj_list[vertex].end(); ++itr) {
        if (color[(*itr).first] == WHITE) {
            predecessor[(*itr).first] = vertex;
            DFSVisit_TS(array, color, discover, finish, (*itr).first, time, count);
        }
    }

    color[vertex] = BLACK;        // set black
    finish[vertex] = ++time;
    array[count--] = vertex;      // [KEY_POINT] generate topological sort
}
void Graph_SP::DAG_SP(int Start) {

    initializeSingleSource(Start);                 // initialization of distance[] and predecessor[]

    unique_ptr<int[]> topological_sort (new int[num_vertex]);
    getTopologicalSort(topological_sort, Start);   // use a array to store topological sort in DFS

    for (int i = 0; i < num_vertex; ++i) {         // follow the topological sort to execute relax() to each edge of vertex.
        int v = topological_sort[i];
        for (list< pair<int, int> >::iterator itr = adj_list[v].begin();
            itr != adj_list[v].end(); ++itr) {
            relax(v, (*itr).first, (*itr).second);
        }
    }
    cout << "\nprint predecessor:\n";
    printDataArray(predecessor);
    cout << "\nprint distance:\n";
    printDataArray(distance);
}

void Graph_SP::printDataArray(vector<int> array) {
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

    Graph_SP g8(7);
    g8.addEdge(0, 1, 3); g8.addEdge(0, 2, -2);
    g8.addEdge(1, 3, -4); g8.addEdge(1, 4, 4);
    g8.addEdge(2, 4, 5); g8.addEdge(2, 5, 6);
    g8.addEdge(3, 5, 8); g8.addEdge(3, 6, 2);
    g8.addEdge(4, 3, -3); g8.addEdge(4, 6, -2);
    g8.addEdge(5, 6, 2);

    g8.DAG_SP(0);         // set vertex(0) as staring point

    g8.~Graph_SP();

    std::cin.get();
    return 0;
}