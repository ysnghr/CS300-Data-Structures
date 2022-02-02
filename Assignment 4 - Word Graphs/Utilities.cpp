#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <vector>
#include "Utilities.h"

using namespace std;

unordered_map<int, string> hash_reversed;

void prepareHashTable(ifstream& word_list, unordered_map<string, int>& hash, int& total) {
    string word;
    while (word_list >> word) {
        if (hash.find(word) == hash.end()) {
            hash[word] = total;
            hash_reversed[total++] = word;
        }
    }
    word_list.close();
}

void startFromSource(vector<bool>& visited_nodes, vector<int>& distance_list, int source, vector<int>& queue) {
    visited_nodes[source] = true;
    distance_list[source] = 0;
    queue.push_back(source);
}

void prepareGraph(int size, vector<bool>& visited_nodes, vector<int>& distance_list, vector<int>& pathway) {
    for (int i = 0; i < size; i++)
    {
        visited_nodes[i] = false;
        distance_list[i] = INT_MAX;
        pathway[i] = -1;
    }
}

bool BFS(vector<vector<int>>& adjecent_nested_list, int source, int dest, int size, vector<int>& pathway, vector<int>& distance_list) {
    vector<int> queue;
    vector<bool> visited_nodes(size);

    prepareGraph(size, visited_nodes, distance_list, pathway);

    startFromSource(visited_nodes, distance_list, source, queue);

    while (queue.size() != 0)
    {
        int n = queue[0];
        queue.erase(queue.begin());

        for (int e = 0; e < adjecent_nested_list[n].size(); e++)
        {
            if (visited_nodes[adjecent_nested_list[n][e]] == false)
            {
                distance_list[adjecent_nested_list[n][e]] = distance_list[n] + 1;
                pathway[adjecent_nested_list[n][e]] = n;
                visited_nodes[adjecent_nested_list[n][e]] = true;
                queue.push_back(adjecent_nested_list[n][e]);

                if (adjecent_nested_list[n][e] == dest) {
                    return true;
                }
            }
        }
    }
    return false;
}

void printTheDifference(string word1, string word2) {
    int word1_len = word1.length();
    int word2_len = word2.length();

    if (word1_len == word2_len) {
        for (int i = 0; i < word1_len; i++)
        {
            if (word1[i] != word2[i])
            {
                cout << " (change " << word1[i] << " at position " << i + 1 << " to " << word2[i] << ")" << endl;
                break;
            }
        }
    } else if (word1_len > word2_len) {
        for (int i = 0; i < word1_len; i++)
        {
            if (word1[i] != word2[i])
            {
                cout << " (delete " << word1[i] << " at position " << i + 1 << ")" << endl;
                break;
            }
        }
    }
    else {
        for (int i = 0; i < word2_len; i++)
        {
            if (word1[i] != word2[i]) {
                cout << " (insert " << word2[i] << " after position " << i << ")" << endl;
                break;
            }
        }
    }
}

void printShortWay(vector<vector<int>>& adjecent_nested_list, int source, int dest, int size) {
    vector<int> pathway(size);
    vector<int> dist(size);
    
    if (!BFS(adjecent_nested_list, source, dest, size, pathway, dist)){
        cout << "The source and destination are not connected!" << endl;
        return;
    }

    vector<int> path;

    int node_d = dest;
    path.push_back(node_d);
    while (pathway[node_d] != -1)
    {
        path.push_back(pathway[node_d]);
        node_d = pathway[node_d];
    }

    string last_string = hash_reversed[path[path.size() - 1]];
    cout << last_string << endl;
    for (int i = path.size() - 2; i >= 0; i--)
    {
        cout << hash_reversed[path[i]];
        printTheDifference(last_string, hash_reversed[path[i]]);
        last_string = hash_reversed[path[i]];
    }
}