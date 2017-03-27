#ifndef BoaToken_hpp

#define BoaToken_hpp

#include <cstdio>
#include <iostream>

#define BOA(id, params, name, word, comp, cpu) name = id,

enum BoaLexemes
{
    #include "BoaList.hpp"
};

#undef BOA

struct BoaToken
{
    int type;
    int value;

    BoaToken ();
    BoaToken (const int setType);
    BoaToken (const int setType, const int setValue);
};

BoaToken :: BoaToken ():
    type  (),
    value ()
    {}

BoaToken :: BoaToken (const int setType):
    type  (setType),
    value ()
    {}

BoaToken :: BoaToken (const int setType, const int setValue):
    type  (setType),
    value (setValue)
    {}

std::ostream& operator << (std::ostream& os, const BoaToken& m);

std::ostream& operator << (std::ostream& os, const BoaToken& value)
{
    #define BOA(id, params, name, word, comp, cpu) \
    case id: { return os << std::string (word); }

    switch (value.type)
    {
        #include "BoaList.inl"

        default: { throw "operator << was broken"; }
    }

    #undef BOA
}

#endif /* BoaToken_hpp */
