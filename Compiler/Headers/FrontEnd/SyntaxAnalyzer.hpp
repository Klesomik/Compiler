#ifndef SYNTAX_INCLUDED
    #define SYNTAX_INCLUDED

#include <cstdio>
#include "LexicialAnalyzer.hpp"
#include "..//..//Librarys//Debug.hpp"
#include "..//..//Librarys//Stream.hpp"
#include "..//..//Librarys//AbstractSyntaxTree.hpp"

//{

// Block = { [Lexem] }
// Lexem = O; | B
// O     = Or | Or = Or
// Or    = E  | E == E
// E     = T  | T + T | T - T
// T     = P  | P * P | P / P
// P     = N  | W     | (O)   | -P | +P
// N     = ['0'-'9']
// W     = ['a'-'z']

//}

void GetNumber                     (AstNode& current, Stream <Token>& example);
void GetVariable                   (AstNode& current, Stream <Token>& example);
void GetP                          (AstNode& current, Stream <Token>& example);
void GetMulDivMod                  (AstNode& current, Stream <Token>& example);
void GetAddSub                     (AstNode& current, Stream <Token>& example);
void GetLessLessEqualMoreMoreEqual (AstNode& current, Stream <Token>& example);
void GetAnd                        (AstNode& current, Stream <Token>& example);
void GetOr                         (AstNode& current, Stream <Token>& example);
void GetEqualNotEqual              (AstNode& current, Stream <Token>& example);
void GetAssignment                 (AstNode& current, Stream <Token>& example);
void GetIfElse                     (AstNode& current, Stream <Token>& example);
void GetLexem                      (AstNode& current, Stream <Token>& example);
void GetBlock                      (AstNode& current, Stream <Token>& example);

void GetNumber (AstNode& current, Stream <Token>& example)
{
    bool first = false;
    if (example.check () && example[example.place ()].type == Digit)
    {
        first = true;

        current.key () = example[example.place ()];

        example++;
    }

    if (!first) THROW ("expected integer");
}

void GetVariable (AstNode& current, Stream <Token>& example)
{
    bool first = false;
    if (example.check () && example[example.place ()].type == Var)
    {
        first = true;

        current.key () = example[example.place ()];

        example++;
    }

    if (!first) THROW ("expected name of variable");
}

void GetP (AstNode& current, Stream <Token>& example)
{
    AstNode value; //else with out; throw

    if (example.check () && example[example.place ()].type == Sub)
    {
        example++;

        //value = -GetP (example); *-1
    }

    else if (example.check () && example[example.place ()].type == Add)
    {
        example++;

        //value = +GetP (example); *+1
    }

    else if (example.check () && example[example.place ()].type == OpenBracket)
    {
        example++;

        GetAssignment (value, example);

        if (example.check () && example[example.place ()].type != CloseBracket) THROW ("forgot ')'");

        example++;
    }

    else if (example.check () && example[example.place ()].type == Var)
    {
        GetVariable (value, example);
    }

    else
    {
        GetNumber (value, example);
    }

    current.move (value);
}

void GetMulDivMod (AstNode& current, Stream <Token>& example)
{
    AstNode value;
    GetP (value, example);

    while (example.check () && (example[example.place ()].type == Mul ||
                                example[example.place ()].type == Div ||
                                example[example.place ()].type == Mod))
    {
        int sign = example[example.place ()].type;

        example++;

        AstNode operation ({ sign, 0 });
                operation.insert (value);

                GetP (value, example);
                operation.insert (value);

        value.move (operation);
    }

    current.move (value);
}

void GetAddSub (AstNode& current, Stream <Token>& example)
{
    AstNode value;
    GetMulDivMod (value, example);

    while (example.check () && (example[example.place ()].type == Add ||
                                example[example.place ()].type == Sub))
    {
        int sign = example[example.place ()].type;

        example++;

        AstNode operation ({ sign, 0 });
                operation.insert (value);

                GetMulDivMod (value, example);
                operation.insert (value);

        value.move (operation);
    }

    current.move (value);
}

