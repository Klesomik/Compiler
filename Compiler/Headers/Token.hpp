#ifndef TOKEN_HPP
    #define TOKEN_HPP

//{==============================================================================

#define DEER(id, name, word) name = id,

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
};

//}==============================================================================

Token :: Token ():
    type  (),
    value (),
    line  ()
    {}

Token :: Token (const int setType):
    type  (setType),
    value (0),
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
    return a.type == b.type; // && a.value == b.value
}

bool operator != (const Token& a, const Token& b)
{
    return !(a == b);
}

std::ostream& operator << (std::ostream& os, Token const &m)
{
    char tmp[9] = "";

    if (m.type == Digit) sprintf (tmp, "%d", m.value);

    else if (m.type == Var) sprintf (tmp, "var_%d", m.value);

    else
    {
        #define DEER(id, name, word) case id: { sprintf (tmp, word); break; }

        switch (m.type)
        {
            #include "CList.hpp"

            default: { break; }
        }

        #undef DEER
    }

    return os << tmp;
}

#endif
