#include <iostream>

template <class T>
class StackArray {
private:
    int _top;                   // index of top
    int _capacity;              // capacity of array
    T *stack;                   // array representing stack

    void doubleCapacity();      // double the capacity of stack when it's full.
public:
    StackArray(int cap = 1)     // initialize a array with constructor
        : _capacity(cap)
    {
        _top = -1;
        stack = new T[_capacity];
    }
    void pop();                 // pop the data at the top
    void push(T);               // push the data into the top
    T top() const;              // the content of top element
    bool isEmpty() const;       // check if stack is empty
    int getSize() const;        // get the size of stack (elements count).
};

template <class T>
void StackArray<T>::pop()
{
    if (_top == -1) {
        std::cout << "Stack is empty." << std::endl;
        return;
    }

    _top--;	    // pseudo-remove
}

template <class T>
void StackArray<T>::push(T value)
{
    // check if top == cap - 1, then call doubleCapacity
    if (_top == _capacity - 1)
        doubleCapacity();

    stack[++_top] = value;
}

template <class T>
T StackArray<T>::top() const
{
    if (_top == -1)
        return 0;
    else
        return stack[_top];
}

template <class T>
bool StackArray<T>::isEmpty() const
{
    return (_top == -1);
}

template <class T>
int StackArray<T>::getSize() const
{
    return (_top + 1);
}

template <class T>
void StackArray<T>::doubleCapacity()
{
    _capacity *= 2;

    T* newStack = new T[_capacity];

    for (int i = 0; i < _capacity / 2; ++i)
        newStack[i] = stack[i];

    delete[] stack;

    stack = newStack;
}

template <class T>
void reportStatus(const StackArray<T>& stack)
{
    std::cout << "stack.isEmpty() = " << stack.isEmpty() << std::endl;
    std::cout << "stack.getSize = " << stack.getSize() << std::endl;
    std::cout << "stack.top() = " << stack.top() << std::endl;

    std::cout << "================" << std::endl;
}


void calculateSpan(int price[], int n, int S[])
{
    // Create a stack and push index of first element to it
    StackArray<int> stack(10);
    stack.push(0);

    // Span value of first element is always 1
    S[0] = 1;

    // Calculate span values for rest of the elements
    for (int i = 1; i < n; i++)
    {
        // Pop elements from stack while stack is not empty and top of
        // stack is smaller than price[i]
        while (!stack.isEmpty() && price[stack.top()] <= price[i])
            stack.pop();

        // If stack becomes empty, then price[i] is greater than all elements
        // on left of it, i.e., price[0], price[1],..price[i-1].  Else price[i]
        // is greater than elements after top of stack
        S[i] = (stack.isEmpty()) ? (i + 1) : (i - stack.top());

        // Push this element to stack
        stack.push(i);
    }
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
}

int main()
{
    int price[] = { 10, 4, 5, 90, 120, 80 };
    int n = sizeof(price) / sizeof(price[0]);
    int *S = new int[n];

    // Fill the span values in array S[]
    calculateSpan(price, n, S);

    // print the calculated span values
    printArray(S, n);


    std::cin.get();
    return 0;
}