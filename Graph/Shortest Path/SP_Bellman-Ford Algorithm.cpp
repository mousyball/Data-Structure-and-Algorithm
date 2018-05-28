#include <iostream>
#include <vector>
#include <list>
#include <utility>          // for std::pair<>
#include <iomanip>          // for std::setw()

#define NO_PREDECESSOR -1

using std::cout;
using std::endl;
using std::vector;
using std::list;
using std::pair;

const int MAX_DISTANCE = 100;

class Graph_SP {             // SP serves as Shortest Path
private:
    int num_vertex;
    vector< list< pair<int, int> > > adj_list;
    vector<int> predecessor, distance;
public:
    Graph_SP() :num_vertex(0) {};
    Graph_SP(int n) :num_vertex(n) {
        adj_list.resize(num_vertex);
    }
    void addEdge(int from, int to, int weight);
    void printDataArray(vector<int> array);

    void initializeSingleSource(int Start);     // START serves as starting point
    void relax(int X, int Y, int weight);       // do relaxation to edge(X,Y)
    bool BellmanFord(int Start = 0);            // START serves as starting point
                                                // if negative cycle exists, return false
};

bool Graph_SP::BellmanFord(int Start) {

    initializeSingleSource(Start);

    for (int i = 0; i < num_vertex - 1; ++i) {                // |V-1| times of iteration
                                                              // for each edge belonging to E(G)
        for (int j = 0; j < num_vertex; ++j) {                // traversal elements of adj_list
            for (list<pair<int, int> >::iterator itr = adj_list[j].begin();
                itr != adj_list[j].end(); ++itr) {            // taversal lists of elements
                relax(j, (*itr).first, (*itr).second);
            }
        }
    }

    // check if there is negative cycle
    for (int i = 0; i < num_vertex; ++i) {
        for (list<pair<int, int> >::iterator itr = adj_list[i].begin();
            itr != adj_list[i].end(); ++itr) {

            // after BellmanFord, "dist[to] > dist[from] + weight" means there is a negative cycle
            if (distance[(*itr).first] > distance[i] + (*itr).second) {   // i:from, *itr:to
                return false;
            }
        }
    }

    // print predecessor[] & distance[]
    cout << "predecessor[]:\n";
    printDataArray(predecessor);
    cout << "distance[]:\n";
    printDataArray(distance);

    return true;
}
void Graph_SP::printDataArray(vector<int> array) {
    for (int i = 0; i < num_vertex; ++i)
        cout << std::setw(4) << i;
    cout << endl;
    for (int i = 0; i < num_vertex; ++i)
        cout << std::setw(4) << array[i];
    cout << endl << endl;
}
void Graph_SP::initializeSingleSource(int Start) {

    distance.resize(num_vertex);
    predecessor.resize(num_vertex);

    for (int i = 0; i < num_vertex; ++i) {
        distance[i] = MAX_DISTANCE;
        predecessor[i] = NO_PREDECESSOR;
    }

    // set the distance of Start to 0 as the initial point
    distance[Start] = 0;
}
void Graph_SP::relax(int from, int to, int weight) {

    // update distance[] when the weight make the cost of path lower
    if (distance[to] > distance[from] + weight) {
        distance[to] = distance[from] + weight;
        predecessor[to] = from;
    }
}
void Graph_SP::addEdge(int from, int to, int weight) {
    adj_list[from].push_back(std::make_pair(to, weight));
}

int main() {

    Graph_SP g7(6);
    g7.addEdge(0, 1, 5);
    g7.addEdge(1, 4, -4); g7.addEdge(1, 2, 6);
    g7.addEdge(2, 4, -3); g7.addEdge(2, 5, -2);
    g7.addEdge(3, 2, 4);
    g7.addEdge(4, 3, 1); g7.addEdge(4, 5, 6);
    g7.addEdge(5, 0, 3); g7.addEdge(5, 1, 7);

    if (g7.BellmanFord(0))
        cout << "There is no negative cycle.\n";
    else
        cout << "There is negative cycle.\n";

    g7.~Graph_SP();

    std::cin.get();
    return 0;
}