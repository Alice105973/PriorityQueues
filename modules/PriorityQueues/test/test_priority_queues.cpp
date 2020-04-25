#include <random>
#include <ctime>
#include <gtest/gtest.h>
#include "../include/DHeap.h"
#include "../include/BinHeap.h"
#include "../include/FibHeap.h"

using namespace std;

TEST(no_exceptions, can_create_DHeap) {
  // Arrange & Act & Assert
  ASSERT_NO_THROW(DHeap A);
}

TEST(no_exceptions, can_create_BinHeap) {
  // Arrange & Act & Assert
  ASSERT_NO_THROW(BinHeap A);
}

TEST(no_exceptions, can_create_FibHeap) {
  // Arrange & Act & Assert
  ASSERT_NO_THROW(FibHeap H);
}

TEST(no_exceptions, can_insert_elem_to_BinHeap) {
  // Arrange
  BinElem b(1, 1);
  BinElem a(0, 0);
  BinHeap A;

  // Act
  A.insert(&a);

  // Assert
  ASSERT_NO_THROW(A.insert(&b));
}

TEST(no_exceptions, can_insert_elem_to_FibHeap) {
  // Arrange
  FibElem a(1, 5);
  FibElem b(4, 2);
  FibHeap H;

  // Act
  H.insert(&a);

  // Assert
  ASSERT_NO_THROW(H.insert(&b));
}

TEST(no_exceptions, can_use_Dijkstra_on_DHeap) {
  // Arrange
  DHeap A;
  vector<vector<pair<int, int>>> g;
  vector<pair<int, int>> g1;
  g1.push_back(pair<int, int>(1, 5));
  g.push_back(g1);

  // Act & Assert
  ASSERT_NO_THROW(Dijkstra(g, A));
}

TEST(no_exceptions, can_use_Dijkstra_on_BinHeap) {
  // Arrange
  BinHeap A;
  vector<BinElem> vec;
  vector<vector<pair<int, int>>> g;
  vector<pair<int, int>> g1;
  g1.push_back(pair<int, int>(1, 5));
  g.push_back(g1);

  // Act & Assert
  ASSERT_NO_THROW(Dijkstra(g, &A, &vec));
}

TEST(correctness, correct_DHeap_build) {
  // Arrange
  DHeap H;
  bool corr = true;
  for (int i = 0; i < 30; i++) {
    H.insert(0, rand() % 100);
  }

  // Act
  for (int i = 1; i < 30; i++) {
    if (H[i].second < H[H.parent(i)].second) {
      corr = false;
      break;
    }
  }

  // Assert
  ASSERT_EQ(corr, true);
}

TEST(correctness, correct_DHeap_Dijkstra) {
  // Arrange
  vector<vector<pair<int, int>>> graph(10);
  DHeap A;
  vector<pair<int, int>> S;
  graph[0].push_back(pair<int, int>(1, 1));
  graph[0].push_back(pair<int, int>(2, 0));
  graph[0].push_back(pair<int, int>(6, 5));
  graph[0].push_back(pair<int, int>(8, 9));
  graph[1].push_back(pair<int, int>(9, 13));
  graph[1].push_back(pair<int, int>(0, 1));
  graph[1].push_back(pair<int, int>(5, 1));
  graph[2].push_back(pair<int, int>(0, 0));
  graph[2].push_back(pair<int, int>(8, 1));
  graph[2].push_back(pair<int, int>(4, 4));
  graph[2].push_back(pair<int, int>(3, 3));
  graph[3].push_back(pair<int, int>(2, 3));
  graph[3].push_back(pair<int, int>(7, 3));
  graph[4].push_back(pair<int, int>(7, 1));
  graph[4].push_back(pair<int, int>(2, 4));
  graph[4].push_back(pair<int, int>(8, 1));
  graph[5].push_back(pair<int, int>(6, 1));
  graph[5].push_back(pair<int, int>(1, 1));
  graph[6].push_back(pair<int, int>(5, 1));
  graph[6].push_back(pair<int, int>(0, 5));
  graph[7].push_back(pair<int, int>(4, 1));
  graph[7].push_back(pair<int, int>(3, 3));
  graph[8].push_back(pair<int, int>(0, 9));
  graph[8].push_back(pair<int, int>(2, 1));
  graph[8].push_back(pair<int, int>(4, 1));
  graph[9].push_back(pair<int, int>(1, 13));

  A.insert(0, 0);
  for (size_t i = 1; i < 10; i++) {
    A.insert(i, 1000);
  }

  S.push_back(pair<int, int>(0, 0));
  S.push_back(pair<int, int>(2, 0));
  S.push_back(pair<int, int>(1, 1));
  S.push_back(pair<int, int>(8, 1));
  S.push_back(pair<int, int>(5, 2));
  S.push_back(pair<int, int>(4, 2));
  S.push_back(pair<int, int>(3, 3));
  S.push_back(pair<int, int>(6, 3));
  S.push_back(pair<int, int>(7, 3));
  S.push_back(pair<int, int>(9, 14));

  // Act & Assert
  ASSERT_EQ(Dijkstra(graph, A), S);
}

