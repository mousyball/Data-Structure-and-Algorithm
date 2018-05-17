#include <iostream>
#include <memory>       // for smart pointer
#include <vector>
#include <algorithm>    // for std::sort()
#include <iomanip>      // for std::setw()

using std::vector;
using std::cout;
using std::endl;

inline bool weightComp(struct Edge e1, struct Edge e2);
int findSetCollapsing(int *subset, int i);
void unionSet(int *subset, int x, int y);

struct Edge {
    int from;
    int to;
    int weight;
    Edge() {};
    Edge(int u, int v, int w) :from(u), to(v), weight(w) {};
};

class GraphMST {
private:
    int num_vertex;
    vector< vector<int> > adj_matrix;
public:
    GraphMST() :num_vertex(0) {};
    GraphMST(int N) :num_vertex(N) {         // constructor with input: number of vertex
        adj_matrix.resize(num_vertex);       // initialize Adjacency Matrix
        for (int i = 0; i < num_vertex; ++i)
            adj_matrix[i].resize(num_vertex);
    };
    ~GraphMST() {}

    void addEdge(int from, int to, int weight);

    void KruskalMST();
    void getSortedEdge(vector<struct Edge> &vec);
    friend int findSetCollapsing(int *subset, int i);
    friend void unionSet(int *subset, int x, int y);
};

inline bool weightComp(struct Edge e1, struct Edge e2) {
    return (e1.weight < e2.weight);
}

void GraphMST::addEdge(int from, int to, int weight) {
    adj_matrix[from][to] = weight;
}

void GraphMST::KruskalMST() {

    struct Edge *edgesetMST = new struct Edge[num_vertex - 1];
    int edgesetcount = 0;

    // initialize subset with value '-1'
    int *subset = new int[num_vertex];
    ///std::unique_ptr<int[]> subset(new int[10]);
    for (int i = 0; i < num_vertex; ++i) {
        subset[i] = -1;
    }

    // get the sorted edge of vertices
    vector<struct Edge> increaseWeight;
    getSortedEdge(increaseWeight);

    // start from vertex(0) to vertex(N-1)
    // IF (from) and (to) belong to the same set, then do two things:
    // 1. add the edge into edgesetMST
    // 2. union two vertice, (from) and (to), to the same set
    for (int i = 0; i < increaseWeight.size(); i++) {
        if (findSetCollapsing(subset, increaseWeight[i].from) != findSetCollapsing(subset, increaseWeight[i].to)) {
            edgesetMST[edgesetcount++] = increaseWeight[i];
            unionSet(subset, increaseWeight[i].from, increaseWeight[i].to);
        }
    }

    // print out vertices and their predecessor
    cout << std::setw(3) << "v1" << " - " << std::setw(3) << "v2" << " : weight\n";
    for (int i = 0; i < num_vertex - 1; i++) {
        cout << std::setw(3) << edgesetMST[i].from << " - " << std::setw(3) << edgesetMST[i].to
            << " : " << std::setw(4) << edgesetMST[i].weight << "\n";
    }

    delete[] subset;
}

void GraphMST::getSortedEdge(std::vector<struct Edge> &edgearray) {

    // push all edges into edgearray
    for (int i = 0; i < num_vertex - 1; ++i) {
        for (int j = i + 1; j < num_vertex; ++j) {
            if (adj_matrix[i][j] != 0) {
                edgearray.push_back(Edge(i, j, adj_matrix[i][j]));     // Edge(from, to, edge_weight)
            }
        }
    }

    // use std::sort for sorting, and make a self-defined comparison function for std::sort
    std::sort(edgearray.begin(), edgearray.end(), weightComp);
}

void unionSet(int *subset, int x, int y) {

    int xroot = findSetCollapsing(subset, x);
    int yroot = findSetCollapsing(subset, y);

    // combine two set
    // [note] xroot, yroot of subset[] must be negative
    if (subset[xroot] <= subset[yroot]) {        // x got more elements, hence merge y into x
        subset[xroot] += subset[yroot];
        subset[yroot] = xroot;
    }
    else {                                       // [opposite case] y got more elements, hence merge x into y
        subset[yroot] += subset[xroot];
        subset[xroot] = yroot;
    }
}

int findSetCollapsing(int *subset, int i) {

    // find the root in the tree where the vertex(i) at
    int root;
    for (root = i; subset[root] >= 0; root = subset[root]);

    // update the root of vertex(i)
    while (i != root) {
        int parent = subset[i];
        subset[i] = root;
        i = parent;
    }

    return root;
}


int main() {

    int number_of_vertex = 7;
    GraphMST g6(number_of_vertex);

    g6.addEdge(0, 1, 5); g6.addEdge(0, 5, 3);
    g6.addEdge(1, 0, 5); g6.addEdge(1, 2, 10); g6.addEdge(1, 4, 1); g6.addEdge(1, 6, 4);
    g6.addEdge(2, 1, 10); g6.addEdge(2, 3, 5); g6.addEdge(2, 6, 8);
    g6.addEdge(3, 2, 5); g6.addEdge(3, 4, 7); g6.addEdge(3, 6, 9);
    g6.addEdge(4, 1, 1); g6.addEdge(4, 3, 7); g6.addEdge(4, 5, 6); g6.addEdge(4, 6, 2);
    g6.addEdge(5, 0, 3); g6.addEdge(5, 4, 6);
    g6.addEdge(6, 1, 4); g6.addEdge(6, 2, 8); g6.addEdge(6, 3, 9); g6.addEdge(6, 4, 2);

    std::cout << "MST found by Kruskal:\n";
    g6.KruskalMST();

    g6.~GraphMST();

    std::cin.get();
    return 0;
}