#ifndef PRIORITYQUEUES_INCLUDE_DHEAP_H_
#define PRIORITYQUEUES_INCLUDE_DHEAP_H_

#include <vector>
#include <algorithm>

using namespace std;

class DHeap {
protected:
  int n = 0;  // ���������� ���������
  vector<pair<int, int>> data;  // ������ ��� (u, dist[u]) � ������� ����������� dist[u]
  int d;  // ���������� ����� � ������ �������
  int minChild(int x);  // �������� ������� � ����������� ������
  int leftChild(int x);  // ����� �������� �������
  int rightChild(int x);  // ������ �������� �������
  void swap(int u, int v);  // �������� ������� �������
  void diving(int x);  // ���������� �������
  void emersion(int x);  // �������� �������
  pair<int, int> extractMin();  // ���������� ��������
  void relax(int v, int u, int uv);
public:
  int parent(int x);  // ������������ �������
  pair<int, int> operator[](int i) { return data[i]; }
  DHeap(int _d = 3) : d(_d) {} // �����������
  void insert(int num, int weight);  // ������� ������� � �������� ������� � �����
  friend vector<int> Dijkstra(const vector < vector<pair<int, int>>>& graph, DHeap q);
};

#endif  // PRIORITY_QUEUES_INCLUDE_DHEAP_H_
