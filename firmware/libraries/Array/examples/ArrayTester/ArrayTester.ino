#include "Arduino.h"
#include "Streaming.h"
#include "Array.h"


const int BAUDRATE = 9600;

const int ELEMENT_COUNT = 5;

void printArray(const int (&array)[ELEMENT_COUNT])
{
  Array<int,ELEMENT_COUNT> array_copy(array);
  Serial << array_copy << endl;
}

Array<int,ELEMENT_COUNT> generateArray()
{
  Array<int,ELEMENT_COUNT> array;
  for (int i=0; i<ELEMENT_COUNT; i++)
  {
    array[i] = (i+1)*3;
  }
  return array;
}

Array<int,ELEMENT_COUNT> doubleElements(Array<int,ELEMENT_COUNT> & array)
{
  Array<int,ELEMENT_COUNT> array_doubled;
  for (int i=0; i<ELEMENT_COUNT; i++)
  {
    array_doubled[i] = array[i]*2;
  }
  return array_doubled;
}

void setup()
{
  Serial.begin(BAUDRATE);
  delay(1000);

  Array<int,ELEMENT_COUNT> array;
  array.push_back(5);
  array.push_back(4);
  array.push_back(3);
  array.push_back(2);
  array.push_back(1);
  array.push_back(0);
  array.pop_back();
  Serial << "array:" << endl;
  Serial << array << endl;

  const int array_simple[ELEMENT_COUNT] = {15,14,13,12,11};
  Serial << "array_simple:" << endl;
  printArray(array_simple);

  Array<int,ELEMENT_COUNT> array_copy(array_simple);
  Serial << "array_copy:" << endl;
  Serial << array_copy << endl;

  Array<int,ELEMENT_COUNT> array_initialized(ELEMENT_COUNT);
  Serial << "array_initialized:" << endl;
  Serial << array_initialized << endl;

  array_initialized.fill(37);
  Serial << "array_initialized.fill(37):" << endl;
  Serial << array_initialized << endl;

  array_initialized.fill(array_simple);
  Serial << "array_initialized.fill(array_simple):" << endl;
  Serial << array_initialized << endl;

  array_initialized[3] = 666;
  Serial << "array_initialized[3] = 666:" << endl;
  Serial << array_initialized << endl;

  Array<int,ELEMENT_COUNT> array_generated = generateArray();
  Serial << "array_generated:" << endl;
  Serial << array_generated << endl;

  Array<int,ELEMENT_COUNT> array_doubled = doubleElements(array_generated);
  Serial << "array_doubled:" << endl;
  Serial << array_doubled << endl;

  int out_of_bounds = array_doubled[ELEMENT_COUNT+1];
  Serial << "out_of_bounds: " << out_of_bounds << endl;

  out_of_bounds = array_doubled.at(ELEMENT_COUNT+1);
  Serial << "out_of_bounds:" << out_of_bounds << endl;

  // fill with value of a different type
  Array<int,ELEMENT_COUNT> array_filled;
  long fill_value = 123;
  array_filled.fill(fill_value);
  Serial << "array_filled:" << endl;
  Serial << array_filled << endl;

  // initialize with array of different size and type
  Array<long,ELEMENT_COUNT*2> array_copy2(array_simple);
  Serial << "array_copy2:" << endl;
  Serial << array_copy2 << endl;
  Serial << "array_copy2.max_size():" << endl;
  Serial << array_copy2.max_size() << endl;

  // initialize with another array instance
  Array<size_t,ELEMENT_COUNT*3> array_copy3(array_copy2);
  Serial << "array_copy3:" << endl;
  Serial << array_copy3 << endl;
  Serial << "array_copy3.max_size():" << endl;
  Serial << array_copy3.max_size() << endl;

  // get pointer to raw data
  size_t * array_copy3_ptr = array_copy3.data();
  size_t index = 2;
  if (index < array_copy3.size())
  {
    Serial << "array_copy3_ptr[index]:" << endl;
    Serial << array_copy3_ptr[index] << endl;
  }
}


void loop()
{
}
