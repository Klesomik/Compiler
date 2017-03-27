#ifndef Tools_hpp

#define Tools_hpp

#include <cstdio>
#include <iostream>
#include <map>
#include <fstream>
#include "Stream.hpp"

namespace Tools
{
    bool IsAlpha (const char symbol);
    bool IsDigit (const char symbol);
    bool IsSpace (const char symbol);
    bool IsAssemblerComment (const char symbol);
    bool IsExtraSymbol (const char symbol);
    bool IsPreProc (const char symbol);
    bool IsQuotation (const char symbol);

    template <typename Data_T>
    bool Search (std::map <std::string, int>& example, std::string& value, const int type, Stream <Data_T>& code);

    void Read (Stream <char>& to, const std::string& name);

    template <typename Data_T>
    void Read (Stream <Data_T>& to, const std::string& name);

    template <typename Data_T>
    void Write (const Stream <Data_T>& from, const std::string& name);

    void FillStream (Stream <Token>& from, Stream <Token>& to, const int delim);
}

bool Tools::IsAlpha (const char symbol)
{
    return isalpha (symbol);
}

bool Tools::IsDigit (const char symbol)
{
    return isdigit (symbol);
}

bool Tools::IsSpace (const char symbol)
{
    return (iscntrl (symbol) || (symbol == ' '));
}

bool Tools::IsAssemblerComment (const char symbol)
{
    return symbol == ';';
}

bool Tools::IsExtraSymbol (const char symbol)
{
    return symbol == '%' || symbol == '$' || symbol == ',';
}

bool Tools::IsPreProc (const char symbol)
{
    return symbol == '#';
}

bool Tools::IsQuotation (const char symbol)
{
    return symbol == '"';
}

template <typename Data_T>
bool Tools::Search (std::map <std::string, int>& example, std::string& value, const int type, Stream <Data_T>& code)
{
    auto it = example.find (value);

    if (it != example.end ())
    {
        int token = 0;

        if (type == -1) token = it -> second;
        else            token = type;

        code.push_back ({ token, it -> second });

        return true;
    }

    return false;
}

void Tools::Read (Stream <char>& to, const std::string& name)
{
    std::ifstream in (name);

    std::string tmp;
    std::getline (in, tmp, '\0');

    to += tmp;
}

template <typename Data_T>
void Tools::Read (Stream <Data_T>& to, const std::string& name)
{
    std::ifstream in (name);

    while (!in.eof ())
    {
        Data_T value;
        in >> value;

        to.push_back (value);
    }
}

template <typename Data_T>
void Tools::Write (const Stream <Data_T>& from, const std::string& name)
{
    std::ofstream out (name);

    for (int i = 0; i < from.size (); i++)
        out << from[i];
}

void Tools::FillStream (Stream <Token>& from, Stream <Token>& to, const int delim)
{
    while (from.check () && !IsLexem (from.current (), delim))
    {
        to.push_back (from.current ());

        from++;
    }
}

#endif
