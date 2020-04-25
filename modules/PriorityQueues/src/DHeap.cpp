#include <algorithm>
#include <vector>
#include "../include/DHeap.h"

using namespace std;

int DHeap::leftChild(int x) {
  int j = x * d + 1;
  if (j >= n) return -1;
  return j;
}

int DHeap::rightChild(int x) {
  int j = leftChild(x);
  if (j == -1) return -1;
  return min(j + d - 1, n - 1);
}

int DHeap::parent(int x) {
  if (x == 0) return -1;
  return (x - 1) % d;
}

int DHeap::minChild(int x) {
  if (leftChild(x) == -1) return -1;
  int min = data[leftChild(x)].second;  // ����������� ����
  int xmin = leftChild(x);  // ������� � ����������� ������
  for (int i = leftChild(x) + 1; i < rightChild(x); i++) {  // ��� ���� ����� �������
    if (data[i].second < min) {  // ���� ���� ������� ������� ������ ��������
      min = data[i].second;  // ��������� ����� �������
      xmin = i;  // ��������� �������
    }
  }
  return xmin;
}

void DHeap::swap(int u, int v) {
  pair<int, int> temp = data[u];
  data[u] = data[v];
  data[v] = temp;
}

void DHeap::diving(int x) {
  int j1 = x;  // ������� � �������� �������
  int j2 = minChild(j1);  // �������� ������� � ����������� ������
  while ((j2 != -1) && (data[j1].second > data[j2].second)) {  // ���� �� ��������� ���� � ��� ������� ������� ������ ���� ������������ �������
    swap(j1, j2);  // �������� ������� ������� ������� � �� ������������ �������
    j1 = j2;  // ���������� ��� ���� �� ����
    j2 = minChild(j1);
  }
}

void DHeap::emersion(int x) {
  int j1 = x;  // ������� � �������� �������
  int j2 = parent(j1);  // ������������ �������
  while ((j2 != -1) && (data[j1].second < data[j2].second)) {  // ���� �� ��������� ������ � ��� ������� ������� ������ ���� ��������
    swap(j1, j2);  // �������� ������� ������� ������� � �� ��������
    j1 = j2;  // ���������� ��� ���� �� ����
    j2 = parent(j1);
  }
}

void DHeap::insert(int num, int weight) {
  n++;  // ��������� ���������� �����
  pair<int, int> tmp(num, weight);  // ������� ���� � ��������� �����������
  data.push_back(tmp);  // �������� ���� � ����� ����
  emersion(n - 1);  // ���������� ���� �� �����
}

pair<int, int> DHeap::extractMin() {
  swap(0, n - 1);  // �������� ������� ����������� � ������������ �������
  n--;  // ��������� ���������� �����
  diving(0);  // ������������ �������� ����
  pair<int, int> tmp = data[n];  // ��������� ����������� ����
  data.pop_back();  // ������� ����������� ���� �� ����
  return tmp;
}

void DHeap::relax(int vweight, int unum, int uvweight) {
  for (int i = 0; i < n; i++) {  // ����� �� ���� ��������� �������
    if (data[i].first == unum) {  // ���� ������� ������� � ������� u
      if (data[i].second > vweight + uvweight) {  // ���� � ��� ����� ��������� ����� �������� �����
        data[i].second = vweight + uvweight;  // ��������� ���
        emersion(i);  // ������������ �������� ����
        return;
      }
    }
  }
}

vector<pair<int, int>> Dijkstra(const vector < vector<pair<int, int>>>& graph, DHeap q) {
  vector<pair<int, int>> S;  // ������ ������, ��� ������� dist ��� ����������
  while (q.n) {
    pair<int, int> v = q.extractMin();  // ������� �������
    S.push_back(v);  // ������� � ������ ������������
    int amount = graph[v.first].size();  // ���������� ������� ������
    for (int i = 0; i < amount; i++) {  // ��� ���� ������� ������
      q.relax(v.second, graph[v.first][i].first, graph[v.first][i].second);  // ����������� ����
    }
  }
  return S;
}
