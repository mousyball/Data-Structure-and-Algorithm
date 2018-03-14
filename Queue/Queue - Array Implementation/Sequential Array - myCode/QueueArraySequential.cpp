#include <iostream>
using std::cout;
using std::endl;

template <class T>
class QueueArraySequential {
private:
    int front, back;            // index of front and back nodes.
    int capacity;               // capacity of QueueArray
    T *queue;                   // pointer to queue
    void doubleCapacity();      // method for enlarging the capacity
public:
    QueueArraySequential() :capacity(5), front(-1), back(-1) {
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
};

template <class T>
void QueueArraySequential<T>::doubleCapacity()
{
    capacity *= 2;

    T *newQueue = new T[capacity];

    int j = 0;
    for (int i = front + 1; i <= back; ++i, ++j)
        newQueue[j] = queue[i];

    front = -1;
    back = j - 1;

    delete[] queue;
    queue = newQueue;
}

template <class T>
void QueueArraySequential<T>::push(T x)
{
    if (isFull())
        doubleCapacity();

    queue[++back] = x;
}

template <class T>
void QueueArraySequential<T>::pop()
{
    if (isEmpty()) {
        cout << "[Warning] pop() | Queue is empty." << endl;
        return;
    }

    ++front;      // pesudo remove
}

template <class T>
bool QueueArraySequential<T>::isEmpty()
{
    return (front == back);
}

template <class T>
bool QueueArraySequential<T>::isFull()
{
    return (capacity == back + 1);
}

template <class T>
T QueueArraySequential<T>::getFront()
{
    if (isEmpty()) {
        cout << "[Warning] getFront() | Queue is empty." << endl;
        return -1;
    }

    return queue[front + 1];
}

template <class T>
T QueueArraySequential<T>::getBack()
{
    if (isEmpty()) {
        cout << "[Warning] getBack() | Queue is empty." << endl;
        return -1;
    }

    return queue[back];
}

template <class T>
int QueueArraySequential<T>::getSize()
{
    return (back - front);
}

template <class T>
int QueueArraySequential<T>::getCapacity()
{
    return capacity;
}

template <class T>
void printSequentialQueue(QueueArraySequential<T> queue) {
    cout << "front: " << queue.getFront() << "    back: " << queue.getBack() << "\n"
        << "capacity: " << queue.getCapacity() << "  number of elements: " << queue.getSize() << "\n\n";
}

int main()
{
    QueueArraySequential<int> q;

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

    std::cin.get();
    return 0;
}
