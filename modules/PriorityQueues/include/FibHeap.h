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
};

class FibHeap {
  int n = 0;  // количество элементов в куче
  FibElem* min = NULL;  // минимальный элемент
  void link(FibElem* x, FibElem* y);  // объединение деревьев одной степени
  void consolidate();  // уплотнение
  void decreaseKey(FibElem* u, int newWeight);  // уменьшение ключа
  void cut(FibElem* x, FibElem* y);  // отрезать x от y
  void cascadingCut(FibElem* y);
  void relax(int v, FibElem* u, int uv);  // релаксация
public:
  bool isEmpty() { return (n == 0); }
  void insert(FibElem* x);  // вставка нового элемента
  pair<int, int> extractMin();  // извлечение минимума
  friend vector<int> Fib_Dijkstra(const vector < vector<pair<int, int>>>& graph);
};

vector<int> Fib_Dijkstra(const vector < vector<pair<int, int>>>& graph);

#endif // RPIORITYQUEUES_INCLUDE_FIBHEAP_H
