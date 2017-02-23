#ifndef STREAM_NEW_HPP_INCLUDED
    #define STREAM_NEW_HPP_INCLUDED

#include <bits/stdc++.h>

#define Vector_t std::vector <Data_T>
#define Stream_t Stream <Data_T>

template <typename Data_T>
class Stream : public std::vector <Data_T>
{
    public:
        Stream ();
        Stream (int size_data);
        Stream (const Data_T* name, const size_t size_data);
        Stream (const Vector_t& name);
        Stream (const Vector_t& name, const size_t start);
        Stream (const Stream_t& from);

        bool ok ();
        void dump ();

        void seek (const size_t value);

        Stream_t& operator = (const Stream_t& from);

        void operator >> (Data_T& write);
        void operator << (const Data_T& record);

        Stream_t& operator += (const size_t jump);

        Stream_t& operator ++ ();
        Stream_t  operator ++ (int);
        Stream_t& operator -- ();
        Stream_t  operator -- (int);

        Data_T& current ();

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
Stream <Data_T>::Stream (int size_data):
    Vector_t (size_data),
    place_   (0)
{
}

template <typename Data_T>
Stream <Data_T>::Stream (const Data_T* name, const size_t size_data):
    Vector_t (name, name + size_data),
    place_ (0)
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
    printf ("\n=============DUMP=============\n");

    printf ("Stream (%s) [%p]\n\n", ok ()? "ok" : "ERROR", this);

    printf ("   size  = %zu;\n", Vector_t::size ());
    printf ("   place = %zu;\n\n", place_);

    for (size_t i = 0; i < Vector_t::size (); i++)
        std::cout << "[" << i << "]" << " " << "=" << " " << "|" << Vector_t::at (i) << "|\n";

    printf ("==============================\n\n");
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
    Stream_t old;

    old.place_ = place_;

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
    Stream_t old;

    old.place_ = place_;

    place_--;

    return old;
}

template <typename Data_T>
Data_T& Stream <Data_T>::current ()
{
    return Vector_t::operator [] (place_);
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

template <typename Data_T>
Stream <Data_T>& operator += (Stream <Data_T>& to, const Stream <Data_T>& from);

template <typename Data_T>
Stream <Data_T>& operator += (Stream <Data_T>& to, const std::vector <Data_T>& from);

template <typename Data_T>
Stream <Data_T>& operator += (Stream <Data_T>& to, const std::string& from);

template <typename Data_T>
bool operator == (const Stream <Data_T>& to, const Stream <Data_T>& from);

template <typename Data_T>
bool operator == (const Stream <Data_T>& to, const std::vector <Data_T>& from);

void CopyFile (Stream <char>& example, FILE* input);
void GetLine (std::istream& in, Stream <char>& example, const char delim);

template <typename Data_T>
Stream <Data_T>& operator += (Stream <Data_T>& to, const Stream <Data_T>& from)
{
    to.data_ += from.data_;

    return to;
}

template <typename Data_T>
Stream <Data_T>& operator += (Stream <Data_T>& to, const std::vector <Data_T>& from)
{
    to += from;

    return to;
}

template <typename Data_T>
Stream <Data_T>& operator += (Stream <Data_T>& to, const std::string& from)
{
    for (int i = 0; i < from.size (); i++)
        to.push_back (from[i]);

    return to;
}

template <typename Data_T>
bool operator == (const Stream <Data_T>& to, const Stream <Data_T>& from)
{
    return (to.data_ == from.data_);
}

template <typename Data_T>
bool operator == (const Stream <Data_T>& to, const std::vector <Data_T>& from)
{
    return (to.data_ == from);
}

void CopyFile (Stream <char>& example, FILE* input)
{
    for (char symbol = 0; fscanf (input, "%c", &symbol) != EOF;)
        example.push_back (symbol);
}

void GetLine (std::istream& in, Stream <char>& example, const char delim)
{
    std::string data;
    getline (in, data, delim);

    Stream <char> tmp (data.c_str (), data.size ());

    example = tmp;
}

#undef Vector_t
#undef Stream_t

#endif /* STREAM_NEW_HPP_INCLUDED */
