#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <unordered_map>
#include <vector>

bool BFS(std::vector<std::vector<int>>& adj, int source, int dest, int size, std::vector<int>& pred, std::vector<int>& distanceList);
void prepareHashTable(std::ifstream& word_list, std::unordered_map<std::string, int>& hash, int& total);
void printShortWay(std::vector<std::vector<int>>& adj, int source, int dest, int size);


#endif
