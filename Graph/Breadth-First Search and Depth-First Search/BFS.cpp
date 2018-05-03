#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <memory>

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
    A, B, C, D, E, F, G, H, I            // value starts from 0 to I
};

class Graph {
private:
    int num_vertex;
    vector< list<int> > adj_list;
                            // [NOTE] color, distance, predecessor are implemented by ARRAY.
    //int *color;             // 0:White, 1:Gray, 2:Black
    //int *distance;          // 0: starting point, 'num_vertex+1': it means 'infinite distance' and represents we cannot get to vertex
    //int *predecessor;       // -1: indicates there is no predecessor and represents it's a starting vertex

    unique_ptr<int[]> color;
    unique_ptr<int[]> distance;
    unique_ptr<int[]> predecessor;
public:
    Graph() :num_vertex(0) {};
    Graph(int N) :num_vertex(N) {        // constructor with input: number of vertex										 
        adj_list.resize(num_vertex);     // initialize Adjacency List
                                         // initialize arrays' space
        //color = new int[num_vertex]();
        //predecessor = new int[num_vertex]();
        //distance = new int[num_vertex]();

        color.reset(new int[num_vertex]());
        predecessor.reset(new int[num_vertex]());
        distance.reset(new int[num_vertex]());
    };
    ~Graph() {
        //adj_list.clear();
        //vector< list<int> >().swap(adj_list);      // [NOTE] Be careful when you are using class object with dynamic allocation without smart pointer.

        //delete[] color;
        //delete[] predecessor;
        //delete[] distance;
    }

    void addEdgeList(int from, int to);
    void BFS(int Start);
    void printGraph();
};

void Graph::addEdgeList(int from_vertex, int to_vertex) {
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

void Graph::printGraph()
{
    cout << "n: ";      // n for name

    for (int i = 'A'; i <= 'I'; ++i)
        cout << static_cast<char>(i) << " ";

    cout << endl;
    cout << "c: ";      // c for color

    for (int i = 0; i < num_vertex; ++i)
        cout << color[i] << " ";

    cout << endl;
    cout << "d: ";      // d for distance

    for (int i = 0; i < num_vertex; ++i)
        cout << distance[i] << " ";

    cout << endl;
    cout << "p:";   // p for predecessor

    if (predecessor[0] >= 0)
        cout << " ";

    for (int i = 0; i < num_vertex; ++i)
        cout << predecessor[i] << " ";

    cout << endl;
}

int main() {

    int number_of_vertex = 9;
    Graph g1(number_of_vertex);

    // According to figure 2(a), we can build an Adjacency List.
    g1.addEdgeList(A, B); g1.addEdgeList(A, C); g1.addEdgeList(A, D);
    g1.addEdgeList(B, A); g1.addEdgeList(B, E);
    g1.addEdgeList(C, A); g1.addEdgeList(C, E); g1.addEdgeList(C, F); g1.addEdgeList(C, G); g1.addEdgeList(C, H);
    g1.addEdgeList(D, A); g1.addEdgeList(D, H);
    g1.addEdgeList(E, B); g1.addEdgeList(E, C); g1.addEdgeList(E, F);
    g1.addEdgeList(F, C); g1.addEdgeList(F, E); g1.addEdgeList(F, I);
    g1.addEdgeList(G, C); g1.addEdgeList(G, H); g1.addEdgeList(G, I);
    g1.addEdgeList(H, C); g1.addEdgeList(H, D); g1.addEdgeList(H, G);
    g1.addEdgeList(I, F); g1.addEdgeList(I, G);


    cout << "Status before BFS()" << endl;
    g1.printGraph();
    
    g1.BFS(A);
    
    cout << "\nStatus after BFS()" << endl;
    g1.printGraph();

    g1.~Graph();

    std::cin.get();
    return 0;
}