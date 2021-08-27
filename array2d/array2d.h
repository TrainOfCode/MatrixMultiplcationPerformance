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

  // ~array2d() {
  //   delete[] this->pArray;
  // }

  unsigned h() {
    return this->height;
  }

  unsigned w() {
    return this->width;
  }

  const T& operator () (unsigned x,unsigned y) const {
    return pArray[ y*this->width + x ];
  }

  T& operator () (unsigned x,unsigned y) {
    return pArray[ y*this->width + x ];
  }

  void operator () (unsigned x,unsigned y, T val) const {
    pArray[ y*this->width + x ] = val;
  }

  void operator () (unsigned x,unsigned y, T val) {
    pArray[ y*this->width + x ] = val;
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
          T l = c(i, j);
          l += r * b(k, j);
          c(i, j, l);
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
        T r = this->pArray[ k*K + i ];  //a[i][k];
        for (int j = 0; j < M; j++) {
          //c[i][j] += r * b[k][j];
          c(i, j, c(i, j) + r * b(k, j));
        }
      }
    }
  }

};

#endif
