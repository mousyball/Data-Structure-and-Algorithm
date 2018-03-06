#include <iostream>
using namespace std;

class StackNode {
private:
    int value;
public:
    StackNode(int val = 0): value(val) {}
    
    friend class StackArray;
};

class StackArray {
private:
    int _top;				// index of top
    int _capacity;			// capacity of array
    //int *stack;			// array representing stack
    StackNode **obj_stack;	// object array representing stack
    void doubleCapacity();	// double the capacity of stack when it's full.
public:
    StackArray(int top = -1, int cap = 1)		// initialize a array with constructor
        : _top(top), _capacity(cap)
    {
        //stack = new int[_capacity];

        obj_stack = new StackNode*[_capacity];

    }
    void pop();			// pop the data at the top
    void push(int);		// push the data into the top
    int top();			// the content of top element
    bool isEmpty();		// check if stack is empty
    int getSize();		// get the size of stack (elements count).
};

void StackArray::pop()
{
    /*
    if (_top == -1) {
        cout << "Stack is empty." << endl;
        return NULL;
    }
    else
        return stack[_top--];
    */

    if (_top == -1) {
        cout << "Stack is empty." << endl;
        return;
    }

    //_top--;
    //stack[_top--] = 0;				// (*1)
    //delete obj_stack[_top--];			// (*2-1) Don't do this!!!
    obj_stack[_top--]->~StackNode();	// (*2-2) These two methods which use dynamic allocation should avoid being used.

}

void StackArray::push(int value)
{
    // check if top == cap - 1, then call doubleCapacity
    if (_top == _capacity - 1)
        doubleCapacity();

    int idx = ++_top;
    obj_stack[idx] = new StackNode;
    obj_stack[idx]->value = value;

    //stack[++_top] = value;
}

int StackArray::top()
{
    if (_top == -1)
        return NULL;
    else
        return obj_stack[_top]->value;
        //return stack[_top];
}

bool StackArray::isEmpty()
{
    return (_top == -1);
}

int StackArray::getSize()
{
    return (_top + 1);
}

void StackArray::doubleCapacity()
{
    /*
    1. cap*2
    2. new a stack with cap*2 size.
    3. copy small stack into big stack.
    4. delete small stack.
    5. redirection
    */
    
    /*
    _capacity *= 2;

    int* newStack = new int[_capacity];

    for (int i = 0; i < _capacity/2; ++i)
        newStack[i] = stack[i];

    delete[] stack;

    stack = newStack;
    */

    _capacity *= 2;

    StackNode** newStack = new StackNode*[_capacity];
    for (int i = 0; i < _capacity / 2; i++)
        newStack[i] = new StackNode;

    for (int i = 0; i < _capacity / 2; ++i)
        newStack[i]->value = obj_stack[i]->value;

    for (int i = 0; i < _capacity / 2; i++)
        delete obj_stack[i];
    delete[] obj_stack;

    obj_stack = newStack;


}

void reportStatus(StackArray stack)
{
    cout << "stack.isEmpty() = " << stack.isEmpty() << endl;
    cout << "stack.getSize = " << stack.getSize() << endl;
    cout << "stack.top() = " << stack.top() << endl;

    cout << "================" << endl;
}

int main()
{
    StackArray stack;

    stack.pop();
    reportStatus(stack);

    stack.push(777);
    reportStatus(stack);

    stack.push(999);
    reportStatus(stack);

    stack.pop();
    reportStatus(stack);

    stack.pop();
    reportStatus(stack);

    stack.pop();
    reportStatus(stack);


    system("pause");
    return 0;
}