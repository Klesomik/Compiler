#ifndef TOKEN_HPP
    #define TOKEN_HPP

//{==============================================================================

#include <cstdio>
#include <iostream>

//}==============================================================================

//{==============================================================================

#define DEER_0(id, name, word, fontcolor, color, fillcolor, shape, style, code) name = id,
#define DEER_1(id, name, word, fontcolor, color, fillcolor, shape, style, code) name = id,
#define DEER_2(id, name, word, fontcolor, color, fillcolor, shape, style, code) name = id,

enum Lexemes
{
    #include "CList.hpp"
};

#undef DEER_0
#undef DEER_1
#undef DEER_2

//}==============================================================================

//{==============================================================================

struct Token
{
    int  type;
    int value;
    int  line;

    Token ();
    Token (const int setType);
    Token (const int setType, const int setValue);
    Token (const int setType, const int setValue, const int setLine);
    Token (const Token& setToken);
};

//}==============================================================================

Token :: Token ():
    type  (),
    value (),
    line  ()
    {}

//===============================================================================

Token :: Token (const int setType):
    type  (setType),
    value (),
    line  ()
    {}

//===============================================================================

Token :: Token (const int setType, const int setValue):
    type  (setType),
    value (setValue),
    line  ()
    {}

//===============================================================================

Token :: Token (const int setType, const int setValue, const int setLine):
    type  (setType),
    value (setValue),
    line  (setLine)
    {}

//===============================================================================

Token :: Token (const Token& setToken):
    type  (setToken.type),
    value (setToken.value),
    line  (setToken.line)
    {}

bool operator == (const Token& a, const Token& b);
bool operator != (const Token& a, const Token& b);
std::ostream& operator << (std::ostream& os, const Token& m);

bool operator == (const Token& a, const Token& b)
{
    return a.type == b.type;
}

//===============================================================================

bool operator != (const Token& a, const Token& b)
{
    return !(a == b);
}

//===============================================================================

std::ostream& operator << (std::ostream& os, const Token& value)
{
    #define DEER_0(id, name, word, fontcolor, color, fillcolor, shape, style, code) \
    case id: { return os << std::string (word); }

    #define DEER_1(id, name, word, fontcolor, color, fillcolor, shape, style, code) \
    case id: { return os << std::string (word); }

    #define DEER_2(id, name, word, fontcolor, color, fillcolor, shape, style, code) \
    case id: { return os << std::string (word); }

    switch (value.type)
    {
        #include "CList.hpp"

        default: { throw "operator << was broken"; }
    }

    #undef DEER_0
    #undef DEER_1
    #undef DEER_2
}

#endif
