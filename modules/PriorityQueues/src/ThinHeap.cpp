#include <vector>
#include <cmath>
#include <cstddef>
#include <climits>
#include <iostream>
#include "../include/ThinHeap.h"

vector<int> Thin_Dijkstra(const vector < vector<pair<int, int>>>& graph) {
  ThinHeap q;
  vector<ThinElem> data(graph.size());
  ThinElem a(0, 0);
  data[0] = a;
  q.insert(&data[0]);
  for (size_t i = 1; i < graph.size(); i++) {
    ThinElem c(i, INT_MAX);
    data[i] = c;
    q.insert(&data[i]);
  }  // дополнительная память для кучи
  vector<int> S(graph.size());  // список вершин, для которых dist уже просчитана
  while (!q.isEmpty()) {
    pair<int, int> v = q.extractMin();  // текущая вершина, (номер, вес)
    S[v.first] = v.second;  // занести в список обработанных
    int amount = graph[v.first].size();  // количество смежных вершин
    for (int i = 0; i < amount; i++) {  // для всех смежных вершин
      int unum = graph[v.first][i].first;  // номер i-той смежной с v вершины
      q.relax(v.second, &data[unum], graph[v.first][i].second);
    }
  }
  return S;
}

bool ThinElem::br_violation() {
  if (this == NULL) return false;
  if (left == NULL)  // с корнями не работает
    return false;
  if (right == NULL)  // если нет правого брата
    if (rank == 1)  // и ранг равен 1
      return true;
    else return false;
  if (rank == right->rank + 2)  // если ранг больше ранга правого брата на 2
    return true;
  return false;
}

bool ThinElem::p_violation() {
  if (this == NULL) return false;
  if (left == NULL)
    if (isThin()) { // узел - тонкий корень дерева
      return true;
    }
  if (child == NULL) {
    if (rank == 2)  //  нет детей и ранг = 2
    {
      return true; 
    }
    else {
      return false;
    }
  }
  if (rank == child->rank + 3) {  // ранг больше ранга сына на 3
    return true;
  }
  return false;
}

ThinElem* ThinElem::parent() {
  if (left == NULL)  // если узел - корень
    return NULL;  // родителя нет
  ThinElem* x = this;
  ThinElem* y = left;
  while (y->child != x) {
    x = y;
    y = x->left;
  }
  return y;
}

void ThinElem::link(ThinElem* A) {
  A->left = this;  // назначить текущую вершину родителем А
  A->right = child;  // назначить ребенка текущей вершины соседом А
  if (child != NULL)
    child->left = A;
  child = A;  // назначить А ребенком текущей вершины
  rank++;  // увеличить степень текущей вершины
}

bool ThinElem::isThin() {
  if (rank == 0)  // узел ранга 0 не тонкий
    return false;
  if (rank == 1)  // если ранг = 1 и детей нет - узел тонкий
    return (child == NULL);
  else  // если ранг на 2 больше ранга старшего сына, узел тонкий
    return (child->rank + 1) != rank;
}

void ThinHeap::insert(ThinElem* x) {
  n++;  // количество элементов в куче увеличивается
  x->left = NULL;  // очистить братские связи
  x->right = NULL;
  if (x->child == NULL)
    x->rank = 0;
  else x->rank = x->child->rank + 1;

  if (first == NULL) {  // если куча пуста
    first = x;  // добавить x
    last = x;  // как единственный элемент
  }
  else {
    if (x->weight < first->weight) {  // если x минимальный
      x->right = first;  // поставить его в начало корневого списка
      first = x;  // корневой список односвязный
    }
    else {
      last->right = x;  // иначе
      last = x;  // вставить в конец корневого списка
    }
  }
}

