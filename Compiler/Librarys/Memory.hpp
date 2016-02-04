#ifndef MEMORY_HPP_INCLUDED
    #define MEMORY_HPP_INCLUDED

#include <cstdio>

template <typename Data_T>
inline void StdCpy (Data_T* to, Data_T* from, size_t size)
{
    memcpy (to, from, size * sizeof (Data_T));
}

inline void CopyObj (int*    to, int*    from, size_t size) { StdCpy (to, from, size); }
inline void CopyObj (char*   to, char*   from, size_t size) { StdCpy (to, from, size); }
inline void CopyObj (char**  to, char**  from, size_t size) { StdCpy (to, from, size); }
inline void CopyObj (double* to, double* from, size_t size) { StdCpy (to, from, size); }
inline void CopyObj (float*  to, float*  from, size_t size) { StdCpy (to, from, size); }

template <typename Data_T>
inline void CopyObj (Data_T* to, Data_T* from, size_t size)
{
    for (size_t i = 0; i < size; i++) to[i] = from[i];
}

#endif /* MEMORY_HPP_INCLUDED */
