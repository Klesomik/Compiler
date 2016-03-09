#ifndef TOKEN_HPP
    #define TOKEN_HPP

//{==============================================================================

#define DEER(id, name, word) name = id,

enum Lexemes
{
    #include "CList.hpp"
};

#undef DEER(id, name, word)

//}==============================================================================

//{==============================================================================

struct Token
{
    int type;
    int line;

    union
    {
        int        value;
        const char* name;
    };

    Token ();
    Token (const int setType);
    Token (const int setType, const int setValue);
    Token (const char* setName);
    Token (const int setType, const char* setName);
};

//}==============================================================================

Token :: Token ():
    type  (),
    line  (),
    value ()
    {}

Token :: Token (int setType):
    type  (setType),
    line  (),
    value (0)
    {}

Token :: Token (int setType, int setValue):
    type  (setType),
    line  (),
    value (setValue)
    {}

Token :: Token (const char* setName):
    type (),
    line (),
    name (setName)
    {}

Token :: Token (const int setType, const char* setName):
    type (setType),
    line (),
    name (setName)
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
        }

        #undef DEER(id, name, word)
    }

    return os << tmp;
}

#endif
