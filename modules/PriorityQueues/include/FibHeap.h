#ifndef RPIORITYQUEUES_INCLUDE_FIBHEAP_H
#define RPIORITYQUEUES_INCLUDE_FIBHEAP_H

#include <vector>

using namespace std;

struct FibElem {
  int num;  // ����� �������
  int weight;  // ��� �������
  FibElem* parent = NULL;  // ��������
  FibElem* child = NULL;  // �������
  FibElem* left;  // ����� �����
  FibElem* right;  // ������ �����
  bool mark = false;  // �������� ������� ����� ����,
  // ��� � ��������� ��� ��������� ��������
  int degree = 0;  // ���������� �����
  FibElem() {
    num = 0;
    weight = 0;
    left = this;
    right = this;
    parent = NULL;
    child = NULL;
  }
  FibElem(int _num, int _weight) {
    num = _num;
    weight = _weight;
    left = this;
    right = this;
    parent = NULL;
    child = NULL;
  }
  void link(FibElem* x);
};

class FibHeap {
  FibElem* min = NULL;  // ����������� �������
  void mergeRLists(FibHeap* A);  // ����������� �������� �������
  int n = 0;  // ����� ����� ���� ������
public:
  int getN() { return n; }
  void insert(FibElem* x);  // ������� ������ ��������
  void unite(FibHeap* A);  // ����������� ���� ���
  void consolidate();  // ����������
  pair<int, int> extractMin();  // ���������� ��������
  friend vector<pair<int, int>> Dijkstra(const vector < vector<pair<int, int>>>& graph, FibHeap* q, vector<FibElem>* data);
};

#endif // RPIORITYQUEUES_INCLUDE_FIBHEAP_H
