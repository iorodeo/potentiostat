#include "Arduino.h"
#include "Streaming.h"
#include "Array.h"
#include "Constants.h"
#include "MultiArray.h"
#include "TemplatedMultiArray.h"


MultiArray multi_array;
TemplatedMultiArray<int,
                    constants::X_SIZE,
                    constants::Y_SIZE,
                    constants::Z_SIZE> templated_multi_array;

void setup()
{
  Serial.begin(constants::baudrate);
  delay(1000);

  Serial << "multi_array:" << endl;
  multi_array.print();

  Serial << "templated_multi_array:" << endl;
  templated_multi_array.print();
}


void loop()
{
}
