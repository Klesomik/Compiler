#ifndef SYNTAX_INCLUDED
    #define SYNTAX_INCLUDED

//{==============================================================================

#include <cstdio>
#include <iostream>
#include "Token.hpp"
#include "..//..//Libraries//Stream.hpp"
#include "..//..//Libraries//AbstractSyntaxNode.hpp"
#include "..//..//Libraries//LogHTML.hpp"

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
        SyntaxAnalyzer (AstNode& root, Stream <Token>& code, LogHTML& log);

        bool IsLexem    (Stream <Token>& example, const int token);
        void FillStream (Stream <Token>& example, Stream <Token>& tmp, const int delim);
        void Hello_C    (std::string& example);
        void Error      (const char* message, LogHTML& log);

        void Get_Number                        (AstNode& current, Stream <Token>& example, LogHTML& log);
        void Get_Name                          (AstNode& current, Stream <Token>& example, LogHTML& log);
        void Get_Function                      (AstNode& current, Stream <Token>& example, LogHTML& log);
        void Get_Value                         (AstNode& current, Stream <Token>& example, LogHTML& log);
        void Get_Mul_Div_Mod                   (AstNode& current, Stream <Token>& example, LogHTML& log);
        void Get_Add_Sub                       (AstNode& current, Stream <Token>& example, LogHTML& log);
        void Get_Less_LessEqual_More_MoreEqual (AstNode& current, Stream <Token>& example, LogHTML& log);
        void Get_And                           (AstNode& current, Stream <Token>& example, LogHTML& log);
        void Get_Or                            (AstNode& current, Stream <Token>& example, LogHTML& log);
        void Get_Equal_NotEqual                (AstNode& current, Stream <Token>& example, LogHTML& log);
        void Get_Assignment                    (AstNode& current, Stream <Token>& example, LogHTML& log);
        void Get_If_Else                       (AstNode& current, Stream <Token>& example, LogHTML& log);
        void Get_While                         (AstNode& current, Stream <Token>& example, LogHTML& log);
        void Get_NewVar                        (AstNode& current, Stream <Token>& example, LogHTML& log);
        void Get_Lexem                         (AstNode& current, Stream <Token>& example, LogHTML& log);
        void Get_Block                         (AstNode& current, Stream <Token>& example, LogHTML& log);
        void Get_ParamsDef                     (AstNode& current, Stream <Token>& example, LogHTML& log);
        void Get_NewFunc                       (AstNode& current, Stream <Token>& example, LogHTML& log);
        void Get_Code                          (AstNode& current, Stream <Token>& example, LogHTML& log);
};

SyntaxAnalyzer :: SyntaxAnalyzer (AstNode& root, Stream <Token>& code, LogHTML& log)
{
    try
    {
        while (code.check ())
        {
            AstNode current;

            Get_Code (current, code, log);

            root.insert (current);
        }
    }
    catch (const char* message)
    {
        std::cout << message << "\n";
    }
}

//===============================================================================

bool SyntaxAnalyzer :: IsLexem (Stream <Token>& example, const int token)
{
    return (example[example.place ()].type == token);
}

//===============================================================================

void SyntaxAnalyzer :: FillStream (Stream <Token>& example, Stream <Token>& tmp, const int delim)
{
    while (example.check () && !IsLexem (example, delim))
    {
        tmp.push_back (example[example.place ()]);

        example++;
    }
}

//===============================================================================

void SyntaxAnalyzer :: Hello_C (std::string& example)
{
    printf ("Input name of C   file: ");

    getline (std::cin, example, '\n');
}

//===============================================================================

void SyntaxAnalyzer :: Error (const char* message, LogHTML& log)
{
    log.output (message);

    throw message;
}

//===============================================================================

void SyntaxAnalyzer :: Get_Number (AstNode& current, Stream <Token>& example, LogHTML& log)
{
    if (example.check () && IsLexem (example, Digit))
    {
        current.key () = example[example.place ()];

        example++;
    }

    else Error ("Expected integer", log);
}

//===============================================================================

void SyntaxAnalyzer :: Get_Name (AstNode& current, Stream <Token>& example, LogHTML& log)
{
    if (example.check () && IsLexem (example, Name))
    {
        current.key () = example[example.place ()];

        example++;
    }

    else Error ("Expected name of variable", log);
}

