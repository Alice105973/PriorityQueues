#include <vector>
#include <cmath>
#include <cstddef>
#include <climits>
#include "../include/ThinHeap.h"

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
    x->left = NULL;
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
    x->left = NULL;
    x->right = NULL;
    if (x->rank > max)  // �������� ��������
      max = x->rank;  //
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
  return pair<int, int>(tmp->num, tmp->weight);
}


