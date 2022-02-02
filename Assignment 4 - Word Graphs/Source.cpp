#include <iostream>
#include <string>
#include <fstream>
#include "Utilities.h"
#include <unordered_map>

using namespace std;

int main() {
	int total = 0;
	ifstream word_list("words.txt");
	unordered_map<string, int> hash;
	if (word_list.fail()) {
		cout << "The words.txt file is not found!" << endl;
		return 1;
	}

	char numbers[28];
	int idx = 0;
	for (int i = 97; i <= 122; i++) {
		numbers[idx] = char(i);
		idx++;
	}
	numbers[26] = '-';
	numbers[27] = '\'';

	prepareHashTable(word_list, hash, total);
	vector<vector<int>> adj(total);
	for (auto item : hash) {
		string text = item.first;
		for (int i = 1; i < text.length() + 1; i++) {
			string abcd = text.substr(0, i - 1) + text.substr(i);
			if (hash.find(abcd) != hash.end()) {
				adj[item.second].push_back(hash[abcd]);
			}
		}

		for (int i = 0; i < text.length() + 2; i++) {

			for (int f = 0; f < sizeof(numbers) / sizeof(numbers[0]); f++) {
				for (int i = 0; i < text.length() + 1; i++) {

					string newOne = text.substr(0, i) + numbers[f] + text.substr(i, text.length());
					if (hash.find(newOne) != hash.end())
					{
						adj[item.second].push_back(hash[newOne]);
					}
				}

				for (int i = 1; i <= text.length(); i++) {
					string newOne = text.substr(0, i - 1) + numbers[f] + text.substr(i, text.length() - 1);
					if (hash.find(newOne) != hash.end())
					{
						adj[item.second].push_back(hash[newOne]);
					}
				}

			}
		}
	}
	cout << "Enter two strings: ";
	string first_word, second_word;
	cin >> first_word >> second_word;

	while (first_word[0] != '*') {
		if (hash.find(first_word) != hash.end() && hash.find(second_word) != hash.end()) {
			printShortWay(adj, hash[first_word], hash[second_word], total);
		}
		else {
			cout << "The first word or second word is not in words.txt." << endl;
		}
		cout << "Enter two strings: ";
		cin >> first_word >> second_word;
	}
	return  0;
}