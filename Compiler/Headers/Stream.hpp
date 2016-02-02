#ifndef STREAM_HPP_INCLUDED
    #define STREAM_HPP_INCLUDED

//Include
//{==============================================================================

#include <cstring>
#include <cassert>
#include <iostream>
#include "Vector.hpp"

//}==============================================================================

//Define
//{==============================================================================

#define DEBUG_STREAM

#ifdef DEBUG_STREAM

    #define OK_STREAM assert (ok ());

#else

    #define OK_STREAM

#endif /* DEBUG_STREAM */

//}==============================================================================

//Class: Stream
//{==============================================================================

template <typename Data_T>
class Stream
{
    private:
        size_t place_;

        Vector <Data_T> data_;

        bool ok   ();
        void dump ();

    public:
        Stream ();
        Stream (const Vector <Data_T> name);
        Stream (const Vector <Data_T> name, const size_t start);
        Stream (Stream <Data_T> &from);

        Data_T& operator [] (const size_t i);
        void    operator >> (Data_T& write);
        void    operator << (Data_T record);
        Stream <Data_T>& operator ++ ();
        Stream <Data_T>  operator ++ (int);
        Stream <Data_T>& operator -- ();
        Stream <Data_T>  operator -- (int);
        Stream <Data_T>& operator = (Stream <Data_T> &from);
        Stream <Data_T>& operator = (Vector <Data_T> &from);

        void push_back (const Data_T value);

        void seek  (const size_t value);
        bool check ();

        size_t          place () /*const*/;
        size_t          size  () /*const*/;
        Vector <Data_T> data  () /*const*/;
};

//}==============================================================================

template <typename Data_T>
Stream <Data_T> :: Stream ():
    place_ (0),
    data_  ()
    { OK_STREAM }

//===============================================================================

template <typename Data_T>
Stream <Data_T> :: Stream (const Vector <Data_T> name):
    place_ (0),
    data_  (name)
    { OK_STREAM }

//===============================================================================

template <typename Data_T>
Stream <Data_T> :: Stream (const Vector <Data_T> name, const size_t start):
    place_ (start),
    data_  (name)
    { OK_STREAM }

//===============================================================================

template <typename Data_T>
Stream <Data_T> :: Stream (Stream <Data_T> &from):
    place_ (0),
    data_  ()
    {
        OK_STREAM

        (*this) = from;

        OK_STREAM
    }

//===============================================================================

template <typename Data_T>
Data_T& Stream <Data_T> :: operator [] (const size_t i)
{
    OK_STREAM
    assert (i < data_.size ());

    return data_[i];
}

//===============================================================================

template <typename Data_T>
void Stream <Data_T> :: operator >> (Data_T& write)
{
    OK_STREAM

    write = data_[place_];

    place_++;

    OK_STREAM
}

//===============================================================================

template <typename Data_T>
void Stream <Data_T> :: operator << (Data_T record)
{
    OK_STREAM

    data_.push_back (record);

    OK_STREAM
}

//===============================================================================

template <typename Data_T>
Stream <Data_T>& Stream <Data_T> :: operator ++ ()
{
    OK_STREAM

    place_++;

    OK_STREAM

    return (*this);
}

//===============================================================================

template <typename Data_T>
Stream <Data_T> Stream <Data_T> :: operator ++ (int)
{
    OK_STREAM

    Stream <Data_T> oldStream (place_);

    place_++;

    OK_STREAM

    return oldStream;
}

//===============================================================================

template <typename Data_T>
Stream <Data_T>& Stream <Data_T> :: operator -- ()
{
    OK_STREAM

    place_--;

    OK_STREAM

    return (*this);
}

//===============================================================================

template <typename Data_T>
Stream <Data_T> Stream <Data_T> :: operator -- (int)
{
    OK_STREAM

    Stream <Data_T> oldStream (place_);

    place_--;

    OK_STREAM

    return oldStream;
}

//===============================================================================

template <typename Data_T>
Stream <Data_T>& Stream <Data_T> :: operator = (Stream <Data_T> &from)
{
    OK_STREAM

    data_  = from.data_;
    place_ = from.place_;

    OK_STREAM

    return (*this);
}

//===============================================================================

template <typename Data_T>
Stream <Data_T>& Stream <Data_T> :: operator = (Vector <Data_T> &from)
{
    OK_STREAM

    data_  = from.data_;
    place_ = 0;

    OK_STREAM

    return (*this);
}

//===============================================================================

template <typename Data_T>
void Stream <Data_T> :: push_back (const Data_T value)
{
    OK_STREAM

    data_.push_back (value);

    OK_STREAM
}

//===============================================================================

template <typename Data_T>
void Stream <Data_T> :: seek (const size_t value)
{
    OK_STREAM
    assert (value < data_.size ());

    place_ = value;

    OK_STREAM
}

//===============================================================================

template <typename Data_T>
bool Stream <Data_T> :: check ()
{
    OK_STREAM

    return (place_ < data_.size ());
}

//===============================================================================

template <typename Data_T>
size_t Stream <Data_T> :: place () /*const*/
{
    OK_STREAM

    return place_;
}

//===============================================================================

template <typename Data_T>
size_t Stream <Data_T> :: size () /*const*/
{
    OK_STREAM

    return data_.size ();
}

//===============================================================================

template <typename Data_T>
Vector <Data_T> Stream <Data_T> :: data () /*const*/
{
    OK_STREAM

    return data_;
}

//===============================================================================

template <typename Data_T>
bool Stream <Data_T> :: ok ()
{
    if (place_ > data_.size ()) return false;

    return true;
}

//===============================================================================

template <typename Data_T>
void Stream <Data_T> :: dump ()
{
    printf ("\n=============DUMP=============\n");

    printf ("Stream (%s) [%p]\n", ok ()? "ok" : "ERROR", (*this));

    printf ("size  = %d;\n", data_.size ());
    printf ("place = %d;\n", place_);

    printf ("==============================\n\n");
}

//===============================================================================

template <typename Data_T>
Stream <Data_T>& operator += (Stream <Data_T> &to, Stream <Data_T> &from);

template <typename Data_T>
Stream <Data_T>& operator += (Stream <Data_T> &to, Vector <Data_T> &from);

template <typename Data_T>
bool operator == (Stream <Data_T> &to, Stream <Data_T> &from);

template <typename Data_T>
bool operator == (Stream <Data_T> &to, Vector <Data_T> &from);

//===============================================================================

template <typename Data_T>
Stream <Data_T>& operator += (Stream <Data_T> &to, Stream <Data_T> &from)
{
    to.data_ += from.data_;

    return to;
}

//===============================================================================

template <typename Data_T>
Stream <Data_T>& operator += (Stream <Data_T> &to, Vector <Data_T> &from)
{
    to.data_ += from;

    return to;
}

//===============================================================================

template <typename Data_T>
bool operator == (Stream <Data_T> &to, Stream <Data_T> &from)
{
    return (to.data_ == from.data_);
}

//===============================================================================

template <typename Data_T>
bool operator == (Stream <Data_T> &to, Vector <Data_T> &from)
{
    return (to.data_ == from);
}

#endif /* STREAM_HPP_INCLUDED */
