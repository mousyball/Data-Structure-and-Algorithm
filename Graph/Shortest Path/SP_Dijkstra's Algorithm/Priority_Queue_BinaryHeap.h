#pragma once
#include <iostream>
#include <memory>       // for smart pointer
#include <vector>
#include <iomanip>      // for std::setw()
#include <cmath>        // for std::floor()

using std::vector;
using std::cout;
using std::endl;

struct HeapNode {
    int element, key;
    HeapNode() :element(0), key(0) {};
    HeapNode(int node, int key) :element(node), key(key) {};
};

class BinaryHeap {
private:
    std::vector<HeapNode> heap;
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
    bool isHeapEmpty() { return (heap.size() <= 1); };

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