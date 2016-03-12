#ifndef TOKEN_HPP
    #define TOKEN_HPP

//{==============================================================================

#define DEER(id, name, word, fontcolor, color, fillcolor, shape, style) name = id,

enum Lexemes
{
    #include "CList.hpp"
};

#undef DEER

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
};

//}==============================================================================

Token :: Token ():
    type  (),
    value (),
    line  ()
    {}

Token :: Token (const int setType):
    type  (setType),
    value (),
    line  ()
    {}

Token :: Token (const int setType, const int setValue):
    type  (setType),
    value (setValue),
    line  ()
    {}

Token :: Token (const int setType, const int setValue, const int setLine):
    type  (setType),
    value (setValue),
    line  (setLine)
    {}

bool operator == (const Token& a, const Token& b);
bool operator != (const Token& a, const Token& b);
std::ostream& operator << (std::ostream& os, Token const &m);

bool operator == (const Token& a, const Token& b)
{
    return a.type == b.type;
}

bool operator != (const Token& a, const Token& b)
{
    return !(a == b);
}

std::ostream& operator << (std::ostream& os, const Token& value)
{
    #define DEER(id, name, word, fontcolor, color, fillcolor, shape, style) \
    case id: { return os << string (word); }

    switch (value.type)
    {
        #include "CList.hpp"

        default: { throw "operator << was broken"; }
    }

    #undef DEER
}

#endif
