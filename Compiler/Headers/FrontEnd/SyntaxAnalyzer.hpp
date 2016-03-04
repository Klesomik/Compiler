#ifndef SYNTAX_INCLUDED
    #define SYNTAX_INCLUDED

//{==============================================================================

#include <cstdio>
#include "LexicialAnalyzer.hpp"
#include "..//..//Librarys//Debug.hpp"
#include "..//..//Librarys//Stream.hpp"
#include "..//..//Librarys//AbstractSyntaxTree.hpp"

//}==============================================================================

//{

// Get_Block                         ::= { [Get_Lexem] }
// Get_Lexem                         ::= Get_Block | Get_If_Else | Get_Assignment
// Get_NewVar                        ::= int GetVariable = Get_Assigment
// Get_While                         ::= while (Get_Lexem) Get_Lexem
// Get_If_Else                       ::= if (Get_Lexem) Get_Lexem else Get_Lexem
// Get_Assignment                    ::= Get_Or | GetVariable = Get_Assignment
// Get_Or                            ::= Get_And | Get_And || Get_And
// Get_And                           ::= Get_Equal_NotEqual | Get_Equal_NotEqual && Get_Equal_NotEqual
// Get_Equal_NotEqual                ::= Get_Less_LessEqual_More_MoreEqual | Get_Less_LessEqual_More_MoreEqual == Get_Less_LessEqual_More_MoreEqual | Get_Less_LessEqual_More_MoreEqual != Get_Less_LessEqual_More_MoreEqual
// Get_Less_LessEqual_More_MoreEqual ::= Get_Add_Sub | Get_Add_Sub < Get_Add_Sub | Get_Add_Sub <= Get_Add_Sub| Get_Add_Sub > Get_Add_Sub | Get_Add_Sub >= Get_Add_Sub
// Get_Add_Sub                       ::= Get_Mul_Div_Mod | Get_Mul_Div_Mod + Get_Mul_Div_Mod | Get_Mul_Div_Mod - Get_Mul_Div_Mod
// Get_Mul_Div_Mod                   ::= Get_Value | Get_Value * Get_Value | Get_Value / Get_Value | Get_Value % Get_Value
// Get_Value                         ::= +Get_Value | -Get_Value | (Get_Assignment) | Get_Variable | Get_Number
// Get_Number                        ::= ['0'-'9']
// Get_Variable                      ::= ['a'-'z']

//}

class SyntaxAnalyzer
{
    private:
        size_t error_;

    public:
        SyntaxAnalyzer (AstNode& root, Stream <Token>& code);

        void Get_Number                        (AstNode& current, Stream <Token>& example);
        void Get_Variable                      (AstNode& current, Stream <Token>& example);
        void Get_Value                         (AstNode& current, Stream <Token>& example);
        void Get_Mul_Div_Mod                   (AstNode& current, Stream <Token>& example);
        void Get_Add_Sub                       (AstNode& current, Stream <Token>& example);
        void Get_Less_LessEqual_More_MoreEqual (AstNode& current, Stream <Token>& example);
        void Get_And                           (AstNode& current, Stream <Token>& example);
        void Get_Or                            (AstNode& current, Stream <Token>& example);
        void Get_Equal_NotEqual                (AstNode& current, Stream <Token>& example);
        void Get_Assignment                    (AstNode& current, Stream <Token>& example);
        void Get_If_Else                       (AstNode& current, Stream <Token>& example);
        void Get_While                         (AstNode& current, Stream <Token>& example);
        void Get_NewVar                        (AstNode& current, Stream <Token>& example);
        void Get_Lexem                         (AstNode& current, Stream <Token>& example);
        void Get_Block                         (AstNode& current, Stream <Token>& example);
};

SyntaxAnalyzer :: SyntaxAnalyzer (AstNode& root, Stream <Token>& code)
{
    while (code.check ())
    {
        AstNode current ({ None, None });

        Get_Block (current, code);

        root.insert (current);
    }
}

