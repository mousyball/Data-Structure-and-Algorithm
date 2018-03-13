#include <iostream>
using std::cout;
using std::endl;

template <class T>
class QueueList;                // Forward Declaration for using friend class LinkedList

template <class T>
class QueueNode {
private:
    T data;
    QueueNode *next;
public:
    QueueNode() :data(0), next(0) {};
    QueueNode(T a) :data(a), next(0) {};

    friend class QueueList<T>;
};

template <class T>
class QueueList {
private:
    int size;                   // record the size of list
    QueueNode<T> *front;
    QueueNode<T> *back;
public:
    QueueList() :size(0), front(0), back(0) {};
    void printQueue();          // print all the data out in the Queue
    void push(T x);             // push data into Queue
    void pop();                 // pop out the data at the front of Queue
    T getFront();               // get the data at the front node
    T getBack();                // get the data at the back node
    bool isEmpty();             // check if Queue is empty
    int getSize();              // get size of Queue
};

template <class T>
void QueueList<T>::printQueue()
{
    if (size == 0) {
        cout << "[Warning] You're printing a empty Queue." << endl;
        return;
    }

    QueueNode<T> *ptr = front;
    while (ptr != 0) {
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
    cout << endl;
}

template <class T>
void QueueList<T>::push(T x)
{
    QueueNode<T> *new_node = new QueueNode<T>(x);

    if (size == 0)
        front = new_node;       // case1: insert the first node
    else
        back->next = new_node;  // case2: insert a node after the first node exists.

    back = new_node;
    ++size;
}

template <class T>
void QueueList<T>::pop()
{

    // return if Queue is empty.
    if (size == 0) {
        cout << "[Warning] pop() cannot be executed on a empty Queue." << endl;
        return;
    }

    QueueNode<T> *delete_node = front;
    front = front->next;
    delete delete_node;
    delete_node = 0;
    --size;

    if (size == 0)          // reset back to 0 if Queue is empty.
        back = 0;
}

template <class T>
T QueueList<T>::getFront()
{
    if (front == 0) {
        cout << "[Warning] getFront() | There is no data node in the Queue." << endl;
        return 0;
    } else {
        return front->data;
    }
}

template <class T>
T QueueList<T>::getBack()
{
    if (back == 0) {
        cout << "[Warning] getBack() | There is no data node in the Queue." << endl;
        return 0;
    }
    else {
        return back->data;
    }
}

template <class T>
bool QueueList<T>::isEmpty()
{
    return (size == 0);
}

template <class T>
int QueueList<T>::getSize()
{
    return size;
}


int main()
{
    QueueList<int> myQueue;

    if (myQueue.isEmpty())
        cout << "isEmpty() | Queue is empty..." << endl;
    else
        cout << "isEmpty() | Queus is NOT empty..." << endl;

    cout << "Size = " << myQueue.getSize() << endl;
    cout << "front->data = " << myQueue.getFront() << endl;
    cout << "back->data = " << myQueue.getBack() << endl;
    myQueue.pop();
    myQueue.printQueue();

    myQueue.push(9);
    myQueue.push(4);
    myQueue.push(8);
    myQueue.push(7);

    myQueue.printQueue();
    cout << "size = " << myQueue.getSize() << endl;
    cout << "front->data = " << myQueue.getFront() << endl;
    cout << "back->data = " << myQueue.getBack() << endl;

    if (myQueue.isEmpty())
        cout << "isEmpty() | Queue is empty..." << endl;
    else
        cout << "isEmpty() | Queus is NOT empty..." << endl;

    myQueue.pop();
    myQueue.pop();
    myQueue.printQueue();
    cout << "size = " << myQueue.getSize() << endl;
    myQueue.pop();
    myQueue.pop();
    myQueue.printQueue();	

    std::cin.get();
    return 0;
}