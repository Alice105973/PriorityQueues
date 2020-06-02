#include <ctime>
#include <random>
#include "../include/Utils.h"

using namespace std;

vector<vector<pair<int, int>>> generateGraph(const int& v, const int& e) {
  if (v > e + 1) throw "��������� ����";
  if (e > v * (v - 1) / 2) throw "������ �����, ��� � ������ �����";
  vector<vector<pair<int, int>>> graph(v);  // ������ ���������
  vector<bool> A(v);  // ������ ����� ������ (0 - �� ������������)
  mt19937 gen(clock());  // ��������� ��������� �����
  int b, c;  // ������� ����������� ������
  int w;  // ��� ������ �����
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
  for (int i = 0; i < e - v + 1; i++) {
    // ������������� ��� ��������� ������������� �������
    b = gen() % v;
    c = gen() % v;
    while (graph[b].size() == v - 1)
      b = gen() % v;
    // ���� �� ������� ������� c, �� ������� � b, ������������ ����� c
    for (int j = 0; j < graph[b].size(); j++) {
      if (graph[b][j].first == c || b == c || graph[c].size() == v - 1) {
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
    for (int i = 0; i < dist.size(); i++)
      // ����� ������������ ������� � ����������� �����������
      if (dist[i] < min && label[i] == 0) {
        min = dist[i];
        argmin = i;
      }
    label[argmin] = true;
    n--;
    // ����������
    for (int j = 0; j < g[argmin].size(); j++) {
      if (dist[g[argmin][j].first] > dist[argmin] + g[argmin][j].second)
        dist[g[argmin][j].first] = dist[argmin] + g[argmin][j].second;
    }
  }
  return dist;
}