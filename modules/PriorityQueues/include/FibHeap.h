#ifndef RPIORITYQUEUES_INCLUDE_FIBHEAP_H
#define RPIORITYQUEUES_INCLUDE_FIBHEAP_H

#define NULL 0

using namespace std;

struct FibElem {
  int num;  // ����� �������
  int weight;  // ��� �������
  FibElem* parent = NULL;  // ��������
  FibElem* child = NULL;  // �������
  FibElem* left;  // ����� �����
  FibElem* right;  // ������ �����
  bool mark = 0;  // �������� ������� ����� ����,
  // ��� � ��������� ��� ��������� ��������
  int degree = 0;  // ���������� �����
  FibElem() {
    num = 0;
    weight = 0;
    left = this;
    right = this;
  }
  FibElem(int _num, int _weight) {
    num = _num;
    weight = _weight;
    left = this;
    right = this;
  }
};

class FibHeap {
  FibElem* min = NULL;  // ����������� �������
  int n = 0;  // ����� ����� ���� ������
public:
  int getN() { return n; }
  void insert(FibElem* x);
};

#endif // RPIORITYQUEUES_INCLUDE_FIBHEAP_H
