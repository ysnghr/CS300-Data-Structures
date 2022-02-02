#ifndef Hashtable_h
#define Hashtable_h

#include <vector>
using namespace std;


// This struct helps us to store key and code of object
struct hashObject {
    string key;
    int code;

    hashObject() {
        key = "";
        code = -1;
    }

    hashObject(string paramKey, int paramCode) {
        key = paramKey;
        code = paramCode;
    }


    hashObject(string paramKey) {
        key = paramKey;
        code = -1;
    }

    // == operator overloading
    bool operator==(const hashObject& right_side) const {
        return this->key == right_side.key;
    }

    // != operator overloading
    bool operator!=(const hashObject& right_side) const {
        return this->key != right_side.key;
    }
};


template <class HashedObj>
class HashTable
{
    public:
        explicit HashTable(const HashedObj& notFound, int size = 4096);
        HashTable(const HashTable& rhs)
            : ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND),
            dataVector(rhs.dataVector), currentSize(rhs.currentSize) { }

        const HashedObj& find(const HashedObj& x) const;

        void insert(const HashedObj& x);
        void remove(const HashedObj& x);

        enum EntryType { ACTIVE, EMPTY, DELETED };

    private:
        struct HashEntry
        {
            HashedObj element;
            EntryType info;

            HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY)
                : element(e), info(i) { }
        };

        vector<HashEntry> dataVector;
        int currentSize;
        const HashedObj ITEM_NOT_FOUND;
        bool isActive(int currentPos) const;
        int findPos(const HashedObj& x) const;
        int hashFunction(const HashedObj& element, int tablesize) const;
};

#include "Hashtable.cpp"
#endif