//===============================================================================

void SyntaxAnalyzer :: Get_Function (AstNode& current, Stream <Token>& example, LogHTML& log)
{
    if (example.check () && example.check_next ({ Name, OpenBracket }))
    {
        current.key () = { Call };
        current.insert ({ example[example.place ()].type, example[example.place ()].value });

        example++;

        AstNode function ({ Params });

        do
        {
            example++;

            Stream <Token> tmp;

            while (example.place () <= example.size () - 2 && !IsLexem (example, Comma))
            {
                tmp.push_back (example[example.place ()]);

                example++;
            }

            if (!tmp.empty ())
            {
                AstNode operation;

                Get_Assignment (operation, tmp, log);

                function.insert (operation);
            }
        }
        while (example.check () && IsLexem (example, Comma));

        if (!IsLexem (example, CloseBracket))
        {
            std::cout << example[example.place ()] << "\n";

            Error ("Expected ')'", log);
        }

        example++;

        current.insert (function);
    }

    else Error ("Expected name of function", log);
}

//===============================================================================

void SyntaxAnalyzer :: Get_Value (AstNode& current, Stream <Token>& example, LogHTML& log)
{
    AstNode value; //else with out; throw

    if (example.check ())
    {
        if (IsLexem (example, Sub))
        {
            example++;

            //value = -Get_Value (example); *-1
        }

        else if (IsLexem (example, Add))
        {
            example++;

            //value = +Get_Value (example); *+1
        }

        else if (IsLexem (example, OpenBracket))
        {
            example++;

            Get_Assignment (value, example, log);

            if (example.check () && IsLexem (example, CloseBracket))
                Error ("Forgot ')'", log);

            example++;
        }

        else if (example.check_next ({ Name, OpenBracket }))
        {
            Stream <Token> tmp;

            while (example.check () && example[example.place ()].type != EndOfToken)
            {
                tmp.push_back (example[example.place ()]);

                example++;
            }

            Get_Function (value, tmp, log);

            //example++;
        }

        else if (IsLexem (example, Name))
        {
            Get_Name (value, example, log);
        }

        else if (IsLexem (example, Digit))
        {
            Get_Number (value, example, log);
        }
    }

    current.move (value);
}

//===============================================================================

void SyntaxAnalyzer :: Get_Mul_Div_Mod (AstNode& current, Stream <Token>& example, LogHTML& log)
{
    AstNode value;
    Get_Value (value, example, log);

    while (example.check () && (example[example.place ()].type == Mul ||
                                example[example.place ()].type == Div ||
                                example[example.place ()].type == Mod))
    {
        int sign = example[example.place ()].type;

        example++;

        AstNode operation;

        if (sign == value.key ().type)
        {
            Get_Value (operation, example, log);
            value.insert (operation);
        }

        else
        {
            operation.key () =  { sign, 0 };
            operation.insert (value);

            Get_Value (value, example, log);
            operation.insert (value);

            value.move (operation);
        }
    }

    current.move (value);
}

//===============================================================================

void SyntaxAnalyzer :: Get_Add_Sub (AstNode& current, Stream <Token>& example, LogHTML& log)
{
    AstNode value;
    Get_Mul_Div_Mod (value, example, log);

    while (example.check () && (example[example.place ()].type == Add ||
                                example[example.place ()].type == Sub))
    {
        int sign = example[example.place ()].type;

        example++;

        AstNode operation;

        if (sign == value.key ().type)
        {
            Get_Mul_Div_Mod (operation, example, log);
            value.insert (operation);
        }

        else
        {
            operation.key () =  { sign, 0 };
            operation.insert (value);

            Get_Mul_Div_Mod (value, example, log);
            operation.insert (value);

            value.move (operation);
        }
    }

    current.move (value);
}

//===============================================================================

void SyntaxAnalyzer :: Get_Less_LessEqual_More_MoreEqual (AstNode& current, Stream <Token>& example, LogHTML& log)
{
    AstNode value;
    Get_Add_Sub (value, example, log);

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
            Get_Add_Sub (operation, example, log);
            value.insert (operation);
        }

        else
        {
            operation.key () =  { sign, 0 };
            operation.insert (value);

            Get_Add_Sub (value, example, log);
            operation.insert (value);

            value.move (operation);
        }
    }

    current.move (value);
}

