#ifndef PRIORITYQUEUES_INCLUDE_THINHEAP_H_
#define PRIORITYQUEUES_INCLUDE_THINHEAP_H_

#include <vector>
#include <cstddef>

using namespace std;

struct ThinElem {
  int num;  // номер вершины
  int weight;  // вес вершины
  ThinElem* left = NULL;  // левый брат/родитель
  ThinElem* right = NULL;  // правый брат
  ThinElem* child = NULL;  // левый сын
  int rank = 0;  // ранг узла

  ThinElem() {
    num = 0;
    weight = 0;
  }
  ThinElem(int _num, int _weight) {
    num = _num;
    weight = _weight;
  }
  bool isThin();  // проверка на тонкость
  void link(ThinElem* A);
  void relax(int v, int uv);  // релаксация
  void decreaseKey(int newWeight);  // уменишение ключа
};

class ThinHeap {
  ThinElem* first = NULL;  // первый узел корневого списка
  ThinElem* last = NULL;  // последний узел корневого списка
  int n;  // количество узлов
public:
  ThinHeap() {}
  void insert(ThinElem* x);  // вставка нового элемента
  pair<int, int> extractMin();  // извлечь минимум

  friend vector<int> Thin_Dijkstra(const vector < vector<pair<int, int>>>& graph);
};

vector<int> Thin_Dijkstra(const vector < vector<pair<int, int>>>& graph);

#endif  // PRIORITYQUEUES_INCLUDE_THINHEAP_H_