pair<int, int> ThinHeap::extractMin() {
  if (n == 1) {  // если в куче один элемент
    n--;  // очистить кучу
    ThinElem* tmp = first;
    first = NULL;
    last = NULL;
    return pair<int, int>(tmp->num, tmp->weight);  // вернуть единственный элемент
  }

  ThinElem* tmp = first;
  n--;
  ThinElem* nextx = NULL;
  int max = -1;
  first = first->right;  // извлечь первый элемент из корневого списка
  if (first == NULL)  // если куча пуста
    last = NULL;

  ThinElem* x = tmp->child;  // перейти к детям
  while (x != NULL) {  // пока не достигнут конец списка
    if (x->isThin())  // если узел тонкий
      x->rank--;  // понизить ранг
    ThinElem* nextx = x->right;
    insert(x);  // добавить в корневой список
    n--;
    x = nextx;  // перейти к следующему
  }

  x = first;  // начать с корня
  vector<ThinElem*> A(static_cast<size_t>(ceil(log2(n)) + 3), NULL);  // вспомогательный массив
  // в ячейке с номером i находится указатель на корень степени i
  while (x != NULL) {  // пока не достигнут конец списка
    nextx = x->right;
    while (A[x->rank] != NULL) {  // пока есть узлы того же ранга
      if (A[x->rank]->weight < x->weight)  // минимальный элемент - x
        swap(A[x->rank], x);
      x->link(A[x->rank]);  // соединить деревья
      A[x->rank - 1] = NULL;  // очистить ячейку
    }
    A[x->rank] = x;  // записать полученное дерево
    if (x->rank > max)  // обновить максимум
      max = x->rank;
    x = nextx;
  }
  // собрать все узлы обратно в кучу
  first = NULL;  // очистить кучу
  last = NULL;
  for (int i = 0; i <= max; i++)
    if (A[i] != NULL) {
      insert(A[i]);  // вставить в корневой список
      n--;  // поддержка правильности n
    }
  tmp->left = NULL;
  tmp->right = NULL;
  tmp->child = NULL;
  return pair<int, int>(tmp->num, tmp->weight);
}

void ThinHeap::decreaseKey(ThinElem* x, int newWeight) {
  if (newWeight > x->weight) return;
  x->weight = newWeight;  // обновить вес
  ThinElem* l = x->left;

  if (x == first)  // с первым (минимальным) элементом 
    return;  // ничего не делать

  if (l == NULL) {  // если x - корень, но не первый
    ThinElem* z = first;
    while (z->right != x) {
      z = z->right;  // найти левого соседа
    }
    if (x == last)  // если x - последний
      last = z;  // назначить последним z
    z->right = x->right;  // удалить x из корневого списка
    insert(x);  // вставить на необходимое место (обновить минимум)
    n--;  // поддержка n
    return;  // закончить
  }

  if (x->weight >= x->parent()->weight)  // если кучеобразность не нарушена
    return;  // закончить

  if (l->child == x)  // если x - первый сын
    l->child = x->right;  // удалить x из списка детей
  else  // если x - не первый сын
    x->left->right = x->right;
  if (x->right != NULL)
    x->right->left = x->left;
  insert(x);  // вставить x в корневой список
  n--; // поддержка n
  

  while (l->br_violation() || l->p_violation())
  {  // пока есть нарушения
    // братские нарушения
    while (l->br_violation() && l != NULL) {
      if (l->isThin() == false) {  // если узел не тонкий
        ThinElem* ch = l->child;  // переместить поддерево с корнем в сыне
        if (ch != NULL) {
          l->child = ch->right;  //  на место пропущенного
          if (l->child != NULL)
            l->child->left = l;
          if (l->right != NULL)
            l->right->left = ch;
          ch->right = l->right;
          l->right = ch;
          ch->left = l;
        }
      }
      else
        l->rank--;
      l = l->left;
    }

    // родительские нарушения
    while (l->p_violation() && l != NULL) {
      if (l->left == NULL) {  // если l - корень
        if (l->child == NULL)  // ранг на 1 больше ранга сына
          l->rank = 0;
        else
          l->rank = l->child->rank + 1;
        l = NULL;
        break;
      }
      ThinElem* le = l->left;  // переместить поддерево с корнем в y в корневой список
      if (le->child == l)
        le->child = l->right;
      else
        le->right = l->right;
      if (l->right != NULL)
        l->right->left = le;
      insert(l);
      n--;
      l = le;
    }
  }
}

void ThinHeap::relax(int vweight, ThinElem* u, int uvweight) {
  if (vweight + uvweight < u->weight) {  // если найден более короткий путь
    decreaseKey(u, vweight + uvweight);  // обновить длину пути
  }
}