//===============================================================================

void SyntaxAnalyzer :: Get_Equal_NotEqual (AstNode& current, Stream <Token>& example, LogHTML& log)
{
    AstNode value;
    Get_Less_LessEqual_More_MoreEqual (value, example, log);

    while (example.check () && (example[example.place ()].type == Equal ||
                                example[example.place ()].type == NotEqual))
    {
        int sign = example[example.place ()].type;

        example++;

        AstNode operation;

        if (sign == value.key ().type)
        {
            Get_Less_LessEqual_More_MoreEqual (operation, example, log);
            value.insert (operation);
        }

        else
        {
            operation.key () =  { sign, 0 };
            operation.insert (value);

            Get_Less_LessEqual_More_MoreEqual (value, example, log);
            operation.insert (value);

            value.move (operation);
        }
    }

    current.move (value);
}

//===============================================================================

void SyntaxAnalyzer :: Get_And (AstNode& current, Stream <Token>& example, LogHTML& log)
{
    AstNode value;
    Get_Equal_NotEqual (value, example, log);

    while (example.check () && example[example.place ()].type == And)
    {
        example++;

        AstNode operation;

        Get_Equal_NotEqual (operation, example, log);
        value.insert (operation);
    }

    current.move (value);
}

//===============================================================================

void SyntaxAnalyzer :: Get_Or (AstNode& current, Stream <Token>& example, LogHTML& log)
{
    AstNode value;
    Get_And (value, example, log);

    while (example.check () && example[example.place ()].type == Or)
    {
        example++;

        AstNode operation;

        Get_And (operation, example, log);
        value.insert (operation);
    }

    current.move (value);
}

//===============================================================================

void SyntaxAnalyzer :: Get_Assignment (AstNode& current, Stream <Token>& example, LogHTML& log)
{
    AstNode operation;

    if (example.check_next ({ Token (Name), Token (Assingment) }))
    {
        operation.key () = { Assingment, 0 };

        while (example.check_next ({ Token (Name), Token (Assingment) }))
        {
            AstNode value;
            Get_Name (value, example, log);

            example++;

            operation.insert (value);
        }

        AstNode value;
        Get_Or (value, example, log);
        operation.insert (value);
    }

    else Get_Or (operation, example, log);

    current.move (operation);
}

//===============================================================================

void SyntaxAnalyzer :: Get_If_Else (AstNode& current, Stream <Token>& example, LogHTML& log)
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
    tmp.push_back ({ EndOfToken });

    example++;

    Get_Lexem (current, tmp, log);

    Get_Lexem (current, example, log);

    if (example.check () && example[example.place ()].type == Else)
    {
        example++;

        Get_Lexem (current, example, log);
    }
}

//===============================================================================

void SyntaxAnalyzer :: Get_While (AstNode& current, Stream <Token>& example, LogHTML& log)
{
    example++;

    current.key () = { While };

    example++;

    Stream <Token> tmp;
    while (example.check () && !IsLexem (example, CloseBracket))
    {
        tmp.push_back (example[example.place ()]);

        example++;
    }
    tmp.push_back ({ EndOfToken });

    example++;

    Get_Lexem (current, tmp, log);
    Get_Lexem (current, example, log);
}

//===============================================================================

void SyntaxAnalyzer :: Get_NewVar (AstNode& current, Stream <Token>& example, LogHTML& log)
{
    current.key () = { DeclVar };

    current.insert (example[example.place ()]);

    example++;

    AstNode operation;
    Get_Name (operation, example, log);
    current.insert (operation);

    if (example.check () && IsLexem (example, Assingment))
    {
        example++;

        Stream <Token> tmp;

        while (example.check () && example[example.place ()].type != EndOfToken)
        {
            tmp.push_back (example[example.place ()]);

            example++;
        }

        AstNode value;
        Get_Assignment (value, tmp, log);

        current.insert (value);
    }

    example++;
}

//===============================================================================

