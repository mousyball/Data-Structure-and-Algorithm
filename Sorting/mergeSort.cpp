#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>      // for std::setw()

#define STATE_SPLIT 0
#define STATE_MERGE 1

using std::cout;
using std::endl;

const int MAX = 1000;    // INF for merge sort
const int MIN = -1000;   // -INF for merge sort

inline int min(int x, int y)
{
    return (x<y) ? x : y;
}

typedef bool(*CMP)(int&, int&);  // function pointer

inline bool greater_and_equal(int& a, int& b) {
    return a >= b;
}

inline bool less_and_equal(int& a, int& b) {
    return a <= b;
}

inline void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

void merge(std::vector<int> &Array, int front, int mid, int end, CMP compare)
{
    // use constructor of std::vector to build temp vector
    std::vector<int> left_sub(Array.begin() + front, Array.begin() + mid + 1);      // left_sub[] contains array[front] ~ array[mid]
    std::vector<int> right_sub(Array.begin() + mid + 1, Array.begin() + end + 1);   // right_sub[] contains array[mid+1] ~ array[end]

    if (compare == less_and_equal) {
        left_sub.insert(left_sub.end(), MAX);      // insert the MAX at the last of left_sub[]
        right_sub.insert(right_sub.end(), MAX);    // insert the MAX at the last of right_sub[]
    }
    else if (compare == greater_and_equal) {
        left_sub.insert(left_sub.end(), MIN);      // insert the MIN at the last of left_sub[]
        right_sub.insert(right_sub.end(), MIN);    // insert the MIN at the last of right_sub[]
    }
    else {
        cout << "[ERROR] Unknown function behavior of 'CMP compare'." << endl;
        return;
    }

    int idx_left = 0, idx_right = 0;

    for (int i = front; i <= end; ++i) {

        //if (left_sub[idx_left] <= right_sub[idx_right]) {
        if (compare(left_sub[idx_left], right_sub[idx_right])) {
            Array[i] = left_sub[idx_left];
            ++idx_left;
        }
        else {
            Array[i] = right_sub[idx_right];
            ++idx_right;
        }
    }
}

void mergeSort(std::vector<int> &array, int front, int end, CMP compare)
{
    // range of array: front ~ end
    if (front < end) {                            // valid range
        int mid = (front + end) / 2;              // mid is the half of index
        mergeSort(array, front, mid, compare);    // process the left half of array
        mergeSort(array, mid + 1, end, compare);  // process the right half of array
        merge(array, front, mid, end, compare);   // merge two sub-array
    }
}

void mergeSort_myIterative(std::vector<int> &array, int front, int end, CMP compare)
{
    // Create n STL stack
    std::stack<int> s;

    // initialize the state
    int state = STATE_SPLIT;

    // push initial values of front, end and state to stack
    s.push(STATE_SPLIT);
    s.push(front);
    s.push(end);

    // keep popping from stack while is not empty
    while (!s.empty())
    {
        // get and pop high, low and state
        end = s.top();
        s.pop();
        front = s.top();
        s.pop();
        state = s.top();
        s.pop();

        // get mid
        int mid = (front + end) / 2;

        // STATE_SPLIT means the recursion do not go to the deepest funtion call
        // STATE_MERGE means all the STATE_SPLIT has finished after it, so we can start to 'merge'
        if (state == STATE_SPLIT) {
            if (front < end) {
                s.push(STATE_MERGE);
                s.push(front);
                s.push(end);

                s.push(STATE_SPLIT);
                s.push(mid + 1);
                s.push(end);

                s.push(STATE_SPLIT);
                s.push(front);
                s.push(mid);                
            }
        }
        else {
            merge(array, front, mid, end, compare);
        }
    }
}

// reference from GFG
void mergeSort_iterative(std::vector<int> &array, int front, int end, CMP compare)
{
    int curr_size;  // For current size of subarrays to be merged
                    // curr_size varies from 1 to n/2
    int left_start; // For picking starting index of left subarray
                    // to be merged

                    // Merge subarrays in bottom up manner.  First merge subarrays of
                    // size 1 to create sorted subarrays of size 2, then merge subarrays
                    // of size 2 to create sorted subarrays of size 4, and so on.

    for (curr_size = 1; curr_size <= end; curr_size = 2 * curr_size)
    {
        // Pick starting point of different subarrays of current size
        for (left_start = 0; left_start < end; left_start += 2 * curr_size)
        {
            // Find ending point of left subarray. mid+1 is starting
            // point of right
            int mid = left_start + curr_size - 1;

            int right_end = min(left_start + 2 * curr_size - 1, end);

            // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
            merge(array, left_start, mid, right_end, compare);
        }
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

    cout << "Merge Sort: Ascending Order (Recursive)" << endl;
    cout << std::setw(8) << "before: ";
    printData(arr_01);
    mergeSort(arr_01, 0, arr_01.size() - 1, less_and_equal);
    cout << std::setw(8) << "after: ";
    printData(arr_01);


    std::vector<int> arr_02(arr, arr + sizeof(arr) / sizeof(arr[0]));
    cout << "Merge Sort: Descending Order (Recursive)" << endl;
    cout << std::setw(8) << "before: ";

    arr_02[2] = 12;
    printData(arr_02);

    mergeSort(arr_02, 0, arr_02.size() - 1, greater_and_equal);
    cout << std::setw(8) << "after: ";
    printData(arr_02);

    /// iterative version referenced from GFG

    std::vector<int> arr_03(arr, arr + sizeof(arr) / sizeof(arr[0]));
    cout << "Merge Sort: Ascending Order (GFG:Iterative)" << endl;
    cout << std::setw(8) << "before: ";
    printData(arr_03);
    mergeSort_iterative(arr_03, 0, arr_03.size() - 1, less_and_equal);
    cout << std::setw(8) << "after: ";
    printData(arr_03);


    std::vector<int> arr_04(arr, arr + sizeof(arr) / sizeof(arr[0]));
    cout << "Merge Sort: Descending Order (GFG:Iterative)" << endl;
    cout << std::setw(8) << "before: ";

    arr_04[2] = 12;
    printData(arr_04);

    mergeSort_iterative(arr_04, 0, arr_04.size() - 1, greater_and_equal);
    cout << std::setw(8) << "after: ";
    printData(arr_04);

    /// iterative version referenced from GFG

    std::vector<int> arr_05(arr, arr + sizeof(arr) / sizeof(arr[0]));
    cout << "Merge Sort: Ascending Order (myIterative)" << endl;
    cout << std::setw(8) << "before: ";
    printData(arr_05);
    mergeSort_myIterative(arr_05, 0, arr_05.size() - 1, less_and_equal);
    cout << std::setw(8) << "after: ";
    printData(arr_05);


    std::vector<int> arr_06(arr, arr + sizeof(arr) / sizeof(arr[0]));
    cout << "Merge Sort: Descending Order (myIterative)" << endl;
    cout << std::setw(8) << "before: ";

    arr_06[2] = 12;
    printData(arr_06);

    mergeSort_myIterative(arr_06, 0, arr_06.size() - 1, greater_and_equal);
    cout << std::setw(8) << "after: ";
    printData(arr_06);

    std::cin.get();
    return 0;
}