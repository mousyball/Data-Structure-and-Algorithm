#include <iostream>
#include <vector>
#include <string>
#include <math.h>       // floor()

using std::vector;
using std::string;
using std::cout;
using std::endl;

struct Node {
    int key;                    // number 
    string value;               // genre
    Node *next;                 // pointer to remember memory address of next node

    Node() :key(0), value(""), next(nullptr) {};
    Node(int Key, string Value) :key(Key), value(Value), next(nullptr) {};
    Node(Node const &data) :key(data.key), value(data.value), next(data.next) {};
};

class HashChainNode {
private:
    int size,                 // size: size of table, count: number of data
        count;                // count/size = load factor
    Node **table;             // pointer to pointer, hash table  

    int hashFunction(int key);             // Multiplication method
    int hashFunction_BitShifting(int key); // Multiplication method using bit-shifting
    void tableDoubling();
    void tableShrinking();
    void rehashing(int size_orig);

public:
    HashChainNode() {};
    HashChainNode(int m) :size(m), count(0) {
        table = new Node *[size];           // allocate the first demension of table
        for (int i = 0; i < size; i++) {    // initialization
            table[i] = 0;                   // ensure every slot points to NULL
        }
    }
    ~HashChainNode();

    void insert(Node data);         // consider tableDoubling()
    void remove(int key);           // consider tableShrinking()
    string search(int key);
    void displayTable();
};

void HashChainNode::insert(Node data)
{
    ++count;
    if (count > size)                     // consider load factor
        tableDoubling();                  // if n/m > 1, then double the size of table

    int index = hashFunction(data.key);   // get index of slot
    Node *newNode = new Node(data);       // create new node to store data

                                          // push_front()
    if (table[index] == nullptr) {        // eg: list: (empty), add4
        table[index] = newNode;           // eg: list: 4->NULL
    }
    else {                                // eg: list: 5->9->NULL  , add 4
        Node *next = table[index]->next;  //     list: 5->4->9->NULL
        table[index]->next = newNode;
        newNode->next = next;
    }
}

void HashChainNode::remove(int key)
{
    int index = hashFunction(key);        // get index of slot
    Node *current = table[index];         // use two pointer for traversal in list
    Node *previous = nullptr;

    while (current != nullptr && current->key != key) {
        previous = current;               // traversal in list, 3 cases:
        current = current->next;          // 1. data not found
    }                                     // 2. data found at first node in list
                                          // 3. data found at other position in list

    if (current == nullptr) {                 // eg: list:5->2->9->NULL, want to delete 3
        cout << "data not found.\n\n";
        return;
    }
    else {
        if (previous == nullptr) {            // eg: list:5->2->9->NULL, want to delete 5
            table[index] = current->next;     // after deleting 5, list:2->9->NULL
        }                                     // current points to 5     

        else {                                // eg: list:5->2->9->NULL, want to delete 2
            previous->next = current->next;   // after deleting 2, list:5->9->NULL
        }                                     // current points to 2
        delete current;
        current = nullptr;
    }

    --count;
    if (count < size / 4)        // consider load factor
        tableShrinking();        // if n/m < 4, then shrink the table
}

string HashChainNode::search(int key)
{
    int index = hashFunction(key);      // get index of slot
    Node *current = table[index];       // current points to the first node in list

    while (current != nullptr) {        // traversal in list
        if (current->key == key)
            return current->value;

        current = current->next;
    }
    return "...\nno such data";
}

int HashChainNode::hashFunction(int key)
{
    // Multiplication method
    double A = 0.6180339887;
    double frac = key * A - floor(key*A);
    return floor(this->size*frac);
}

int HashChainNode::hashFunction_BitShifting(int key)
{
    // Multiplication method using bit-shifting
    double A = 0.6180339887;
    int bits_of_word = 32;
    unsigned long long size_of_word = pow(2, bits_of_word);
    int p = 0;                   // size is equal to 2 to the p-th power

    int size_tmp = this->size;
    while ((size_tmp & 0x00000001) != 1) {
        size_tmp = size_tmp >> 1;
        ++p;
    }

    unsigned int s = floor(A * size_of_word);
    return (key * s) >> (bits_of_word - p);
}

void HashChainNode::tableDoubling()
{
    int size_orig = size;    // size_orig represents the original size of table
    size *= 2;               // double the size of table
    rehashing(size_orig);;   // create new table with new larger size
}

