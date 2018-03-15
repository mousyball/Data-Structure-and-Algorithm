#include <iostream>
using std::cout;
using std::endl;

template <class T>
class QueueArrayCircular {
private:
    int front, back;            // index of front and back nodes.
    int capacity;               // capacity of QueueArray
    T *queue;                   // pointer to queue
    void doubleCapacity();      // method for enlarging the capacity
public:
    QueueArrayCircular() :capacity(5), front(0), back(0) {
        queue = new T[capacity];
    };
    void push(T x);
    void pop();
    bool isEmpty();
    bool isFull();
    T getFront();
    T getBack();
    int getSize();
    int getCapacity();          // [option]
    void printQueue();
};

template <class T>
void QueueArrayCircular<T>::printQueue()
{
    int size = getSize();
    int j = 1;
    cout << "==================" << endl;
    for (int i = front; j <= size; ++j) {
        int idx = (++i) % capacity;
        cout << "Index: " << idx << ", Data: " << queue[idx] << endl;
    }
    cout << "==================" << endl << endl;
}

template <class T>
void QueueArrayCircular<T>::doubleCapacity()
{
    T *newQueue = new T[capacity*2];

    int size = getSize();
    int j = 1;
    for (int i = front; j <= size; ++j)
        newQueue[j] = queue[(++i) % capacity];

    capacity *= 2;
    front = 0;
    back = size;

    delete[] queue;
    queue = newQueue;
}

template <class T>
void QueueArrayCircular<T>::push(T x)
{
    if (isFull()) {
        cout << "[Warning] Overcapacity!!! Calling doubleCapacity()..." << endl;
        doubleCapacity();
    }

    back = (back + 1) % capacity;      // index transformation to avoid out-of-bounds access
    queue[back] = x;
}

template <class T>
void QueueArrayCircular<T>::pop()
{
    if (isEmpty()) {
        cout << "[Warning] pop() | Queue is empty." << endl;
        return;
    }

    front = (front + 1) % capacity;    // pesudo remove and index transformation to avoid out-of-bounds access
}

template <class T>
bool QueueArrayCircular<T>::isEmpty()
{
    return (front == back);
}

template <class T>
bool QueueArrayCircular<T>::isFull()
{
    // leave ONE element for checking isFull()
    // hence, (front == back) is left for isEmpty()
    return (front == (back + 1) % capacity);
}

template <class T>
T QueueArrayCircular<T>::getFront()
{
    if (isEmpty()) {
        cout << "[Warning] getFront() | Queue is empty." << endl;
        return -1;
    }

    // use mod to avoid out-of-bounds access
    return queue[(front + 1) % capacity];
}

template <class T>
T QueueArrayCircular<T>::getBack()
{
    if (isEmpty()) {
        cout << "[Warning] getBack() | Queue is empty." << endl;
        return -1;
    }

    return queue[back];
}

template <class T>
int QueueArrayCircular<T>::getSize()
{
    if (back > front)
        return (back - front);
    else if (back < front)
        return (capacity + back - front);
    else
        return 0;
}

template <class T>
int QueueArrayCircular<T>::getCapacity()
{
    return capacity;
}

template <class T>
void printSequentialQueue(QueueArrayCircular<T> queue) {
    cout << "front: " << queue.getFront() << "    back: " << queue.getBack() << "\n"
        << "capacity: " << queue.getCapacity() << "  number of elements: " << queue.getSize() << "\n\n";
}

int main()
{
    QueueArrayCircular<int> q;

    if (q.isEmpty()) {
        cout << "Queue is empty.\n\n";
    }
    q.push(24);
    cout << "After push 24: \n";
    printSequentialQueue(q);
    q.push(8);
    q.push(23);
    cout << "After push 8, 23: \n";
    printSequentialQueue(q);
    q.pop();
    cout << "After pop 24: \n";
    printSequentialQueue(q);
    q.push(13);
    cout << "After push 13: \n";
    printSequentialQueue(q);
    q.pop();
    cout << "After pop 8: \n";
    printSequentialQueue(q);
    q.push(35);
    cout << "After push 35: \n";
    printSequentialQueue(q);
    q.push(9);
    cout << "After push 9: \n";
    printSequentialQueue(q);

    q.printQueue();

    q.push(64);
    cout << "After push 64: \n";
    printSequentialQueue(q);

    q.printQueue();

    std::cin.get();
    return 0;
}
