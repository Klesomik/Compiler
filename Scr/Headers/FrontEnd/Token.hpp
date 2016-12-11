#ifndef TOKEN_HPP
    #define TOKEN_HPP

//{==============================================================================

#include <cstdio>
#include <iostream>

//}==============================================================================

//{==============================================================================

#define DEER(id, name, word, code) name = id,

enum Lexemes
{
    #include "CList.inl"
};

#undef DEER

//}==============================================================================

//{==============================================================================

struct Token
{
    int  type;
    int value;

    Token ();
    Token (const int setType);
    Token (const int setType, const int setValue);
    Token (const Token& setToken);
};

//}==============================================================================

Token::Token ():
    type  (),
    value ()
{
}

//===============================================================================

Token::Token (const int setType):
    type  (setType),
    value ()
{
}

//===============================================================================

Token::Token (const int setType, const int setValue):
    type  (setType),
    value (setValue),
    line  ()
{
}

//===============================================================================

Token::Token (const Token& setToken):
    type  (setToken.type),
    value (setToken.value)
{
}

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
    #define DEER(id, name, word, code) \
    case id: { return os << std::string (word); }

    switch (value.type)
    {
        #include "CList.inl"

        default: { throw "operator << was broken"; }
    }

    #undef DEER
}

#endif
