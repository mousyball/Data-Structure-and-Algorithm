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
    ListNode<T> *first;         // pointer to the first node
public:
    LinkedList() :first(0) {};
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
    if (first == 0) {
        cout << "[Warning] You're printing a empty list." << endl;
        return;
    }

    // traverse the list, and print out the data of nodes.
    for (ListNode<T> *ptr = first; ptr != 0; ptr = ptr->next)
        cout << ptr->data << " ";

    cout << endl;
}

template <class T>
void LinkedList<T>::push_front(T x)
{
    ListNode<T> *new_node = new ListNode<T>(x);
    new_node->next = first;
    first = new_node;
}

template <class T>
void LinkedList<T>::push_back(T x)
{
    // traverse the list to the last node, then insert a new node.
    ListNode<T> *ptr;
    for (ptr = first; ptr->next != 0; ptr = ptr->next);

    ListNode<T> *new_node = new ListNode<T>(x);
    new_node->next = ptr->next;
    ptr->next = new_node;
}

template <class T>
void LinkedList<T>::erase(T x)
{
    ListNode<T> *delete_node;
    ListNode<T> *previous, *current;

    // return if list is empty.
    if (first == 0) {
        cout << "[Warning] You cannot do Erase operation to a empty list." << endl;
        return;
    }

    // traverse the list to find the `x`
    for (previous = 0, current = first; current != 0; previous = current, current = current->next)
        if (current->data == x) break;

    // return if `x` doesn't exist in the list.
    if (current == 0) {
        cout << "[Warning] Cannot find the value '" << x << "' in the list." << endl;
        return;
    }

    delete_node = current; 
    if (previous != 0)
        previous->next = current->next;    // `x` is not the first node.
    else
        first = current->next;             // `x` is the first node.
    delete delete_node;
    delete_node = 0;

}

template <class T>
void LinkedList<T>::clear()
{
    // traverse the list, and delete node by the order.
    while (first != 0) {
        ListNode<T> *delete_node = first;
        first = first->next;
        delete delete_node;
        delete_node = 0;
    }
}

template <class T>
void LinkedList<T>::reverse()
{
    if (first == 0 || first->next == 0)    // list is empty or list has only one node.
        return;

    ListNode<T> *previous = 0,
                *current = first,
                *preceding = first->next;

    while (preceding != 0) {
        current->next = previous;          // reverse the pointer bewteen previous and current.
        previous = current;                // move previous to current's position
        current = preceding;               // move current to preceding's position
        preceding = preceding->next;       // move preceding to the next node
    }
    current->next = previous;              // reverse the pointer of last node.
    first = current;                       // reset the pointer first to the head node
}


int main()
{
    LinkedList<int> myList;

    myList.push_front(8);
    myList.printList();

    myList.push_front(4);
    myList.push_front(9);
    myList.printList();

    myList.push_back(7);
    myList.erase(888);
    myList.printList();

    myList.erase(4);
    myList.erase(9);
    myList.printList();

    myList.erase(7);
    myList.erase(8);
    myList.erase(8);
    myList.printList();

    // reverse & clear
    myList.push_front(8);
    myList.push_front(4);
    myList.push_front(9);
    myList.push_back(7);
    myList.printList();

    // reverse
    myList.reverse();
    myList.printList();
    // clear
    myList.clear();
    myList.printList();

    std::cin.get();
    return 0;
}