void HashChainNode::tableShrinking()
{
    int size_orig = size;    // size_orig represents the original size of table
    size /= 2;               // shrink the size of table
    rehashing(size_orig);    // create new table with new smaller size
}

void HashChainNode::rehashing(int size_orig)
{
    Node **newtable = new Node *[size];    // allocate memory for new table
    for (int i = 0; i < size; i++)         // initializetion 
        newtable[i] = nullptr;             // ensure every node in slot points to NULL


    for (int i = 0; i < size_orig; i++) {  // visit every node in the original table

        Node *curr_orig = table[i];        // curr_orig: current node in original table
        Node *prev_orig = nullptr;         // prev_orig: following curr_orig 

        while (curr_orig != nullptr) {     // traversal in list of each slot in original table

            prev_orig = curr_orig->next;   // curr_orig will be directly move to new table
                                           // need prev_orig to keep pointer in original table

            int index = hashFunction(curr_orig->key);    // get index of slot in new table

                                                         // push_front(), do not allocate new memory space for data
                                                         // directly move node in original table to new table
            if (newtable[index] == nullptr) {        // means newtable[index] is empty
                newtable[index] = curr_orig;
                newtable[index]->next = nullptr;     // equivalent to curr_orig->next = 0;
            }
            // if there is no initialization for newtable, segmentation faults might happen
            // because newtable[index] might not point to NULL 
            // but newtable[index] is empty
            else {                                   // if newtable[index] is not empty
                Node *next = newtable[index]->next;  // push_front()
                newtable[index]->next = curr_orig;
                curr_orig->next = next;
            }
            curr_orig = prev_orig;          // visit the next node in list in original table
        }
    }
    delete[] table;                // release memory of original table
    this->table = newtable;        // point table of object to new table
}

HashChainNode::~HashChainNode()
{
    for (int i = 0; i < size; i++) {    // visit every node in table
                                        // and release the memory of each node
        Node *current = table[i];       // point *current to first node in list
        while (current != nullptr) {    // traversal in list
            Node *previous = current;
            current = current->next;
            delete previous;
            previous = nullptr;
        }
    }
    delete[] table;
}

void HashChainNode::displayTable()
{
    for (int i = 0; i < size; i++) {    // visit every node in table 
        cout << "#slot#" << i << ": ";
        Node *current = table[i];
        while (current != nullptr) {
            cout << "(" << current->key << "," << current->value << ") ";
            current = current->next;
        }
        cout << endl;
    }
    cout << endl;
}

int main() {

    HashChainNode hash(2);

    hash.insert(Node(12, "post rock"));
    hash.insert(Node(592, "shoegaze"));
    cout << "After inserting key(12),key(592):\n";
    hash.displayTable();
    hash.insert(Node(6594, "blues"));        // evoke TableDoubling()
    cout << "After inserting key(6594), evoke TableDoubling():\n";
    hash.displayTable();
    hash.insert(Node(7, "folk"));
    cout << "After inserting key(7):\n";
    hash.displayTable();
    hash.insert(Node(123596, "hiphop"));     // evoke TableDoubling()
    cout << "After inserting key(123596), evoke TableDoubling():\n";
    hash.displayTable();
    hash.insert(Node(93, "soul"));
    hash.insert(Node(2288, "indie"));
    hash.insert(Node(793, "jazz"));
    cout << "After inserting key(93),key(2288),key(793):\n";
    hash.displayTable();
    hash.insert(Node(8491, "electro"));      // evoke TableDoubling()
    cout << "After inserting key(8491), evoke TableDoubling():\n";
    hash.displayTable();
    hash.insert(Node(323359, "pop"));
    cout << "After inserting key(323359):\n";
    hash.displayTable();

    cout << "Searching: genre(8491) is " << hash.search(8491) << ".\n\n";
    cout << "Searching: genre(7) is " << hash.search(7) << ".\n\n";

    hash.remove(7);
    cout << "After deleting key(7):\n";
    cout << "Searching: genre(7) is " << hash.search(7) << ".\n\n";

    hash.remove(592);
    cout << "After deleting key(592):\n";
    hash.displayTable();

    cout << "Want to  delete key(592) again:\n";
    hash.remove(592);

    hash.remove(123596);
    hash.remove(323359);
    hash.remove(793);
    hash.remove(93);
    cout << "After deleting key(123596),key(323359),key(793),key(93):\n";
    hash.displayTable();

    hash.remove(6594);      // evoke TableShrinking()
    cout << "After deleting key(6594), evoke TableShrinking():\n";
    hash.displayTable();

    std::cin.get();
    return 0;
}