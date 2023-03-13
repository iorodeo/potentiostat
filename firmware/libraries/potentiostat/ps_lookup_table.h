#ifndef PS_LOOKUP_TABLE_H
#define PS_LOOKUP_TABLE_H
#include "Array.h"

namespace ps
{

    template<typename T, size_t SIZE>
    class LookupTable
    {
        public:
            
            LookupTable();
            T& operator[](const size_t ind);
            T  operator[](const size_t ind) const;
            T getValue(T pos) const;  // pos >= 0  and pos < SIZE - 1 

        protected:

            Array<T,SIZE> data_;
    };


    template<typename T, size_t SIZE>
    LookupTable<T,SIZE>::LookupTable()
    {
        T dummy = {};
        data_.fill(dummy);
    }


    template<typename T, size_t SIZE>
    T & LookupTable<T,SIZE>::operator[](const size_t ind)
    {
        return data_[ind];
    }

    
    template<typename T, size_t SIZE>
    T LookupTable<T,SIZE>::operator[](const size_t ind) const
    {
        return data_[ind];
    }


    template<typename T, size_t SIZE>
    T LookupTable<T,SIZE>::getValue(T pos) const
    {
        T value;
        if (pos < T(0))
        {
            value = data_[0];
        }
        else if (pos > T(SIZE-1))
        {
            value = data_[SIZE-1];
        }
        else
        {
            size_t ind = size_t(pos);
            value = (data_[ind+1] - data_[ind])*(pos - T(ind)) + data_[ind];
        }
        return value;
    }
}

#endif
