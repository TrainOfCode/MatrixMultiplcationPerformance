#include<iostream>
#include<vector>
#include<stdlib.h>
#include<chrono>



void MMulVec(const std::vector<std::vector<double>> a, const std::vector<std::vector<double>> b,
  std::vector<std::vector<double>> &c, int N, int K, int M);

void MMulArr(double **a, double **b, double **c, int N, int M, int K);

void MMulArrRec(const double *a, const double *b, double *c, int M, int N, int K);
void addMatMulRec(const double *A, const double *B, double *C, int M, int N, int K, int fdA, int fdB, int fdC);

void printNestedArray(double **inp, int SIZE);
void printNestedVector(std::vector<std::vector<double>> inp);
void printNonNestedArray(const double *inp, int SIZE);

int main(int argc, char* argv[]) {

  srand(500);

  int SIZE = 2;
  // int ROUNDS = 1000;

  std::vector<std::vector<double>> a;
  std::vector<std::vector<double>> b;

  double **A;
  double **B;
  double **C;
  A = new double *[SIZE];
  B = new double *[SIZE];
  C = new double *[SIZE];

  double A1[SIZE * SIZE];
  double B1[SIZE * SIZE];
  double C1[SIZE * SIZE];


  for (int i = 0; i < SIZE; i++) {
    A[i] = new double[SIZE];
    B[i] = new double[SIZE];
    C[i] = new double[SIZE];
  }
  int count = 1;
  int countB = 5;

  for(int i = 0; i < SIZE; i++) {
    std::vector<double> newRa;
    std::vector<double> newRb;
    for(int j = 0; j < SIZE; j++) {
      newRa.push_back(rand() % 5 + 1);
      newRb.push_back(rand() % 5 + 1);
      A[i][j] = count;//rand() % 5 + 1;
      B[i][j] = countB;//rand() % 5 + 1;
      A1[(i * SIZE) + j] = A[i][j];//rand() % 5 + 1;
      B1[(i * SIZE) + j] = B[i][j];//rand() % 5 + 1;
      C1[(i * SIZE) + j] = 0;
      count++;
      countB++;
    }
    a.push_back(newRa);
    b.push_back(newRb);
  }
  /*
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

  */

  std::cout << "Array a1" << std::endl;
  printNonNestedArray(A1, SIZE);

  std::cout << "Array b1" << std::endl;
  printNonNestedArray(B1, SIZE);


  std::cout << "Array A" << std::endl;
  printNestedArray(A, SIZE);

  std::cout << "Array A" << std::endl;
  printNestedArray(B, SIZE);

  MMulArrRec(A1, B1, C1, SIZE, SIZE, SIZE);

  std::cout << "Result" << std::endl;
  printNonNestedArray(C1, SIZE);

  std::cout << "To check" << std::endl;
  MMulArr(A, B, C, SIZE, SIZE, SIZE);
  printNestedArray(C, SIZE);


  return 0;
}

void MMulVec(const std::vector<std::vector<double>> a, const std::vector<std::vector<double>> b, std::vector<std::vector<double>> &c, int N, int K, int M) {
  /*
  for i in range(0,N) :
    for k in range(0,K) :
      r = A[i][k]
      for j in range(0,M) :
        C[i][j] += r * B[k][j]
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
  for (int i = 0; i < N; i++) {
    for (int k = 0; k < K; k++) {
      double r = a[i][k];
      for (int j = 0; j < M; j++) {
        c[i][j] += r * b[k][j];
      }
    }
  }
}


/*
a: m * n
b: n * k
c: m * k
*/

void addMatMulRec(const double *A, const double *B, double *C, int M, int N, int K, int fdA, int fdB, int fdC) {
  if(M + N + K <= 4) {
    for (int i = 0; i < M; i++) {
      for (int k = 0; k < K; k++) {
        double sum = 0;
        for (int j = 0; j < N; j++) {
          sum += A[i*fdA +j] * B[j*fdB + k];
        }
        C[i*fdC + k] += sum;
      }
    }
  } else {
    int M2 = M/2;
    int N2 = N/2;
    int K2 = K/2;
    std::cout << M2 << std::endl;
    std::cout << N2 << std::endl;
    std::cout << K2 << std::endl;

    addMatMulRec(A, B, C, M2, N2, K2, fdA, fdB, fdC);
    addMatMulRec(A+N2, B+(N2 *fdB), C, M2, N-N2, K2, fdA, fdB, fdC);

    addMatMulRec(A, B+K2, C+K2, M2, N2, K-K2, fdA, fdB, fdC);
    addMatMulRec(A+N2, B+K2+(N2*fdB), C, M2, N-N2, K-K2, fdA, fdB, fdC);

    addMatMulRec(A+(M2*fdA), B, C+(M2*fdC), M-M2, N2, K2, fdA, fdB, fdC);
    addMatMulRec(A+(M2*fdA)+N2, B+(N2*fdB), C+(M2*fdC), M-M2, N-N2, K2, fdA, fdB, fdC);

    addMatMulRec(A+(M2*fdA), B+K2, C+(M2*fdC)+K2, M-M2, N2, K-K2, fdA, fdB, fdC);
    addMatMulRec(A+(M2*fdA)+N2, B+K2+(N2*fdB), C+(M2*fdC), M-M2, N-N2, K-K2, fdA, fdB, fdC);
  }
}

void MMulArrRec(const double *a, const double *b, double *c, int M, int N, int K) {
  addMatMulRec(a, b, c, M, N, K, N, K, K);
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

void printNonNestedArray(const double *inp, int SIZE) {
  for(int i = 0; i < SIZE; i++) {
    std::cout << "[ ";
    for(int j = 0; j < SIZE; j++) {
      std::cout << inp[(i * SIZE) + j] << ", ";
    }
    std::cout << " ]";
    std::cout << std::endl;
  }
}
