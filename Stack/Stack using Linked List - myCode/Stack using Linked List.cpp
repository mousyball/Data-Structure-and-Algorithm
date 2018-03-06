#include <iostream>
using namespace std;

class StackNode {
private:
    int value;
    StackNode *next;
public:
    StackNode(int val = 0) : value(val), next(NULL) {};
    StackNode(int val, StackNode *nextNode) : value(val), next(nextNode) {};

    friend class StackList;
};

class StackList {
private:
    int _size;          // record size
    StackNode *_top;    // pointer points to the top
public:
    StackList() : _size(0), _top(NULL) {};

    void pop();			// pop the data at the top
    void push(int);		// push the data into the top
    int top();			// the content of top element
    bool isEmpty();		// check if stack is empty
    int getSize();		// get the size of stack (elements count).
};

void StackList::pop()
{
    /*
    1. size check
    [NOTE] *2. top should be assigned to a Node, or we can't delete the node we wanna pop.
    3. top points to the nextNode.
    4. delete the node under poping.
    5. --size
    */


    if (_size == 0) {
        cout << "Stack is empty." << endl;
        return;
    }

    StackNode *deleteNode = _top;       // [Note] Don't forget to do this.
    _top = deleteNode->next;
    delete deleteNode;
    deleteNode = 0;                     // [Note] Like in C, we set the pointer to NULL (0 in C++) after we delete the pointer.
    --_size;

}

void StackList::push(int value)
{
    /*
    1. Instantiate a node with value
    2. node.next points to top
    3. top points to node
    4. ++size
    */

    StackNode *newNode = new StackNode(value);
    newNode->next = _top;
        // StackNode *newNode = new StackNode(value, _top);     // [Good Practice] use constructor to do the instantiation.
    _top = newNode;
    ++_size;
}

int StackList::top()
{
    if (_top == NULL) {
        cout << "Stack is empty." << endl;
        return -1;
    }

    return _top->value;
}

bool StackList::isEmpty()
{
    return (_size == 0);
}

int StackList::getSize()
{
    return _size;
}

void reportStatus(StackList stack)
{
    cout << "stack.isEmpty() = " << stack.isEmpty() << endl;
    cout << "stack.getSize = " << stack.getSize() << endl;
    cout << "stack.top() = " << stack.top() << endl;

    cout << "================" << endl;
}

int main()
{
    StackList stack;

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