const T& array2d<T>::operator () (unsigned x,unsigned y) const {
  return pArray[ y*this->width + x ];
}
T& array2d<T>::operator () (unsigned x,unsigned y) {
  return pAr[ y*this->width + x ];
}
