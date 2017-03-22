#Array

Authors:

    Peter Polidoro <polidorop@janelia.hhmi.org>

License:

    BSD

An array container similar to the C++
[std::array](http://www.cplusplus.com/reference/array/array/), with
some [std::vector](http://www.cplusplus.com/reference/vector/vector/)
methods added. The maximum size is fixed as a template parameter, but
the size is variable, like a vector. Values can be pushed and popped
and the size adjusts accordingly. The data are stored internally as a
statically allocated c style array. Care must be taken not to
dereference an empty array or access elements beyond bounds.

This library is very similar to
[Vector](https://github.com/janelia-arduino/Vector), however Vector
stores data externally, outside the container, and this library stores
data internally. The pointer to the external memory causes the Vector
container to use more memory than this container, but storing the data
internally makes it necessary to use the maximum size as a class
template parameter.

## Array vs Vector

###Array

```c++
const int ELEMENT_COUNT = 5;
Array<int,ELEMENT_COUNT> array;
array.push_back(77);
```

###Vector

```c++
const int ELEMENT_COUNT = 5;
int storage_array[ELEMENT_COUNT_MAX];
Vector<int> vector(storage_array);
vector.push_back(77);
```

[Usage Examples](./examples)

##Install Library Dependencies

[arduino-libraries](https://github.com/janelia-arduino/arduino-libraries)
