#ifndef PS_CIRCULAR_BUFFER_H
#define PS_CIRCULAR_BUFFER_H
#include <Arduino.h>
#include "Array.h"

namespace ps
{
    template<typename T, size_t MAX_SIZE>
    class CircularBuffer
    {

        public:

            CircularBuffer();
            T& front();
            T& back();
            void push_back(const T &value);
            void push_front(const T &value);
            void pop_front();
            void pop_back();
            void clear();
            bool empty() const;
            size_t size() const;
            size_t max_size() const;
            size_t pos_front() const;
            size_t pos_back() const;

        protected:

            Array<T,MAX_SIZE> data_;

            size_t  pos_front_ = 0;
            size_t  pos_back_  = 0;

    };


    template<typename T, size_t MAX_SIZE>
    CircularBuffer<T,MAX_SIZE>::CircularBuffer() 
    {
        T dummy = T();
        data_.fill(dummy);
    };


    template<typename T, size_t MAX_SIZE>
    T& CircularBuffer<T,MAX_SIZE>::front()
    {
        return data_[pos_front_];
    }


    template<typename T, size_t MAX_SIZE>
    T& CircularBuffer<T,MAX_SIZE>::back()
    {
        return data_[pos_back_];
    }


    template<typename T, size_t MAX_SIZE>
    void CircularBuffer<T,MAX_SIZE>::push_back(const T &value)
    {
        if (size() < (MAX_SIZE - 1))
        {
            pos_back_ = (pos_back_ + 1)%MAX_SIZE; 
            data_[pos_back_] = value;
        }
    }


    template<typename T, size_t MAX_SIZE>
    void CircularBuffer<T,MAX_SIZE>::push_front(const T &value)
    {
        if (size() < (MAX_SIZE - 1))
        {
            if (pos_front_ > 0)
            {
                pos_front_--;
            }
            else
            {
                pos_front_ = MAX_SIZE-1;
            }
            data_[pos_front_] = value;
        }
    }


    template<typename T, size_t MAX_SIZE>
    void CircularBuffer<T,MAX_SIZE>::pop_front()
    {
        if (size() > 0)
        {
            pos_front_ = (pos_front_ + 1)%MAX_SIZE; 
        }
    }


    template<typename T, size_t MAX_SIZE>
    void CircularBuffer<T,MAX_SIZE>::pop_back()
    {
        if (size() > 0)
        {
            if (pos_back_ > 0)
            {
                pos_back_--;
            }
            else
            {
                pos_back_ = MAX_SIZE - 1;
            }
        }
    }


    template<typename T, size_t MAX_SIZE>
    void CircularBuffer<T,MAX_SIZE>::clear()
    {
        pos_front_ = 0;
        pos_back_ = 0;
    }


    template<typename T, size_t MAX_SIZE>
    bool CircularBuffer<T,MAX_SIZE>::empty() const
    {
        return (size() == 0);
    }


    template<typename T, size_t MAX_SIZE>
    size_t CircularBuffer<T,MAX_SIZE>::size() const
    {
        if (pos_front_ <= pos_back_)
        {
            return pos_back_ - pos_front_;
        }
        else
        {
            return MAX_SIZE - pos_front_ + pos_back_;
        }
    }


    template<typename T, size_t MAX_SIZE> 
    size_t CircularBuffer<T,MAX_SIZE>::max_size() const
    {
        return MAX_SIZE;
    }


    template<typename T, size_t MAX_SIZE>
    size_t CircularBuffer<T,MAX_SIZE>::pos_front() const
    {
        return pos_front_;
    }


    template<typename T, size_t MAX_SIZE>
    size_t CircularBuffer<T,MAX_SIZE>::pos_back() const
    {
        return pos_back_;
    }


} // namespace ps

#endif
