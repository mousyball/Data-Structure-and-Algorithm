#include <iostream>
#include <vector>
#include <iomanip>      // for std::setw()

using std::vector;
using std::cout;
using std::endl;

const int MAX_DISTANCE = 1000;

class Graph_SP_AllPairs {
private:
    int num_vertex;
    vector< vector<int> > adj_matrix;
    vector< vector<int> > distance;
    vector< vector<int> > predecessor;
public:
    Graph_SP_AllPairs() :num_vertex(0) {};
    Graph_SP_AllPairs(int n);
    void addEdge(int from, int to, int weight);
    void printData(vector< vector<int> > array);
    void initializeData();
    void FloydWarshall();
};

Graph_SP_AllPairs::Graph_SP_AllPairs(int n) :num_vertex(n) {
    // Constructor, initialize adj_matrix with 0 or MAX_DISTANCE
    adj_matrix.resize(num_vertex);
    for (int i = 0; i < num_vertex; ++i) {
        adj_matrix[i].resize(num_vertex, MAX_DISTANCE);
        for (int j = 0; j < num_vertex; ++j) {
            // set the diagonal elements to 0
            if (i == j) {
                adj_matrix[i][j] = 0;
            }
        }
    }
}

void Graph_SP_AllPairs::initializeData() {

    distance.resize(num_vertex);
    predecessor.resize(num_vertex);

    for (int i = 0; i < num_vertex; ++i) {
        distance[i].resize(num_vertex);
        predecessor[i].resize(num_vertex, -1);
        for (int j = 0; j < num_vertex; ++j) {
            distance[i][j] = adj_matrix[i][j];

            // if the value of distance[i][j] isn't 0 and INF, it means that there is a path between vertex[i] and vertex[j].
            // hence we set predecessor[i][j] to i
            if (distance[i][j] != 0 && distance[i][j] != MAX_DISTANCE) {
                predecessor[i][j] = i;
            }
        }
    }
}

void Graph_SP_AllPairs::FloydWarshall() {

    initializeData();

    cout << "initial distance[]:\n";
    printData(distance);
    cout << "\ninitial predecessor[]:\n";
    printData(predecessor);

    // k: for each intermediate vertex
    for (int k = 0; k < num_vertex; k++) {
        cout << "\nincluding vertex(" << k << "):\n";

        // i,j: for each edge(i, j)
        for (int i = 0; i < num_vertex; ++i) {
            for (int j = 0; j < num_vertex; ++j) {
                if ((distance[i][j] > distance[i][k] + distance[k][j]) // relaxation
                    && (distance[i][k] != MAX_DISTANCE)) {             // there must be a connection between i and k.
                    distance[i][j] = distance[i][k] + distance[k][j];  // replace the higher cost path with the lower one
                    predecessor[i][j] = predecessor[k][j];             // path: i - ... - k - j, means that path(i,j) must pass by k
                }
            }
        }

        // print data after including new vertex and updating the shortest paths
        cout << "distance[]:\n";
        printData(distance);
        cout << "\nPredecessor[]:\n";
        printData(predecessor);
    }
}

void Graph_SP_AllPairs::printData(vector< vector<int> > array) {

    for (int i = 0; i < num_vertex; ++i) {
        for (int j = 0; j < num_vertex; ++j) {
            cout << std::setw(5) << array[i][j];
        }
        cout << endl;
    }
}

void Graph_SP_AllPairs::addEdge(int from, int to, int weight) {
    adj_matrix[from][to] = weight;
}

int main() {

    Graph_SP_AllPairs g10(4);
    g10.addEdge(0, 1, 2); g10.addEdge(0, 2, 6); g10.addEdge(0, 3, 8);
    g10.addEdge(1, 2, -2); g10.addEdge(1, 3, 3);
    g10.addEdge(2, 0, 4); g10.addEdge(2, 3, 1);

    g10.FloydWarshall();

    g10.~Graph_SP_AllPairs();

    std::cin.get();
    return 0;
}