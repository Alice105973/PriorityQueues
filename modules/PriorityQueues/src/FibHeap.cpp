#include <vector>
#include <cmath>
#include <cstddef>
#include <climits>
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

void FibHeap::insert(FibElem* x) {
  x->parent = NULL;
  x->mark = 0;  // оборвать связи
  if (min == NULL) {  // если куча пуста
    x->left = x;
    x->right = x;  // создать список корней, содержащий только x
    min = x;  // обновить минимум
  }
  else {
    min->right->left = x;
    x->right = min->right;
    min->right = x;
    x->left = min;  // вставить x в корневой список
    if (x->weight < min->weight)
      min = x;  // обновить значение минимума
  }
  n++;  // увеличить количество вершин
}

pair<int, int> FibHeap::extractMin() {
  if (min == NULL)  // если куча пуста
    return pair<int, int>(-1, -1);  // вернуть мусор
  FibElem* z = min;  // минимальный элемент
  FibElem* x = z->child;  // перейти к детям
  if (x != NULL) {  // если дети есть
    FibElem* nextx = x->right;  // следующий элемент
    for (int i = 0; i < z->degree; i++) {  // пока список детей не закончился
      min->right->left = x;
      x->right = min->right;
      x->left = min;
      min->right = x;
      x->parent = NULL;  // добавить x в корневой список
      x = nextx;
      nextx = nextx->right;  // следующий шаг
    }
  }
  if (z == z->right && z->degree == 0) {  // если вершина была единственной и не имела потомков
    min = NULL;
    n = 0;  // куча пуста
  } else {  // иначе
  z->left->right = z->right;
  z->right->left = z->left;  // удалить z из корневого списка
  min = z->right;  // минимум указывает на любую другую вершину
  consolidate();  // уплотнить
  n--;
  }
  return pair<int, int>(z->num, z->weight);  // вернуть минимум
}

void FibHeap::link(FibElem* x, FibElem* y) {
  // cout << "link\n";
  x->left->right = x->right;
  x->right->left = x->left; // удалить x из корневого списка
  if (y->left == y)  // если остался последний узел
    min = y;  // назначить его минимальным
  x->parent = y;  // назначить текущий узел родителем x
  if (y->child == NULL) {  // если детей не было
    y->child = x;  // назначить x единственным ребенком
    x->left = x;
    x->right = x;
  } else {  // иначе
    y->child->right->left = x;
    x->right = y->child->right;
    y->child->right = x;
    x->left = y->child;  // включить x в список детей текущего узла
    if (x->weight < y->child->weight)
      y->child = x;
  }
  y->degree++;  // увеличить степень текущей вершины
  x->mark = false;  // x не помечена
}

void FibHeap::consolidate() {
  if (min == NULL)
    return;
  vector<FibElem*> A(static_cast<size_t>(ceil(log2(n))), NULL);  // вспомогательный массив
  // в ячейке с номером i находится указатель на корень степени i
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
  }
  min->left = min;
  min->right = min;  // заполнить вспомогательный массив, разорвав все связи
  for (size_t i = 0; i < rList.size(); i++) {  // для каждой вершины корневого списка
    x = rList[i];  // обновить значение вершины
    int d = x->degree;  // значение степени
    while (A[d] != NULL) {  // пока есть одинаковые деревья
      y = A[d];  // дерево с той же степенью
      if (x->weight > y->weight)
        std::swap(x, y);
      link(y, x);  // присоединить больший узел к меньшему
      A[d] = NULL;  // обнулить текущий элемент
      d++;  // увеличить степень
    }
    A[d] = x;  // записать полученное дерево
  }
  min = NULL;  // очистить кучу
  for (size_t i = 0; i < A.size(); i++) {
    if (A[i] == NULL)
      continue;
    if (min == NULL) {
      min = A[i];
      continue;
    }
    min->right->left = A[i];
    A[i]->right = min->right;
    min->right = A[i];
    A[i]->left = min;
    if (A[i]->weight < min->weight)
      min = A[i];
  }  // добавить получившиеся деревья в кучу
}

void FibHeap::decreaseKey(FibElem* u, int newWeight) {
  //cout << "decrease\n";
  u->weight = newWeight;  // обновить вес
  FibElem* y = u->parent;  // перейти к родителю
  if (y != NULL && u->weight < y->weight) {  // если y - не корень
    // и его вес больше веса потомка
    cut(u, y);  // отрезать u
    cascadingCut(y);
  }
  if (u->weight < min->weight)
    min = u;
}

void FibHeap::cut(FibElem* x, FibElem* y) {
  //cout << "cut\n";
  if (y->degree == 1) {  // если x - единственный ребенок
    y->child = NULL;  // очистить дочерний список
  } else {  // иначе удалить x из дочернего списка
    if (x == y->child)
      y->child = x->right;
    x->left->right = x->right;
    x->right->left = x->left;
  }
  y->degree--;  // уменьшить степень y
  y->mark = true;  // пометить y
  x->parent = NULL;
  min->right->left = x;
  x->right = min->right;
  min->right = x;
  x->left = min;  // добавить x в корневой список
}
  
void FibHeap::cascadingCut(FibElem* y) {
  //cout << "cascading\n";
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

void FibHeap::relax(int vweight, FibElem* u, int uvweight) {
  //cout << "relax\n";
  if (vweight + uvweight < u->weight) {  // если найден более короткий путь
    decreaseKey(u, vweight + uvweight);  // обновить длину пути
  }
}
