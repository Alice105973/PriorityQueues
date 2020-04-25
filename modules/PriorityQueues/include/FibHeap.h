#ifndef RPIORITYQUEUES_INCLUDE_FIBHEAP_H
#define RPIORITYQUEUES_INCLUDE_FIBHEAP_H

#include <vector>

using namespace std;

struct FibElem {
  int num;  // номер вершины
  int weight;  // вес вершины
  FibElem* parent = NULL;  // родитель
  FibElem* child = NULL;  // ребенок
  FibElem* left;  // левый сосед
  FibElem* right;  // правый сосед
  bool mark = false;  // потеряла ребенка после того,
  // как в последний раз сделалась ребенком
  int degree = 0;  // количество детей
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
  FibElem* min = NULL;  // минимальный элемент
  void mergeRLists(FibHeap* A);  // объединение корневых списков
  int n = 0;  // общее число всех вершин
public:
  int getN() { return n; }
  void insert(FibElem* x);  // вставка нового элемента
  void unite(FibHeap* A);  // объединение двух куч
  void consolidate();  // уплотнение
  pair<int, int> extractMin();  // извлечение минимума
  friend vector<pair<int, int>> Dijkstra(const vector < vector<pair<int, int>>>& graph, FibHeap* q, vector<FibElem>* data);
};

#endif // RPIORITYQUEUES_INCLUDE_FIBHEAP_H
