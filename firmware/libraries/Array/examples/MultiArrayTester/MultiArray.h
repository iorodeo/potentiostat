// ----------------------------------------------------------------------------
// MultiArray.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef MULTI_ARRAY_H
#define MULTI_ARRAY_H
#include "Arduino.h"
#include "Streaming.h"
#include "Array.h"
#include "Constants.h"

class MultiArray
{
public:
  MultiArray();
  void print();
private:
  Array<int, constants::X_SIZE> x_;
  Array<int, constants::Y_SIZE> y_;
  Array<int, constants::Z_SIZE> z_;
};

#endif
