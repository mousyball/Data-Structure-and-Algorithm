#include <iostream>
#include <memory>       // for smart pointer
#include <list>
#include <vector>
#include <iomanip>      // for std::setw()
#include <cmath>        // for std::floor()
#include <utility>      // for std::pair<>

using std::pair;
using std::list;
using std::vector;
using std::cout;
using std::endl;

const int Max_Weight = 1000;    // Represent 'infinity' in key[]

///// Min Heap /////

struct HeapNode {
    int element, key;
    HeapNode() :element(0), key(0) {};
    HeapNode(int node, int key) :element(node), key(key) {};
};

class BinaryHeap {
private:
    std::vector<HeapNode> heap;        // 存放HeapNode資料的矩陣
    void swap(struct HeapNode &p1, struct HeapNode &p2);
    int findPosition(int node);
    int getParentNode(int node) { return std::floor(node / 2); };
public:
    BinaryHeap() {               // default constructor, index 0 is a reservation index
        heap.resize(1);          // HeapNode starts from index 1
    }
    BinaryHeap(int n) {
        heap.resize(n + 1);
    }
    bool isHeapEmpty() { return (heap.size()<=1); };

    // Min-Priority Queue
    void minHeapify(int node, int length);
    void buildMinHeap(std::vector<int> array);
    void decreaseKey(int node, int newKey);
    void minHeapInsert(int node, int key);
    int minimum() { return heap[1].element; };  // return the index of root
    int extractMin();                           // return the index of root


    /// [TODO]
    // void HeapSort();

    // Max-Priority Queue
};

void BinaryHeap::minHeapify(int node, int length) {

    int left = 2 * node;          // left child
    int	right = 2 * node + 1;     // right child
    int	smallest;                 // smallest is used to store the minimal value among root, left and right

    if (left <= length && heap[left].key < heap[node].key)
        smallest = left;
    else
        smallest = node;

    if (right <= length && heap[right].key < heap[smallest].key)
        smallest = right;

    if (smallest != node) {                 // if node is not the smallest
        swap(heap[smallest], heap[node]);   // swap smallest and node
        minHeapify(smallest, length);       // adjust the new subtree to become MinHeap
    }
}

void BinaryHeap::buildMinHeap(std::vector<int> array) {

    // put the data of array[] into vector of heap, heap[0] is a reservation space
    for (int i = 0; i < array.size(); ++i) {
        heap[i + 1].element = i;                 // index of array[] is 'element'
        heap[i + 1].key = array[i];              // index of array[] is 'key'
    }
    for (int i = (int)heap.size() / 2; i >= 1; --i) {
        minHeapify(i, (int)heap.size() - 1);     // because heap stores the data from index 1, length need to be (size - 1)
    }
}

void BinaryHeap::swap(struct HeapNode &p1, struct HeapNode &p2) {

    struct HeapNode temp = p1;
    p1 = p2;
    p2 = temp;
}

int BinaryHeap::findPosition(int node) {

    int idx = 0;
    for (int i = 1; i < heap.size(); ++i) {
        if (heap[i].element == node) {
            //idx = i;
            return i;
        }
    }
    //return idx;
}

int BinaryHeap::extractMin() {

    // check if heap is empty
    if (isHeapEmpty()) {
        std::cout << "error: heap is empty\n";
        exit(-1);
    }

    // the root of heap got the minimal key. store the min, then return
    int min = heap[1].element;

    // delete the first element/vertex
    heap[1] = heap[heap.size() - 1];              // replace the root with the last element
    heap.erase(heap.begin() + heap.size() - 1);   // then, delete the last element
    minHeapify(1, (int)heap.size() - 1);          // heap[1] is not the smallest key after overwriting. need minHeapify()

    return min;
}

void BinaryHeap::decreaseKey(int node, int newKey) {

    int index_node = findPosition(node);      // get the index of node

    if (newKey > heap[index_node].key) {      // we dont care (newKey > nodeKey)
        std::cout << "new key is larger than current key\n";
        return;
    }
    heap[index_node].key = newKey;            // we have to check if the new subtree meet the conditions of MinHeap after update
    while (index_node > 1 && heap[getParentNode(index_node)].key > heap[index_node].key) {
        swap(heap[index_node], heap[getParentNode(index_node)]);
        index_node = getParentNode(index_node);
    }
}

