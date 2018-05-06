#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <memory>
#include <iomanip>      // for std::setw()

using std::vector;
using std::list;
using std::queue;
using std::cout;
using std::endl;
using std::unique_ptr;

enum Vertex_Color {
    WHITE = 0,
    GRAY = 1,
    BLACK = 2
};

enum Vertex_Predecessor {
    NO_PREDECESSOR = -1
};

enum Vertex_Name {
    A, B, C, D, E, F, G, H               // value starts from 0 to 7
};

int map_to_ascii(int num);

class Graph {
private:
    int num_vertex;
    vector< list<int> > adj_list;
                                         // [NOTE] smart pointer is used to prevent memory leak
    unique_ptr<int[]> color;             // 0:White, 1:Gray, 2:Black
    unique_ptr<int[]> predecessor;       // -1: indicates there is no predecessor and represents it's a starting vertex
    unique_ptr<int[]> discover;          // discovered time in the timeline
    unique_ptr<int[]> finish;            // finished time in the timeline
public:
    Graph() :num_vertex(0) {};
    Graph(int N) :num_vertex(N) {        // constructor with input: number of vertex										 
        adj_list.resize(num_vertex);     // initialize Adjacency List
                                         // initialize arrays' space with smart pointer
        color.reset(new int[num_vertex]());
        predecessor.reset(new int[num_vertex]());
        discover.reset(new int[num_vertex]());
        finish.reset(new int[num_vertex]());
    };
    ~Graph() {}

    void inline addEdgeList(int from, int to);
    void DFS(int Start);
    void DFSVisit(int vertex, int &time);
    void printStatus();
};

void inline Graph::addEdgeList(int from_vertex, int to_vertex) {
    adj_list[from_vertex].push_back(to_vertex);
}

void Graph::DFS(int Start) {

    int time = 0;                          // initialization
    for (int i = 0; i < num_vertex; ++i) {
        color[i] = WHITE;
        discover[i] = 0;
        finish[i] = 0;
        predecessor[i] = NO_PREDECESSOR;
    }

    int i = Start;
    for (int j = 0; j < num_vertex; j++) { // traversal of the graph makes sure all vertices be checked.
        if (color[i] == WHITE) {           // if vertex isn't WHITE, use this vertex as a starting point to do the visiting stuff
            DFSVisit(i, time);
        }

        // if the loop does not end in one time, it means graph has multiple connected components
        // Then assign j to i, and keep checking which vertex is WHITE. if any vertex is WHITE, repeat the loop.
        i = j;
    }
}

void Graph::DFSVisit(int vertex, int &time) {  // if any vertex is WHITE, get into DFSVisit()
    color[vertex] = GRAY;                      // paint the vertex to gray
    discover[vertex] = ++time;                 // update discovered time of vertex
    for (list<int>::iterator itr = adj_list[vertex].begin();
        itr != adj_list[vertex].end(); 
        ++itr) {
        if (color[*itr] == WHITE) {            // if a WHITE vertex is searched,
            predecessor[*itr] = vertex;        // update its predecessor
            DFSVisit(*itr, time);              // use this vertex as a new starting point to get into the new DFSVisit()
        }
    }
    color[vertex] = BLACK;                     // if the traversal in a row of adj_list is done, make the vertex to BLACK
    finish[vertex] = ++time;                   // update its finished time
}

void Graph::printStatus()
{
    cout << "predecessor:" << endl;          // predecessor: A(0) ~ H(7)
    for (char i = 'A'; i <= 'H'; ++i)
        cout << std::setw(4) << i;
    cout << endl;

    for (int i = 0; i < num_vertex; ++i) {
        int vertex_name_int = map_to_ascii(predecessor[i]);

        if (vertex_name_int >= 0)
            cout << std::setw(4) << static_cast<char>(vertex_name_int);
        else
            cout << std::setw(4) << -1;
    }

    cout << "\ndiscovered time:" << endl;    // discover time: A(0) ~ H(7)
    for (char i = 'A'; i <= 'H'; ++i)
        cout << std::setw(4) << i;
    cout << endl;

    for (int i = 0; i < num_vertex; ++i)
        cout << std::setw(4) << discover[i];

    cout << "\nfinished time:" << endl;      // finish time: A(0) ~ H(7)
    for (char i = 'A'; i <= 'H'; ++i)
        cout << std::setw(4) << i;
    cout << endl;

    for (int i = 0; i < num_vertex; ++i)
        cout << std::setw(4) << finish[i];

}

int map_to_ascii(int num)
{
    if (num >= 0)
        return static_cast<int>('A') + num;
    else
        return -1;
}

int main() {

    int number_of_vertex = 8;
    Graph g2(number_of_vertex);

    // According to figure 3, we can build an Adjacency List.
    g2.addEdgeList(A, B); g2.addEdgeList(A, C);
    g2.addEdgeList(B, D);
    g2.addEdgeList(C, B); g2.addEdgeList(C, F);
    g2.addEdgeList(D, E); g2.addEdgeList(D, F);
    // AdjList[4] is empty
    g2.addEdgeList(F, B);
    g2.addEdgeList(G, E); g2.addEdgeList(G, H);
    g2.addEdgeList(H, G);

    g2.DFS(A);
    
    cout << "Depth-First Search():\n" << endl;
    g2.printStatus();

    g2.~Graph();

    std::cin.get();
    return 0;
}