#ifndef ARRAY2D_H
#define ARRAY2D_H


template <typename T>
class array2d {

  unsigned width;
  unsigned height;
  T* pArray;

public:
  array2d(unsigned width, unsigned height) {
    this->width = width;
    this->height = height;
    this->pArray = new T[width * height];
  }
  array2d(unsigned width, unsigned height, T init) {
    this->width = width;
    this->height = height;
    this->pArray = new T[width * height];
    for (int i = 0; i < width * height; i++) {
      this->pArray[i] = init;
    }
  }

  // ~array2d() {
  //   delete[] this->pArray;
  // }

  unsigned h() {
    return this->height;
  }

  unsigned w() {
    return this->width;
  }

  T* operator () (unsigned x) {
    return this->pArray + x;
  }

  const T& operator () (unsigned x,unsigned y) const {
    return pArray[ x*this->width + y ];
  }

  T& operator () (unsigned x,unsigned y) {
    return pArray[ x*this->width + y ];
  }

  void operator () (unsigned x,unsigned y, T val) const {
    pArray[ x*this->width + y ] = val;
  }

  void operator () (unsigned x,unsigned y, T val) {
    pArray[ x*this->width + y ] = val;
  }

  array2d operator*(const array2d& b) {
    int N = this->height;
    int K = this->width;
    int M = b.width;
    array2d c(N, M);
    for (int i = 0; i < N; i++) {
      for (int k = 0; k < K; k++) {
        T r = (*this)(i, k);  //a[i][k];
        for (int j = 0; j < M; j++) {
          //c[i][j] += r * b[k][j];
          c(i, j, c(i, j) + r * b(k, j));
        }
      }
    }
    return c;
  }

  void mult(const array2d& b, array2d& c) {
    int N = this->height;
    int K = this->width;
    int M = b.width;
    for (int i = 0; i < N; i++) {
      for (int k = 0; k < K; k++) {
        T r = this->pArray[ i*K + k ];  //a[i][k];
        for (int j = 0; j < M; j++) {
          //c[i][j] += r * b[k][j];
          c(i, j, c(i, j) + r * b(k, j));
        }
      }
    }
  }

  void testPrint() {
    std::cout << "HI:";
    std::cout << "[ ";
    for (int i = 0; i < width * height; i++) {
      std::cout << this->pArray[i] << ", ";
    }
    std::cout << "]" << std::endl;
  }

};

#endif
