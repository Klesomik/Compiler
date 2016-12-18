#ifndef STREAM_NEW_HPP_INCLUDED
    #define STREAM_NEW_HPP_INCLUDED

#include <bits/stdc++.h>

#define Vector_t std::vector <Data_T>
#define Stream_t Stream <Data_T>

template <typename Data_T>
class Stream : public Vector_t
{
    public:
        Stream ();
        Stream (const Vector_t& name);
        Stream (const Vector_t& name, const size_t start);
        Stream (const Stream_t& from);

        bool ok ();
        void dump ();

        void seek (const size_t value);

        Stream_t& operator = (const Stream_t& from);
        Stream_t& operator = (const Vector_t& from);

        void operator >> (Data_T& write);
        void operator << (const Data_T& record);

        Stream_t& operator += (const size_t jump);

        Stream_t& operator ++ ();
        Stream_t  operator ++ (int);
        Stream_t& operator -- ();
        Stream_t  operator -- (int);

        size_t& place ();

        bool check       ();
        size_t avaliable ();
        bool check_next  (const std::initializer_list <Data_T>& next);
        bool check_next  (const Data_T next[], const size_t len);
        bool compare     (const Data_T& element, const size_t shift);

    private:
        size_t place_;
};

template <typename Data_T>
Stream_t::Stream ():
    Vector_t (),
    place_   (0)
{
}

template <typename Data_T>
Stream_t::Stream (const Vector_t& name):
    Vector_t (name),
    place_   (0)
{
}

template <typename Data_T>
Stream_t::Stream (const Vector_t& name, const size_t start):
    Vector_t (name),
    place_   (start)
{
}

template <typename Data_T>
Stream_t::Stream (const Stream_t& from):
    Vector_t (),
    place_   (0)
{
    (*this) = from;
}

template <typename Data_T>
bool Stream_t::ok ()
{
    return true;
}

template <typename Data_T>
void Stream_t::dump ()
{
}

template <typename Data_T>
void Stream_t::seek (const size_t value)
{
    place_ = value;
}

template <typename Data_T>
Stream_t& Stream_t::operator = (const Stream_t& from)
{
    Vector_t::operator = (from);

    place_ = from.place_;

    return (*this);
}

template <typename Data_T>
Stream_t& Stream_t::operator = (const Vector_t& from)
{
    Vector_t::operator = (from);

    place_ = 0;

    return (*this);
}

template <typename Data_T>
void Stream_t::operator >> (Data_T& write)
{
    write = Vector_t::operator [] (place_);

    place_++;
}

template <typename Data_T>
void Stream_t::operator << (const Data_T& record)
{
    Vector_t::push_back (record);
}

template <typename Data_T>
Stream_t& Stream_t::operator += (const size_t jump)
{
    place_ += jump;
}

template <typename Data_T>
Stream_t& Stream_t::operator ++ ()
{
    place_++;

    return (*this);
}

template <typename Data_T>
Stream_t Stream_t::operator ++ (int)
{
    Stream_t old (place_);

    place_++;

    return old;
}

template <typename Data_T>
Stream_t& Stream_t::operator -- ()
{
    place_--;

    return (*this);
}

template <typename Data_T>
Stream_t Stream_t::operator -- (int)
{
    Stream_t old (place_);

    place_--;

    return old;
}

template <typename Data_T>
size_t& Stream_t::place ()
{
    return place_;
}

template <typename Data_T>
bool Stream_t::check ()
{
    return (place_ < Vector_t::size ());
}

template <typename Data_T>
size_t Stream_t::avaliable ()
{
    return (Vector_t::size () - place_);
}

template <typename Data_T>
bool Stream_t::check_next (const std::initializer_list <Data_T>& next)
{
    return check_next (next.begin (), next.size ());
}

template <typename Data_T>
bool Stream_t::check_next (const Data_T next[], const size_t len)
{
    if (avaliable () < len) return false;

    for (size_t i = 0; i < len; i++)
    {
        if (Vector_t::operator [] (place_ + i) != next[i]) return false;
    }

    return true;
}

template <typename Data_T>
bool Stream_t::compare (const Data_T& element, const size_t shift)
{
    if (shift < avaliable ()) return false;

    if (Vector_t::operator [] (place_ + shift) != element) return false;

    return true;
}

#undef Vector_t
#undef Stream_t

#endif /* STREAM_NEW_HPP_INCLUDED */
