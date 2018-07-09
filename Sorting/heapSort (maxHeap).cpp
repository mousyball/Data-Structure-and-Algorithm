#include <iostream>
#include <vector>
#include <iomanip>      // for std::setw()

using std::cout;
using std::endl;

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void maxHeapify(std::vector<int> &array, int root, int length)
{
    int left = 2 * root;        // left child
    int right = 2 * root + 1;   // right child
    int largest;                // largest is used to store the maximal value among root, left and right

    // get the largest one among root, left and right
    if (left <= length && array[left] > array[root])
        largest = left;
    else
        largest = root;

    if (right <= length && array[right] > array[largest])
        largest = right;

    if (largest != root) {                         // if node is not the largest
        swap(array[largest], array[root]);         // swap largest and node
        maxHeapify(array, largest, length);        // adjust the new subtree to become MaxHeap
    }
}

void buildMaxHeap(std::vector<int> &array)
{
    for (int i = (int)array.size() / 2; i >= 1; --i) {
        maxHeapify(array, i, (int)array.size() - 1);     // because heap stores the data from index 1, length need to be (size - 1)
    }
}

void heapSort(std::vector<int> &array)
{
    array.insert(array.begin(), 0);                     // reserve index(0)

    buildMaxHeap(array);                                // make array into maxHeap

    int size = (int)array.size() - 1;                   // use "size" to record the length "under processing"
    for (int i = (int)array.size() - 1; i >= 2; --i) {
        swap(array[1], array[i]);                       // swap the maximum (index(1)) with the last element (index(size-1))
        --size;
        maxHeapify(array, 1, size);                     // apply maxHeapify to array from index(1) to index(size)
    }

    array.erase(array.begin());                         // delete index(0)
}


void printData(std::vector<int>& arr)
{
    for (int i = 0; i < arr.size(); ++i)
        cout << std::setw(3) << arr[i] << " ";
    cout << endl;
}

int main()
{
    const int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
    std::vector<int> arr_01(arr, arr + sizeof(arr) / sizeof(arr[0]));

    cout << "Heap Sort (maxHeap): Ascending Order" << endl;
    cout << std::setw(8) << "before: ";
    printData(arr_01);
    heapSort(arr_01);
    cout << std::setw(8) << "after: ";
    printData(arr_01);

    std::cin.get();
    return 0;
}