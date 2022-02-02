#include <iostream>
#include <string>
#include "Hashtable.h"

using namespace std;

/**
* Construct the hash table.
*/
template <class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj& notFound, int size):ITEM_NOT_FOUND(notFound), dataVector(size)
{
}

template <class HashedObj>
int HashTable<HashedObj>::hashFunction(const HashedObj& element, int tableSize) const
{
    int sum = 0;
    for (int i = 0; i < element.key.length(); i++) // add all bytes in a loop
        sum = sum + (unsigned char)element.key[i]; // unsigned char because of -128

    // If the key size is one the it means that it is just ascii value
    // however, if it is not then we will get modulos of the sum
    if (element.key.length() != 1 && sum % tableSize <= 255) {
        return 255;
    }
    return (sum % tableSize);
}

/**
* Method that performs quadratic probing resolution.
* Return the position where the search for x terminates.
*/
template <class HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj& x) const
{
    int p = hashFunction(x, dataVector.size());
    while (dataVector[p].info != EMPTY && dataVector[p].element != x) {
        // Adding one because of linear probing
        p += 1; 
        if (p >= dataVector.size()) // perform the mod 
        {
            p -= dataVector.size();                // if necessary
        }          
    }
    return p;
}

/**
* Return true if currentPos exists and is active.
*/
template <class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const
{
    return dataVector[currentPos].info == ACTIVE;
}

/**
* Remove item x from the hash table.
*  x has to be in the table
*/
template <class HashedObj>
void HashTable<HashedObj>::remove(const HashedObj& x)
{
    int currentPos = findPos(x);

    if (isActive(currentPos))
        dataVector[currentPos].info = DELETED;
}

/**
* Find item x in the hash table.
* Return the matching item, or ITEM_NOT_FOUND, if not found.
*/
template <class HashedObj>
const HashedObj& HashTable<HashedObj>::find(const HashedObj& x) const
{
    int currentPos = findPos(x);
    if (isActive(currentPos))
        return dataVector[currentPos].element;
    return ITEM_NOT_FOUND;
}

/**
* Insert item x into the hash table. If the item is
* already present, then do nothing.
*/
template <class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj& x)
{
    // Insert x as active
    int currentPos = findPos(x);
    if (isActive(currentPos))
        return;
    dataVector[currentPos] = HashEntry(x, ACTIVE);
}