#ifndef RPIORITYQUEUES_INCLUDE_FIBHEAP_H
#define RPIORITYQUEUES_INCLUDE_FIBHEAP_H

#define NULL 0

using namespace std;

struct FibElem {
  int num;  // номер вершины
  int weight;  // вес вершины
  FibElem* parent = NULL;  // родитель
  FibElem* child = NULL;  // ребенок
  FibElem* left;  // левый сосед
  FibElem* right;  // правый сосед
  bool mark = 0;  // потеряла ребенка после того,
  // как в последний раз сделалась ребенком
  int degree = 0;  // количество детей
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
  FibElem* min = NULL;  // минимальный элемент
  int n = 0;  // общее число всех вершин
public:
  int getN() { return n; }
  void insert(FibElem* x);
};

#endif // RPIORITYQUEUES_INCLUDE_FIBHEAP_H
