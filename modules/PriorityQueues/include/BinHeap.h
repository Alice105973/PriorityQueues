#ifndef PRIORITYQUEUES_INCLUDE_BINHEAP_H_
#define PRIORITYQUEUES_INCLUDE_BINHEAP_H_

#include <vector>
#include <cstddef>

using namespace std;

struct BinElem  {
  int num;  // номер вершины
  int weight;  // вес вершины
  BinElem* parent;  // родитель вершины
  BinElem* child;  // левый ребенок
  BinElem* sibling;  // правый сосед
  int degree = 0;  // степень (число детей)
  BinElem(int _num, int _weight) : num(_num), weight(_weight) { degree = 0; parent = NULL; child = NULL; sibling = NULL; };
  // создание нового элемента с заданным номером и весом
  BinElem() { num = 0; weight = 0; degree = 0; parent = NULL; child = NULL; sibling = NULL; }
  // конструктор по умолчанию
  void link(BinElem* A);  // объединение двух деревьев одного размера
  void relax(int v, int uv);  // релаксация
  void decreaseKey(int newWeight);
};

class BinHeap {
  int n = 0;  // количество деревьев в куче
  BinElem* head;  // первая вершина в корневом списке
  void unite(BinHeap* A);  // объединение двух куч
  void mergeRLists(BinHeap* A);  // слияние корневых списков двух куч по неубыванию степеней
public:
  BinHeap() { head = NULL; n = 0; };  // создание пустой кучи
  pair<int, int> extractMin();  // извлечь минимум
  void insert(BinElem* h);  // вставить элемент
  int getN() { return n; }  // получить размер
  friend vector<int> Bin_Dijkstra(const vector < vector<pair<int, int>>>& graph);
};

vector<int> Bin_Dijkstra(const vector < vector<pair<int, int>>>& graph);

#endif  // PRIORITYQUEUES_INCLUDE_BINHEAP_H_
