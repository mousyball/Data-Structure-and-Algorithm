#include "Priority_Queue_BinaryHeap.h"

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
	return idx;
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