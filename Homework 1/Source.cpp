#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <string>

using namespace std;

//#define Queue(x) queue_ ## x

struct Process {
	queue<char> stages;
	int index_current;
	bool is_finished;
	string processName;

	Process() : is_finished(false), index_current(0), stages()
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

string getFilePath(const string &folderName, string configFile) {
	return folderName + "/" + configFile;
}

int readFromConfig(ifstream& configReader) {
	int value;
	configReader >> value;
	return value;
}

void readProcessFile(const string &processName, Process& newProcess) {
	ifstream processFileReader(processName);
	char processChar;
	while (processFileReader >> processChar) {
		newProcess.stages.push(processChar);
	}
	processFileReader.close();
}

bool isEmptyVector(const vector<queue<Process>>& queues) {
	for (int i = 0; i < queues.size(); i++)
	{
		if (!queues[i].empty()) {
			return false;
		}
	}
	return true;
}

int main() {
	string folderName = getFolderName();
	string configFilePath = getFilePath(folderName, "configuration.txt");
	ifstream configReader(configFilePath);
	int numberOfQueues = readFromConfig(configReader), 
		numberOfProcesses = readFromConfig(configReader), 
		numberOfSlices = readFromConfig(configReader);
	configReader.close();

	vector<queue<Process>> allQueues;

	for (int i = 0; i < numberOfQueues; i++) {
		// queue<Process> Queue(id);
		queue<Process> queueProcess;
		allQueues.push_back(queueProcess);
	}

	for (int i = 1; i < numberOfProcesses + 1; i++)
	{
		string processFileName = "p" + to_string(i) + ".txt", processFilePath = getFilePath(folderName, processFileName);
		Process newProcess;
		readProcessFile(processFilePath, newProcess);
		newProcess.processName = processFileName;
		allQueues[0].push(newProcess);
	}

	int iterator_all = 0;
	while (iterator_all != allQueues.size()) {
		while (!allQueues[iterator_all].empty()) {
			Process *element = &allQueues[iterator_all].front();
			if (element->stages.front() == '1') {
				element->stages.pop();
				allQueues[iterator_all + 1].push(*element);
				allQueues[iterator_all].pop();
			}
			else if (element->stages.front() == '0') {
				allQueues[iterator_all].push(*element);
				allQueues[iterator_all].pop();
			}
			else {

			}
		}
		iterator_all++;
	}


	//	while (!allQueues[0].empty()) {
	//		cout << allQueues[0].front().processName << endl;
	//		while (!allQueues[0].front().stages.empty()) {
	//			cout << allQueues[0].front().stages.front() << endl;
	//			allQueues[0].front().stages.pop();
	//		}
	//		cout << " --------" << endl;
	//		allQueues[0].pop();
	//	}

	
	
}