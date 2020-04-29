#ifndef PRIORITYQUEUES_INCLUDE_DHEAP_H_
#define PRIORITYQUEUES_INCLUDE_DHEAP_H_

#include <vector>
#include <algorithm>

using namespace std;

class DHeap {
protected:
  int n = 0;  // количество элементов
  vector<pair<int, int>> data;  // массив пар (u, dist[u]) в порядке возрастания dist[u]
  int d;  // количество детей у каждой вершины
  int minChild(int x);  // дочерняя вершина с минимальным ключом
  int leftChild(int x);  // левая дочерняя вершина
  int rightChild(int x);  // правая дочерняя вершина
  void swap(int u, int v);  // поменять вершины местами
  void diving(int x);  // погружение вершины
  void emersion(int x);  // всплытие вершины
  pair<int, int> extractMin();  // извлечение минимума
  void relax(int v, int u, int uv);
public:
  int parent(int x);  // родительская вершина
  pair<int, int> operator[](int i) { return data[i]; }
  DHeap(int _d = 3) : d(_d) {} // конструктор
  void insert(int num, int weight);  // вставка вершины с заданным номером и весом
  friend vector<int> Dijkstra(const vector < vector<pair<int, int>>>& graph, DHeap q);
};

#endif  // PRIORITY_QUEUES_INCLUDE_DHEAP_H_