void SyntaxAnalyzer :: Get_Lexem (AstNode& current, Stream <Token>& example, LogHTML& log)
{
    Stream <Token> tmp;

    if (example.check ())
    {
        if (IsLexem (example, Begin))
        {
            AstNode grayNode ({ Block, Block });

            Get_Block (grayNode, example, log);

            current.insert (grayNode);
        }

        else if (IsLexem (example, If))
        {
            AstNode operation;

            Get_If_Else (operation, example, log);

            current.insert (operation);
        }

        else if (IsLexem (example, While))
        {
            AstNode operation;

            Get_While (operation, example, log);

            current.insert (operation);
        }

        else if (IsLexem (example, Int))
        {
            AstNode operation;

            Get_NewVar (operation, example, log);

            current.insert (operation);
        }

        else if (IsLexem (example, Return))
        {
            AstNode operation ({ Return });

            example++;

            while (example.check () && example[example.place ()].type != EndOfToken)
            {
                tmp.push_back (example[example.place ()]);

                example++;
            }

            AstNode return_value;

            Get_Assignment (return_value, tmp, log);

            operation.insert (return_value);
            current.insert   (operation);

            example++;
        }

        else if (IsLexem (example, Out))
        {
            AstNode operation ({ Out });

            example++;

            while (example.check () && example[example.place ()].type != EndOfToken)
            {
                tmp.push_back (example[example.place ()]);

                example++;
            }

            AstNode out_value;

            Get_Assignment (out_value, tmp, log);

            operation.insert (out_value);
            current.insert   (operation);

            example++;
        }

        else if (IsLexem (example, Break))
        {
            AstNode operation ({ Break });

            example++;

            current.insert (operation);
        }

        else
        {
            AstNode operation;

            while (example.check () && !IsLexem (example, EndOfToken))
            {
                tmp.push_back (example[example.place ()]);

                example++;
            }

            Get_Assignment (operation, tmp, log);

            current.insert (operation);

            example++;
        }
    }
}

//===============================================================================

void SyntaxAnalyzer :: Get_Block (AstNode& current, Stream <Token>& example, LogHTML& log)
{
    current.key () = { Block };

    if (example.check () && IsLexem (example, Begin))
    {
        example++;

        while (example.check () && example[example.place ()].type != End)
            Get_Lexem (current, example, log);

        example++;
    }

    else Error ("Expected '{'", log);
}

//===============================================================================

void SyntaxAnalyzer :: Get_ParamsDef (AstNode& current, Stream <Token>& example, LogHTML& log)
{
    do
    {
        example++;

        if (IsLexem (example, Int))
        {
            AstNode operation ({ DeclVar });

            operation.insert ({ Int });

            example++;

            AstNode value;
            Get_Name (value, example, log);

            operation.insert (value);
            current.insert (operation);
        }
    }
    while (IsLexem (example, Comma));

    if (!IsLexem (example, CloseBracket)) Error ("Expected )", log);

    example++;
}

//===============================================================================

void SyntaxAnalyzer :: Get_NewFunc (AstNode& current, Stream <Token>& example, LogHTML& log)
{
    current.key () = { DeclFunc };

    if (IsLexem (example, Int)) current.insert ({ Int });

    example++;

    AstNode value;
    Get_Name (value, example, log);
    current.insert (value);

    AstNode params ({ Params });
    Get_ParamsDef  (params, example, log);
    current.insert (params);

    if (IsLexem (example, EndOfToken))
    {
        example++;

        return;
    }

    if (IsLexem (example, Begin))
    {
        AstNode block;
        Get_Block      (block, example, log);
        current.insert (block);
    }

    else Error ("Expected ';' or '{'", log);
}

//===============================================================================

void SyntaxAnalyzer :: Get_Code (AstNode& current, Stream <Token>& example, LogHTML& log)
{
    if (example.check ())
    {
        if (example.check_next ({ Int, Name, OpenBracket }))
            Get_NewFunc (current, example, log);

        else if (example.check_next ({ Int, Name, Assingment }))
            Get_NewVar (current, example, log);

        else if (example.check_next ({ Int, Name, EndOfToken }))
            Get_NewVar (current, example, log);

        else Error ("Expected declaration of function or variable", log);
    }
}

#endif
