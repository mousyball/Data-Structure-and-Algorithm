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

void insertionSort_recursion(std::vector<int>& arr, int n, CMP compare)
{
    // Base case
    if (n <= 1)
        return;

    // Sort first n-1 elements
    insertionSort_recursion(arr, n - 1, compare);

    // Insert last element at its correct position
    // in sorted array.
    int last = arr[n - 1];
    int j = n - 2;

    // shift elements to insert 'inserted_value'
    while (j >= 0 && compare(arr[j], last)) {
        arr[j + 1] = arr[j];
        --j;
    }
    arr[j + 1] = last;
}

void insertionSort(std::vector<int>& arr, CMP compare)
{
    int j;
    int inserted_value;
    int n = arr.size();

    // N-1 times of loop
    for (int i = 1; i < n; ++i) {

        inserted_value = arr[i];     // store the value ready to be inserted
        j = i - 1;

        // shift elements to insert 'inserted_value'
        while (j >= 0 && compare(arr[j], inserted_value)) {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = inserted_value;
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

    cout << "Insertion Sort: Ascending Order" << endl;
    cout << std::setw(8) << "before: ";
    printData(arr_01);
    insertionSort(arr_01, larger);
    cout << std::setw(8) << "after: ";
    printData(arr_01);

    std::vector<int> arr_02(arr, arr + sizeof(arr) / sizeof(arr[0]));
    cout << "Insertion Sort: Descending Order" << endl;
    cout << std::setw(8) << "before: ";
    printData(arr_02);
    insertionSort(arr_02, smaller);
    cout << std::setw(8) << "after: ";
    printData(arr_02);

    std::vector<int> arr_03(arr, arr + sizeof(arr) / sizeof(arr[0]));
    cout << "Insertion Sort: Ascending Order (recursion)" << endl;
    cout << std::setw(8) << "before: ";
    printData(arr_03);
    insertionSort_recursion(arr_03, arr_03.size(), larger);
    cout << std::setw(8) << "after: ";
    printData(arr_03);

    std::vector<int> arr_04(arr, arr + sizeof(arr) / sizeof(arr[0]));
    cout << "Insertion Sort: Descending Order (recursion)" << endl;
    cout << std::setw(8) << "before: ";
    printData(arr_04);
    insertionSort_recursion(arr_04, arr_04.size(), smaller);
    cout << std::setw(8) << "after: ";
    printData(arr_04);


    std::cin.get();
    return 0;
}