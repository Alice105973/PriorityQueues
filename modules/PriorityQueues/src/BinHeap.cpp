#include <cstddef>
#include <vector>
#include "../include/BinHeap.h"

using namespace std;

vector<BinElem*> ptrs;  // указатель на i-тую вершину в очереди

vector<int> Bin_Dijkstra(const vector < vector<pair<int, int>>>& graph) {
  ptrs.clear();
  BinHeap q;
  vector<BinElem> data(graph.size());
  BinElem a(0, 0);
  data[0] = a;
  q.insert(&data[0]);
  ptrs.push_back(&data[0]);
  for (size_t i = 1; i < graph.size(); i++) {
    BinElem c(i, INT_MAX);
    data[i] = c;
    q.insert(&data[i]);
    ptrs.push_back(&data[i]);
  }  // дополнительная память для кучи
  vector<int> S(graph.size());  // список вершин, для которых dist уже просчитана
  BinElem* u = NULL;  // вершина, для которой проводится релаксация
  while (q.getN()) {
    pair<int, int> v = q.extractMin();  // текущая вершина, (номер, вес)
    S[v.first] = v.second;  // занести в список обработанных
    int amount = graph[v.first].size();  // количество смежных вершин
    for (int i = 0; i < amount; i++) {  // для всех смежных вершин
      int unum = graph[v.first][i].first;  // номер i-той смежной с v вершины
      ptrs[unum]->relax(v.second, graph[v.first][i].second);
    }
  }
  return S;
}

void BinElem::relax(int vweight, int uvweight) {
  if (vweight + uvweight < this->weight) {  // если найден более короткий путь
    decreaseKey(vweight + uvweight);  // обновить длину пути
  }
}

void BinElem::decreaseKey(int newWeight) {
  weight = newWeight;  // обновить вес
  BinElem* y = this;  // текущий элемент
  BinElem* z = y->parent;  // родитель текущего элемента
  while (z != NULL && y->weight < z->weight) {
    // пока y - не корень и его вес меньше веса родителя
    int tmp = y->weight;
    y->weight = z->weight;
    z->weight = tmp;
    tmp = y->num;
    y->num = z->num;
    z->num = tmp;  // обмен информацией
    BinElem* temp = ptrs[z->num];
    ptrs[z->num] = ptrs[y->num];
    ptrs[y->num] = temp;  // обмен указателями
    y = z;
    z = y->parent;  // следующий шаг
  }
}

void BinElem::link(BinElem* A) {
  A->parent = this;  // назначить текущую вершину родителем А
  A->sibling = this->child;  // назначить ребенка текущей вершины соседом А
  child = A;  // назначить А ребенком текущей вершины
  this->degree++;  // увеличить степень текущей вершины
}

void BinHeap::unite(BinHeap* A) {
  mergeRLists(A);  // объединить корневые списки 
  if (head == NULL)  // если куча пуста
    return;  // завершить
  BinElem* prevx = NULL;  // предыдущий для текущего элемент
  BinElem* x = head;  // текущий элемент
  BinElem* nextx = x->sibling;  // следующий для текущего элемент
  while (nextx != NULL) {  // пока список не закончился
    if (x->degree != nextx->degree  // если соседние деревья различны
      || (nextx->sibling != NULL  // или текущий узел не предпоследний
        && nextx->sibling->degree == x->degree)) {  // и деревья через одно одинаковы (т. е. три подряд)
      prevx = x;
      x = nextx;  // следующий шаг
    } else {  // если деревья равны
      if (x->weight <= nextx->weight) {  // если вес текущего узла меньше веса следующего
        x->sibling = nextx->sibling;  // удалить следующий узел из корневого списка
        x->link(nextx);  // присоединить дерево с корнем в удаленном узле к текущему
      } else {  // если вес текущего больше веса следующего
        if (prevx == NULL)  // если текущий узел первый
          head = nextx;  // назначить следующий корнем
        else
          prevx->sibling = nextx;  // иначе удалить текущий узел из корневого списка
        nextx->link(x);  // присоединить дерево с корнем в удаленном узле к следующему
        x = x->parent;
      }
      n--;  // уменьшить количество деревьев в куче
    }
    nextx = x->sibling;  // следующий шаг
  }
}

