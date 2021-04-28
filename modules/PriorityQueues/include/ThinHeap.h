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
  ThinElem* parent();  // найти родителя
  bool br_violation();  // проверка на братское нарушение
  bool p_violation();  // проверка на родительское нарушение
  bool isThin();  // проверка на тонкость
  void link(ThinElem* A);  // соединить деревья
};

class ThinHeap {
  ThinElem* first = NULL;  // первый узел корневого списка
  ThinElem* last = NULL;  // последний узел корневого списка
  int n = 0;  // количество узлов
public:
  ThinHeap() {}
  int getN() { return n; }
  bool isEmpty() { if (first == NULL) return true; else return false; }
  void insert(ThinElem* x);  // вставка нового элемента
  pair<int, int> extractMin();  // извлечь минимум
  void decreaseKey(ThinElem* x, int newWeight);  // уменьшение ключа
  void relax(int vweight, ThinElem* u, int uvweight);  // релаксация

  friend vector<int> Thin_Dijkstra(const vector < vector<pair<int, int>>>& graph);
};

vector<int> Thin_Dijkstra(const vector < vector<pair<int, int>>>& graph);

#endif  // PRIORITYQUEUES_INCLUDE_THINHEAP_H_
