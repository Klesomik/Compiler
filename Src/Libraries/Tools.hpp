#ifndef Tools_hpp

#define Tools_hpp

#include <bits/stdc++.h>

bool IsSpace (const char symbol);
bool IsComment (const char symbol);
bool IsDigit (const char symbol);
bool IsAlpha (const char symbol);
bool IsExtraSymbol (const char symbol);
bool IsOption (const char symbol);
bool IsFile (const char symbol);
bool IsConfigComment (const char symbol);
bool IsPreProc (const char symbol);
bool IsQuotation (const char symbol);

template <typename T>
bool Search (std::map <std::string, int>& example, std::string& value, const int type, Stream <T>& code);

void ScanFile  (Stream <char>&   to, const std::string& name);
void PrintFile (Stream <char>& from, const std::string& name);

bool IsSpace (const char symbol)
{
    return (iscntrl (symbol) || (symbol == ' '));
}

bool IsComment (const char symbol)
{
    return symbol == ';';
}

bool IsDigit (const char symbol)
{
    return isdigit (symbol);
}

bool IsAlpha (const char symbol)
{
    return isalpha (symbol);
}

bool IsExtraSymbol (const char symbol)
{
    return symbol == '%' || symbol == '$' || symbol == ',';
}

bool IsOption (const char symbol)
{
    return symbol == '-';
}

bool IsFile (const char symbol)
{
    return symbol == '@';
}

bool IsConfigComment (const char symbol)
{
    return symbol == '#';
}

bool IsPreProc (const char symbol)
{
    return symbol == '#';
}

bool IsQuotation (const char symbol)
{
    return symbol == '"';
}

template <typename T>
bool Search (std::map <std::string, int>& example, std::string& value, const int type, Stream <T>& code)
{
    std::map <std::string, int>::iterator it = example.find (value);

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

void ScanFile (Stream <char>& to, const std::string& name)
{
    std::ifstream from (name);

    std::string copy;
    std::getline (from, copy, '\0');

    Stream <char> tmp (copy.data (), copy.size ());

    to = tmp;
}

void PrintFile (Stream <char>& from, const std::string& name)
{
    std::ofstream to (name);

    for (size_t i = 0; i < from.size (); i++)
    {
        char symbol = 0;
        from >> symbol;

        to << symbol;
    }
}

void Read (Stream <char>& to, const std::string& name);

template <typename Data_T>
void Read (Stream <Data_T>& to, const std::string& name);

template <typename Data_T>
void Write (const Stream <Data_T>& from, const std::string& name);

void Read (Stream <char>& to, const std::string& name)
{
    std::ifstream in (name);

    std::string tmp;
    std::getline (in, tmp, '\0');

    to += tmp;
}

template <typename Data_T>
void Read (Stream <Data_T>& to, const std::string& name)
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
void Write (const Stream <Data_T>& from, const std::string& name)
{
    std::ofstream out (name);

    for (int i = 0; i < from.size (); i++)
        out << from[i];
}

#endif
