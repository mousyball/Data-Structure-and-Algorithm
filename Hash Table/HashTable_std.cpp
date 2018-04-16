#include <iostream>
#include <vector>
#include <list>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::list;
using std::string;

struct dict {                        // self-defined dictionary
    string key;                      // key for Name (eg:Jordan)
    string value;                    // value for Team (eg:Bulls)
    dict() :key(""), value("") {};
    dict(string Key, string Value) :key(Key), value(Value) {};
};

class HashChain_std {
private:
    int size,                             // size of table
        count;                            // count: number of data

    vector<list<dict> > table;            // hash table with linked list; [NOTE] the blank space between double closing angle brackets (>>)

    int preHashing(string key_str);       // turn string_type_key to int_type_key
    int hashFunction(string key_str);     // using Division method

    unsigned int preHashing_CRC(string key_str);
    unsigned int preHashing_PJW(string key_str);

public:
    HashChain_std() {};
    HashChain_std(int m) :size(m), count(0) {
        table.resize(size);               // allocate memory for each slot
    }

    void insert(dict data);
    void remove(string key);
    string search(string key);
    void displayTable();
};

unsigned int HashChain_std::preHashing_PJW(string key_str)
{
    const unsigned int PJW_HASH_SHIFT =4;
    const unsigned int PJW_HASH_RIGHT_SHIFT = 24;
    const unsigned int PJW_HASH_MASK = 0xf0000000;

    unsigned int hashValue = 0;
    int i;

    for (i = 0; i<key_str.length(); i++)
    {
        hashValue = (hashValue << PJW_HASH_SHIFT) + (unsigned)(key_str.at(i));
        unsigned int rotate_bits = hashValue & PJW_HASH_MASK;
        hashValue ^= rotate_bits | (rotate_bits >> PJW_HASH_RIGHT_SHIFT);
    }
    return hashValue;
}

unsigned int HashChain_std::preHashing_CRC(string key_str)
{
    const unsigned int BYTE_WIDTH = 8;
    const unsigned int WORD_WIDTH = sizeof(int) * BYTE_WIDTH;
    const unsigned int CRC_HASH_SHIFT = 5;

    unsigned int hashValue = 0;
    int i = key_str.length();

    for (i = 0; i<key_str.length(); i++)
    {
        unsigned int leftShiftedValue = hashValue << CRC_HASH_SHIFT;
        unsigned int rightShiftedValue = hashValue >> (WORD_WIDTH - CRC_HASH_SHIFT);
        hashValue = (leftShiftedValue | rightShiftedValue) ^ (unsigned)(key_str.at(i));
    }
    return hashValue;
}

string HashChain_std::search(string key_str)
{
    // 1. get index from hash function
    // 2. traversal in the linked list
    // 2-1. if key_str exists, return its value
    // 2-2. if key_str doesn't exists, return message
    // [NOTE] list.end() is the next element of the last element containing value.
    int index = hashFunction(key_str);
    for (list<dict>::iterator itr = table[index].begin(); itr != table[index].end(); ++itr) {
        if (itr->key == key_str)
            return itr->value;
    }
    return "...\nno such data";
}

void HashChain_std::remove(string key_str)
{
    // 1. get index from hash function
    // 2. traversal in the linked list
    // 2-1. if key_str exists, do erase()
    // 2-2. if key_str doesn't exists, do nothing
    // [NOTE] return is needed to avoid exception after deletion.
    int index = hashFunction(key_str);
    for (list<dict>::iterator itr = table[index].begin(); itr != table[index].end(); ++itr) {
        if (itr->key == key_str) {
            table[index].erase(itr);
            return;
        }
    }
}

void HashChain_std::insert(dict data)
{
    // 1. get index from hash function
    // 2. insert data at the front of linked list
    int index = hashFunction(data.key);
    table[index].push_front(data);
}

int HashChain_std::preHashing(string key_str)
{
    // if   key_str = Jordan, exp = 9
    // then key_int = ASCII(J)*9^5+ASCII(o)*9^4+ASCII(r)*9^3
    //               +ASCII(d)*9^2+ASCII(a)*9^1+ASCII(n)*9^0

    int exp = 9,        // choose randomly 
        key_int = 0,
        p = 1;

    for (int i = (int)key_str.size() - 1; i >= 0; --i) {
        key_int += key_str[i] * p;
        p *= exp;
    }
    return key_int;
}

int HashChain_std::hashFunction(string key_str)
{
    return (preHashing(key_str) % this->size);     // Division method
    //return (preHashing_CRC(key_str) % this->size);
    //return (preHashing_PJW(key_str) % this->size);
}

void HashChain_std::displayTable()
{
    for (int i = 0; i < table.size(); i++) {
        cout << "slot#" << i << ": ";
        for (list<dict>::iterator itr = table[i].begin(); itr != table[i].end(); itr++)
            cout << "(" << (*itr).key << "," << (*itr).value << ") ";
        cout << endl;
    }
    cout << endl;
}

int main()
{
    HashChain_std hash(5);
    hash.insert(dict("T-Mac", "Magic"));
    hash.insert(dict("Bryant", "Lakers"));
    hash.insert(dict("Webber", "Kings"));
    hash.insert(dict("Arenas", "Wizards"));
    hash.insert(dict("Davis", "Clippers"));
    hash.insert(dict("Kidd", "Nets"));
    hash.displayTable();

    cout << "T-Mac is in " << hash.search("T-Mac") << ". " << endl;
    cout << "Arenas is in " << hash.search("Arenas") << ". " << endl;

    hash.remove("Kidd");
    hash.remove("T-Mac");
    cout << "\nAfter deleing Kidd and T-Mac:\n";
    hash.displayTable();

    std::cin.get();
    return 0;
}