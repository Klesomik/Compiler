#ifndef TOKEN_HPP
    #define TOKEN_HPP

//{==============================================================================

enum Lexemes
{
    Digit = 0,
    Var,
    Equal,
    NotEqual,
    And,
    Or,
    LessEqual,
    MoreEqual,
    If,
    Else,
    While,
    Int,
    Declaration,
    Include,
    Define,
    None,

    OpenBracket  = '(',
    CloseBracket = ')',
    Mul          = '*',
    Div          = '/',
    Mod          = '%',
    Add          = '+',
    Sub          = '-',
    Assignment   = '=',
    Less         = '<',
    More         = '>',
    Begin        = '{',
    End          = '}',
    EndOfToken   = ';'
};

//}==============================================================================

//{==============================================================================

struct Token
{
    int type;

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
    value ()
    {}

Token :: Token (int setType):
    type  (setType),
    value (0)
    {}

Token :: Token (int setType, int setValue):
    type  (setType),
    value (setValue)
    {}

Token :: Token (const char* setName):
    type (),
    name (setName)
    {}

Token :: Token (const int setType, const char* setName):
    type (setType),
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

    switch (m.type)
    {
        case       Digit: { sprintf (tmp, "%d",     m.value); break; }

        case         Var: { sprintf (tmp, "var_%d", m.value); break; }
        case       Equal: { sprintf (tmp, "==");              break; }
        case    NotEqual: { sprintf (tmp, "!=");              break; }
        case         And: { sprintf (tmp, "&&");              break; }
        case          Or: { sprintf (tmp, "||");              break; }
        case   LessEqual: { sprintf (tmp, "<=");              break; }
        case   MoreEqual: { sprintf (tmp, ">=");              break; }
        case          If: { sprintf (tmp, "if");              break; }
        case        Else: { sprintf (tmp, "else");            break; }
        case       While: { sprintf (tmp, "while");           break; }
        case         Int: { sprintf (tmp, "int");             break; }
        case Declaration: { sprintf (tmp, "declaration");     break; }
        case        None: { sprintf (tmp, "none");            break; }

        default:          { sprintf (tmp, "%c", m.type);      break; }
    }

    return os << tmp;
}

#endif
