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

class Graph {
private:
    int num_vertex;
    vector< list<int> > adj_list;
                                         // [NOTE] smart pointer is used to prevent memory leak
    unique_ptr<int[]> color;             // 0:White, 1:Gray, 2:Black
    unique_ptr<int[]> predecessor;       // -1: indicates there is no predecessor and represents it's a starting vertex
    unique_ptr<int[]> discover;          // discovered time in the timeline; for DFS()
    unique_ptr<int[]> distance;          // distance to the starting vertex; for BFS()
    unique_ptr<int[]> finish;            // finished time in the timeline
public:
    Graph() :num_vertex(0) {};
    Graph(int N) :num_vertex(N) {        // constructor with input: number of vertex
        adj_list.resize(num_vertex);     // initialize Adjacency List
                                         // initialize arrays' space with smart pointer
        color.reset(new int[num_vertex]());
        predecessor.reset(new int[num_vertex]());
        discover.reset(new int[num_vertex]());
        distance.reset(new int[num_vertex]());
        finish.reset(new int[num_vertex]());
    };
    ~Graph() {}

    void inline addEdgeList(int from, int to);
    void BFS(int Start);
    void DFS(int Start);
    void DFSVisit(int vertex, int &time);

    void CCDFS(int vertex);                // using DFS find Connected Component
    void CCBFS(int vertex = 0);            // using BFS find Connected Component
    void setCollapsing(int vertex);
    void printPredecessor();               // [optional] print predecessor. it's not necessary.
};

void inline Graph::addEdgeList(int from_vertex, int to_vertex) {
    adj_list[from_vertex].push_back(to_vertex);
}

void Graph::BFS(int starting_vextex) {

    for (int i = 0; i < num_vertex; ++i) {  // Initialize array of vertices status
        color[i] = WHITE;                   // 0: WHITE
        predecessor[i] = NO_PREDECESSOR;    // -1: indicates there is no predecessor
        distance[i] = num_vertex + 1;       // 'longest distance' = num_vertex - 1 (edges)
    }

    queue<int> q;
    int i = starting_vextex;

    for (int j = 0; j < num_vertex; ++j) {  // j is from 0 to vertex-1, hence j can traversal all vertices in the graph

        if (color[i] == WHITE) {            // BFS() starts from i(starting_vextex), as shown in figure 2(c)
            color[i] = GRAY;                // 0:White, 1:Gray, 2:Black
            distance[i] = 0;                // The distance from the starting point of each connected component is set to 0
            predecessor[i] = NO_PREDECESSOR;// The starting point of each connected component has no predecessor
            q.push(i);

            while (!q.empty()) {

                int u = q.front();                         // 'u' is the new starting point
                for (list<int>::iterator itr = adj_list[u].begin();  // traversal the single row of Adjacency List
                    itr != adj_list[u].end();
                    ++itr) {

                    if (color[*itr] == WHITE) {            // if the found vertex is WHITE
                        color[*itr] = GRAY;                // paint it to GRAY. this indicates the vertex has been found.
                        distance[*itr] = distance[u] + 1;  // the new distance is distance of predecessor plus one
                        predecessor[*itr] = u;             // update the predecessor of vertex which has been found
                        q.push(*itr);                      // push vertex into queue
                    }
                }
                q.pop();            // pop out 'u' in the queue
                color[u] = BLACK;   // paint 'u' to black
            }
        }
        // if the loop does not end in one time, it means graph has multiple connected components
        // Then assign j to i, and keep checking which vertex is WHITE. if any vertex is WHITE, repeat the loop.
        i = j;
    }
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

void Graph::setCollapsing(int current) {

    // find the root of certain connected component where the current vertex is
    int root;
    for (root = current; predecessor[root] >= 0; root = predecessor[root]);

    // setCollapsing: connect the vertex to the root
    while (current != root) {
        int parent = predecessor[current];
        predecessor[current] = root;
        current = parent;
    }
}

void Graph::CCDFS(int vertex = 0) {

    DFS(vertex);
    printPredecessor();

    // note that the "current vertex" may not be the last one in the connection
    // hence it should repeat for all vertices in the graph
    for (int i = 0; i< num_vertex; i++)
        setCollapsing(i);

    printPredecessor();

    int num_cc = 0;
    for (int i = 0; i < num_vertex; i++) {
        if (predecessor[i] < 0) {                                    // find the root(i) of certain CC
            cout << "Component#" << ++num_cc << ": " << i << " ";
            for (int j = 0; j < num_vertex; j++) {                   // and find how many vertices(j) connect to the root(i)
                if (predecessor[j] == i) {
                    cout << j << " ";
                }
            }
            cout << endl;
        }
    }
}

void Graph::CCBFS(int vertex) {

    BFS(vertex);
    printPredecessor();

    // note that the "current vertex" may not be the last one in the connection
    // hence it should repeat for all vertices in the graph
    for (int i = 0; i< num_vertex; i++)
        setCollapsing(i);

    printPredecessor();

    int num_cc = 0;
    for (int i = 0; i < num_vertex; i++) {
        if (predecessor[i] < 0) {                                     // find the root(i) of certain CC
            cout << "Component#" << ++num_cc << ": " << i << " ";
            for (int j = 0; j < num_vertex; j++) {                    // and find how many vertices(j) connect to the root(i)
                if (predecessor[j] == i) {
                    cout << j << " ";
                }
            }
            cout << endl;
        }
    }
}
void Graph::printPredecessor() {
    cout << "predecessor:" << endl;

    for (int i = 0; i < num_vertex; i++)
        cout << std::setw(4) << i;

    cout << endl;

    for (int i = 0; i < num_vertex; i++)
        cout << std::setw(4) << predecessor[i];

    cout << endl;
}

int main() {

    int number_of_vertex = 9;
    Graph g3(number_of_vertex);

    g3.addEdgeList(0, 1);
    g3.addEdgeList(1, 0); g3.addEdgeList(1, 4); g3.addEdgeList(1, 5);
    // adj_list[2] is empty
    g3.addEdgeList(3, 6);
    g3.addEdgeList(4, 1); g3.addEdgeList(4, 5);
    g3.addEdgeList(5, 1); g3.addEdgeList(5, 4); g3.addEdgeList(5, 7);
    g3.addEdgeList(6, 3); g3.addEdgeList(6, 8);
    g3.addEdgeList(7, 5);
    g3.addEdgeList(8, 6);

    cout << "CCDFS():" << endl;
    g3.CCDFS();
    cout << endl;

    cout << "CCBFS():" << endl;
    g3.CCBFS();
    cout << endl;

    g3.~Graph();

    std::cin.get();
    return 0;
}