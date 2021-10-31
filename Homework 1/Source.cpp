#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

#define Queue(x) queue_ ## x

struct Process {
	vector<char> stages;
	int index_current;
	bool is_finished;

	Process() : is_finished(false), index_current(0)
	{}
};

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
	queue<int> Queue(id);
}