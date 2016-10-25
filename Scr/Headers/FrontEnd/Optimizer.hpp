#ifndef Optimizer_hpp

#define Optimizer_hpp

#include <iostream>
#include <cstdio>
#include "..//..//Libraries//AbstractSyntaxNode.hpp"

typedef std::pair <int, int> ret_t;

class Optimizer
{
    private:
        enum
        {
            DIGIT,
            NOT_DIGIT
        };

        ret_t detour (AstNode* current);

        ret_t check_AddSubMulDiv (AstNode* current, const int default_value, char symbol);
        void check_Default      (AstNode* current);

    public:
        Optimizer (AstNode& root);

        void Start (AstNode& root);
};

Optimizer :: Optimizer (AstNode& root)
{
    Start (root);
}

void Optimizer :: Start (AstNode& root)
{
    try
    {
        for (size_t i = 0; i < root.children ().size (); i++)
            detour (root.children ()[i]);
    }
    catch (const char* message)
    {
        std::cout << message << "\n";
    }
    catch (const std::string& message)
    {
        std::cout << message << "\n";
    }
    catch (const int message)
    {
        std::cout << message << "\n";
    }
}

ret_t Optimizer :: detour (AstNode* current)
{
    switch (current -> key ().type)
    {
        case Digit: { current -> erase (); return ret_t (DIGIT, current -> key ().value); }

        case Add: { return check_AddSubMulDiv (current, 0, '+'); }
        case Sub: { return check_AddSubMulDiv (current, 0, '-'); }
        case Mul: { return check_AddSubMulDiv (current, 1, '*'); }
        case Div: { return check_AddSubMulDiv (current, 1, '/'); }
        case Mod: { return check_AddSubMulDiv (current, 1, '%'); }

        default: { check_Default (current); break; }
    }

    return ret_t (NOT_DIGIT, current -> key ().value);
}

ret_t Optimizer :: check_AddSubMulDiv (AstNode* current, const int default_value, char symbol)
{
    int answer = default_value;

    bool action = false;
    for (size_t i = 0; i < current -> size ();)
    {
        ret_t result = detour (current -> children ()[i]);

        if (result.first == DIGIT)
        {
            switch (symbol)
            {
                case '+': { answer += result.second; break; }
                case '-': { answer -= result.second; break; }
                case '*': { answer *= result.second; break; }
                case '/': { answer /= result.second; break; }
                case '%': { answer %= result.second; break; }

                default: { std::cout << "|" << symbol << "|\n"; throw "Unknown symbol"; }
            }

            action = true;
        }

        else i++;
    }

    if (current -> empty ())
    {
        current -> erase ();

        return ret_t (DIGIT, answer);
    }

    else if (action) current -> insert ({ Digit, answer });

    return ret_t (NOT_DIGIT, answer);
}

void Optimizer :: check_Default (AstNode* current)
{
    for (size_t i = 0; i < current -> size (); i++)
    {
        ret_t result = detour (current -> children ()[i]);

        if (result.first == DIGIT) current -> insert ({ Digit, result.second });
    }
}

#endif /* Optimizer_hpp */
