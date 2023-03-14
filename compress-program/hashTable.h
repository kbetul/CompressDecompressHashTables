#include <vector>
#include <iostream>
#include <string>

using namespace std;

template <class Key, class Value>
class HashTable
{
    public:
        HashTable(const Key & x, int size = 256); //initial size is 256 however we will initialize it to 4096 in main
        HashTable(const HashTable & rhs): array(rhs.array){}
        Key find(const Value & x); //finding and returning the value of Key x
        void makeEmpty();
        void insert(const Key & x, const Value & y); //inserting to array
        void remove(const Value & x); //removing the key from the array
        const HashTable & operator=(const HashTable & rhs){ //operator overloading
            (*this) = rhs;
        };
        enum EntryType {ACTIVE, EMPTY, DELETED};
        
    private:
        struct HashEntry
        { //struct for keeping the code, value, and info
            Key code;
            Value value;
            EntryType info;

            HashEntry(Key code = Key(), const Value & value = Value(), EntryType info = EMPTY)
            : code(code), value(value), info(info){}
        };

        int hash(const Value & value) const; //hashing function  
        vector<HashEntry> array;
        const Key ITEM_NOT_FOUND;
        bool isActive(int currentPos) const;
        int findPos(const Value & x) const; //finding the position to add the key X
};

template <class Key, class Value>
HashTable<Key, Value>::HashTable(const Key & notFound, int size)
: ITEM_NOT_FOUND(notFound), array(size)
{
    makeEmpty();
}

template <class Key, class Value>
int HashTable<Key, Value>::hash(const Value & value) const
{ //hashing function using 31 rule
  int hpos = 0;
  for (int i = 0; i < value.size(); i++) {
    hpos = (hpos * 31 + value[i]) % array.size();
  }
  return hpos;
}

template <class Key, class Value>
Key HashTable<Key, Value>::find(const Value & x)
{
    int currentPos = findPos(x);
    if (isActive(currentPos)) 
        return array[currentPos].code;  
    return ITEM_NOT_FOUND;
}

template <class Key, class Value>
void HashTable<Key, Value>::makeEmpty()
{
    for (int i = 0; i < array.size(); i++) {
        array[i].info = EMPTY;
    }
}

template <class Key, class Value>
void HashTable<Key, Value>::insert(const Key & code, const Value & x)
{
    // Insert x as active
    int currentPos = findPos(x);
    if(isActive(currentPos))
        return;
    array[currentPos] = HashEntry(code, x, ACTIVE); // inserting it as ACTIVE
}

template <class Key, class Value>
void HashTable<Key, Value>::remove(const Value & x)
{
    int currentPos = findPos(x);
    if(isActive(currentPos))
        array[currentPos].info = DELETED; //updating it as DELETED
}

template <class Key, class Value>
int HashTable<Key, Value>::findPos(const Value & val) const
{              
	int p = hash(val);
    while(array[p].info != EMPTY && array[p].value != val) {
        p++;                           // add the difference 
        if(p >= array.size())         // perform the mod
            p = p - array.size();    // if necessary
    }
    return p;
}

template <class Key, class Value>
bool HashTable<Key, Value>::isActive(int currentPos) const
{
    return array[currentPos].info == ACTIVE;
}