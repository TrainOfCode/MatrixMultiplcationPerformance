#include<iostream>
#include<vector>
#include <stdlib.h>



std::vector<std::vector<double>> MMulVec(std::vector<std::vector<double>> a, std::vector<std::vector<double>> b);
void printNestedVector(std::vector<std::vector<double>> inp);

int main(int argc, char* argv[]) {

  std::vector<std::vector<double>> a;
  std::vector<std::vector<double>> b;

  for(int i = 0; i < 2; i++) {
    std::vector<double> newRa;
    std::vector<double> newRb;
    for(int j = 0; j < 2; j++) {
      newRa.push_back(rand() % 5 + 1);
      newRb.push_back(rand() % 5 + 1);
    }
    a.push_back(newRa);
    b.push_back(newRb);
  }

  std::cout<< "Vector a" << std::endl;
  printNestedVector(a);

  std::cout<< "Vector b" << std::endl;
  printNestedVector(b);

  std::cout<< "First test with only vectors" << std::endl;

  std::vector<std::vector<double>> c = MMulVec(a, b);

  std::cout<< "Result" << std::endl;
  printNestedVector(c);

  return 0;
}

std::vector<std::vector<double>> MMulVec(std::vector<std::vector<double>> a, std::vector<std::vector<double>> b) {
  /*
  for i in range(0,N) :
    for k in range(0,K) :
      r = A[i][k]
      for j in range(0,M) :
        C[i][j] += r * B[k][j]

  a: N * K
  b: K * M
  */
  int N = a.size();
  int K = b.size();
  int M = b[0].size();

  std::vector<std::vector<double>> c( N , std::vector<double> (M, 0));

  for (int i = 0; i < N; i++) {
    for (int k = 0; k < K; k++) {
      double r = a[i][k];
      for (int j = 0; j < M; j++) {
        c[i][j] += r * b[k][j];
      }
    }
  }
  return c;
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
