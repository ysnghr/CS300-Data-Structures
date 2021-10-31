#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

string getFolderName() {
	cout << "Please enter the process folder name: ";
	string folderName, outputName = "output.txt";
	cin >> folderName;

	cout << "When all processes are completed, you can find execution sequence in \"" <<
		folderName << "/" << outputName << "\"." << endl << endl;
	return folderName;
}



int main() {
	string folderName = getFolderName();
}