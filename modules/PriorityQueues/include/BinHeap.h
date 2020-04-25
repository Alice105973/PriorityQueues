#ifndef PRIORITYQUEUES_INCLUDE_BINHEAP_H_
#define PRIORITYQUEUES_INCLUDE_BINHEAP_H_

#include <vector>

using namespace std;

struct BinElem  {
  int weight;  // ��� �������
  int num;  // ����� �������
  BinElem* parent;  // �������� �������
  BinElem* child;  // ����� �������
  BinElem* sibling;  // ������ �����
  int degree = 0;  // ������� (����� �����)
  BinElem(int _num, int _weight) : num(_num), weight(_weight) { degree = 0; parent = NULL; child = NULL; sibling = NULL; };
  // �������� ������ �������� � �������� ������� � �����
  BinElem() { num = 0; weight = 0; degree = 0; parent = NULL; child = NULL; sibling = NULL; }
  // ����������� �� ���������
  void link(BinElem* A);  // ����������� ���� �������� ������ �������
  void relax(int v, int uv);  // ����������
  void decreaseKey(int newWeight);
};

class BinHeap {
  int n = 0;  // ���������� �������� � ����
  BinElem* head;  // ������ ������� � �������� ������
  void unite(BinHeap* A);  // ����������� ���� ���
  void mergeRLists(BinHeap* A);  // ������� �������� ������� ���� ��� �� ���������� ��������
public:
  BinHeap() { head = NULL; n = 0; };  // �������� ������ ����
  pair<int, int> extractMin();  // ������� �������
  void insert(BinElem* h);  // �������� �������
  int getN() { return n; }  // �������� ������
  friend vector<pair<int, int>> Dijkstra(const vector < vector<pair<int, int>>>& graph, BinHeap* q, vector<BinElem>* data);
};

#endif  // PRIORITYQUEUES_INCLUDE_BINHEAP_H_
