#ifndef STACK_H_INCLUDED
    #define STACK_H_INCLUDED

//{==============================================================================

#include "Vector.hpp"

//}==============================================================================

//{==============================================================================

template <typename Data_T>
class Stack
{
    private:
        Vector <Data_T> data_;

    public:
        Stack ();
        Stack (const Stack &from);

        void push  (const Data_T& value);
        Data_T pop ();

        Data_T& top ();
        size_t size ();
        void clear  ();
        bool empty  ();

        Data_T& operator [] (const size_t i);

        void dump ();
};

//}==============================================================================

template <typename Data_T>
Stack <Data_T> :: Stack ():
    data_ ()
    {}

//===============================================================================

template <typename Data_T>
Stack <Data_T> :: Stack (const Stack &from)
    { (*this) = from; }

//===============================================================================

template <typename Data_T>
void Stack <Data_T> :: push (const Data_T& value)
{ data_.push_back (value); }

//===============================================================================

template <typename Data_T>
Data_T Stack <Data_T> :: pop ()
{
    Data_T answer = data_.back ();

    data_.resize (size () - 1);

    return answer;
}

//===============================================================================

template <typename Data_T>
size_t Stack <Data_T> :: size ()
{ return data_.size (); }

//===============================================================================

template <typename Data_T>
Data_T& Stack <Data_T> :: top ()
{ return data_.back (); }

//===============================================================================

template <typename Data_T>
void Stack <Data_T> :: clear ()
{ data_.clear (); }

//===============================================================================

template <typename Data_T>
bool Stack <Data_T> :: empty ()
{ return data_.empty (); }

//===============================================================================

template <typename Data_T>
Data_T& Stack <Data_T> :: operator [] (const size_t i)
{
    return data_[i];
}

//===============================================================================

template <typename Data_T>
void Stack <Data_T> :: dump ()
{
}

#endif /* STACK_H_INCLUDED */
