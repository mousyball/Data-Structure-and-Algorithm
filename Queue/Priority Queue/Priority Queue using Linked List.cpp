#include <iostream>
using std::cout;
using std::endl;

template <class T>
class QueueList;                // Forward Declaration for using friend class LinkedList

template <class T>
class QueueNode {
private:
    T data;
    int priority;               // lower values indicate higher priority
    QueueNode *next;
public:
    QueueNode() :data(0), priority(99), next(0) {};
    QueueNode(T a, int p) :data(a), priority(p), next(0) {};

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
    void push(T x, int p);      // push data into Queue
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
void QueueList<T>::push(T x, int p)
{
    QueueNode<T> *new_node = new QueueNode<T>(x, p);

    if (size == 0) {                      // case0: first node
        front = new_node;
        back = new_node;
    }
    else {
        
        if (front->priority > p) {        // case1: new_node has a higher priority than the first node.
            new_node->next = front;
            front = new_node;
        }
        else {                            // case2: new_node has a lower priority than the first node.

            // use the insertion sort
            QueueNode<T> *ptr = front;
            while (ptr->next != NULL &&
                ptr->next->priority <= p) {    // '=' handle the case that new_node will be placed at the end of nodes with same priority
                ptr = ptr->next;
            }

            new_node->next = ptr->next;
            ptr->next = new_node;	
        }
    }

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
    }
    else {
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

    myQueue.printQueue();

    myQueue.pop();
    myQueue.push(4, 1);
    myQueue.push(5, 2);
    myQueue.push(6, 3);
    myQueue.push(7, 0);
    myQueue.push(87, 2);
    myQueue.printQueue();

    myQueue.pop();
    myQueue.printQueue();
    myQueue.pop();
    myQueue.pop();
    myQueue.printQueue();
    myQueue.pop();
    myQueue.pop();
    myQueue.printQueue();

    std::cin.get();
    return 0;
}