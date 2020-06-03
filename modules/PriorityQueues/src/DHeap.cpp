#include <algorithm>
#include <vector>
#include <cstddef>
#include "../include/DHeap.h"

using namespace std;

int DHeap::leftChild(int x) {
  int j = x * d + 1;
  if (j >= n) return -1;
  return j;
}

int DHeap::rightChild(int x) {
  int j = leftChild(x);
  if (j == -1) return -1;
  return min(j + d - 1, n - 1);
}

int DHeap::parent(int x) {
  if (x == 0) return -1;
  return (x - 1) / d;
}

int DHeap::minChild(int x) {
  if (leftChild(x) == -1) return -1;
  int min = data[leftChild(x)].second;  // минимальный ключ
  int xmin = leftChild(x);  // вершина с минимальным ключом
  for (int i = leftChild(x) + 1; i <= rightChild(x); i++) {  // для всех детей вершины
    if (data[i].second < min) {  // если ключ текущей вершины меньше минимума
      min = data[i].second;  // сохранить новый минимум
      xmin = i;  // запомнить вершину
    }
  }
  return xmin;
}

void DHeap::swap(int u, int v) {
  pair<int, int> temp = data[u];
  data[u] = data[v];
  data[v] = temp;
  std::swap(ptrs[data[u].first], ptrs[data[v].first]);
}

void DHeap::diving(int x) {
  int j1 = x;  // начиная с заданной вершины
  int j2 = minChild(j1);  // дочерняя вершина с минимальным ключом
  while ((j2 != -1) && (data[j1].second > data[j2].second)) {  // пока не достигнут лист и вес текущей вершины больше веса минимального потомка
    swap(j1, j2);  // поменять местами текущую вершину и ее минимального потомка
    j1 = j2;  // продолжить для того же узла
    j2 = minChild(j1);
  }
}

void DHeap::emersion(int x) {
  int j1 = x;  // начиная с заданной вершины
  int j2 = parent(j1);  // родительская вершина
  while ((j2 != -1) && (data[j1].second < data[j2].second)) {  // пока не достигнут корень и вес текущей вершины меньше веса родителя
    swap(j1, j2);  // поменять местами текущую вершину и ее родителя
    j1 = j2;  // продолжить для того же узла
    j2 = parent(j1);
  }
}

void DHeap::insert(int num, int weight) {
  n++;  // увеличить количество узлов
  pair<int, int> tmp(num, weight);  // создать пару с заданными параметрами
  data.push_back(tmp);  // добавить пару в конец кучи
  ptrs.push_back(num);
  emersion(n - 1);  // установить узел на место
}

pair<int, int> DHeap::extractMin() {
  pair<int, int> tmp = data[0];  // сохранить минимальный узел
  swap(0, n - 1);  // поменять местами минимальную и максимальную вершины
  n--;  // уменьшить количество узлов
  diving(0);  // восстановить свойство кучи
  return tmp;
}

void DHeap::relax(int vweight, int unum, int uvweight) {
  int loc = ptrs[unum];
  if (data[loc].second > vweight + uvweight) {
    data[loc].second = vweight + uvweight;
    emersion(loc);
  }
}

vector<int> D_Dijkstra(const vector < vector<pair<int, int>>>& graph) {
  DHeap q;
  q.insert(0, 0);
  for (size_t i = 1; i < graph.size(); i++) {
    q.insert(i, INT_MAX);
  }  // дополнительная память для кучи
  vector<int> S(graph.size());  // список вершин, для которых dist уже просчитана
  while (q.n) {
    pair<int, int> v = q.extractMin();  // текущая вершина
    S[v.first] = v.second;  // занести в список обработанных
    int amount = graph[v.first].size();  // количество смежных вершин
    for (int i = 0; i < amount; i++) {  // для всех смежных вершин
      q.relax(v.second, graph[v.first][i].first, graph[v.first][i].second);  // пересчитать веса
    }
  }
  return S;
}
