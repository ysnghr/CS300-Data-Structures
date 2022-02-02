#include <iostream>
#include <string>
#include <fstream>
#include "Hashtable.h"

using namespace std;


/**
* Adding all ASCII values to HashTable from 0 to 255
*/
void addSingleCharacters(HashTable<hashObject>& HASH_ARRAY) {
	for (int index = 0; index <= 255; index++)
	{
		string stringVersionOfChar = string(1, char(index));
		hashObject oneAsciiObject(stringVersionOfChar, index);
		HASH_ARRAY.insert(oneAsciiObject);
	}
}

int main() {
	// initializing dummy object for HashTable
	hashObject DUMMY_OBJECT; 

	// initializing Hash Table
	HashTable<hashObject> HASH_ARRAY = HashTable<hashObject>(DUMMY_OBJECT, 4096);

	// Adding all ascii values
	addSingleCharacters(HASH_ARRAY);
	
	ifstream COMPIN_FILE("compin");
	ofstream COMPOUT_FILE("compout");
	
	char charReadFromFile;

	// String that contains combination of chars
	string stringJoinValue = "";

	// Counter from 255 --> 
	// We already know that HashTable contains values from 0 to 255
	int counter = 255;
	while (true) {

		// Read char from file
		COMPIN_FILE.get(charReadFromFile);

		// End of line then exit from the endless loop
		if (COMPIN_FILE.eof())
		{
			break;
		}

		// Add char to dummy string
		stringJoinValue += charReadFromFile;

		string stringNotInHashTable;
		hashObject newObjectNotInHashTable(stringJoinValue);
		if (HASH_ARRAY.find(newObjectNotInHashTable) == DUMMY_OBJECT) {
			// Updating the code value
			newObjectNotInHashTable.code = ++counter;

			HASH_ARRAY.insert(newObjectNotInHashTable);

			// Adding the string into the HashTable
			stringNotInHashTable = stringJoinValue.substr(0, stringJoinValue.length() - 1);
			hashObject objectNotInHashTable(stringNotInHashTable);
			objectNotInHashTable = HASH_ARRAY.find(objectNotInHashTable);
			

			// Getting the last character of previous value
			stringJoinValue = string(1, stringJoinValue.back());

			// Writing to the file
			COMPOUT_FILE << objectNotInHashTable.code << " ";
		}
	}

	// Adding last HashedObject which is not in the HashTable
	hashObject lastHashedObject(stringJoinValue);
	lastHashedObject = HASH_ARRAY.find(stringJoinValue);

	// if it is not in the HasTable it will return dummy
	if (lastHashedObject != DUMMY_OBJECT) 
	{
		COMPOUT_FILE << lastHashedObject.code;
	}

	// Closing the files
	COMPIN_FILE.close();
	COMPOUT_FILE.close();
	return 0;
}