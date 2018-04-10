#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

struct dict{
    int key;
    string value;
    dict():key(0),value(""){};
    dict(int k, string s):key(k),value(s){};
};

class HashOpenAddress{
private:
    int size, count;
    dict *table;

    int quadraticProbing(int key, int i);

    // tableDoubling()
    // tableShrinking()
    // rehashing()

public:
    HashOpenAddress():size(0),count(0),table(0){};
    HashOpenAddress(int m):size(m),count(0){
        table = new dict[size];
    }
    void insert(int key, string value);
    void remove(int key);
    string search(int key);
    void display();
};

string HashOpenAddress::Search(int key)
{

}

void HashOpenAddress::remove(int key)
{

}

void HashOpenAddress::insert(int key, string value)
{

}

int HashOpenAddress::quadraticProbing(int key, int i)
{

}

void HashOpenAddress::display()
{

}
int main(){

    HashOpenAddress hash(8);          // probing sequence:
    hash.Insert(33, "blue");          // 1,2,4,7,3,0,6,5 -> 1
    hash.Insert(10, "yellow");        // 2,3,5,0,4,1,7,6 -> 2
    hash.Insert(77, "red");           // 5,6,0,3,7,4,2,1 -> 5
    hash.Insert(2, "white");          // 2,3,5,0,4,1,7,6 -> 3
    hash.Display();
    hash.Insert(8, "black");          // 0,1,3,6,2,7,5,4 -> 0
    hash.Insert(47, "gray");          // 7,0,2,5,1,6,4,3 -> 7
    hash.Insert(90, "purple");        // 2,3,5,0,4,1,7,6 -> 4
    hash.Insert(1, "deep purple");    // 4,5,7,2,6,3,1,0 -> 6
    hash.Display();
    hash.Insert(15, "green");         // hash table overflow

    cout << "number#90 is " << hash.Search(90) << "\n\n";

    hash.Delete(90);
    cout << "after deleting (90,purple):\n";
    cout << "number#90 is " << hash.Search(90) << "\n";

    hash.Insert(12, "orange");        // 4,5,7,2,6,3,1,0 -> 4
    hash.Display();

    return 0;
}