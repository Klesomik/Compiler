#ifndef VECTOR_HPP_INCLUDED
    #define VECTOR_HPP_INCLUDED

//{==============================================================================

#include <cstdio>
#include <cassert>
#include "Memory.hpp"

//new (size_t addres)

//}==============================================================================

//{==============================================================================

#define DEBUG_VECT

#ifdef DEBUG_VECT

    #define OK_VECT assert (ok ());

#endif

#ifdef TEST_VECT

    #define OK_VECT ok ();

#endif

#ifdef RELASE_VECT

    #define OK_VECT

#endif

//}==============================================================================

//{==============================================================================

template <typename Data_T>
class Vector
{
     private:
        static const size_t BASE_CAPACITY = 30;

        Data_T* data_;
        size_t capacity_, size_;

        void expand ();

        bool ok   ();
        void dump ();

     public:
        Vector ();
        Vector (const size_t mySize);
        Vector (const Vector&  from);
        Vector (const size_t mySize, const Data_T value);

        ~Vector ();

        void resize (const size_t mySize);

        Data_T& at (const size_t i);
        void push_back (const Data_T value);
        Data_T pop ();

        bool empty ();
        void clear ();
        Data_T& front ();
        Data_T& back ();
        void insert (const Data_T value, const size_t place);
        void erase  (const size_t place);
        void fill (const Data_T value);

        bool             operator == (const Vector <Data_T> &vect);
        Data_T&          operator [] (const size_t i);
        Vector <Data_T>& operator =  (const Vector <Data_T> &from);

        size_t capacity () /*const*/;
        size_t     size () /*const*/;
        Data_T*    data () /*const*/;
};

//}==============================================================================

template <typename Data_T>
void Vector <Data_T> :: dump ()
{
    printf ("\n=====================DUMP=====================\n");

    printf ("capacity = %d;\n", capacity_);
    printf ("size     = %d;\n",     size_);
    printf ("data     = 0x%p;\n",   data_);

    printf ("==============================================\n\n");
}

//===============================================================================

template <typename Data_T>
bool Vector <Data_T> :: ok ()
{
    if ((size_ > 0) && (data_ == nullptr) && (capacity_ > 0))
    {
        #ifdef DEBUG_VECT

            return false;

        #endif

        #ifdef TEST_VECT

            throw "size_ > 0 && data_ == nullptr && capacity_ > 0";

        #endif
    }

    else return true;
}

//===============================================================================

template <typename Data_T>
Vector <Data_T> :: Vector ():
    data_     (),
    capacity_ (),
    size_     ()
    {
        OK_VECT

        clear ();

        OK_VECT
    }

//===============================================================================

template <typename Data_T>
Vector <Data_T> :: Vector (const size_t mySize):
    data_     (nullptr),
    capacity_ (mySize),
    size_     (mySize)
    {
        data_ = new Data_T[capacity_];

        OK_VECT
    }

//===============================================================================

template <typename Data_T>
Vector <Data_T> :: Vector (const Vector& from):
    data_     (),
    capacity_ (),
    size_     ()
    {
        OK_VECT

        (*this) = from;

        OK_VECT
    }

//===============================================================================

template <typename Data_T>
Vector <Data_T> :: Vector (const size_t mySize, const Data_T value):
    data_     (new Data_T[capacity_]),
    capacity_ (mySize),
    size_     (mySize)
    {
        OK_VECT

        for (size_t i = 0; i < capacity_; i++) data_[i] = value;

        OK_VECT
    }

//===============================================================================

template <typename Data_T>
Vector <Data_T> :: ~Vector ()
{
    if (data_ != nullptr)
    {
        delete[] data_;
                 data_ = nullptr;
    }
}

//===============================================================================

template <typename Data_T>
void Vector <Data_T> :: resize (const size_t mySize)
{
    OK_VECT

    size_ = mySize;

    if (size_ > capacity_) expand ();

    OK_VECT
}

//===============================================================================

