#include <iostream>

template <class T>
class StackArray {
private:
    int _top;                   // index of top
    int _capacity;              // capacity of array
    T *stack;                   // array representing stack
    T minEle;                   // minimum element in the stack

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
    T getMin() const;
};

template <class T>
T StackArray<T>::getMin() const
{	
    if (this->isEmpty())
        return 0;
    else
        return minEle;
}

template <class T>
void StackArray<T>::pop()
{
    if (_top == -1) {
        std::cout << "Stack is empty." << std::endl;
        return;
    }

    T temp = stack[_top--];	    // pseudo-remove

    // Minimum will change as the minimum element
    // of the stack is being removed.
    if (temp <= minEle)
        minEle = 2 * minEle - temp;

    std::cout << "Top Most Element Removed: \n";
}

template <class T>
void StackArray<T>::push(T value)
{
    // check if array is full, then call doubleCapacity
    if (_top == _capacity - 1)
        doubleCapacity();

    // Insert new number into the stack
    if (this->isEmpty()) {
        minEle = value;
        stack[++_top] = value;
        return;
    }

    // If new number is less than minEle
    if (value < minEle)	{
        stack[++_top] = 2 * value - minEle;		
        minEle = value;
    } else
        stack[++_top] = value;

}

template <class T>
T StackArray<T>::top() const
{
    int temp = stack[_top];

    if (_top == -1)
        return NULL;
    else
        return (temp < minEle) ? minEle : temp;
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
    std::cout << "stack.getMin() = " << stack.getMin() << std::endl;

    std::cout << "================" << std::endl;
}

int main()
{
    StackArray<int> stack;

    stack.pop();
    reportStatus(stack);

    stack.push(5);
    reportStatus(stack);

    stack.push(2);
    reportStatus(stack);

    stack.push(1);
    reportStatus(stack);

    stack.push(1);
    reportStatus(stack);

    stack.push(-1);
    reportStatus(stack);

    stack.pop();
    reportStatus(stack);

    stack.pop();
    reportStatus(stack);

    stack.pop();
    reportStatus(stack);

    stack.pop();
    reportStatus(stack);

    stack.pop();
    reportStatus(stack);


    std::cin.get();
    return 0;
}