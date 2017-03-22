// ----------------------------------------------------------------------------
// TemplatedMultiArray.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef TEMPLATED_MULTI_ARRAY_H
#define TEMPLATED_MULTI_ARRAY_H
#include "Arduino.h"
#include "Streaming.h"
#include "Array.h"


template <typename T,
          unsigned int X_SIZE,
          unsigned int Y_SIZE,
          unsigned int Z_SIZE>
class TemplatedMultiArray
{
public:
  TemplatedMultiArray();
  void print();
private:
  Array<T, X_SIZE> x_;
  Array<T, Y_SIZE> y_;
  Array<T, Z_SIZE> z_;
  Array<T, X_SIZE+1> x2_;
  template <unsigned int ARRAY_SIZE>
  void printArray(Array<T,ARRAY_SIZE> array);
};
#include "TemplatedMultiArrayDefinitions.h"

#endif
