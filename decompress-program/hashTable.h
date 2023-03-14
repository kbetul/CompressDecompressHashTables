#include <vector>
#include <iostream>
#include <string>

using namespace std;

template <class Key, class Value>
class HashTable
{
    public:
        HashTable(const Value & x, int size = 256); //initial size is 256 however we will initialize it to 4096 in main
        HashTable(const HashTable & rhs): array(rhs.array){}
        Value find(const Key & x); //finding and returning the value of Key x
        void makeEmpty();
        void insert(const Key & x, const Value & y); //inserting to array
        void remove(const Key & x); //removing the key from the array
        const HashTable & operator=(const HashTable & rhs){ //operator overloading
            (*this) = rhs;
        };
        Value getItemNotFound();
        enum EntryType {ACTIVE, EMPTY, DELETED};
        
    private:
        struct HashEntry //struct for keeping the code, value, and info
        {
            Key code;
            Value value;
            EntryType info;

            HashEntry(Key code = Key(), const Value & value = Value(), EntryType info = EMPTY)
            : code(code), value(value), info(info){}
        };

        int hash(const Value & value) const; //hashing function    
        vector<HashEntry> array;
        const Value ITEM_NOT_FOUND;
        bool isActive(int currentPos) const;
        int findPos(const Key & x) const; //finding the position to add the key X
};

template <class Key, class Value>
Value HashTable<Key, Value>::getItemNotFound(){
    return ITEM_NOT_FOUND;
}

template <class Key, class Value>
HashTable<Key, Value>::HashTable(const Value & notFound, int size)
: ITEM_NOT_FOUND(notFound), array(size)
{
    makeEmpty();
}

template <class Key, class Value>
int HashTable<Key, Value>::hash(const Value & value) const
{ //hashing function using 31 rule, actually we don't use the hashing function for decompress class
  int hpos = 0;
  for (int i = 0; i < value.size(); i++) {
    hpos = (hpos * 31 + value[i]) % array.size();
  }
  return hpos;
}

template <class Key, class Value>
Value HashTable<Key, Value>::find(const Key & code)
{
    int currentPos = findPos(code);
    if (isActive(currentPos)) 
        return array[currentPos].value;  
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
    int currentPos = findPos(code);
    if(isActive(currentPos))
        return;
    array[currentPos] = HashEntry(code, x, ACTIVE); // inserting it as ACTIVE
}

template <class Key, class Value>
void HashTable<Key, Value>::remove(const Key & code)
{
    int currentPos = findPos(code);
    if(isActive(currentPos))
        array[currentPos].info = DELETED; //updating it as DELETED
}

template <class Key, class Value>
int HashTable<Key, Value>::findPos(const Key & val) const
{              
	int p = val;
    while(array[p].info != EMPTY && array[p].code != val) {
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