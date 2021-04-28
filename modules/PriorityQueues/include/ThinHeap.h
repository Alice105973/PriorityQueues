#ifndef PRIORITYQUEUES_INCLUDE_THINHEAP_H_
#define PRIORITYQUEUES_INCLUDE_THINHEAP_H_

#include <vector>
#include <cstddef>

using namespace std;

struct ThinElem {
  int num;  // ����� �������
  int weight;  // ��� �������
  ThinElem* left = NULL;  // ����� ����/��������
  ThinElem* right = NULL;  // ������ ����
  ThinElem* child = NULL;  // ����� ���
  int rank = 0;  // ���� ����

  ThinElem() {
    num = 0;
    weight = 0;
  }
  ThinElem(int _num, int _weight) {
    num = _num;
    weight = _weight;
  }
  ThinElem* parent();  // ����� ��������
  bool br_violation();  // �������� �� �������� ���������
  bool p_violation();  // �������� �� ������������ ���������
  bool isThin();  // �������� �� ��������
  void link(ThinElem* A);  // ��������� �������
};

class ThinHeap {
  ThinElem* first = NULL;  // ������ ���� ��������� ������
  ThinElem* last = NULL;  // ��������� ���� ��������� ������
  int n = 0;  // ���������� �����
public:
  ThinHeap() {}
  int getN() { return n; }
  bool isEmpty() { if (first == NULL) return true; else return false; }
  void insert(ThinElem* x);  // ������� ������ ��������
  pair<int, int> extractMin();  // ������� �������
  void decreaseKey(ThinElem* x, int newWeight);  // ���������� �����
  void relax(int vweight, ThinElem* u, int uvweight);  // ����������

  friend vector<int> Thin_Dijkstra(const vector < vector<pair<int, int>>>& graph);
};

vector<int> Thin_Dijkstra(const vector < vector<pair<int, int>>>& graph);

#endif  // PRIORITYQUEUES_INCLUDE_THINHEAP_H_
