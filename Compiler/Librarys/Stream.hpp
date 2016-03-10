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

#if defined (DEBUG_STREAM)

    #include "Debug.hpp"
    #define DO_STREAM(codeDebug, codeTest)  codeDebug
    #define OK_STREAM ok ();

#elif defined (TEST_STREAM)

    #include "Debug.hpp"
    #define DO_STREAM(codeDebug, codeTest)  codeTest
    #define OK_STREAM assert (ok ());

#elif defined (RELEASE_STREAM)

    #define DO_STREAM(codeDebug, codeTest)
    #define OK_STREAM

#else

    #error "Either DEBUG_STREAM or TEST_STREAM or RELEASE_STREAM MUST be defined"

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

    public:
        Stream ();
        Stream (const Vector <Data_T>& name);
        Stream (const Vector <Data_T>& name, const size_t start);
        Stream (const Stream <Data_T>& from);

        Data_T& operator [] (const size_t i);
        void    operator >> (Data_T& write);
        void    operator << (const Data_T& record);
        Stream <Data_T>& operator ++ ();
        Stream <Data_T>  operator ++ (int);
        Stream <Data_T>& operator -- ();
        Stream <Data_T>  operator -- (int);
        Stream <Data_T>& operator = (const Stream <Data_T>& from);
        Stream <Data_T>& operator = (const Vector <Data_T>& from);

        void push_back (const Data_T& value);

        void seek  (const size_t value);

        size_t           place ();
        size_t           size  ();
        Vector <Data_T>& data  ();

        bool ok   ();
        void dump ();
};

//}==============================================================================

template <typename Data_T>
Stream <Data_T> :: Stream ():
    place_ (0),
    data_  ()
    { OK_STREAM }

//===============================================================================

template <typename Data_T>
Stream <Data_T> :: Stream (const Vector <Data_T>& name):
    place_ (0),
    data_  (name)
    { OK_STREAM }

//===============================================================================

template <typename Data_T>
Stream <Data_T> :: Stream (const Vector <Data_T>& name, const size_t start):
    place_ (start),
    data_  (name)
    { OK_STREAM }

//===============================================================================

template <typename Data_T>
Stream <Data_T> :: Stream (const Stream <Data_T>& from):
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
void Stream <Data_T> :: operator << (const Data_T& record)
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
Stream <Data_T>& Stream <Data_T> :: operator = (const Stream <Data_T>& from)
{
    OK_STREAM

    data_  = from.data_;
    place_ = from.place_;

    OK_STREAM

    return (*this);
}

//===============================================================================

template <typename Data_T>
Stream <Data_T>& Stream <Data_T> :: operator = (const Vector <Data_T>& from)
{
    OK_STREAM

    data_  = from.data_;
    place_ = 0;

    OK_STREAM

    return (*this);
}

//===============================================================================

template <typename Data_T>
void Stream <Data_T> :: push_back (const Data_T& value)
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
size_t Stream <Data_T> :: place ()
{
    OK_STREAM

    return place_;
}

//===============================================================================

template <typename Data_T>
size_t Stream <Data_T> :: size ()
{
    OK_STREAM

    return data_.size ();
}

//===============================================================================

template <typename Data_T>
Vector <Data_T>& Stream <Data_T> :: data ()
{
    OK_STREAM

    return data_;
}

//===============================================================================

template <typename Data_T>
bool Stream <Data_T> :: ok ()
{
    if (place_ > data_.size ())
    {
        DO_STREAM({ throw "place_ > data_.size ()"; },
                  { return false; })
    }

    return true;
}

//===============================================================================

template <typename Data_T>
void Stream <Data_T> :: dump ()
{
    printf ("\n=============DUMP=============\n");

    printf ("Stream (%s) [%p]\n\n", ok ()? "ok" : "ERROR", this);

    printf ("   size  = %d;\n", data_.size ());
    printf ("   place = %d;\n\n", place_);

    for (size_t i = 0; i < data_.size (); i++)
    {
        std::cout << "[" << i << "]" << " " << "=" << " " << "|" << data_[i] << "|\n";
    }

    printf ("==============================\n\n");
}

//===============================================================================

//{==============================================================================

template <typename Data_T>
Stream <Data_T>& operator += (Stream <Data_T>& to, const Stream <Data_T>& from);

template <typename Data_T>
Stream <Data_T>& operator += (Stream <Data_T>& to, const Vector <Data_T>& from);

template <typename Data_T>
bool operator == (const Stream <Data_T>& to, const Stream <Data_T>& from);

template <typename Data_T>
bool operator == (const Stream <Data_T>& to, const Vector <Data_T>& from);

//}==============================================================================

//===============================================================================

template <typename Data_T>
Stream <Data_T>& operator += (Stream <Data_T>& to, const Stream <Data_T>& from)
{
    to.data_ += from.data_;

    return to;
}

//===============================================================================

template <typename Data_T>
Stream <Data_T>& operator += (Stream <Data_T>& to, const Vector <Data_T>& from)
{
    to.data_ += from;

    return to;
}

//===============================================================================

template <typename Data_T>
bool operator == (const Stream <Data_T>& to, const Stream <Data_T>& from)
{
    return (to.data_ == from.data_);
}

//===============================================================================

template <typename Data_T>
bool operator == (const Stream <Data_T>& to, const Vector <Data_T>& from)
{
    return (to.data_ == from);
}

#endif /* STREAM_HPP_INCLUDED */
