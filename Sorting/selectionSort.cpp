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

void selectionSort(std::vector<int>& arr, CMP compare)
{
    int temp_idx;
    int n = arr.size();

    // N-1 times of loop
    for (int i = n - 1; i > 0; --i) {
        // Find the minimum or maximum element in unsorted array
        temp_idx = i;
        for (int j = i - 1; j >= 0; --j)
            if (compare(arr[j], arr[temp_idx]))
                temp_idx = j;

        // Swap the found minimum or maximum element with the last element
        swap(arr[temp_idx], arr[i]);
    }
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

    cout << "Selection Sort: Ascending Order" << endl;
    cout << std::setw(8) << "before: ";
    printData(arr_01);
    selectionSort(arr_01, larger);
    cout << std::setw(8) << "after: ";
    printData(arr_01);

    std::vector<int> arr_02(arr, arr + sizeof(arr) / sizeof(arr[0]));
    cout << "Selection Sort: Descending Order" << endl;
    cout << std::setw(8) << "before: ";
    printData(arr_02);
    selectionSort(arr_02, smaller);
    cout << std::setw(8) << "after: ";
    printData(arr_02);


    std::cin.get();
    return 0;
}