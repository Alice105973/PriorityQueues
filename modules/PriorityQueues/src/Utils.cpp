#include <ctime>
#include <random>
#include <climits>
#include "../include/Utils.h"

using namespace std;

vector<vector<pair<int, int>>> generateGraph(const size_t& v, const size_t& e) {
  if (v > e + 1) throw "��������� ����";
  if (e > v * (v - 1) / 2) throw "������ �����, ��� � ������ �����";
  vector<vector<pair<int, int>>> graph(v);  // ������ ���������
  if (e == v * (v - 1) / 2) {
    for (int i = 0; i < v; i++)  // full graph generation
      for (int j = i + 1; j < v; j++) {
        mt19937 gen(clock());  // random number generator
        int w = gen() % 10 + 1;  // edge weight
        graph[i].push_back(pair<int, int>(j, w));
        graph[j].push_back(pair<int, int>(i, w));
      }
    return graph;
  }
  vector<bool> A(v);  // ������ ����� ������ (0 - �� ������������)
  mt19937 gen(clock());  // ��������� ��������� �����
  size_t b, c;  // ������� ����������� ������
  size_t w;  // ��� ������ �����
  A[0] = true;  // ������ � 0 �������
  for (size_t i = 0; i < v - 1; i++) {  // ��� ������ ������� �� ������
    b = gen() % v;  // b - ��������� �������
    while (!A[b] && b > 0)  // ���� b ���������� � ������ ��������� � �������� �������
      b--;  // ��������� �� ������� �����
    c = gen() % v;  // c - ��������� �������
    while (A[c] && c < v) { // ���� � �������� � ������ ��������� � �������� �������
      c++;  // ��������� �� ������� ������
      if (c == v) {  // ���� �� ����� ������� ������������ ������� �� �������
        do {
          c--;  // ��������� �����
        } while (A[c]);  // �� ������������
      }
    }
    w = gen() % 10 + 1;  // ��������� ���� ������ �����
    A[c] = true;
    graph[b].push_back(pair<int, int>(c, w));
    graph[c].push_back(pair<int, int>(b, w));  // ������� ������� ������ � �������� �����
  }
  // ���� �������, �������� ��������� �����
  for (size_t i = 0; i < e - v + 1; i++) {
    // ������������� ��� ��������� ������������� �������
    b = gen() % v;
    c = gen() % v;
    while (graph[b].size() == v - 1)
      b = gen() % v;
    // ���� �� ������� ������� c, �� ������� � b, ������������ ����� c
    for (int j = 0; j < static_cast<int>(graph[b].size()); j++) {
      if (graph[b][j].first == static_cast<int>(c) || b == c || graph[c].size() == v - 1) {
        c = gen() % v;
        j = -1;
      }
    }
    w = gen() % 10 + 1;  // ������������� ����� ���
    graph[b].push_back(pair<int, int>(c, w));
    graph[c].push_back(pair<int, int>(b, w));  // ������� ������� ������ � �������� �����
  }
  return graph;
}

vector<int> Dijkstra(const vector<vector<pair<int, int>>>& g) {
  vector<bool> label(g.size(), 0);  // ������ ����� ������ (0 - ����������)
  vector<int> dist(g.size(), INT_MAX);  // ������ ���������� �� ������
  dist[0] = 0;
  int n = g.size();  // ���������� ������������ ������
  int argmin = 0;  // ����� ������� � ����������� ����������
  while (n != 0) {  // ���� ���� ������������ �������
    int min = INT_MAX;  // ����������� ����� ���� �� ������������
    for (size_t i = 0; i < dist.size(); i++)
      // ����� ������������ ������� � ����������� �����������
      if (dist[i] < min && label[i] == 0) {
        min = dist[i];
        argmin = i;
      }
    label[argmin] = true;
    n--;
    // ����������
    for (size_t j = 0; j < g[argmin].size(); j++) {
      if (dist[g[argmin][j].first] > dist[argmin] + g[argmin][j].second)
        dist[g[argmin][j].first] = dist[argmin] + g[argmin][j].second;
    }
  }
  return dist;
}