void SyntaxAnalyzer :: Get_Number (AstNode& current, Stream <Token>& example)
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

void SyntaxAnalyzer :: Get_Variable (AstNode& current, Stream <Token>& example)
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

void SyntaxAnalyzer :: Get_Value (AstNode& current, Stream <Token>& example)
{
    AstNode value; //else with out; throw

    if (example.check () && example[example.place ()].type == Sub)
    {
        example++;

        //value = -Get_Value (example); *-1
    }

    else if (example.check () && example[example.place ()].type == Add)
    {
        example++;

        //value = +Get_Value (example); *+1
    }

    else if (example.check () && example[example.place ()].type == OpenBracket)
    {
        example++;

        Get_Assignment (value, example);

        if (example.check () && example[example.place ()].type != CloseBracket) THROW ("forgot ')'");

        example++;
    }

    else if (example.check () && example[example.place ()].type == Var)
    {
        Get_Variable (value, example);
    }

    else
    {
        Get_Number (value, example);
    }

    current.move (value);
}

void SyntaxAnalyzer :: Get_Mul_Div_Mod (AstNode& current, Stream <Token>& example)
{
    AstNode value;
    Get_Value (value, example);

    while (example.check () && (example[example.place ()].type == Mul ||
                                example[example.place ()].type == Div ||
                                example[example.place ()].type == Mod))
    {
        int sign = example[example.place ()].type;

        example++;

        AstNode operation;

        if (sign == value.key ().type)
        {
            Get_Value (operation, example);
            value.insert (operation);
        }

        else
        {
            operation.key () =  { sign, 0 };
            operation.insert (value);

            Get_Value (value, example);
            operation.insert (value);

            value.move (operation);
        }
    }

    current.move (value);
}

void SyntaxAnalyzer :: Get_Add_Sub (AstNode& current, Stream <Token>& example)
{
    AstNode value;
    Get_Mul_Div_Mod (value, example);

    while (example.check () && (example[example.place ()].type == Add ||
                                example[example.place ()].type == Sub))
    {
        int sign = example[example.place ()].type;

        example++;

        AstNode operation;

        if (sign == value.key ().type)
        {
            Get_Mul_Div_Mod (operation, example);
            value.insert (operation);
        }

        else
        {
            operation.key () =  { sign, 0 };
            operation.insert (value);

            Get_Mul_Div_Mod (value, example);
            operation.insert (value);

            value.move (operation);
        }
    }

    current.move (value);
}

void SyntaxAnalyzer :: Get_Less_LessEqual_More_MoreEqual (AstNode& current, Stream <Token>& example)
{
    AstNode value;
    Get_Add_Sub (value, example);

    while (example.check () && (example[example.place ()].type == Less      ||
                                example[example.place ()].type == LessEqual ||
                                example[example.place ()].type == More      ||
                                example[example.place ()].type == MoreEqual))
    {
        int sign = example[example.place ()].type;

        example++;

        AstNode operation;

        if (sign == value.key ().type)
        {
            Get_Add_Sub (operation, example);
            value.insert (operation);
        }

        else
        {
            operation.key () =  { sign, 0 };
            operation.insert (value);

            Get_Add_Sub (value, example);
            operation.insert (value);

            value.move (operation);
        }
    }

    current.move (value);
}

void SyntaxAnalyzer :: Get_Equal_NotEqual (AstNode& current, Stream <Token>& example)
{
    AstNode value;
    Get_Less_LessEqual_More_MoreEqual (value, example);

    while (example.check () && (example[example.place ()].type == Equal ||
                                example[example.place ()].type == NotEqual))
    {
        int sign = example[example.place ()].type;

        example++;

        AstNode operation;

        if (sign == value.key ().type)
        {
            Get_Less_LessEqual_More_MoreEqual (operation, example);
            value.insert (operation);
        }

        else
        {
            operation.key () =  { sign, 0 };
            operation.insert (value);

            Get_Less_LessEqual_More_MoreEqual (value, example);
            operation.insert (value);

            value.move (operation);
        }
    }

    current.move (value);
}

