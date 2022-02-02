#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <string>

using namespace std;

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
	for (int i = 0; i < queues.size(); i++)	{
		if (!queues[i].empty()) {
			return false;
		}
	}
	return true;
}

string getQueueName(int queueSize, int id) {
	return "Q" + to_string(queueSize - id);
}

void getAllToTopMostQueue(vector<queue<Process>> &allQueues, ofstream &outputTXT) {
	int iterator_new = 1;
	while (iterator_new != allQueues.size()) {
		while (!allQueues[iterator_new].empty()) {
			allQueues[0].push(allQueues[iterator_new].front());
			outputTXT << "B, " << allQueues[0].back().processName << ", " << getQueueName(allQueues.size(), 0) << "\n";
			allQueues[iterator_new].pop();
		}
		iterator_new++;
	}

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
		queue<Process> queueProcess;
		allQueues.push_back(queueProcess);
	}

	for (int i = 1; i < numberOfProcesses + 1; i++)	{
		string processFileName = "p" + to_string(i) + ".txt", processFilePath = getFilePath(folderName, processFileName);
		Process newProcess;
		readProcessFile(processFilePath, newProcess);
		newProcess.processName = "PC" + to_string(i);
		allQueues[0].push(newProcess);
	}

	int iterator_all = 0, time_slicer = 0, count_processors = numberOfProcesses;
	ofstream outputTXT;
	outputTXT.open(getFilePath(folderName, "output.txt"));
	while (iterator_all != allQueues.size()) {
		while (!allQueues[iterator_all].empty()) {
			if (time_slicer == numberOfSlices)	{
				getAllToTopMostQueue(allQueues, outputTXT);
				iterator_all = -1; time_slicer = 0;
				break;
			}
			Process *element = &allQueues[iterator_all].front();
			if (element->stages.front() == '1') {
				element->stages.pop();
				time_slicer++;

				if (element->stages.front() == '-') {
					count_processors--;
					outputTXT << "E, " << element->processName << ", " << "QX";
					if (count_processors != 0) {
						outputTXT << "\n";
					}
					allQueues[iterator_all].pop();
				}
				else {
					if (iterator_all + 1 != allQueues.size())
					{
						allQueues[iterator_all + 1].push(*element);
						outputTXT << "1, " << element->processName << ", " << getQueueName(allQueues.size(), iterator_all + 1) << "\n";
						allQueues[iterator_all].pop();
					}
					else {
						outputTXT << "1, " << element->processName << ", " << getQueueName(allQueues.size(), iterator_all) << "\n";
					}
				}
			}
			else if (element->stages.front() == '0') {
				element->stages.pop();
				time_slicer++;
				if (element->stages.front() == '-') {
					count_processors--;
					outputTXT << "E, " << element->processName << ", " << "QX";
					if (count_processors != 0) {
						outputTXT << "\n";
					}
					allQueues[iterator_all].pop();
				}
				else {
					allQueues[iterator_all].push(*element);
					outputTXT << "0, " << element->processName << ", " << getQueueName(allQueues.size(), iterator_all) << "\n";
					allQueues[iterator_all].pop();
				}
			}
		}
		iterator_all++;
	}
	outputTXT.close();	
}