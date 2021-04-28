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
  }  // �������������� ������ ��� ����
  vector<int> S(graph.size());  // ������ ������, ��� ������� dist ��� ����������
  while (!q.isEmpty()) {
    pair<int, int> v = q.extractMin();  // ������� �������, (�����, ���)
    S[v.first] = v.second;  // ������� � ������ ������������
    int amount = graph[v.first].size();  // ���������� ������� ������
    for (int i = 0; i < amount; i++) {  // ��� ���� ������� ������
      int unum = graph[v.first][i].first;  // ����� i-��� ������� � v �������
      q.relax(v.second, &data[unum], graph[v.first][i].second);
    }
  }
  return S;
}

bool ThinElem::br_violation() {
  if (this == NULL) return false;
  if (left == NULL)  // � ������� �� ��������
    return false;
  if (right == NULL)  // ���� ��� ������� �����
    if (rank == 1)  // � ���� ����� 1
      return true;
    else return false;
  if (rank == right->rank + 2)  // ���� ���� ������ ����� ������� ����� �� 2
    return true;
  return false;
}

bool ThinElem::p_violation() {
  if (this == NULL) return false;
  if (left == NULL)
    if (isThin()) { // ���� - ������ ������ ������
      return true;
    }
  if (child == NULL) {
    if (rank == 2)  //  ��� ����� � ���� = 2
    {
      return true; 
    }
    else {
      return false;
    }
  }
  if (rank == child->rank + 3) {  // ���� ������ ����� ���� �� 3
    return true;
  }
  return false;
}

ThinElem* ThinElem::parent() {
  if (left == NULL)  // ���� ���� - ������
    return NULL;  // �������� ���
  ThinElem* x = this;
  ThinElem* y = left;
  while (y->child != x) {
    x = y;
    y = x->left;
  }
  return y;
}

void ThinElem::link(ThinElem* A) {
  A->left = this;  // ��������� ������� ������� ��������� �
  A->right = child;  // ��������� ������� ������� ������� ������� �
  if (child != NULL)
    child->left = A;
  child = A;  // ��������� � �������� ������� �������
  rank++;  // ��������� ������� ������� �������
}

bool ThinElem::isThin() {
  if (rank == 0)  // ���� ����� 0 �� ������
    return false;
  if (rank == 1)  // ���� ���� = 1 � ����� ��� - ���� ������
    return (child == NULL);
  else  // ���� ���� �� 2 ������ ����� �������� ����, ���� ������
    return (child->rank + 1) != rank;
}

void ThinHeap::insert(ThinElem* x) {
  n++;  // ���������� ��������� � ���� �������������
  x->left = NULL;  // �������� �������� �����
  x->right = NULL;
  if (x->child == NULL)
    x->rank = 0;
  else x->rank = x->child->rank + 1;

  if (first == NULL) {  // ���� ���� �����
    first = x;  // �������� x
    last = x;  // ��� ������������ �������
  }
  else {
    if (x->weight < first->weight) {  // ���� x �����������
      x->right = first;  // ��������� ��� � ������ ��������� ������
      first = x;  // �������� ������ �����������
    }
    else {
      last->right = x;  // �����
      last = x;  // �������� � ����� ��������� ������
    }
  }
}

pair<int, int> ThinHeap::extractMin() {
  if (n == 1) {  // ���� � ���� ���� �������
    n--;  // �������� ����
    ThinElem* tmp = first;
    first = NULL;
    last = NULL;
    return pair<int, int>(tmp->num, tmp->weight);  // ������� ������������ �������
  }

  ThinElem* tmp = first;
  n--;
  ThinElem* nextx = NULL;
  int max = -1;
  first = first->right;  // ������� ������ ������� �� ��������� ������
  if (first == NULL)  // ���� ���� �����
    last = NULL;

  ThinElem* x = tmp->child;  // ������� � �����
  while (x != NULL) {  // ���� �� ��������� ����� ������
    if (x->isThin())  // ���� ���� ������
      x->rank--;  // �������� ����
    ThinElem* nextx = x->right;
    insert(x);  // �������� � �������� ������
    n--;
    x = nextx;  // ������� � ����������
  }

  x = first;  // ������ � �����
  vector<ThinElem*> A(static_cast<size_t>(ceil(log2(n)) + 3), NULL);  // ��������������� ������
  // � ������ � ������� i ��������� ��������� �� ������ ������� i
  while (x != NULL) {  // ���� �� ��������� ����� ������
    nextx = x->right;
    while (A[x->rank] != NULL) {  // ���� ���� ���� ���� �� �����
      if (A[x->rank]->weight < x->weight)  // ����������� ������� - x
        swap(A[x->rank], x);
      x->link(A[x->rank]);  // ��������� �������
      A[x->rank - 1] = NULL;  // �������� ������
    }
    A[x->rank] = x;  // �������� ���������� ������
    if (x->rank > max)  // �������� ��������
      max = x->rank;
    x = nextx;
  }
  // ������� ��� ���� ������� � ����
  first = NULL;  // �������� ����
  last = NULL;
  for (int i = 0; i <= max; i++)
    if (A[i] != NULL) {
      insert(A[i]);  // �������� � �������� ������
      n--;  // ��������� ������������ n
    }
  tmp->left = NULL;
  tmp->right = NULL;
  tmp->child = NULL;
  return pair<int, int>(tmp->num, tmp->weight);
}

void ThinHeap::decreaseKey(ThinElem* x, int newWeight) {
  if (newWeight > x->weight) return;
  x->weight = newWeight;  // �������� ���
  ThinElem* l = x->left;

  if (x == first)  // � ������ (�����������) ��������� 
    return;  // ������ �� ������

  if (l == NULL) {  // ���� x - ������, �� �� ������
    ThinElem* z = first;
    while (z->right != x) {
      z = z->right;  // ����� ������ ������
    }
    if (x == last)  // ���� x - ���������
      last = z;  // ��������� ��������� z
    z->right = x->right;  // ������� x �� ��������� ������
    insert(x);  // �������� �� ����������� ����� (�������� �������)
    n--;  // ��������� n
    return;  // ���������
  }

  if (x->weight >= x->parent()->weight)  // ���� �������������� �� ��������
    return;  // ���������

  if (l->child == x)  // ���� x - ������ ���
    l->child = x->right;  // ������� x �� ������ �����
  else  // ���� x - �� ������ ���
    x->left->right = x->right;
  if (x->right != NULL)
    x->right->left = x->left;
  insert(x);  // �������� x � �������� ������
  n--; // ��������� n
  

  while (l->br_violation() || l->p_violation())
  {  // ���� ���� ���������
    // �������� ���������
    while (l->br_violation() && l != NULL) {
      if (l->isThin() == false) {  // ���� ���� �� ������
        ThinElem* ch = l->child;  // ����������� ��������� � ������ � ����
        if (ch != NULL) {
          l->child = ch->right;  //  �� ����� ������������
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

    // ������������ ���������
    while (l->p_violation() && l != NULL) {
      if (l->left == NULL) {  // ���� l - ������
        if (l->child == NULL)  // ���� �� 1 ������ ����� ����
          l->rank = 0;
        else
          l->rank = l->child->rank + 1;
        l = NULL;
        break;
      }
      ThinElem* le = l->left;  // ����������� ��������� � ������ � y � �������� ������
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
  if (vweight + uvweight < u->weight) {  // ���� ������ ����� �������� ����
    decreaseKey(u, vweight + uvweight);  // �������� ����� ����
  }
}
