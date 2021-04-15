#include <vector>
#include <cmath>
#include <cstddef>
#include <climits>
#include "../include/ThinHeap.h"

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
    x->left = NULL;
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
    x->left = NULL;
    x->right = NULL;
    if (x->rank > max)  // обновить максимум
      max = x->rank;  //
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
  return pair<int, int>(tmp->num, tmp->weight);
}


