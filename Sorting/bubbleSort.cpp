#include <iostream>
#include <vector>
#include <iomanip>      // for std::setw()

using std::cout;
using std::endl;

typedef bool(*CMP)(int&, int&);  // function pointer

inline bool larger(int& a, int& b) {
    return a > b;
}

inline bool smaller(int& a, int& b) {
    return a < b;
}

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSort_recursion(std::vector<int>& arr, int n, CMP compare)
{
    // Base case
    if (n == 1)
        return;

    // check if there is no swapping in inner loop.
    bool swapped = false;

    // move the largest number of loop to the rightmost index
    for (int i = 0; i < n - 1; ++i) {
        if (compare(arr[i], arr[i + 1])) {
            swap(arr[i], arr[i + 1]);
            swapped = true;
        }
    }

    // return if swapping does not happen
    if (swapped == false)
        return;

    // recursive call
    bubbleSort_recursion(arr, n - 1, compare);
}

void bubbleSort(std::vector<int>& arr, CMP compare)
{
    int arr_size = arr.size();
    bool swapped;      // check if there is no swapping in inner loop.

    for (int i = 0; i < arr_size - 1; ++i) {
        swapped = false;

        for (int j = 0; j < arr_size - i - 1; ++j) {
            if (compare(arr[i], arr[i + 1])) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // break the loop if swapping does not happen
        if (swapped == false)
            break;
    }
}

void printData(std::vector<int> arr)
{
    for (int i = 0; i < arr.size(); ++i)
        cout << std::setw(3) << arr[i] << " ";
    cout << endl;
}

int main()
{
    const int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
    std::vector<int> arr_01(arr, arr + sizeof(arr) / sizeof(arr[0]));

    cout << "Bubble Sort: Ascending Order" << endl;
    cout << std::setw(8) << "before: ";
    printData(arr_01);
    bubbleSort(arr_01, larger);
    cout << std::setw(8) << "after: ";
    printData(arr_01);

    std::vector<int> arr_02(arr, arr + sizeof(arr) / sizeof(arr[0]));
    cout << "Bubble Sort (recursion): Descending Order" << endl;
    cout << std::setw(8) << "before: ";
    printData(arr_02);
    bubbleSort_recursion(arr_02, arr_02.size(), smaller);
    cout << std::setw(8) << "after: ";
    printData(arr_02);

    std::cin.get();
    return 0;
}