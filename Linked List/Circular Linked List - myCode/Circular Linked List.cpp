#include <iostream>
using std::cout;
using std::endl;

template <class T>
class LinkedList;                // Forward Declaration for using friend class LinkedList

template <class T>
class ListNode {
private:
    T data;
    ListNode *next;
public:
    ListNode() :data(0), next(0) {};
    ListNode(T a) :data(a), next(0) {};

    friend class LinkedList<T>;
};

template <class T>
class LinkedList {
private:
    // int size;                // [option] record the size of list
    //ListNode<T> *last->next;  // pointer to the last->next node
    ListNode<T> *last;
public:
    LinkedList() :last(0) {};
    void printList();           // print all the data out in the list
    void push_front(T x);       // insert a node at the front of list
    void push_back(T x);        // insert a node at the end of list
    void erase(T x);            // delete a node which data is `int x` in the list
    void clear();               // clear out the list
    void reverse();             // reverse the list: 7->3->14 => 14->3->7
};

template <class T>
void LinkedList<T>::printList()
{
    if (last == 0) {
        cout << "[Warning] You're printing a empty list." << endl;
        return;
    }

    // traverse the list, and print out the data of nodes.
    ListNode<T> *ptr = last->next;

    do
    {
        cout << ptr->data << " ";
        ptr = ptr->next;
    } while (ptr != last->next);

    cout << endl;
}

template <class T>
void LinkedList<T>::push_front(T x)
{
    ListNode<T> *new_node = new ListNode<T>(x);

    // case: if list is empty.
    if (last == 0) {
        last = new_node;
        new_node->next = new_node;   // point to the head
        return;
    }

    new_node->next = last->next;     // last->next == last->next
    last->next = new_node;
}

template <class T>
void LinkedList<T>::push_back(T x)
{
    ListNode<T> *new_node = new ListNode<T>(x);

    // case: if list is empty.
    if (last == 0) {
        last = new_node;
        new_node->next = new_node;   // point to the head
        return;
    }

    // Traversal is not needed due to last pointer
    new_node->next = last->next;
    last->next = new_node;
    last = new_node;
}

template <class T>
void LinkedList<T>::erase(T x)
{
    ListNode<T> *delete_node;
    ListNode<T> *previous, *current;

    // return if list is empty.
    if (last == 0) {
        cout << "[Warning] erase() | You cannot do Erase operation to a empty list." << endl;
        return;
    }

    // traverse the list to find the `x
    previous = 0;
    current = last->next;
    do
    {
        if (current->data == x) break;
        previous = current;
        current = current->next;
    } while (current != last->next);

    // return if `x` doesn't exist in the list.
    // (previous == last) means that we cannot find `x` while traversing.
    if (previous == last) {
        cout << "[Warning] erase() | Cannot find the value '" << x << "' in the list." << endl;
        return;
    }

    delete_node = current;
    if (previous != 0) {                   // `x` is not the first node.
        previous->next = current->next;

        if (current == last)               // and `x` is the last node.
            last = previous;
    }
    else
        last->next = current->next;        // `x` is the first node.
    delete delete_node;
    delete_node = 0;

}

template <class T>
void LinkedList<T>::clear()
{
    // traverse the list, and delete node by the order.
    ListNode<T> *ptr = last->next;

    do
    {
        ListNode<T> *delete_node = ptr;
        ptr = ptr->next;
        last->next = ptr;
        delete delete_node;
        delete_node = 0;
    } while (ptr != last->next);

    delete ptr;
    ptr = 0;
    last = 0;
}

template <class T>
void LinkedList<T>::reverse()
{
    if (last == 0 || last->next == last)    // list is empty or list has only one node.
        return;

    ListNode<T> *previous = 0,
        *current = last->next,
        *preceding = last->next->next;

    while (last->next != preceding) {
        current->next = previous;          // reverse the pointer bewteen previous and current.
        previous = current;                // move previous to current's position
        current = preceding;               // move current to preceding's position
        preceding = preceding->next;       // move preceding to the next node
    }

    current->next = previous;              // reverse the pointer of last node.
    preceding->next = current;             // link the head and the tail node
    last = preceding;                      // reset the pointer last to the tail node
}


int main()
{
    LinkedList<int> myList;

    myList.push_back(9);
    myList.push_front(8);
    myList.push_front(7);
    myList.push_front(4);
    myList.push_front(87);
    myList.printList();
    myList.reverse();
    myList.printList();

    myList.push_back(777);
    myList.printList();

    myList.erase(777);
    myList.erase(777);
    myList.erase(9);
    myList.erase(7);
    myList.printList();

    myList.clear();
    myList.printList();

    std::cin.get();
    return 0;
}