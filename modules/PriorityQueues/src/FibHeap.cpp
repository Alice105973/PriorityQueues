#include "../include/FibHeap.h"
#define NULL 0

using namespace std;

void FibHeap::insert(FibElem* x) {
  x->degree = 0;
  x->parent = NULL;
  x->child = NULL;
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
