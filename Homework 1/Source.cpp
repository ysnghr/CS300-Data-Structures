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

string getConfigFilePath(const string &folderName) {
	return folderName + "/" + "configuration.txt";
}

int readFromConfig(ifstream& configReader) {
	int value;
	configReader >> value;
	return value;
}

int main() {
	string folderName = getFolderName();
	string configFilePath = getConfigFilePath(folderName);
	ifstream configReader(configFilePath);
	int numberOfQueues = readFromConfig(configReader), 
		numberOfProcesses = readFromConfig(configReader), 
		numberOfSlices = readFromConfig(configReader);
	
	queue<int> Queue(id);
}