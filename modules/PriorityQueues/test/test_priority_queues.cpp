// Copyright 2020 Kukushkina Ksenia

#include <gtest/gtest.h>
#include <random>
#include <ctime>
#include <iostream>
#include <utility>
#include <vector>
#include "../include/Utils.h"
#include "../include/DHeap.h"
#include "../include/BinHeap.h"
#include "../include/FibHeap.h"
#include "../include/ThinHeap.h"

TEST(no_exceptions, can_generate_graph) {
  // Arrange & Act & Assert
  ASSERT_NO_THROW(generateGraph(10, 45));
}

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

TEST(no_exceptions, can_create_ThinHeap) {
  // Arrange & Act & Assert
  ASSERT_NO_THROW(ThinHeap H);
}

TEST(no_exceptions, can_insert_elem_to_DHeap) {
  // Arrange
  DHeap A;

  // Act
  A.insert(2, 5);

  // Assert
  ASSERT_NO_THROW(A.insert(7, 10));
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

TEST(no_exceptions, can_insert_elem_to_ThinHeap) {
  // Arrange
  ThinElem a(1, 5);
  ThinElem b(4, 2);
  ThinHeap H;

  // Act
  H.insert(&a);

  // Assert
  ASSERT_NO_THROW(H.insert(&b));
}

TEST(no_exceptions, can_use_Dijkstra_on_DHeap) {
  // Arrange
  std::vector<std::vector<std::pair<int, int>>> g
    = generateGraph(1000, 20000);

  // Act & Assert
  ASSERT_NO_THROW(D_Dijkstra(g));
}

TEST(no_exceptions, can_use_Dijkstra_on_BinHeap) {
  // Arrange
  std::vector<std::vector<std::pair<int, int>>> g
    = generateGraph(1000, 20000);

  // Act & Assert
  ASSERT_NO_THROW(Bin_Dijkstra(g));
}

TEST(no_exceptions, can_use_Dijkstra_on_FibHeap) {
  // Arrange
  std::vector<std::vector<std::pair<int, int>>> g
    = generateGraph(1000, 20000);

  // Act & Assert
  ASSERT_NO_THROW(Fib_Dijkstra(g));
}

TEST(no_exceptions, can_use_Dijkstra_on_ThinHeap) {
  // Arrange
  std::vector<std::vector<std::pair<int, int>>> g
    = generateGraph(1000, 20000);

  // Act & Assert
  ASSERT_NO_THROW(Thin_Dijkstra(g));
}

TEST(correctness, correct_DHeap_build) {
  // Arrange
  DHeap H;
  bool corr = true;
  for (int i = 0; i < 30; i++) {
    H.insert(0, rand() % 100);
  }

  // Act
  for (std::size_t i = 1; i < 30; i++) {
    if (H[i].second < H[H.parent(i)].second) {
      corr = false;
      break;
    }
  }

  // Assert
  ASSERT_EQ(corr, true);
}

TEST(correctness, correct_BinHeap_build) {
  // Arrange
  BinHeap A;
  std::vector<BinElem> vec(10);

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
  std::vector<BinElem> vec(10);
  std::vector<std::pair<int, int>> S;

  // Act
  for (int i = 0; i < 10; i++) {
    vec[i] = BinElem(i, rand() % 10);
    A.insert(&vec[i]);
  }
  for (int i = 0; i < 10; i++) {
    S.push_back(A.extractMin());
  }

  // Assert
  bool corr = 1;
  for (std::size_t i = 0; i < S.size() - 1; i++)
    if (S[i].second > S[i + 1].second)
      corr = 0;
  ASSERT_EQ(corr, true);
}

TEST(correctness, correct_minimum_extraction_FibHeap) {
  // Arrange
  FibHeap A;
  std::size_t n = 10;
  std::vector<FibElem> vec(n);
  std::vector<std::pair<int, int>> S;
  for (std::size_t i = 0; i < n; i++) {
    vec[i] = FibElem(i, rand() % 10);
    A.insert(&vec[i]);
  }
  // Act
  for (std::size_t i = 0; i < n; i++) {
    S.push_back(A.extractMin());
  }

  // Assert
  bool corr = 1;
  for (std::size_t i = 0; i < S.size() - 1; i++)
    if (S[i].second > S[i + 1].second)
      corr = 0;
  ASSERT_EQ(corr, true);
}

TEST(correctness, correct_label_Dijkstra) {
  // Arrange
  std::vector<std::vector<std::pair<int, int>>> graph(10);
  std::vector<int> S(10);
  graph[0].push_back(std::pair<int, int>(1, 1));
  graph[0].push_back(std::pair<int, int>(2, 0));
  graph[0].push_back(std::pair<int, int>(6, 5));
  graph[0].push_back(std::pair<int, int>(8, 9));
  graph[1].push_back(std::pair<int, int>(9, 13));
  graph[1].push_back(std::pair<int, int>(0, 1));
  graph[1].push_back(std::pair<int, int>(5, 1));
  graph[2].push_back(std::pair<int, int>(0, 0));
  graph[2].push_back(std::pair<int, int>(8, 1));
  graph[2].push_back(std::pair<int, int>(4, 4));
  graph[2].push_back(std::pair<int, int>(3, 3));
  graph[3].push_back(std::pair<int, int>(2, 3));
  graph[3].push_back(std::pair<int, int>(7, 3));
  graph[4].push_back(std::pair<int, int>(7, 1));
  graph[4].push_back(std::pair<int, int>(2, 4));
  graph[4].push_back(std::pair<int, int>(8, 1));
  graph[5].push_back(std::pair<int, int>(6, 1));
  graph[5].push_back(std::pair<int, int>(1, 1));
  graph[6].push_back(std::pair<int, int>(5, 1));
  graph[6].push_back(std::pair<int, int>(0, 5));
  graph[7].push_back(std::pair<int, int>(4, 1));
  graph[7].push_back(std::pair<int, int>(3, 3));
  graph[8].push_back(std::pair<int, int>(0, 9));
  graph[8].push_back(std::pair<int, int>(2, 1));
  graph[8].push_back(std::pair<int, int>(4, 1));
  graph[9].push_back(std::pair<int, int>(1, 13));

  S[0] = 0;
  S[1] = 1;
  S[2] = 0;
  S[3] = 3;
  S[4] = 2;
  S[5] = 2;
  S[6] = 3;
  S[7] = 3;
  S[8] = 1;
  S[9] = 14;

  // Act & Assert
  ASSERT_EQ(S, Dijkstra(graph));
}

TEST(correctness, correct_DHeap_Dijkstra) {
  // Arrange
  std::vector<std::vector<std::pair<int, int>>> graph(10);
  DHeap A;
  std::vector<int> S(10);
  graph[0].push_back(std::pair<int, int>(1, 1));
  graph[0].push_back(std::pair<int, int>(2, 0));
  graph[0].push_back(std::pair<int, int>(6, 5));
  graph[0].push_back(std::pair<int, int>(8, 9));
  graph[1].push_back(std::pair<int, int>(9, 13));
  graph[1].push_back(std::pair<int, int>(0, 1));
  graph[1].push_back(std::pair<int, int>(5, 1));
  graph[2].push_back(std::pair<int, int>(0, 0));
  graph[2].push_back(std::pair<int, int>(8, 1));
  graph[2].push_back(std::pair<int, int>(4, 4));
  graph[2].push_back(std::pair<int, int>(3, 3));
  graph[3].push_back(std::pair<int, int>(2, 3));
  graph[3].push_back(std::pair<int, int>(7, 3));
  graph[4].push_back(std::pair<int, int>(7, 1));
  graph[4].push_back(std::pair<int, int>(2, 4));
  graph[4].push_back(std::pair<int, int>(8, 1));
  graph[5].push_back(std::pair<int, int>(6, 1));
  graph[5].push_back(std::pair<int, int>(1, 1));
  graph[6].push_back(std::pair<int, int>(5, 1));
  graph[6].push_back(std::pair<int, int>(0, 5));
  graph[7].push_back(std::pair<int, int>(4, 1));
  graph[7].push_back(std::pair<int, int>(3, 3));
  graph[8].push_back(std::pair<int, int>(0, 9));
  graph[8].push_back(std::pair<int, int>(2, 1));
  graph[8].push_back(std::pair<int, int>(4, 1));
  graph[9].push_back(std::pair<int, int>(1, 13));

  S[0] = 0;
  S[1] = 1;
  S[2] = 0;
  S[3] = 3;
  S[4] = 2;
  S[5] = 2;
  S[6] = 3;
  S[7] = 3;
  S[8] = 1;
  S[9] = 14;

  // Act & Assert
  ASSERT_EQ(D_Dijkstra(graph), S);
}

TEST(correctness, correct_BinHeap_Dijkstra) {
  // Arrange
  std::vector<std::vector<std::pair<int, int>>> graph(10);
  std::vector<int> S(10);
  graph[0].push_back(std::pair<int, int>(1, 1));
  graph[0].push_back(std::pair<int, int>(2, 0));
  graph[0].push_back(std::pair<int, int>(6, 5));
  graph[0].push_back(std::pair<int, int>(8, 9));
  graph[1].push_back(std::pair<int, int>(9, 13));
  graph[1].push_back(std::pair<int, int>(0, 1));
  graph[1].push_back(std::pair<int, int>(5, 1));
  graph[2].push_back(std::pair<int, int>(0, 0));
  graph[2].push_back(std::pair<int, int>(8, 1));
  graph[2].push_back(std::pair<int, int>(4, 4));
  graph[2].push_back(std::pair<int, int>(3, 3));
  graph[3].push_back(std::pair<int, int>(2, 3));
  graph[3].push_back(std::pair<int, int>(7, 3));
  graph[4].push_back(std::pair<int, int>(7, 1));
  graph[4].push_back(std::pair<int, int>(2, 4));
  graph[4].push_back(std::pair<int, int>(8, 1));
  graph[5].push_back(std::pair<int, int>(6, 1));
  graph[5].push_back(std::pair<int, int>(1, 1));
  graph[6].push_back(std::pair<int, int>(5, 1));
  graph[6].push_back(std::pair<int, int>(0, 5));
  graph[7].push_back(std::pair<int, int>(4, 1));
  graph[7].push_back(std::pair<int, int>(3, 3));
  graph[8].push_back(std::pair<int, int>(0, 9));
  graph[8].push_back(std::pair<int, int>(2, 1));
  graph[8].push_back(std::pair<int, int>(4, 1));
  graph[9].push_back(std::pair<int, int>(1, 13));

  S[0] = 0;
  S[1] = 1;
  S[2] = 0;
  S[3] = 3;
  S[4] = 2;
  S[5] = 2;
  S[6] = 3;
  S[7] = 3;
  S[8] = 1;
  S[9] = 14;

  // Act & Assert
  ASSERT_EQ(Bin_Dijkstra(graph), S);
}

TEST(correctness, correct_FibHeap_Dijkstra) {
  // Arrange
  std::vector<std::vector<std::pair<int, int>>> graph(10);
  std::vector<int> S(10);
  graph[0].push_back(std::pair<int, int>(1, 1));
  graph[0].push_back(std::pair<int, int>(2, 0));
  graph[0].push_back(std::pair<int, int>(6, 5));
  graph[0].push_back(std::pair<int, int>(8, 9));
  graph[1].push_back(std::pair<int, int>(9, 13));
  graph[1].push_back(std::pair<int, int>(0, 1));
  graph[1].push_back(std::pair<int, int>(5, 1));
  graph[2].push_back(std::pair<int, int>(0, 0));
  graph[2].push_back(std::pair<int, int>(8, 1));
  graph[2].push_back(std::pair<int, int>(4, 4));
  graph[2].push_back(std::pair<int, int>(3, 3));
  graph[3].push_back(std::pair<int, int>(2, 3));
  graph[3].push_back(std::pair<int, int>(7, 3));
  graph[4].push_back(std::pair<int, int>(7, 1));
  graph[4].push_back(std::pair<int, int>(2, 4));
  graph[4].push_back(std::pair<int, int>(8, 1));
  graph[5].push_back(std::pair<int, int>(6, 1));
  graph[5].push_back(std::pair<int, int>(1, 1));
  graph[6].push_back(std::pair<int, int>(5, 1));
  graph[6].push_back(std::pair<int, int>(0, 5));
  graph[7].push_back(std::pair<int, int>(4, 1));
  graph[7].push_back(std::pair<int, int>(3, 3));
  graph[8].push_back(std::pair<int, int>(0, 9));
  graph[8].push_back(std::pair<int, int>(2, 1));
  graph[8].push_back(std::pair<int, int>(4, 1));
  graph[9].push_back(std::pair<int, int>(1, 13));

  S[0] = 0;
  S[1] = 1;
  S[2] = 0;
  S[3] = 3;
  S[4] = 2;
  S[5] = 2;
  S[6] = 3;
  S[7] = 3;
  S[8] = 1;
  S[9] = 14;

  // Act & Assert
  ASSERT_EQ(Fib_Dijkstra(graph), S);
}

TEST(correctness, correct_ThinHeap_Dijkstra) {
  // Arrange
  std::vector<std::vector<std::pair<int, int>>> graph(10);
  std::vector<int> S(10);
  graph[0].push_back(std::pair<int, int>(1, 1));
  graph[0].push_back(std::pair<int, int>(2, 0));
  graph[0].push_back(std::pair<int, int>(6, 5));
  graph[0].push_back(std::pair<int, int>(8, 9));
  graph[1].push_back(std::pair<int, int>(9, 13));
  graph[1].push_back(std::pair<int, int>(0, 1));
  graph[1].push_back(std::pair<int, int>(5, 1));
  graph[2].push_back(std::pair<int, int>(0, 0));
  graph[2].push_back(std::pair<int, int>(8, 1));
  graph[2].push_back(std::pair<int, int>(4, 4));
  graph[2].push_back(std::pair<int, int>(3, 3));
  graph[3].push_back(std::pair<int, int>(2, 3));
  graph[3].push_back(std::pair<int, int>(7, 3));
  graph[4].push_back(std::pair<int, int>(7, 1));
  graph[4].push_back(std::pair<int, int>(2, 4));
  graph[4].push_back(std::pair<int, int>(8, 1));
  graph[5].push_back(std::pair<int, int>(6, 1));
  graph[5].push_back(std::pair<int, int>(1, 1));
  graph[6].push_back(std::pair<int, int>(5, 1));
  graph[6].push_back(std::pair<int, int>(0, 5));
  graph[7].push_back(std::pair<int, int>(4, 1));
  graph[7].push_back(std::pair<int, int>(3, 3));
  graph[8].push_back(std::pair<int, int>(0, 9));
  graph[8].push_back(std::pair<int, int>(2, 1));
  graph[8].push_back(std::pair<int, int>(4, 1));
  graph[9].push_back(std::pair<int, int>(1, 13));

  S[0] = 0;
  S[1] = 1;
  S[2] = 0;
  S[3] = 3;
  S[4] = 2;
  S[5] = 2;
  S[6] = 3;
  S[7] = 3;
  S[8] = 1;
  S[9] = 14;

  // Act & Assert
  ASSERT_EQ(Thin_Dijkstra(graph), S);
}

TEST(correctness, eq_res_on_large_graph_DHeap) {
  // Arrange
  std::vector<std::vector<std::pair<int, int>>> g
    = generateGraph(1000, 20000);

  // Act & Assert
  ASSERT_EQ(Dijkstra(g), D_Dijkstra(g));
}

TEST(correctness, eq_res_on_large_graph_BinHeap) {
  // Arrange
  std::vector<std::vector<std::pair<int, int>>> g
    = generateGraph(1000, 20000);

  // Act & Assert
  ASSERT_EQ(Dijkstra(g), Bin_Dijkstra(g));
}

TEST(correctness, eq_res_on_large_graph_FibHeap) {
  // Arrange
  std::vector<std::vector<std::pair<int, int>>> g
    = generateGraph(1000, 20000);

  // Act & Assert
  ASSERT_EQ(Dijkstra(g), Fib_Dijkstra(g));
}

TEST(correctness, eq_res_on_large_graph_ThinHeap) {
  // Arrange
  std::vector<std::vector<std::pair<int, int>>> g
    = generateGraph(1000, 20000);

  // Act & Assert
  ASSERT_EQ(Dijkstra(g), Thin_Dijkstra(g));
}