void BinHeap::mergeRLists(BinHeap* A) {
  n += A->n;
  BinElem* Hhead;  // корневая вершина списка
  BinElem* curA = A->head;  // текущая вершина в A
  BinElem* curB = head;  // текущая вершина в B
  if (curB == NULL) {  // если B пуста
    head = A->head;  // вернуть A
    return;
  }
  if (curA == NULL) {  // если A пуста
    return;  // вернуть B
  }
  if (curA->degree < curB->degree) {  // если степень корня A меньше степени корня B
    Hhead = curA;  // назначить новым корнем корень A
    curA = curA->sibling;  // следующий шаг
  } else {
    Hhead = curB;  // иначе назначить новым корнем корень B
    curB = curB->sibling;  // следующий шаг
  }
  BinElem* curH = Hhead;  // текущая вершина в новой куче
  while (curA != NULL && curB != NULL) {  // пока списки не пусты
    if (curA->degree < curB->degree) {
      // если степень текущей вершины в A меньше степени текущей вершины B
      curH->sibling = curA;  // добавить текущую вершину A в корневой список
      curA = curA->sibling;  // следующий шаг
    } else {
      curH->sibling = curB;  // иначе добавить текущую вершину B в корневой писок
      curB = curB->sibling;  // следующий шаг
    }
    curH = curH->sibling;  // следующий шаг по H
  }
  if (curA == NULL)  // если закончился список A
    curH->sibling = curB;  // присоединить к списку список B
  else  // если закончился список B
    curH->sibling = curA;  // присоединить к списку список A
  head = Hhead;  // обновить корень
}

pair<int, int> BinHeap::extractMin() {
  BinElem* prevx = NULL;  // предыдущий для минимального элемент
  BinElem* x = head;  // текущий элемент
  if (head == NULL)  // если куча пуста
    return (pair<int, int>(-1, -1));
  // в корневом списке найти вершину с минимальным ключом
  BinElem* minx = head;  // элемент с минимальным ключом
  while (x->sibling != NULL) {  // пока список не закончился
    if (x->sibling->weight < minx->weight) {  // если вес следующего узла меньше минимального
      minx = x->sibling;  // обновить минимальный элемент
      prevx = x;  // обновить предыдущий для минимального элемент
    }
    x = x->sibling;  // следующий шаг
  }
  if (prevx == NULL)  // если минимальный элемент - первый
    head = minx->sibling;  // назначить корнем следующий
  else
    prevx->sibling = minx->sibling;  // иначе удалить минимальный узел из корневого списка
  n--;  // уменьшить количество деревьев
  BinHeap H;  // новая куча
  pair<int, int> m(minx->num, minx->weight);  // сохранить значения минимального элемента
  // обратить порядок в списке детей minx
  x = minx->child;  // перейти к левому ребенку x
  BinElem* nextx;  // следующий узел
  prevx = NULL;  // предыдущий узел
  while (x != NULL) {  // пока дети не закончились
    H.n++;  // увеличиваем количество деревьев в H
    x->parent = NULL;  // сделать x корнем
    nextx = x->sibling;  // запомнить следующего ребенка
    x->sibling = prevx;  // сделать правым соседом x предыдущий элемент
    prevx = x;  //
    x = nextx;  // шаг алгоритма
  }
  H.head = prevx;  // сделать последний узел корнем H
  this->unite(&H);  // связать H с текущей кучей
  return m;  // вернуть минимум
}

void BinHeap::insert(BinElem* x) {
  BinHeap H;  // создать новую кучу
  x->parent = NULL;  // удалить все связи x
  x->child = NULL;
  x->sibling = NULL;
  x->degree = 0;
  H.n = 1;
  H.head = x;  // x - единственный элемент в новой куче
  this->unite(&H);  // объединить x с текущей кучей
}
