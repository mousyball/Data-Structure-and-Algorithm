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

int partition(std::vector<int>& arr, int low, int high)
{
    int pivot = arr[high];    // pivot
    int i = (low - 1);        // Index of smaller element

    for (int j = low; j <= high - 1; ++j)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            ++i;              // increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<int>& arr, int low, int high)
{
    if (low < high)
    {
        // pivot is partitioning index
        int pivot = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

void quickSort_iterative(std::vector<int>& arr, int low, int high)
{
    // Create an auxiliary stack
    int n = arr.size();
    int *stack = new int[n];

    // initialize top of stack
    int top = -1;

    // push initial values of low and high to stack
    stack[++top] = low;
    stack[++top] = high;

    // Keep popping from stack while is not empty
    while (top >= 0)
    {
        // Pop high and low
        high = stack[top--];
        low = stack[top--];

        // Set pivot element at its correct position
        // in sorted array
        int pivot = partition(arr, low, high);

        // If there are elements on left side of pivot,
        // then push left side to stack
        if (pivot - 1 > low)
        {
            stack[++top] = low;
            stack[++top] = pivot - 1;
        }

        // If there are elements on right side of pivot,
        // then push right side to stack
        if (pivot + 1 < high)
        {
            stack[++top] = pivot + 1;
            stack[++top] = high;
        }
    }

    delete[] stack;
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

    cout << "Quick Sort: Ascending Order" << endl;
    cout << std::setw(8) << "before: ";
    printData(arr_01);
    quickSort(arr_01, 0, arr_01.size() - 1);
    cout << std::setw(8) << "after: ";
    printData(arr_01);


    std::vector<int> arr_02(arr, arr + sizeof(arr) / sizeof(arr[0]));
    cout << "Quick Sort: Descending Order" << endl;
    cout << std::setw(8) << "before: ";
    printData(arr_02);
    quickSort_iterative(arr_02, 0, arr_02.size() - 1);
    cout << std::setw(8) << "after: ";
    printData(arr_02);


    std::cin.get();
    return 0;
}