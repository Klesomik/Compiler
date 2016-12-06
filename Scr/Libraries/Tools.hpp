#include <bits/stdc++.h>

bool IsSpace (const char symbol);
bool IsComment (const char symbol);
bool IsDigit (const char symbol);
bool IsAlpha (const char symbol);
bool IsExtraSymbol (const char symbol);

bool Search (std::map <std::string, int>& example, std::string& value, const int type, Stream <BoaToken>& code);

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

bool Search (std::map <std::string, int>& example, std::string& value, const int type, Stream <BoaToken>& code)
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

    for (int i = 0; i < from.size (); i++)
    {
        char symbol = 0;
        from >> symbol;

        to << symbol;
    }
}
