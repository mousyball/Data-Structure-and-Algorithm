#include <iostream>
using std::cout;
using std::endl;

template <class T>
class LinkedList;                // Forward Declaration for using friend class LinkedList

template <class T>
class ListNode {
private:
    T data;
    ListNode<T> *next;
    ListNode<T> *prev;
public:
    ListNode() :data(0), next(0), prev(0) {};
    ListNode(T x) :data(x), next(0), prev(0) {};

    friend class LinkedList<T>;
};

template <class T>
class LinkedList {
private:
    // int size;                // [option] record the size of list
    ListNode<T> *first;         // pointer to the first node
    //void swap(ListNode<T> **a, ListNode<T> **b);  // pointer to pointer
    void swap(ListNode<T> *&a, ListNode<T> *&b);    // pointer by reference
public:
    LinkedList() :first(0) {};
    void printList();           // print all the data out in the list
    void insert_front(T x);     // insert a node at the front of list
    void insert_back(T x);      // insert a node at the end of list
    void insert_after(T x, T new_value);     // insert a node after the node which value is `x`
    void insert_before(T x, T new_value);    // insert a node before the node which value is `x`
    void erase(T x);            // delete a node which data is `int x` in the list
    void clear();               // clear out the list
    void reverse();             // reverse the list: 7->3->14 => 14->3->7
};

/*
template <class T>
void LinkedList<T>::swap(ListNode<T> **a, ListNode<T> **b)
{
    unsigned int tmp = (unsigned int)*a ^ (unsigned int)*b;
    *a = (ListNode<T>*) ((unsigned int)*a ^ tmp);
    *b = (ListNode<T>*) ((unsigned int)*b ^ tmp);
}
*/

template <class T>
void LinkedList<T>::swap(ListNode<T> *&a, ListNode<T> *&b)
{
    a = (ListNode<T>*) ((unsigned int)a ^ (unsigned int)b);
    b = (ListNode<T>*) ((unsigned int)a ^ (unsigned int)b);
    a = (ListNode<T>*) ((unsigned int)a ^ (unsigned int)b);

    /*
    unsigned int tmp = (unsigned int)a ^ (unsigned int)b;
    a = (ListNode<T>*) ((unsigned int)a ^ tmp);
    b = (ListNode<T>*) ((unsigned int)b ^ tmp);
    */
}

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
void LinkedList<T>::insert_front(T x)
{
    ListNode<T> *new_node = new ListNode<T>(x);
    
    if (first != 0)
        first->prev = new_node;

    new_node->next = first;
    first = new_node;
}

template <class T>
void LinkedList<T>::insert_back(T x)
{
    ListNode<T> *new_node = new ListNode<T>(x);

    // insert in a empty list.
    if (first == 0) {
        new_node->next = first;
        first = new_node;
        return;
    }

    // traverse the list to the last node, then insert a new node.
    ListNode<T> *ptr;
    for (ptr = first; ptr->next != 0; ptr = ptr->next);

    new_node->next = ptr->next;
    new_node->prev = ptr;
    ptr->next = new_node;
}

template <class T>
void LinkedList<T>::insert_after(T x, T new_value)
{
    ListNode<T> *ptr;

    // return if list is empty.
    if (first == 0) {
        cout << "[Warning] insert_after() cannot be executed on a empty list." << endl;
        return;
    }

    // traverse the list to find the `x`
    for (ptr = first; ptr != 0; ptr = ptr->next)
        if (ptr->data == x) break;

    // return if `x` doesn't exist in the list.
    if (ptr == 0) {
        cout << "[Warning] insert_after() | Cannot find the value '" << x << "' in the list." << endl;
        return;
    }

    // insert_after()
    ListNode<T> *new_node = new ListNode<T>(new_value);

    new_node->next = ptr->next;
    new_node->prev = ptr;

    // if the node we find is not the end of list.
    if (ptr->next != 0)
        ptr->next->prev = new_node;

    ptr->next = new_node;	
}

template <class T>
void LinkedList<T>::insert_before(T x, T new_value)
{
    ListNode<T> *ptr;

    // return if list is empty.
    if (first == 0) {
        cout << "[Warning] insert_before() cannot be executed on a empty list." << endl;
        return;
    }

    // traverse the list to find the `x`
    for (ptr = first; ptr != 0; ptr = ptr->next)
        if (ptr->data == x) break;

    // return if `x` doesn't exist in the list.
    if (ptr == 0) {
        cout << "[Warning] insert_before() | Cannot find the value '" << x << "' in the list." << endl;
        return;
    }

    // insert_before()
    ListNode<T> *new_node = new ListNode<T>(new_value);

    new_node->next = ptr;
    new_node->prev = ptr->prev;

    if (ptr->prev != 0)
        ptr->prev->next = new_node;    // if the node we find is not the head of list
    else
        first = new_node;              // reset the head pointer if the new_node is the head of list.

    ptr->prev = new_node;	
}

template <class T>
void LinkedList<T>::erase(T x)
{
    // return if list is empty.
    if (first == 0) {
        cout << "[Warning] You cannot do Erase operation to a empty list." << endl;
        return;
    }

    ListNode<T> *ptr;

    // traverse the list to find the `x`
    for (ptr = first; ptr != 0; ptr = ptr->next)
        if (ptr->data == x) break;

    // return if `x` doesn't exist in the list.
    if (ptr == 0) {
        cout << "[Warning] erase() | Cannot find the value '" << x << "' in the list." << endl;
        return;
    }

    if (ptr->prev != 0) {                  // `x` is not the first node.
        if (ptr->next != 0)                // and also `x` is not the last node.
            ptr->next->prev = ptr->prev;
        ptr->prev->next = ptr->next;
    }
    else {
        ptr->next->prev = ptr->prev;       // `x` is the first node.
        first = ptr->next;
    }

    delete ptr;
    ptr = 0;
}

template <class T>
void LinkedList<T>::clear()
{
    // traverse the list, and delete node in a forward order.
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

    ListNode<T> *ptr = first;
    ListNode<T> *current = first;

    while (ptr != 0) {
        current = ptr;
        ptr = ptr->next;

        swap(current->prev, current->next);	
    }

    first = current;       // reset the head pointer;
}


int main()
{
    LinkedList<int> myList;

    // missing value test
    myList.insert_after(7, 999);
    myList.insert_before(9, 888);

    // insert {9, 4, 8, 7}
    myList.insert_front(8);
    myList.printList();

    myList.insert_front(4);
    myList.insert_front(9);
    myList.printList();

    myList.insert_back(7);
    myList.printList();

    // insertion method test
    myList.insert_after(7, 999);
    myList.insert_before(9, 888);
    myList.insert_after(4, 123);
    myList.insert_before(8, 555);	
    myList.printList();

    // missing value test
    myList.insert_after(1586, 123);
    myList.insert_before(10, 555);

    // erase method test
    myList.erase(888);
    myList.erase(123);
    myList.erase(999);
    myList.erase(555);
    myList.erase(1024);
    myList.printList();

    // reverse DLL
    myList.reverse();
    myList.printList();

    std::cin.get();
    return 0;
}