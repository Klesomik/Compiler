#ifndef MEMORY_HPP_INCLUDED
    #define MEMORY_HPP_INCLUDED

#include <cstdio>
#include <cstring>

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

template <typename Data_T>
inline bool StdCmp (Data_T* to, Data_T* from, size_t size)
{
    return memcmp (to, from, size * sizeof (Data_T));
}

inline bool CmpObj (int*    to, int*    from, size_t size) { return StdCmp (to, from, size); }
inline bool CmpObj (char*   to, char*   from, size_t size) { return StdCmp (to, from, size); }
inline bool CmpObj (char**  to, char**  from, size_t size) { return StdCmp (to, from, size); }
inline bool CmpObj (double* to, double* from, size_t size) { return StdCmp (to, from, size); }
inline bool CmpObj (float*  to, float*  from, size_t size) { return StdCmp (to, from, size); }

template <typename Data_T>
inline void StdCmp (Data_T* to, Data_T* from, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (to[i] != from[i]) return false;
    }

    return true;
}

#endif /* MEMORY_HPP_INCLUDED */
