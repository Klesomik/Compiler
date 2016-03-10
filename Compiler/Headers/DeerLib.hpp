#ifndef DeerLib_hpp
    #define DeerLib_hpp

//{==============================================================================

#include "..//Librarys//LogHTML.hpp"

//}==============================================================================

//{==============================================================================

template <typename Data_T>
bool check (Stream <Data_T>& example);

template <typename Data_T>
size_t avaliable (Stream <Data_T>& example);

template <typename Data_T>
bool check_next (Stream <Data_T>& example, const std::initializer_list <Data_T>& next);

template <typename Data_T>
bool compare (Stream <Data_T>& example, const Data_T& element, const size_t shift);

//}==============================================================================

//===============================================================================

template <typename Data_T>
bool check (Stream <Data_T>& example)
{
    return (example.place () < example.size ());
}

//===============================================================================

template <typename Data_T>
size_t avaliable (Stream <Data_T>& example)
{
    return (example.size () - example.place ());
}

//===============================================================================

template <typename Data_T>
bool check_next (Stream <Data_T>& example, const std::initializer_list <Data_T>& next)
{
    return check_next (next.begin (), next.size ());
}

//===============================================================================

template <typename Data_T>
bool check_next (Stream <Data_T>& example, const Data_T next[], const size_t len)
{
    if (avaliable (example) < len) return false;

    for (size_t i = 0; i < len; i++)
    {
        if (example[example.place () + i] != next[i]) return false;
    }

    return true;
}

//===============================================================================

template <typename Data_T>
bool compare (Stream <Data_T>& example, const Data_T& element, const size_t shift)
{
    if (shift < avaliable (example)) return false;

    if (example[example.place () + shift] != element) return false;

    return true;
}

#endif
