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
  void link(FibElem* x);  // объединение деревьев одной степени
};

class FibHeap {
  int n = 0;  // общее число всех вершин
  FibElem* min = NULL;  // минимальный элемент
  void relax(int v, FibElem* u, int uv);  // релаксация
  void decreaseKey(FibElem* u, int newWeight);
  void mergeRLists(FibHeap* A);  // объединение корневых списков
  void cut(FibElem* x, FibElem* y);  // отрезать x от y
  void cascadingCut(FibElem* y);
  void unite(FibHeap* A);  // объединение двух куч
  void consolidate();  // уплотнение
public:
  int getN() { return n; }
  void insert(FibElem* x);  // вставка нового элемента
  pair<int, int> extractMin();  // извлечение минимума
  friend vector<pair<int, int>> Dijkstra(const vector < vector<pair<int, int>>>& graph, FibHeap* q, vector<FibElem>* data);
};

#endif // RPIORITYQUEUES_INCLUDE_FIBHEAP_H
