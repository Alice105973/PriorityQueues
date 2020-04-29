#ifndef RPIORITYQUEUES_INCLUDE_UTILS_H
#define RPIORITYQUEUES_INCLUDE_UTILS_H

#include <vector>

using namespace std;

vector<vector<pair<int, int>>> generateGraph(const int& v, const int& e);
vector<int> Dijkstra(const vector<vector<pair<int, int>>>& g);

#endif  // RPIORITYQUEUES_INCLUDE_UTILS_H