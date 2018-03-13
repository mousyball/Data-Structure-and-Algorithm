// C++ code
#include <iostream>

struct QueueNode{
    int data;
    QueueNode *next;
    QueueNode():data(0),next(0){};
    QueueNode(int x):data(x),next(0){};
};

class QueueList{
private:
    QueueNode *front;
    QueueNode *back;
    int size;
public:
    QueueList():front(0),back(0),size(0){};
    void Push(int x);
    void Pop();
    bool IsEmpty();
    int getFront();
    int getBack();
    int getSize();
};

void QueueList::Push(int x){

    if (IsEmpty()) {
        front = new QueueNode(x);
        back = front;
        size++;
        return;
    }

    QueueNode *newNode = new QueueNode(x);
    back->next = newNode;
    back = newNode;         // update back pointer
    size++;
}

void QueueList::Pop(){

    if (IsEmpty()) {
        std::cout << "Queue is empty.\n";
        return;
    }

    QueueNode *deletenode = front;
    front = front->next;    // update front pointer
    delete deletenode;
    deletenode = 0;
    size--;
}

int QueueList::getFront(){

    if (IsEmpty()) {
        std::cout << "Queue is empty.\n";
        return -1;
    }

    return front->data;
}

int QueueList::getBack(){

    if (IsEmpty()) {
        std::cout << "Queue is empty.\n";
        return -1;
    }

    return back->data;
}

bool QueueList::IsEmpty(){

//    return (size == 0);
    return ((front && back) == 0);
}

int QueueList::getSize(){

    return size;
}

int main(){

    QueueList q;
    if (q.IsEmpty()) {
        std::cout << "Queue is empty.\n";
    }
    q.Push(24);
    std::cout<< "\nAfter push 24: \n";
    std::cout << "front: " << q.getFront() << "    back: " << q.getBack() << "\n";
    q.Push(8);
    std::cout<< "\nAfter push 8: \n";
    std::cout << "front: " << q.getFront() << "    back: " << q.getBack() << "\n";
    q.Push(23);
    std::cout<< "\nAfter push 23: \n";
    std::cout << "front: " << q.getFront() << "    back: " << q.getBack() << "\n";
    q.Push(13);
    std::cout<< "\nAfter push 13: \n";
    std::cout << "front: " << q.getFront() << "    back: " << q.getBack() << "\n";
    q.Pop();
    std::cout<< "\nAfter pop the front element: \n";
    std::cout << "front: " << q.getFront() << "     back: " << q.getBack() << "\n";
    q.Push(35);
    std::cout<< "\nAfter push 35: \n";
    std::cout << "front: " << q.getFront() << "     back: " << q.getBack() << "\n";
    q.Pop();
    std::cout<< "\nAfter pop the front element: \n";
    std::cout << "front: " << q.getFront() << "    back: " << q.getBack() << "\n";
    q.Pop();
    std::cout<< "\nAfter pop the front element: \n";
    std::cout << "front: " << q.getFront() << "    back: " << q.getBack() << "\n";
    q.Pop();
    std::cout<< "\nAfter pop the front element: \n";
    std::cout << "front: " << q.getFront() << "    back: " << q.getBack() << "\n";
    q.Pop();
    std::cout<< "\nAfter pop the front element: \n";
    q.Pop();

    return 0;
}