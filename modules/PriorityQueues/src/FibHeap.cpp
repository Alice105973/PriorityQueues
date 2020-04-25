#include <vector>
#include <cmath>
#include <iostream>
#include "../include/FibHeap.h"

using namespace std;

void FibElem::link(FibElem* x) {
  degree++;  // увеличить степень текущей вершины
  x->left->right = x->right;
  x->right->left = x->left; // удалить x из корневого списка
  x->parent = this;  // назначить текущий узел родителем x
  if (child == NULL) {
    child = x;
    x->left = x;
    x->right = right;
  } else {
    child->right->left = x;
    x->right = child->right;
    child->right = x;
    x->left = child;  // включить x в список детей текущего узла
  }
  x->mark = false;  // x не помечена
}

void FibHeap::insert(FibElem* x) {
  x->degree = 0;
  x->parent = NULL;
  x->mark = 0;  // очистить связи
  n++;  // увеличить количество вершин
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
  FibElem* x = min;  // текущая вершина
  FibElem* y;  // вершина, сравниваемая с текущей
  FibElem* nextx = x->right;  // следующая вершина корневого списка
  do {
    int d = x->degree;  // степень x
    while (A[d] != NULL) {  // пока есть одинаковые деревья
      y = A[d];  // получить указатель на дерево с той же степенью
      if (x->weight > y->weight) {  // если вес текущей вершины > веса y
        FibElem* tmp = x;
        x = y;
        y = tmp;  // поменять местами
      }
      x->link(y);  // объединить деревья
      A[d] = NULL;  // очистить ячейку
      d++;  // увеличить степень
    }
    A[d] = x;  // записать полученное дерево в свободную вершину
    x = nextx;
    nextx = nextx->right;  // следующий шаг
  } while (x != min);  // пока корневой список не закончился
  min = NULL;  // очистить кучу
  // добавить получившиеся деревья в кучу
  for (int i = 0; i < A.size(); i++) {
    if (A[i] != NULL) {
      insert(A[i]);
    }
  }
}

pair<int, int> FibHeap::extractMin() {
  FibElem* z = min;
  if (min == NULL)
    return pair<int, int>(-1, -1);
  FibElem* x = z->child;
  FibElem* nextx = z->child;
  if (x != nextx) {
    do {
      insert(x);
      x = nextx;
      nextx = nextx->right;
    } while (x != z->child);
  }
  if (z == z->right) {
    min = NULL;
  } else {
  z->left->right = z->right;
  z->right->left = z->left;
  min = z->right;
  consolidate();
  }
  n--;
  return pair<int, int>(z->num, z->weight);
}
