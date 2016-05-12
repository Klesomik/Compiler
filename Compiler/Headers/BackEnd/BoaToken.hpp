#ifndef BoaToken_hpp
    #define BoaToken_hpp

//{==============================================================================

#include <cstdio>
#include <iostream>

//}==============================================================================

//{==============================================================================

#define BOA_1(id, params, name, word, comp, cpu) name = id,
#define BOA_2(id, params, name, word, comp, cpu) name = id,
#define BOA_3(id, params, name, word, comp, cpu) name = id,
#define BOA_4(id, params, name, word, comp, cpu) name = id,

enum BoaLexemes {
                    #include "BoaList.hpp"
                };

#undef BOA_1
#undef BOA_2
#undef BOA_3
#undef BOA_4

//}==============================================================================

//{==============================================================================

struct BoaToken
{
    int type;
    int value;

    BoaToken ();
    BoaToken (const int setType);
    BoaToken (const int setType, const int setValue);
};

//}==============================================================================

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
    #define BOA_1(id, params, name, word, comp, cpu) \
    case id: { return os << std::string (word); }

    #define BOA_2(id, params, name, word, comp, cpu) \
    case id: { return os << std::string (word); }

    #define BOA_3(id, params, name, word, comp, cpu) \
    case id: { return os << std::string (word); }

    #define BOA_4(id, params, name, word, comp, cpu) \
    case id: { return os << std::string (word); }

    switch (value.type)
    {
        #include "BoaList.hpp"

        default: { throw "operator << was broken"; }
    }

    #undef BOA_1
    #undef BOA_2
    #undef BOA_3
    #undef BOA_4
}

#endif
