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
// Get_Value                         ::= +Get_Value | -Get_Value | (Get_Assignment) | Get_Name | Get_Number
// Get_Number                        ::= ['0'-'9']
// Get_Name                          ::= ['a'-'z']

//}

class SyntaxAnalyzer
{
    public:
        SyntaxAnalyzer (AstNode& root, Stream <Token>& code);

        bool IsLexem (const int token);

        void Hello_C (std::string& example);

        void Get_Number                        (AstNode& current, Stream <Token>& example);
        void Get_Name                          (AstNode& current, Stream <Token>& example);
        void Get_Function                      (AstNode& current, Stream <Token>& example);
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
    try
    {
        while (code.check ())
        {
            AstNode current ({ Block, Block });

            Get_Block (current, code);

            root.insert (current);
        }
    }
    catch (...)
    {
    }
}

//===============================================================================

bool SyntaxAnalyzer :: IsLexem (Stream <Token>& example, const int token)
{
    return (example[example.place ()].type == token);
}

//===============================================================================

void SyntaxAnalyzer :: Hello_C (std::string& example)
{
    printf ("Input name of C   file: ");

    getline (std::cin, example, '\n');
}

//===============================================================================

void SyntaxAnalyzer :: Get_Number (AstNode& current, Stream <Token>& example)
{
    bool first = false;
    if (example.check () && IsLexem (example, Digit))
    {
        first = true;

        current.key () = example[example.place ()];

        example++;
    }

    if (!first)
    {
        Inform.log_file.output ("Expected integer\n");

        throw "error";
    }
}

//===============================================================================

void SyntaxAnalyzer :: Get_Name (AstNode& current, Stream <Token>& example)
{
    bool first = false;
    if (example.check () && IsLexem (example, Name))
    {
        first = true;

        current.key () = example[example.place ()];

        example++;
    }

    if (!first)
    {
        Inform.log_file.output ("Expected name of variable\n");

        throw "error";
    }
}

//===============================================================================

void SyntaxAnalyzer :: Get_Function (AstNode& current, Stream <Token>& example)
{
    bool first = false;
    if (example.check () && check_next (example, { Name, OpenBracket }))
    {
        first = true;

        current.key () = { Call };

        AstNode function ({ example[example.place ()].type });

        example++;

        if (example.check ()) example++;
        else throw "error";

        do
        {
            if (!IsLexem (example, Name))
            {
                Inform.log_file.output ("Expected name\n");

                throw "error";
            }

            function.insert ({ example[example.place ()].type, example[example.place ()].value });

            example++;
        }
        while (example.check () && IsLexem (example, Comma))

        example++;
    }

    if (!first)
    {
        Inform.log_file.output ("Expected name of function\n");

        throw "error";
    }
}

//===============================================================================

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

        if (example.check () && example[example.place ()].type != CloseBracket)
        {
            Inform.log_file.output ("Forgot ')'\n");

            throw "error";
        }

        example++;
    }

    else if (example.check () && example[example.place ()].type == Name)
    {
        Get_Name (value, example);
    }

    else if (check_next (example, { Name, OpenBracket })) //Name
    {
        Get_Function (value, example);
    }

    else
    {
        Get_Number (value, example);
    }

    current.move (value);
}

//===============================================================================

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

//===============================================================================

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

//===============================================================================

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

//===============================================================================

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

//===============================================================================

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

//===============================================================================

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

//===============================================================================

void SyntaxAnalyzer :: Get_Assignment (AstNode& current, Stream <Token>& example)
{
    AstNode operation;

    if (example.check_next ({ Token (Name), Token (Assignment) }))
    {
        operation.key () = { Assignment, 0 };

        while (example.check_next ({ Token (Name), Token (Assignment) }))
        {
            AstNode value;
            Get_Name (value, example);

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

//===============================================================================

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

//===============================================================================

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

//===============================================================================

void SyntaxAnalyzer :: Get_NewVar (AstNode& current, Stream <Token>& example)
{
    current.insert (example[example.place ()]);

    example++;

    AstNode operation;

    Get_Name (operation, example);

    current.insert (operation);

    if (!example.check () || example[example.place ()].type != Assignment) return;

    example++;

    AstNode value;

    Get_Assignment (value, example);

    example++;

    current.insert (value);
}

//===============================================================================

void SyntaxAnalyzer :: Get_Lexem (AstNode& current, Stream <Token>& example)
{
    Stream <Token> tmp;

    if (example.check ())
    {
        if (example[example.place ()].type == Begin)
        {
            AstNode grayNode ({ Block, Block });

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

//===============================================================================

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

//===============================================================================

void SyntaxAnalyzer :: Get_Params (AstNode& current, Stream <Token>& example)
{
    do
    {
        if (IsLexem (example, Int))
        {
            AstNode operation ({ Declaration });

            operation.insert ({ Int });

            AstNode value;
            Get_Name (value, example);

            operation.insert (value);

            current.insert (operation);
        }
    }
    while (IsLexem (example, Comma))
}

//===============================================================================

void SyntaxAnalyzer :: Get_Code (AstNode& current, Stream <Token>& example)
{
    AstNode operation ({ Declaration });

    if (IsLexem (example, Int))
    {
        operation.insert ({ Int });

        example++;

        AstNode value;

        Get_Name (value, example);

        operation.insert (value);

        if (IsLexem (example, OpenBracket))
        {
            AstNode params;

            Get_Params (params, example);

            operation.insert (params);

            AstNode code;

            Get_Block (code, example);

            operation.insert (code);
        }

        else if (IsLexem (example, Assignment))
        {
            example++;

            AstNode var;

            Get_Assignment (var, example);

            example++;

            current.insert (var);
        }
    }

    else if (IsLexem (example, Void))
}

#endif
