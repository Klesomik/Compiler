#include <bits/stdc++.h>
#include "..//..//Libraries//Stream.hpp"
#include "..//..//Libraries//Tools.hpp"

namespace CAP
{
    class Preprocessor
    {
        public:
            Preprocessor ();

            void parsing (Stream <char>& from, Stream <char>& to);

        private:
            std::map <std::string, std::string> data;

            bool check (Stream <char>& text, const std::string& pattern, int i); // I want to learn more about iterators and replace it into check (iteartor it, string pattern)
            void name (Stream <char>& from, std::string& to, const char delim, int& i);

            void include (Stream <char>& from, Stream <char>& to, int& i);
            void define (Stream <char>& from, int& i);
            void undef (Stream <char>& from, int& i);
            void commentary (Stream <char>& from, int& i, const std::string& delim);

            void other (Stream <char>& from, Stream <char>& to, int& i);
    };
}

CAP::Preprocessor::Preprocessor ():
    data ()
{
}

void CAP::Preprocessor::parsing (Stream <char>& from, Stream <char>& to)
{
    for (int i = 0; i < from.size ();)
    {
        if (check (from, "#include", i))    { i += 8; include (from, to, i); }
        else if (check (from, "#define", i)) { i += 7; define (from, i); }
        else if (check (from, "#undef", i)) { i += 6; undef (from, i); }
        else if (check (from, "//", i)) { i += 2; commentary (from, i, "\n"); }
        else if (check (from, "/*", i)) { i += 2; commentary (from, i, "*/"); }

        else
            other (from, to, i);
    }
}

bool CAP::Preprocessor::check (Stream <char>& text, const std::string& pattern, int i)
{
    if (text.size () - i < pattern.size ())
        return false;

    for (int j = 0; j < pattern.size (); j++, i++)
        if (text[i] != pattern[j])
            return false;

    return true;
}

void CAP::Preprocessor::name (Stream <char>& from, std::string& to, const char delim, int& i)
{
    for (; i < from.size (); i++)
    {
        if (from[i] == delim)
            break;

        to.push_back (from[i]);
    }
}

void CAP::Preprocessor::include (Stream <char>& from, Stream <char>& to, int& i)
{
    i++; // ' '
    i++; // '"'

    std::string file;

    for (; i < from.size (); i++)
    {
        if (from[i] == '"')
            break;

        file.push_back (from[i]);
    }

    i++; // '"'

    Stream <char> content;
    Read (content, file);

    parsing (content, to);
}

void CAP::Preprocessor::define (Stream <char>& from, int& i)
{
    i++; // ' '

    std::string first, second;

    name (from,  first,  ' ', i);
    name (from, second, '\n', i);

    data.insert ({ first, second });
}

void CAP::Preprocessor::undef (Stream <char>& from, int& i)
{
    i++; // ' '

    std::string first, second;

    name (from,  first,  ' ', i);
    name (from, second, '\n', i);

    data.erase (first);
}

void CAP::Preprocessor::commentary (Stream <char>& from, int& i, const std::string& delim)
{
    for (; i < from.size (); i++)
        if (check (from, delim, i))
            break;

    i += delim.size () + 1;
}

void CAP::Preprocessor::other (Stream <char>& from, Stream <char>& to, int& i)
{
    std::string word;

    for (; i < from.size (); i++)
    {
        if ((from[i] == ' ') || (from[i] == '\n'))
            break;

        word.push_back (from[i]);
    }

    to.push_back (from[i]);
    i++; // ' ' | '\n'

    auto it = data.find (word);

    if (it != data.end ())
        to += it->second;

    else
        to += word;
}
