#include <iostream>
#include <memory>       // for smart pointer
#include <vector>
#include <list>
#include <iomanip>      // for std::setw()

using std::vector;
using std::cout;
using std::endl;

const int Max_Weight = 1000;    // Represent 'infinity' in key[]

int minKeyExtract(int *key, bool *visited, int size);

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

    void PrimMST(int Start = 0);             // default starting vertex is 0
    friend int minKeyExtract(int *key, bool *visited, int size);
};

void GraphMST::addEdge(int from, int to, int weight) {
    adj_matrix[from][to] = weight;
}

int minKeyExtract(int *key, bool *visited, int size) {

    int min = Max_Weight, min_idx = 0;
    for (int i = 0; i < size; ++i) {
        if (visited[i] == false && key[i] < min) {
            min = key[i];
            min_idx = i;
        }
    }
    return min_idx;
}

void GraphMST::PrimMST(int Start) {

    // dynamic allocation need to be deleted manually, or use 'smart pointer' to replace it
    int *key = new int[num_vertex];
    int *predecessor = new int[num_vertex];
    bool *visited = new bool[num_vertex];

    for (int i = 0; i < num_vertex; ++i) {
        key[i] = Max_Weight;
        predecessor[i] = -1;
        visited[i] = false;             // false means vertex has not been visited yet
    }

    key[Start] = 0;
    for (int i = 0; i < num_vertex; ++i) {
        int u = minKeyExtract(key, visited, num_vertex);
        visited[u] = true;
        for (int i = 0; i < num_vertex; ++i) {
            if (visited[i] == false && adj_matrix[u][i] != 0 && adj_matrix[u][i]<key[i]) {
                predecessor[i] = u;
                key[i] = adj_matrix[u][i];
            }
        }
    }

    // print out MST info
    std::cout << std::setw(3) << "v1" << " - " << std::setw(3) << "v2" << " : weight\n";
    int i = (Start + 1) % num_vertex;    // use MOD to prevent out-of-boundary. if it starts from 4, order of i is 5,6,0,1,2,3
    while (i != Start) {
        std::cout << std::setw(3) << predecessor[i] << " - " << std::setw(3) << i
            << " : " << std::setw(4) << adj_matrix[predecessor[i]][i] << "\n";
        i = (++i) % num_vertex;          // use MOD to prevent out-of-boundary.
    }

    delete[] key;
    delete[] predecessor;
    delete[] visited;
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

    std::cout << "MST found by Prim:\n";
    g6.PrimMST(2);

    g6.~GraphMST();

    std::cin.get();
    return 0;
}