void GetLessLessEqualMoreMoreEqual (AstNode& current, Stream <Token>& example)
{
    AstNode value;
    GetAddSub (value, example);

    while (example.check () && (example[example.place ()].type == Less      ||
                                example[example.place ()].type == LessEqual ||
                                example[example.place ()].type == More      ||
                                example[example.place ()].type == MoreEqual))
    {
        int sign = example[example.place ()].type;

        example++;

        AstNode operation ({ sign, 0 });
                operation.insert (value);

                GetAddSub (value, example);
                operation.insert (value);

        value.move (operation);
    }

    current.move (value);
}

void GetEqualNotEqual (AstNode& current, Stream <Token>& example)
{
    AstNode value;
    GetLessLessEqualMoreMoreEqual (value, example);

    while (example.check () && (example[example.place ()].type == Equal ||
                                example[example.place ()].type == NotEqual))
    {
        int sign = example[example.place ()].type;

        example++;

        AstNode operation ({ sign, 0 });
                operation.insert (value);

                GetLessLessEqualMoreMoreEqual (value, example);
                operation.insert (value);

        value.move (operation);
    }

    current.move (value);
}

void GetAnd (AstNode& current, Stream <Token>& example)
{
    AstNode value;
    GetEqualNotEqual (value, example);

    while (example.check () && example[example.place ()].type == And)
    {
        int sign = example[example.place ()].type;

        example++;

        AstNode operation ({ sign, 0 });
                operation.insert (value);

                GetEqualNotEqual (value, example);
                operation.insert (value);

        value.move (operation);
    }

    current.move (value);
}

void GetOr (AstNode& current, Stream <Token>& example)
{
    AstNode value;
    GetAnd (value, example);

    while (example.check () && example[example.place ()].type == Or)
    {
        int sign = example[example.place ()].type;

        example++;

        AstNode operation ({ sign, 0 });
                operation.insert (value);

                GetAnd (value, example);
                operation.insert (value);

        value.move (operation);
    }

    current.move (value);
}

void GetAssignment (AstNode& current, Stream <Token>& example)
{
    AstNode value;
    GetOr (value, example);

    while (example.check () && (example[example.place ()].type == Assignment))
    {
        int sign = example[example.place ()].type;

        example++;

        AstNode operation ({ sign, 0 });
                operation.insert (value);

                GetOr (value, example);
                operation.insert (value);

        value.move (operation);
    }

    current.move (value);
}

void GetIfElse (AstNode& current, Stream <Token>& example)
{
    cout << example[example.place ()].type << "\n";

    example++;

    current.key () = { If, 0 };

    AstNode condition;
    GetLexem (condition, example);
    current.insert (condition);

    AstNode true_action;
    GetLexem (true_action, example);
    current.insert (true_action);

    if (example.check () && example[example.place ()].type == Else)
    {
        AstNode false_action;
        GetLexem (false_action, example);
        current.insert (false_action);
    }
}

void GetLexem (AstNode& current, Stream <Token>& example)
{
    Stream <Token> tmp;

    if (example.check ())
    {
        if (example[example.place ()].type == Begin)
        {
            AstNode grayNode ({ None, None }); //

            GetBlock (grayNode, example);

            current.insert (grayNode);
        }

        else if (example[example.place ()].type == If)
        {
            AstNode operation;

            GetIfElse (operation, example);

            current.insert (operation);
        }

        else
        {
            AstNode operation;

            while (example.check () && example[example.place ()].type != EndOfToken)
            {
                tmp.push_back (example[example.place ()]);

                example++;
            }

            GetAssignment (operation, tmp);

            current.insert (operation);

            example++;
        }
    }
}

void GetBlock (AstNode& current, Stream <Token>& example)
{
    if (example.check () && example[example.place ()].type == Begin)
    {
        example++;

        //AstNode grayNode ({ None, None });

        while (example.check () && example[example.place ()].type != End)
            GetLexem (current, example); //grayNode

        //current.insert (grayNode);

        example++;
    }

    else throw "expected '{'";
}

#endif
