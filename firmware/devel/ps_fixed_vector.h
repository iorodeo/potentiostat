#ifndef FIXED_VECTOR_H
#define FIXED_VECTOR_H

namespace ps
{

    template<typename T, unsigned int n>
    class FixedVector;

    class BaseFixedVectorIter
    {
        public:

            BaseFixedVectorIter(int pos) : pos_(pos) {}

            bool operator!=(const BaseFixedVectorIter &other)
            {
                return pos_ != other.pos_;
            }

            const BaseFixedVectorIter& operator++()
            {
                ++pos_;
                return *this;
            }

        protected:
            int pos_;
    };

    template<typename T, unsigned int n>
    class RefFixedVectorIter : public BaseFixedVectorIter
    {
        public:

            RefFixedVectorIter(FixedVector<T,n> *vectorPtr, int pos)
                : vectorPtr_(vectorPtr) , BaseFixedVectorIter(pos)
            {}

            T& operator*();

        protected:

            FixedVector<T,n> *vectorPtr_;
    };


    template<typename T, unsigned int n>
    class ConstFixedVectorIter : public BaseFixedVectorIter 
    {
        public:

            ConstFixedVectorIter (const FixedVector<T,n> *vectorPtr, int pos) 
                : vectorPtr_(vectorPtr), BaseFixedVectorIter(pos) 
            {}

            T operator* () const;

        protected:

            const FixedVector<T,n> *vectorPtr_;
    };


    template<typename T, unsigned int n>
    class FixedVector 
    {
        public:

            FixedVector() {};

            unsigned int size() 
            { 
                return n;
            };

            T& operator[](int index) 
            {
                return data_[index];
            };

            void set(int index, T val) 
            {
                data_[index] = val;
            }

            T get(int index) const
            {
                return data_[index];
            }

            T& get(int index)
            {
                return data_[index];
            }

            const T& getConstRef(int index) const
            {
                return data_[index];
            }

            ConstFixedVectorIter<T,n> begin() const 
            {
                return ConstFixedVectorIter<T,n>(this,0); 
            };

            ConstFixedVectorIter<T,n> end() const
            { 
                return ConstFixedVectorIter<T,n>(this,n);
            };

            RefFixedVectorIter<T,n> begin()
            {
                return RefFixedVectorIter<T,n>(this,0);
            }

            RefFixedVectorIter<T,n> end()
            {
                return RefFixedVectorIter<T,n>(this,n);
            }

        protected:

            T data_[n];
    };

    template<typename T, unsigned int n>
    T ConstFixedVectorIter<T,n>::operator* () const
    {
        return vectorPtr_ -> get(pos_);
    }


    template<typename T, unsigned int n>
    T& RefFixedVectorIter<T,n>::operator* ()
    {
        return vectorPtr_ -> get(pos_);
    }

}


#endif
