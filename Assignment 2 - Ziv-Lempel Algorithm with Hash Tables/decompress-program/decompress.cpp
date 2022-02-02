#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() 
{
	int currentSize = 255;
	string DICTIONARY[4096] = { "" };

	// Adding all ascii values from 0 to 255
	for (int i = 0; i <= 255; i++)
	{
		DICTIONARY[i] = string(1, char(i));
	}
	
	// Openning the files
	ifstream COMPOUT_FILE("compout");
	ofstream DECOMPOUT_FILE("decompout");

	// integer that reads from file
	int codeFromFile;
	int counter = 0;
	string previous_value;
	while (COMPOUT_FILE >> codeFromFile) {

		if (counter == 0) {
			DECOMPOUT_FILE << DICTIONARY[codeFromFile];
			previous_value = DICTIONARY[codeFromFile];
		}
		else {
			// If the value is not in dictionary
			if (DICTIONARY[codeFromFile] == "") 
			{
				// Add new value to dictionary
				DICTIONARY[++currentSize] = previous_value + previous_value[0];
				
				// Uncompress the value
				DECOMPOUT_FILE << DICTIONARY[currentSize];
			}
			// If the value is in dictionary
			else 
			{
				// Decompress the value
				DECOMPOUT_FILE << DICTIONARY[codeFromFile];

				// Add new value to dictionary
				DICTIONARY[++currentSize] = previous_value + DICTIONARY[codeFromFile][0];
			}
		}
		// Getting the previous value from dictionary
		previous_value = DICTIONARY[codeFromFile];
		counter++;
	}

	// Closing the files
	DECOMPOUT_FILE.close();
	COMPOUT_FILE.close();
	return 0;
}