void BinaryHeap::minHeapInsert(int node, int key) {

    heap.push_back(HeapNode(node, key));    // add a node at the end of heap[]
    decreaseKey(node, key);
}

///// Prim's Algorithm /////
class GraphMST {
private:
    int num_vertex;
    vector< list< pair<int, int> > > adj_list;
    vector<int> predecessor;
    vector<int> distance;
    vector<bool> visited;
    void initializeSingleSource(int Start);       // take 'Start' as starting point
    void printDataArray(vector<int> array);
public:
    GraphMST() :num_vertex(0) {};
    GraphMST(int N) :num_vertex(N) {         // constructor with input: number of vertex
        adj_list.resize(num_vertex);         // initialize Adjacency List
    };
    ~GraphMST() {}

    void addEdge(int from, int to, int weight);
    void Prim_MinQueue(int Start);

    friend class BinaryHeap;
};

void GraphMST::initializeSingleSource(int Start) {

    distance.resize(num_vertex);
    predecessor.resize(num_vertex);

    for (int i = 0; i < num_vertex; ++i) {
        distance[i] = Max_Weight;
        predecessor[i] = -1;
    }
    distance[Start] = 0;       // distance of starting vertex is set to 0, hence extractMin() starts from here.
}

void GraphMST::Prim_MinQueue(int Start) {

    initializeSingleSource(Start);

    BinaryHeap minQueue(num_vertex);
    minQueue.buildMinHeap(distance);      // use minQueue to handle distance[]

    visited.resize(num_vertex, false);    // initializa visited[] as {0,0,0,...,0}

    while (!minQueue.isHeapEmpty()) {
        int u = minQueue.extractMin();    // extract minimal distance in the minHeap
        visited[u] = true;
        for (std::list<std::pair<int, int> >::iterator itr = adj_list[u].begin();
            itr != adj_list[u].end(); ++itr) {
            if (visited[(*itr).first] == false && (*itr).second < distance[(*itr).first]) {  // weight(X,Y) < distance[Y]

                // for edge(X,Y)
                // u: X {from extractMin()}, (*itr).first: Y, (*itr).second: weight(X,Y)
                // (*itr).second < distance[(*itr).first]: weight(X,Y) < distance[Y]

                distance[(*itr).first] = (*itr).second;                       // distance[Y] = weight(X,Y)
                predecessor[(*itr).first] = u;                                // predecessor[Y] = X
                minQueue.decreaseKey((*itr).first, distance[(*itr).first]);   // minQueue.decreaseKey(Y, distance[Y])
            }
        }
    }
    ///////   print result   /////////

    cout << "print predecessor[]:\n";
    printDataArray(predecessor);
    cout << "print distance[]:\n";
    printDataArray(distance);

    cout << std::setw(3) << "v1" << " - " << std::setw(3) << "v2" << " : weight\n";
    int i = (Start + 1) % num_vertex;   // use MOD to prevent out-of-boundary. if it starts from 4, order of i is 5,6,0,1,2,3
    while (i != Start) {
        cout << std::setw(3) << predecessor[i] << " - " << std::setw(3) << i
            << " : " << std::setw(3) << distance[i] << "\n";
        i = (++i) % num_vertex;         // use MOD to prevent out-of-boundary.
    }
}

void GraphMST::printDataArray(vector<int> array) {
    for (int i = 0; i < num_vertex; ++i) {
        cout << std::setw(4) << i;
    }
    cout << endl;
    for (int i = 0; i < num_vertex; ++i) {
        cout << std::setw(4) << array[i];
    }
    cout << endl << endl;
}

void GraphMST::addEdge(int from, int to, int weight) {
    //adj_matrix[from][to] = weight;
    adj_list[from].push_back(std::make_pair(to, weight));
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

    cout << "MST found by Prim_MinQueue:\n";
    g6.Prim_MinQueue(2);

    g6.~GraphMST();

    std::cin.get();
    return 0;
}