template <typename Data_T>
void Vector <Data_T> :: expand ()
{
    OK_VECT

    size_t old_capacity = capacity_;

    if (capacity_ == 0) capacity_ = BASE_CAPACITY;

    while (capacity_ < size_) capacity_ *= 2;

    Data_T* new_data = new Data_T[capacity_];

    CopyObj (new_data, data_, old_capacity);

    delete[] data_;
             data_ = new_data;

    OK_VECT
}

//===============================================================================

template <typename Data_T>
Data_T& Vector <Data_T> :: at (const size_t i)
{
    OK_VECT

    #ifdef DEBUG_VECT

        assert (i < size_);

    #endif

    #ifdef TEST_VECT

        throw "i < size_";

    #endif

    return data_[i];
}

//===============================================================================

template <typename Data_T>
void Vector <Data_T> :: push_back (const Data_T value)
{
    OK_VECT

    resize (size_ + 1);

    at (size_ - 1) = value;

    OK_VECT
}

//===============================================================================

template <typename Data_T>
Data_T Vector <Data_T> :: pop ()
{
    OK_VECT

    Data_T tmp = data_[size_];

    size_--;

    OK_VECT

    return tmp;
}

//===============================================================================

template <typename Data_T>
size_t Vector <Data_T> :: size () /*const*/
{
    OK_VECT

    return size_;
}

//===============================================================================

template <typename Data_T>
bool Vector <Data_T> :: empty ()
{
    OK_VECT

    return (size_ == 0);
}

//===============================================================================

template <typename Data_T>
void Vector <Data_T> :: clear ()
{
    OK_VECT

    size_     = 0;
    capacity_ = 0;

    OK_VECT
}

//===============================================================================

template <typename Data_T>
Data_T& Vector <Data_T> :: front ()
{
    OK_VECT

    return data_[0];
}

//===============================================================================

template <typename Data_T>
Data_T& Vector <Data_T> :: back ()
{
    OK_VECT

    #ifdef DEBUG_VECT

        assert (0 < size_);

    #endif

    #ifdef TEST_VECT

        throw "0 < size_";

    #endif

    return data_[size_ - 1];
}

//===============================================================================

template <typename Data_T>
void Vector <Data_T> :: insert (const Data_T value, const size_t place)
{
    OK_VECT

    resize (size_ + 1);

    for (size_t i = size_ - 2; i >= place; i--)
    {
        data_[i + 1] = data_[i];
    }

    data_[place] = value;

    OK_VECT
}

//===============================================================================

template <typename Data_T>
void Vector <Data_T> :: fill (const Data_T value)
{
    OK_VECT

    for (size_t i = 0; i < size_; i++) data_[i] = value;

    OK_VECT
}

//===============================================================================

template <typename Data_T>
bool Vector <Data_T> :: operator == (const Vector <Data_T> &vect)
{
    OK_VECT

    if (size_ != vect.size_) return false;

    for (size_t i = 0; i < size_; i++)
    {
        if (data_[i] != vect.data_[i])
            return false;
    }

    OK_VECT

    return true;
}

//===============================================================================

template <typename Data_T>
Data_T& Vector <Data_T> :: operator [] (const size_t i)
{
    OK_VECT

    #ifdef DEBUG_VECT

        assert (i < size_);

    #endif

    #ifdef TEST_VECT

        throw "i < size_";

    #endif

    return data_[i];
}

//===============================================================================

template <typename Data_T>
Vector <Data_T>& Vector <Data_T> :: operator = (const Vector <Data_T> &from)
{
    OK_VECT

    capacity_ = from.capacity_;
    size_     = from.size_;

    data_ = new Data_T[capacity_];

    CopyObj (data_, from.data_, capacity_);

    OK_VECT

    return (*this); //
}

//===============================================================================

template <typename Data_T>
size_t Vector <Data_T> :: capacity () /*const*/
{
    OK_VECT

    return capacity_;
}

//===============================================================================

template <typename Data_T>
Data_T* Vector <Data_T> :: data () /*const*/
{
    OK_VECT

    return data_;
}

#endif /* VECTOR_H_INCLUDED */
