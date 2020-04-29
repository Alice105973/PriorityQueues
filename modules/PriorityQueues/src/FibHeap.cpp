#include <vector>
#include <cmath>
#include <iostream>
#include "../include/FibHeap.h"

using namespace std;

vector<int> Fib_Dijkstra(const vector < vector<pair<int, int>>>& graph) {
  FibHeap q;
  vector<FibElem> data(graph.size());
  FibElem a(0, 0);
  data[0] = a;
  q.insert(&data[0]);
  for (size_t i = 1; i < graph.size(); i++) {
    FibElem c(i, INT_MAX);
    data[i] = c;
    q.insert(&data[i]);
  }  // дополнительная память для кучи
  vector<int> S(graph.size());  // список вершин, для которых dist уже просчитана
  FibElem* u = NULL;  // вершина, для которой проводится релаксация
  while (q.getN()) {
    pair<int, int> v = q.extractMin();  // текущая вершина, (номер, вес)
    S[v.first] = v.second;  // занести в список обработанных
    int amount = graph[v.first].size();  // количество смежных вершин
    for (int i = 0; i < amount; i++) {  // для всех смежных вершин
      int unum = graph[v.first][i].first;  // номер i-той смежной с v вершины
      u = &data[0];  // начинаем поиск с первой вершины
      int j = 0;
      while (u->num != unum) {  // пока не найдена вершина с нужным номером
        j++;
        u = &data[j];  // перейти к следующей вершине
      }
      q.relax(v.second, u, graph[v.first][i].second);
    }
  }
  return S;
}


void FibHeap::relax(int vweight, FibElem* u, int uvweight) {
  if (vweight + uvweight < u->weight) {  // если найден более короткий путь
    decreaseKey(u, vweight + uvweight);  // обновить длину пути
  }
}

void FibHeap::decreaseKey(FibElem* u, int newWeight) {
  u->weight = newWeight;  // обновить вес
  FibElem* y = u->parent;  // перейти к родителю
  if (y != NULL && u->weight < y->weight) {  // если y - не корень
    // и его вес больше веса потомка
    cut(u, y);  // отрезать u
    cascadingCut(y);
  }
}

void FibElem::link(FibElem* x) {
  degree++;  // увеличить степень текущей вершины
  x->left->right = x->right;
  x->right->left = x->left; // удалить x из корневого списка
  x->parent = this;  // назначить текущий узел родителем x
  if (child == NULL) {  // если детей не было
    child = x;  // назначить x единственным ребенком
    x->left = x;
    x->right = x;
  } else {  // иначе
    child->right->left = x;
    x->right = child->right;
    child->right = x;
    x->left = child;  // включить x в список детей текущего узла
  }
  x->mark = false;  // x не помечена
}

void FibHeap::cut(FibElem* x, FibElem* y) {
  if (y->degree == 1) {  // если x - единственный ребенок
    y->child = NULL;  // очистить дочерний список
  } else {  // иначе удалить x из дочернего списка
    x->left->right = x->right;
    x->right->left = x->left;
  }
  y->degree--;  // уменьшить степень y
  insert(x);  // добавить x в корневой список
  n -= pow(2, x->degree);  // компенсировать лишние добавленне вершины
}
  
void FibHeap::cascadingCut(FibElem* y) {
  FibElem* z = y->parent;  // подняться к родителю
  if (z == NULL)  // если y - корень
    return;  // завершить
  if (y->mark == false) {  // если y непомечен
    y->mark = true;  // пометить
  } else {  // иначе
    cut(y, z);  // отрезать y от z
    cascadingCut(z);  // рекурсивно повторить
  }
}

void FibHeap::insert(FibElem* x) {
  n += pow(2, x->degree);
  x->parent = NULL;  // очистить связи
  x->mark = 0;
  if (min == NULL) {  // если куча пуста
    x->left = x;
    x->right = x;  // зациклить список
    min = x;  // обновить значение минимума
    return;
  }
  x->right = min->right;
  min->right->left = x;
  x->left = min;
  min->right = x;  // включить x в корневой список справа от min
  if (x->weight < min->weight)  // если значение x меньше текущего минимума
    min = x;  // обновить минимум
}

void FibHeap::mergeRLists(FibHeap* A) {
  FibElem* tmp;  // вспомогательная переменная
  if (A->min == NULL)  // если A пуста, не делать ничего
    return;
  if (min == NULL) {  // если текущая куча пуста
    min = A->min;  // вернуть A
    return;
  }
  min->left->right = A->min;
  A->min->left->right = min;
  tmp = A->min->left;
  A->min->left = min->left;
  min->left = tmp;  // объединить списки
  if (min->weight > A->min->weight)
    min = A->min;  // если требуется, обновить значение минимума
}

void FibHeap::unite(FibHeap* A) {
  mergeRLists(A);  // объединить корневые списки
  n += A->n;  // увеличить количество элементов
}

void FibHeap::consolidate() {
  if (min == NULL)
    return;
  vector<FibElem*> A(n, NULL);  // вспомогательный массив
  // в ячейке с номером i находится указатель на корень степени i
  int d;  // степень текущей вершины
  FibElem* x = min;  // текущая вершина
  FibElem* y;  // вершина, сравниваемая с текущей
  vector<FibElem*> rList;  // вспомогательный массив для хранения
  // начального корневого списка в начальном порядке
  rList.push_back(min);
  x = x->right;
  while (x != min) {
    rList.push_back(x);
    x->left = x;
    x = x->right;
    x->left->right = x->left;
  }  // заполнить вспомогательный массив, разорвав все связи
  min->left = min;
  min->right = min;
  for (size_t i = 0; i < rList.size(); i++) {  // для каждой вершины корневого списка
    x = rList[i];  // обновить значение вершины
    d = x->degree;  // значение степени
    while (A[d] != NULL) {  // пока есть одинаковые деревья
      y = A[d];  // дерево с той же степенью
      if (x->weight > y->weight) {
        FibElem* tmp = x;
        x = y;
        y = tmp;
      }
      x->link(y);  // присоединить больший узел к меньшему
      A[d] = NULL;  // обнулить текущий элемент
      d++;  // увеличить степень
    }
    A[d] = x;  // записать полученное дерево
  }
  min = NULL;  // очистить кучу
  n = 0;
  // добавить получившиеся деревья в кучу
  for (int i = 0; i < A.size(); i++) {
    if (A[i] != NULL) {
      insert(A[i]);
    }
  }
}

pair<int, int> FibHeap::extractMin() {
  FibElem* z = min;  // минимальный элемент
  if (min == NULL)  // если куча пуста
    return pair<int, int>(-1, -1);  // вернуть мусор
  FibElem* x = z->child;  // перейти к детям
  n--;  // уменьшить количество элементов
  if (x != NULL) {  // если дети есть
    FibElem* nextx = x->right;  // следующий элемент
    for (int i = 0; i < z->degree; i++) {  // пока список детей не закончился
      insert(x);  // добавить x в корневой список
      x = nextx;
      nextx = nextx->right;  // следующий шаг
    }
  }
  if (z == z->right && z->degree == 0) {  // если вершина была единственной и не имела потомков
    min = NULL;  // куча пуста
  } else {  // иначе
  z->left->right = z->right;
  z->right->left = z->left;  // удалить z из корневого списка
  min = z->right;  // минимум указывает на любую другую вершину
  consolidate();  // уплотнить
  }
  return pair<int, int>(z->num, z->weight);  // вернуть минимум
}
