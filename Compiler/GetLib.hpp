#include <cstdio>
#include "Parser.hpp"
#include "Headers//Stream.hpp"

double GetN (Stream <Token>& example);
double GetP (Stream <Token>& example);
double GetT (Stream <Token>& example);
double GetE (Stream <Token>& example);

//{

// E = T | T + T | T - T
// T = P | P + P | P - P
// P = N | (E)   | -P
// N = {0; 1; 2; 3; 4; 5; 6; 7; 8; 9}

//}

double GetN (Stream <Token>& example)
{
    double value = 0;

    bool first = false;

    if (example.check () && example[example.place ()].type_ == Digit)
    {
        first = true;

        value = example[example.place ()].value_;

        example++;
    }

    if (!first) throw "expected integer";

    return value;
}

double GetP (Stream <Token>& example)
{
    double value = 0;

    if (example.check () && example[example.place ()].type_ == Sub)
    {
        example++;

        value = -GetP (example);
    }

    else if (example.check () && example[example.place ()].type_ == Start)
    {
        example++;

        value = GetE (example);

        if (example.check () && example[example.place ()].type_ == Finish);

        else throw "forget ')'";

        example++;
    }

    else //
    {
        value = GetN (example);
    }

    return value;
}

double GetT (Stream <Token>& example)
{
    double value = GetP (example);

    while (example.check () && (example[example.place ()].type_ == Mul || example[example.place ()].type_ == Div))
    {
        int sign = example[example.place ()].type_;

        example++;

        double tmp = GetP (example);

        if (sign == Mul) value *= tmp;
        if (sign == Div)
        {
            if ((int) tmp == 0) throw "div on zero";

            value /= tmp;
        }
    }

    return value;
}

double GetE (Stream <Token>& example)
{
    double value = GetT (example);

    while (example.check () && (example[example.place ()].type_ == Add || example[example.place ()].type_ == Sub))
    {
        int sign = example[example.place ()].type_;

        example++;

        double tmp = GetT (example);

        if (sign == Add) value += tmp;
        if (sign == Sub) value -= tmp;
    }

    return value;
}
