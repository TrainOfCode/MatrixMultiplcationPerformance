#include<iostream>
#include<vector>
#include<stdlib.h>
#include<chrono>



void MMulVec(std::vector<std::vector<double>> a, std::vector<std::vector<double>> b, std::vector<std::vector<double>> &c, int N, int K, int M);
void printNestedVector(std::vector<std::vector<double>> inp);
void MMulArr(double **a, double **b, double **c, int N, int M, int K);
void printNestedArray(double **inp, int SIZE);

int main(int argc, char* argv[]) {

  srand(50);

  int SIZE = 100;
  int ROUNDS = 1000;

  std::vector<std::vector<double>> a;
  std::vector<std::vector<double>> b;

  double **A;
  double **B;
  double **C;
  A = new double *[SIZE];
  B = new double *[SIZE];
  C = new double *[SIZE];
  for (int i = 0; i < SIZE; i++) {
    A[i] = new double[SIZE];
    B[i] = new double[SIZE];
    C[i] = new double[SIZE];
  }

  for(int i = 0; i < SIZE; i++) {
    std::vector<double> newRa;
    std::vector<double> newRb;
    for(int j = 0; j < SIZE; j++) {
      newRa.push_back(rand() % 5 + 1);
      newRb.push_back(rand() % 5 + 1);
      A[i][j] = rand() % 5 + 1;
      B[i][j] = rand() % 5 + 1;
    }
    a.push_back(newRa);
    b.push_back(newRb);
  }

  std::vector<std::vector<double>> c( SIZE , std::vector<double> (SIZE, 0));


  auto startVec = std::chrono::high_resolution_clock::now();
  for(int i = 0; i < ROUNDS; i++) {
    MMulVec(a, b, c, SIZE, SIZE, SIZE);
  }
  auto stopVec = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopVec - startVec);
  double durationVe = duration.count();

  std::cout << "Time taken by vector: " << durationVe*1e-6 << " seconds" << std::endl;

  auto startArr = std::chrono::high_resolution_clock::now();
  for(int i = 0; i < ROUNDS; i++) {
    MMulArr(A, B, C, SIZE, SIZE, SIZE);
  }
  auto stopArr = std::chrono::high_resolution_clock::now();

  duration = std::chrono::duration_cast<std::chrono::microseconds>(stopArr - startArr);
  double durationAr = duration.count();

  std::cout << "Time taken by array: " << durationAr*1e-6 << " seconds" << std::endl;

  return 0;
}

void MMulVec(std::vector<std::vector<double>> a, std::vector<std::vector<double>> b, std::vector<std::vector<double>> &c, int N, int K, int M) {
  /*
  for i in range(0,N) :
    for k in range(0,K) :
      r = A[i][k]
      for j in range(0,M) :
        C[i][j] += r * B[k][j]

  a: N * K
  b: K * M
  */
  for (int i = 0; i < N; i++) {
    for (int k = 0; k < K; k++) {
      double r = a[i][k];
      for (int j = 0; j < M; j++) {
        c[i][j] += r * b[k][j];
      }
    }
  }
}

void MMulArr(double **a, double **b, double **c, int N, int M, int K) {
  /*
  for i in range(0,N) :
    for k in range(0,K) :
      r = A[i][k]
      for j in range(0,M) :
        C[i][j] += r * B[k][j]

  a: N * K
  b: K * M
  */
  for (int i = 0; i < N; i++) {
    for (int k = 0; k < K; k++) {
      double r = a[i][k];
      for (int j = 0; j < M; j++) {
        c[i][j] += r * b[k][j];
      }
    }
  }
}

void printNestedVector(std::vector<std::vector<double>> inp) {
  for(int i = 0; i < inp.size(); i++) {
    std::cout << "[ ";
    for(int j = 0; j < inp[i].size(); j++) {
      std::cout << inp[i][j] << ", ";
    }
    std::cout << " ]";
    std::cout << std::endl;
  }
}

void printNestedArray(double **inp, int SIZE) {
  for(int i = 0; i < SIZE; i++) {
    std::cout << "[ ";
    for(int j = 0; j < SIZE; j++) {
      std::cout << inp[i][j] << ", ";
    }
    std::cout << " ]";
    std::cout << std::endl;
  }
}