void SyntaxAnalyzer :: Get_And (AstNode& current, Stream <Token>& example)
{
    AstNode value;
    Get_Equal_NotEqual (value, example);

    while (example.check () && example[example.place ()].type == And)
    {
        example++;

        AstNode operation;

        Get_Equal_NotEqual (operation, example);
        value.insert (operation);
    }

    current.move (value);
}

void SyntaxAnalyzer :: Get_Or (AstNode& current, Stream <Token>& example)
{
    AstNode value;
    Get_And (value, example);

    while (example.check () && example[example.place ()].type == Or)
    {
        example++;

        AstNode operation;

        Get_And (operation, example);
        value.insert (operation);
    }

    current.move (value);
}

void SyntaxAnalyzer :: Get_Assignment (AstNode& current, Stream <Token>& example)
{
    AstNode operation;

    if (example.check_next ({ Token (Var), Token (Assignment) }))
    {
        operation.key () = { Assignment, 0 };

        while (example.check_next ({ Token (Var), Token (Assignment) }))
        {
            AstNode value;
            Get_Variable (value, example);

            example++;

            operation.insert (value);
        }

        AstNode value;
        Get_Or (value, example);
        operation.insert (value);
    }

    else Get_Or (operation, example);

    current.move (operation);
}

void SyntaxAnalyzer :: Get_If_Else (AstNode& current, Stream <Token>& example)
{
    example++;

    current.key () = { If, 0 };

    example++;

    Stream <Token> tmp;
    while (example.check () && example[example.place ()].type != CloseBracket)
    {
        tmp.push_back (example[example.place ()]);

        example++;
    }
    tmp.push_back ({ End, 0 });

    example++;

    Get_Lexem (current, tmp);

    Get_Lexem (current, example);

    if (example.check () && example[example.place ()].type == Else)
    {
        example++;

        Get_Lexem (current, example);
    }
}

void SyntaxAnalyzer :: Get_While (AstNode& current, Stream <Token>& example)
{
    example++;

    current.key () = { While, 0 };

    example++;

    Stream <Token> tmp;
    while (example.check () && example[example.place ()].type != CloseBracket)
    {
        tmp.push_back (example[example.place ()]);

        example++;
    }
    tmp.push_back ({ End, 0 });

    example++;

    Get_Lexem (current, tmp);

    Get_Lexem (current, example);
}

void SyntaxAnalyzer :: Get_NewVar (AstNode& current, Stream <Token>& example)
{
    current.insert (example[example.place ()]);

    example++;

    AstNode operation;

    Get_Variable (operation, example);

    current.insert (operation);

    if (!example.check () || example[example.place ()].type != Assignment) return;

    example++;

    AstNode value;

    Get_Assignment (value, example);

    example++;

    current.insert (value);
}

void SyntaxAnalyzer :: Get_Lexem (AstNode& current, Stream <Token>& example)
{
    Stream <Token> tmp;

    if (example.check ())
    {
        if (example[example.place ()].type == Begin)
        {
            AstNode grayNode ({ None, None });

            Get_Block (grayNode, example);

            current.insert (grayNode);
        }

        else if (example[example.place ()].type == If)
        {
            AstNode operation;

            Get_If_Else (operation, example);

            current.insert (operation);
        }

        else if (example[example.place ()].type == While)
        {
            AstNode operation;

            Get_While (operation, example);

            current.insert (operation);
        }

        else if (example[example.place ()].type == Int)
        {
            AstNode operation ({ Declaration, 0 });

            Get_NewVar (operation, example);

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

            Get_Assignment (operation, tmp);

            current.insert (operation);

            example++;
        }
    }
}

void SyntaxAnalyzer :: Get_Block (AstNode& current, Stream <Token>& example)
{
    if (example.check () && example[example.place ()].type == Begin)
    {
        example++;

        while (example.check () && example[example.place ()].type != End)
            Get_Lexem (current, example);

        example++;
    }

    else throw "expected '{'";
}

#endif
