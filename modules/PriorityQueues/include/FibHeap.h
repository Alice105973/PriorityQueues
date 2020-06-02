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
};

class FibHeap {
  int n = 0;  // ���������� ��������� � ����
  FibElem* min = NULL;  // ����������� �������
  void link(FibElem* x, FibElem* y);  // ����������� �������� ����� �������
  void consolidate();  // ����������
  void decreaseKey(FibElem* u, int newWeight);  // ���������� �����
  void cut(FibElem* x, FibElem* y);  // �������� x �� y
  void cascadingCut(FibElem* y);
  void relax(int v, FibElem* u, int uv);  // ����������
public:
  bool isEmpty() { return (n == 0); }
  void insert(FibElem* x);  // ������� ������ ��������
  pair<int, int> extractMin();  // ���������� ��������
  friend vector<int> Fib_Dijkstra(const vector < vector<pair<int, int>>>& graph);
};

vector<int> Fib_Dijkstra(const vector < vector<pair<int, int>>>& graph);

#endif // RPIORITYQUEUES_INCLUDE_FIBHEAP_H