TEST(correctness, correct_BinHeap_build) {
  // Arrange
  BinHeap A;
  vector<BinElem> vec(10);

  // Act
  for (int i = 0; i < 10; i++) {
    vec[i] = BinElem(i, rand() % 10);
    A.insert(&vec[i]);
  }

  // Assert
  ASSERT_EQ(A.getN(), 2);
}

TEST(correctness, correct_minimum_extraction_BinHeap) {
  // Arrange
  BinHeap A;
  vector<BinElem> vec(10);
  vector<pair<int, int>> S;

  // Act
  for (int i = 0; i < 10; i++) {
    vec[i] = BinElem(i, rand() % 10);
    A.insert(&vec[i]);
  }
  for (int i = 0; i < 10; i++)
  {
    S.push_back(A.extractMin());
  }

  // Assert
  bool corr = 1;
  for (int i = 0; i < S.size() - 1; i++)
    if (S[i].second > S[i + 1].second)
      corr = 0;
  ASSERT_EQ(corr, true);
}

TEST(correctness, correct_BinHeap_Dijkstra) {
  // Arrange
  vector<vector<pair<int, int>>> graph(10);
  BinHeap A;
  vector<BinElem> vec(10);
  vector<pair<int, int>> S;
  graph[0].push_back(pair<int, int>(1, 1));
  graph[0].push_back(pair<int, int>(2, 0));
  graph[0].push_back(pair<int, int>(6, 5));
  graph[0].push_back(pair<int, int>(8, 9));
  graph[1].push_back(pair<int, int>(9, 13));
  graph[1].push_back(pair<int, int>(0, 1));
  graph[1].push_back(pair<int, int>(5, 1));
  graph[2].push_back(pair<int, int>(0, 0));
  graph[2].push_back(pair<int, int>(8, 1));
  graph[2].push_back(pair<int, int>(4, 4));
  graph[2].push_back(pair<int, int>(3, 3));
  graph[3].push_back(pair<int, int>(2, 3));
  graph[3].push_back(pair<int, int>(7, 3));
  graph[4].push_back(pair<int, int>(7, 1));
  graph[4].push_back(pair<int, int>(2, 4));
  graph[4].push_back(pair<int, int>(8, 1));
  graph[5].push_back(pair<int, int>(6, 1));
  graph[5].push_back(pair<int, int>(1, 1));
  graph[6].push_back(pair<int, int>(5, 1));
  graph[6].push_back(pair<int, int>(0, 5));
  graph[7].push_back(pair<int, int>(4, 1));
  graph[7].push_back(pair<int, int>(3, 3));
  graph[8].push_back(pair<int, int>(0, 9));
  graph[8].push_back(pair<int, int>(2, 1));
  graph[8].push_back(pair<int, int>(4, 1));
  graph[9].push_back(pair<int, int>(1, 13));

  BinElem b(0, 0);
  vec[0] = b;
  A.insert(&vec[0]);
  for (size_t i = 1; i < 10; i++) {
    BinElem c(i, 1000);
    vec[i] = c;
    A.insert(&vec[i]);
  }

  S.push_back(pair<int, int>(0, 0));
  S.push_back(pair<int, int>(2, 0));
  S.push_back(pair<int, int>(1, 1));
  S.push_back(pair<int, int>(8, 1));
  S.push_back(pair<int, int>(5, 2));
  S.push_back(pair<int, int>(4, 2));
  S.push_back(pair<int, int>(6, 3));
  S.push_back(pair<int, int>(7, 3));
  S.push_back(pair<int, int>(3, 3));
  S.push_back(pair<int, int>(9, 14));

  // Act & Assert
  ASSERT_EQ(Dijkstra(graph, &A, &vec), S);
}
