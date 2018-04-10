#include <iostream>
#include <vector>
#include <string>
#include <math.h>       // floor()

using std::vector;
using std::string;
using std::cout;
using std::endl;

struct Node{
    int key;                    // number 
    string value;               // genre
    Node *next;                 // pointer to remember memory address of next node

    Node():key(0),value(""),next(0){};
    Node(int Key, string Value):key(Key),value(Value),next(0){};
    Node(Node const &data):key(data.key),value(data.value),next(data.next){};
};

class HashChainNode{
private:
    int size,                 // size: size of table, count: number of data
        count;                // count/size = load factor
    Node **table;             // pointer to pointer, hash table  

    int hashFunction(int key);      // Multiplication method
    void tableDoubling();           
    void tableShrinking();          
    void rehashing(int size_orig);  

public:
    HashChainNode(){};
    HashChainNode(int m):size(m),count(0){
        table = new Node *[size];           // allocate the first demension of table
        for (int i = 0; i < size; i++) {    // initialization
            table[i] = 0;                   // ensure every slot points to NULL
        }
    }
    ~HashChainNode();

    void insert(Node data);         // consider TableDoubling()
    void remove(int key);           // consider TableShrinking()
    string search(int key);
    void displayTable();
};

void HashChainNode::insert(Node data)
{

}

void HashChainNode::remove(int key)
{

}

string HashChainNode::search(int key)
{

}

int HashChainNode::hashFunction(int key)
{

}

void HashChainNode::tableDoubling()
{

}

void HashChainNode::tableShrinking()
{

}

void HashChainNode::rehashing(int size_orig)
{

}

HashChainNode::~HashChainNode()
{

}

void HashChainNode::displayTable()
{

}

int main(){

    HashChainNode hash(2);

    hash.Insert(Node(12,"post rock"));
    hash.Insert(Node(592,"shoegaze"));
    cout << "After inserting key(12),key(592):\n";
    hash.DisplayTable();
    hash.Insert(Node(6594,"blues"));        // evoke TableDoubling()
    cout << "After inserting key(6594), evoke TableDoubling():\n";
    hash.DisplayTable();
    hash.Insert(Node(7,"folk"));
    cout << "After inserting key(7):\n";
    hash.DisplayTable();
    hash.Insert(Node(123596,"hiphop"));     // evoke TableDoubling()
    cout << "After inserting key(123596), evoke TableDoubling():\n";
    hash.DisplayTable();
    hash.Insert(Node(93,"soul"));
    hash.Insert(Node(2288,"indie"));
    hash.Insert(Node(793,"jazz"));
    cout << "After inserting key(93),key(2288),key(793):\n";
    hash.DisplayTable();
    hash.Insert(Node(8491,"electro"));      // evoke TableDoubling()
    cout << "After inserting key(8491), evoke TableDoubling():\n";
    hash.DisplayTable();
    hash.Insert(Node(323359,"pop"));
    cout << "After inserting key(323359):\n";
    hash.DisplayTable();

    cout << "Searching: genre(8491) is " << hash.Search(8491) << ".\n\n";
    cout << "Searching: genre(7) is " << hash.Search(7) << ".\n\n";

    hash.Delete(7);
    cout << "After deleting key(7):\n";
    cout << "Searching: genre(7) is " << hash.Search(7) << ".\n\n";

    hash.Delete(592);
    cout << "After deleting key(592):\n";
    hash.DisplayTable();

    cout << "Want to  delete key(592) again:\n";
    hash.Delete(592);

    hash.Delete(123596);
    hash.Delete(323359);
    hash.Delete(793);
    hash.Delete(93);
    cout << "After deleting key(123596),key(323359),key(793),key(93):\n";
    hash.DisplayTable();

    hash.Delete(6594);      // evoke TableShrinking()
    cout << "After deleting key(6594), evoke TableShrinking():\n";
    hash.DisplayTable();

    return 0;
}