#include <iostream>
#include <string>
#include <cmath>

using std::string;
using std::cout;
using std::endl;

struct dict {
    int key;
    string value;
    dict() :key(0), value("") {};
    dict(int k, string s) :key(k), value(s) {};
};

class HashOpenAddress {
private:
    int size, count;
    const float load_factor_upper = 0.7;
    const float load_factor_lower = 0.25;
    dict *table;

    int linearProbing(int key, int i);
    int quadraticProbing(int key, int i);
    int doubleHashing(int key, int i);

    void tableDoubling();
    void tableShrinking();
    void rehashing(int size_orig);

public:
    HashOpenAddress() :size(0), count(0), table(0) {};
    HashOpenAddress(int m) :size(m), count(0) {
        table = new dict[size];
    }
    void insert(int key, string value);
    void remove(int key);
    string search(int key);
    void display();
};

void HashOpenAddress::tableDoubling()
{
    int size_orig = size;    // size_orig represents the original size of table
    size *= 2;               // double the size of table
    rehashing(size_orig);;   // create new table with new larger size
}

void HashOpenAddress::tableShrinking()
{
    int size_orig = size;    // size_orig represents the original size of table
    size /= 2;               // shrink the size of table
    rehashing(size_orig);    // create new table with new smaller size
}

void HashOpenAddress::rehashing(int size_orig)
{
    dict* newtable = new dict[size];       // allocate memory for new table

    for (int i = 0; i < size_orig; i++) {  // visit every node in the original table
        
        if (table[i].value != "") {

            int k = 0;
            while (k != size) {            // if there is a empty slot in the newtable, insert the key and the value
                int j = quadraticProbing(table[i].key, k);
                if (newtable[j].value == "") {
                    newtable[j].key = table[i].key;
                    newtable[j].value = table[i].value;
                    break;
                }
                else
                    ++k;
            }
        }
    }

    delete[] table;                // release memory of original table
    this->table = newtable;        // point table of object to new table
}

string HashOpenAddress::search(int key)
{
    int i = 0;
    while (i != size) {
        int j = quadraticProbing(key, i);
        if (table[j].key == key)
            return table[j].value;
        else
            ++i;
    }
    return "...data not found\n";
}

void HashOpenAddress::remove(int key)
{
    int i = 0;
    while (i != size) {
        int j = quadraticProbing(key, i);
        if (table[j].key == key) {
            table[j].key = 0;
            table[j].value = "";
            
            --count;
            if (static_cast<float>(count) / size < load_factor_lower)   // consider load factor
                tableShrinking();                                       // if n/m < 4, then shrink the table
            return;
        }
        else
            ++i;
    }
    cout << "...data not found\n";
}

void HashOpenAddress::insert(int key, string value)
{
    ++count;
    if (static_cast<float>(count) / size > load_factor_upper)
        tableDoubling();

    int i = 0;
    while (i != size) {
        int j = quadraticProbing(key, i);
        if (table[j].value == "") {
            table[j].key = key;
            table[j].value = value;
            //++count;
            return;
        }
        else
            ++i;
    }
    //cout << "Hash Table Overflow\n";
}

int HashOpenAddress::linearProbing(int key, int i)
{
    return ((key + i) % size);
}

int HashOpenAddress::quadraticProbing(int key, int i)
{
    // c1 = c2 = 0.5
    return ((int)((key % size) + 0.5*i + 0.5*i*i) % size);

    // another quadraticProbing
    //return ((key % size) - pow(-1, i) * pow(ceil(i/2), 2));
}

int HashOpenAddress::doubleHashing(int key, int i)
{
    // [NOTE-1] using doubleHashing has to make hash table's size be prime
    // [NOTE-2] tableDoubling and tableShrinking should grow by following the prime table, instead of multiplying or dividing 2.
    return ((key % size) + i * (1 + (key % (size - 1)))) % size;
}

void HashOpenAddress::display()
{
    for (int i = 0; i < size; i++) {
        cout << "slot#" << i << ": (" << table[i].key
            << "," << table[i].value << ")" << endl;
    }
    cout << endl;
}

int main() {

    HashOpenAddress hash(8);          // probing sequence:
    hash.insert(33, "blue");          // 1,2,4,7,3,0,6,5 -> 1
    hash.insert(10, "yellow");        // 2,3,5,0,4,1,7,6 -> 2
    hash.insert(77, "red");           // 5,6,0,3,7,4,2,1 -> 5
    hash.insert(2, "white");          // 2,3,5,0,4,1,7,6 -> 3
    hash.display();
    hash.insert(8, "black");          // 0,1,3,6,2,7,5,4 -> 0
    hash.insert(47, "gray");          // 7,0,2,5,1,6,4,3 -> 7
    hash.insert(90, "purple");        // evoke tableDoubling()
    hash.insert(1, "deep purple");
    hash.display();
    hash.insert(15, "green");

    cout << "number#90 is " << hash.search(90) << "\n\n";

    hash.remove(90);
    cout << "after deleting (90,purple):\n";
    cout << "number#90 is " << hash.search(90) << "\n";

    hash.insert(12, "orange");
    hash.display();

    hash.remove(47);
    hash.remove(77);
    hash.remove(1);
    hash.remove(2);
    hash.remove(15);
    hash.remove(12);                  // evoke tableShrinking()
    cout << "Execute several remove() to make the quantity lower than 0.25 :\n";
    hash.display();

    hash.remove(8);
    hash.remove(33);                  // evoke tableShrinking()
    cout << "Execute several remove() to make the quantity lower than 0.25 :\n";
    hash.display();

    std::cin.get();
    return 0;
}