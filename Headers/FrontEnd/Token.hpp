#ifndef Token_hpp

#define Token_hpp

#include <cstdio>
#include <iostream>
#include "..//..//Libraries//Dotter//Dotter.hpp"

#define DEER(id, name, word, fontcolor, color, fillcolor, shape, style, code_generation, dis_syntax_analyzer) \
name = id,

enum Lexemes
{
    #include "CList.inl"
};

#undef DEER

struct Token
{
    int  type;
    int value;

    Token ();
    Token (const int setType);
    Token (const int setType, const int setValue);
    Token (const Token& setToken);
};

Token::Token ():
    type  (),
    value ()
{
}

Token::Token (const int setType):
    type  (setType),
    value ()
{
}

Token::Token (const int setType, const int setValue):
    type  (setType),
    value (setValue)
{
}

Token::Token (const Token& setToken):
    type  (setToken.type),
    value (setToken.value)
{
}

bool operator == (const Token& a, const Token& b);
bool operator != (const Token& a, const Token& b);
std::ostream& operator << (std::ostream& os, const Token& m);
std::string BtInf (Dotter::Digraph& tree, const Token& value);

bool IsLexem (const Token& example, const int token);

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
    #define DEER(id, name, word, fontcolor, color, fillcolor, shape, style, code_generation, dis_syntax_analyzer) \
    case id: { return os << std::string (word); }

    switch (value.type)
    {
        #include "CList.inl"

        default: { throw "operator << was broken"; }
    }

    #undef DEER
}

std::string BtInf (Dotter::Digraph& tree, const Token& value)
{
    #define DEER(id, name, word, fontcolor, color, fillcolor, shape, style, code_generation, dis_syntax_analyzer) \
    case id:\
    {\
        tree.set ("fontcolor", fontcolor);\
        tree.set ("color",     color);\
        tree.set ("fillcolor", fillcolor);\
        tree.set ("shape",     shape);\
        tree.set ("style",     style);\
    \
        return std::string (word);\
    }

    switch (value.type)
    {
        #include "CList.inl"

        default: { throw "BtInf was broken"; }
    }

    #undef DEER
}

bool IsLexem (const Token& example, const int token)
{
    return (example.type == token);
}

#endif /* Token_hpp */
