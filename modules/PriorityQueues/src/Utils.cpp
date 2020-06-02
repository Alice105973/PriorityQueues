#include <ctime>
#include <random>
#include "../include/Utils.h"

using namespace std;

vector<vector<pair<int, int>>> generateGraph(const int& v, const int& e) {
  if (v > e + 1) throw "несвязный граф";
  if (e > v * (v - 1) / 2) throw "больше ребер, чем в полном графе";
  vector<vector<pair<int, int>>> graph(v);  // списки смежности
  vector<bool> A(v);  // вектор меток вершин (0 - не использована)
  mt19937 gen(clock());  // генератор случайных чисел
  int b, c;  // индексы связываемых вершин
  int w;  // вес нового ребра
  A[0] = true;  // начнем с 0 вершины
  for (size_t i = 0; i < v - 1; i++) {  // для каждой вершины из списка
    b = gen() % v;  // b - случайная вершина
    while (!A[b] && b > 0)  // пока b непомечена и индекс находится в границах массива
      b--;  // двигаться по массиву влево
    c = gen() % v;  // c - случайная вершина
    while (A[c] && c < v) { // пока с помечена и индекс находится в границах массива
      c++;  // двигаться по массиву вправо
      if (c == v) {  // если до конца массива непомеченная вершина не найдена
        do {
          c--;  // двигаться влево
        } while (A[c]);  // до непомеченной
      }
    }
    w = gen() % 10 + 1;  // генерация веса нового ребра
    A[c] = true;
    graph[b].push_back(pair<int, int>(c, w));
    graph[c].push_back(pair<int, int>(b, w));  // связать вершины ребром с заданным весом
  }
  // граф связный, добавить остальные ребра
  for (int i = 0; i < e - v + 1; i++) {
    // сгенерировать две случайные несовпадающие вершины
    b = gen() % v;
    c = gen() % v;
    while (graph[b].size() == v - 1)
      b = gen() % v;
    // пока не найдена вершина c, не смежная с b, генерировать новую c
    for (int j = 0; j < graph[b].size(); j++) {
      if (graph[b][j].first == c || b == c || graph[c].size() == v - 1) {
        c = gen() % v;
        j = -1;
      }
    }
    w = gen() % 10 + 1;  // сгенерировать новый вес
    graph[b].push_back(pair<int, int>(c, w));
    graph[c].push_back(pair<int, int>(b, w));  // связать вершины ребром с заданным весом
  }
  return graph;
}

vector<int> Dijkstra(const vector<vector<pair<int, int>>>& g) {
  vector<bool> label(g.size(), 0);  // массив меток вершин (0 - непомечена)
  vector<int> dist(g.size(), INT_MAX);  // массив расстояний до вершин
  dist[0] = 0;
  int n = g.size();  // количество непомеченных вершин
  int argmin = 0;  // номер вершины с минимальной дистанцией
  while (n != 0) {  // пока есть непомеченные вершины
    int min = INT_MAX;  // минимальная длина пути из просчитанных
    for (int i = 0; i < dist.size(); i++)
      // поиск непомеченной вершины с минимальным расстоянием
      if (dist[i] < min && label[i] == 0) {
        min = dist[i];
        argmin = i;
      }
    label[argmin] = true;
    n--;
    // релаксация
    for (int j = 0; j < g[argmin].size(); j++) {
      if (dist[g[argmin][j].first] > dist[argmin] + g[argmin][j].second)
        dist[g[argmin][j].first] = dist[argmin] + g[argmin][j].second;
    }
  }
  return dist;
}