#ifndef SyntaxAnalyzer_hpp

#define SyntaxAnalyzer_hpp

#include <cstdio>
#include <iostream>
#include "Token.hpp"
#include "..//..//Libraries//Stream.hpp"
#include "..//..//Libraries//AbstractSyntaxNode.hpp"
#include "..//..//Libraries//LogHTML.hpp"

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

namespace CAP
{
    class SyntaxAnalyzer
    {
        public:
            SyntaxAnalyzer ();

            void parsing (Stream <Token>& from, AstNode& to, LogHTML& log);

        private:
            void Get_Number                        (Stream <Token>& from, AstNode& to, LogHTML& log);
            void Get_Name                          (Stream <Token>& from, AstNode& to, LogHTML& log);
            void Get_Function                      (Stream <Token>& from, AstNode& to, LogHTML& log);
            void Get_Value                         (Stream <Token>& from, AstNode& to, LogHTML& log);
            void Get_Mul_Div_Mod                   (Stream <Token>& from, AstNode& to, LogHTML& log);
            void Get_Add_Sub                       (Stream <Token>& from, AstNode& to, LogHTML& log);
            void Get_Less_LessEqual_More_MoreEqual (Stream <Token>& from, AstNode& to, LogHTML& log);
            void Get_And                           (Stream <Token>& from, AstNode& to, LogHTML& log);
            void Get_Or                            (Stream <Token>& from, AstNode& to, LogHTML& log);
            void Get_Equal_NotEqual                (Stream <Token>& from, AstNode& to, LogHTML& log);
            void Get_Assignment                    (Stream <Token>& from, AstNode& to, LogHTML& log);
            void Get_If_Else                       (Stream <Token>& from, AstNode& to, LogHTML& log);
            void Get_While                         (Stream <Token>& from, AstNode& to, LogHTML& log);
            void Get_NewVar                        (Stream <Token>& from, AstNode& to, LogHTML& log);
            void Get_Lexem                         (Stream <Token>& from, AstNode& to, LogHTML& log);
            void Get_Block                         (Stream <Token>& from, AstNode& to, LogHTML& log);
            void Get_ParamsDef                     (Stream <Token>& from, AstNode& to, LogHTML& log);
            void Get_NewFunc                       (Stream <Token>& from, AstNode& to, LogHTML& log);
            void Get_Code                          (Stream <Token>& from, AstNode& to, LogHTML& log);
    };
}

CAP::SyntaxAnalyzer::SyntaxAnalyzer ()
{
}

void CAP::SyntaxAnalyzer::parsing (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    try
    {
        while (from.check ())
        {
            AstNode to;

            Get_Code (from, to, log);

            to.insert (to);
        }
    }
    catch (const char* message)
    {
        std::cout << message << "\n";
    }
}

void CAP::SyntaxAnalyzer::Get_Number (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    if (from.check () && IsLexem (from.current (), Digit))
    {
        to.key () = from.current ();

        from++;
    }

    else LogError (log, "Expected integer");
}

void CAP::SyntaxAnalyzer::Get_Name (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    if (from.check () && IsLexem (from.current (), Name))
    {
        to.key () = from.current ();

        from++;
    }

    else LogError (log, "Expected name of variable");
}

void CAP::SyntaxAnalyzer::Get_Function (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    if (from.check () && from.check_next ({ Name, OpenBracket }))
    {
        to.key () = { Call };
        to.insert ({ from.current ().type, from.current ().value });

        from++;

        AstNode function ({ Params });

        do
        {
            from++;

            Stream <Token> tmp;

            while (from.place () <= from.size () - 2 && !IsLexem (from.current (), Comma))
            {
                tmp.push_back (from.current ());

                from++;
            }

            if (!tmp.empty ())
            {
                AstNode operation;

                Get_Assignment (tmp, operation, log);

                function.insert (operation);
            }
        }
        while (from.check () && IsLexem (from.current (), Comma));

        if (!IsLexem (from.current (), CloseBracket))
        {
            std::cout << from.current () << "\n";

            LogError (log, "Expected ')'");
        }

        from++;

        to.insert (function);
    }

    else LogError (log, "Expected name of function");
}

void CAP::SyntaxAnalyzer::Get_Value (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    AstNode value; //else with out; throw

    if (from.check ())
    {
        if (IsLexem (from.current (), Sub))
        {
            from++;

            //value = -Get_Value (from); *-1
        }

        else if (IsLexem (from.current (), Add))
        {
            from++;

            //value = +Get_Value (from); *+1
        }

        else if (IsLexem (from.current (), OpenBracket))
        {
            from++;

            Get_Assignment (from, value, log);

            if (from.check () && IsLexem (from.current (), CloseBracket))
                LogError (log, "Forgot ')'");

            from++;
        }

        else if (from.check_next ({ Name, OpenBracket }))
        {
            Stream <Token> tmp;

            while (from.check () && from.current ().type != EndOfToken)
            {
                tmp.push_back (from.current ());

                from++;
            }

            Get_Function (tmp, value, log);

            //from++;
        }

        else if (IsLexem (from.current (), Name))
        {
            Get_Name (from, value, log);
        }

        else if (IsLexem (from.current (), Digit))
        {
            Get_Number (from, value, log);
        }
    }

    to.move (value);
}

void CAP::SyntaxAnalyzer::Get_Mul_Div_Mod (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    AstNode value;
    Get_Value (from, value, log);

    while (from.check () && (from.current ().type == Mul ||
                             from.current ().type == Div ||
                             from.current ().type == Mod))
    {
        int sign = from.current ().type;

        from++;

        AstNode operation;

        if (sign == value.key ().type)
        {
            Get_Value (from, operation, log);
            value.insert (operation);
        }

        else
        {
            operation.key () =  { sign, 0 };
            operation.insert (value);

            Get_Value (from, value, log);
            operation.insert (value);

            value.move (operation);
        }
    }

    to.move (value);
}

void CAP::SyntaxAnalyzer::Get_Add_Sub (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    AstNode value;
    Get_Mul_Div_Mod (from, value, log);

    while (from.check () && (from.current ().type == Add ||
                             from.current ().type == Sub))
    {
        int sign = from.current ().type;

        from++;

        AstNode operation;

        if (sign == value.key ().type)
        {
            Get_Mul_Div_Mod (from, operation, log);
            value.insert (operation);
        }

        else
        {
            operation.key () =  { sign, 0 };
            operation.insert (value);

            Get_Mul_Div_Mod (from, value, log);
            operation.insert (value);

            value.move (operation);
        }
    }

    to.move (value);
}

void CAP::SyntaxAnalyzer::Get_Less_LessEqual_More_MoreEqual (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    AstNode value;
    Get_Add_Sub (from, value, log);

    while (from.check () && (from.current ().type == Less      ||
                             from.current ().type == LessEqual ||
                             from.current ().type == More      ||
                             from.current ().type == MoreEqual))
    {
        int sign = from.current ().type;

        from++;

        AstNode operation;

        if (sign == value.key ().type)
        {
            Get_Add_Sub (from, operation, log);
            value.insert (operation);
        }

        else
        {
            operation.key () =  { sign, 0 };
            operation.insert (value);

            Get_Add_Sub (from, value, log);
            operation.insert (value);

            value.move (operation);
        }
    }

    to.move (value);
}

void CAP::SyntaxAnalyzer::Get_Equal_NotEqual (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    AstNode value;
    Get_Less_LessEqual_More_MoreEqual (from, value, log);

    while (from.check () && (from.current ().type == Equal ||
                                from.current ().type == NotEqual))
    {
        int sign = from.current ().type;

        from++;

        AstNode operation;

        if (sign == value.key ().type)
        {
            Get_Less_LessEqual_More_MoreEqual (from, operation, log);
            value.insert (operation);
        }

        else
        {
            operation.key () =  { sign, 0 };
            operation.insert (value);

            Get_Less_LessEqual_More_MoreEqual (from, value, log);
            operation.insert (value);

            value.move (operation);
        }
    }

    to.move (value);
}

void CAP::SyntaxAnalyzer::Get_And (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    AstNode value;
    Get_Equal_NotEqual (from, value, log);

    while (from.check () && from.current ().type == And)
    {
        from++;

        AstNode operation;

        Get_Equal_NotEqual (from, operation, log);
        value.insert (operation);
    }

    to.move (value);
}

void CAP::SyntaxAnalyzer::Get_Or (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    AstNode value;
    Get_And (from, value, log);

    while (from.check () && from.current ().type == Or)
    {
        from++;

        AstNode operation;

        Get_And (from, operation, log);
        value.insert (operation);
    }

    to.move (value);
}

void CAP::SyntaxAnalyzer::Get_Assignment (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    AstNode operation;

    if (from.check_next ({ Token (Name), Token (Assingment) }))
    {
        operation.key () = { Assingment, 0 };

        while (from.check_next ({ Token (Name), Token (Assingment) }))
        {
            AstNode value;
            Get_Name (from, value, log);

            from++;

            operation.insert (value);
        }

        AstNode value;
        Get_Or (from, value, log);
        operation.insert (value);
    }

    else Get_Or (from, operation, log);

    to.move (operation);
}

void CAP::SyntaxAnalyzer::Get_If_Else (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    from++;

    to.key () = { If, 0 };

    from++;

    Stream <Token> tmp;
    while (from.check () && from.current ().type != CloseBracket)
    {
        tmp.push_back (from.current ());

        from++;
    }
    tmp.push_back ({ EndOfToken });

    from++;

    Get_Lexem (tmp, to, log);

    Get_Lexem (from, to, log);

    if (from.check () && from.current ().type == Else)
    {
        from++;

        Get_Lexem (from, to, log);
    }
}

void CAP::SyntaxAnalyzer::Get_While (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    from++;

    to.key () = { While };

    from++;

    Stream <Token> tmp;
    while (from.check () && !IsLexem (from.current (), CloseBracket))
    {
        tmp.push_back (from.current ());

        from++;
    }
    tmp.push_back ({ EndOfToken });

    from++;

    Get_Lexem ( tmp, to, log);
    Get_Lexem (from, to, log);
}

void CAP::SyntaxAnalyzer::Get_NewVar (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    to.key () = { DeclVar };

    to.insert (from.current ());

    from++;

    AstNode operation;
    Get_Name (from, operation, log);
    to.insert (operation);

    if (from.check () && IsLexem (from.current (), Assingment))
    {
        from++;

        Stream <Token> tmp;

        while (from.check () && from.current ().type != EndOfToken)
        {
            tmp.push_back (from.current ());

            from++;
        }

        AstNode value;
        Get_Assignment (tmp, value, log);

        to.insert (value);
    }

    from++;
}

void CAP::SyntaxAnalyzer::Get_Lexem (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    Stream <Token> tmp;

    if (from.check ())
    {
        if (IsLexem (from.current (), Begin))
        {
            AstNode grayNode ({ Block, Block });

            Get_Block (from, grayNode, log);

            to.insert (grayNode);
        }

        else if (IsLexem (from.current (), If))
        {
            AstNode operation;

            Get_If_Else (from, operation, log);

            to.insert (operation);
        }

        else if (IsLexem (from.current (), While))
        {
            AstNode operation;

            Get_While (from, operation, log);

            to.insert (operation);
        }

        else if (IsLexem (from.current (), Int))
        {
            AstNode operation;

            Get_NewVar (from, operation, log);

            to.insert (operation);
        }

        else if (IsLexem (from.current (), Return))
        {
            AstNode operation ({ Return });

            from++;

            while (from.check () && from.current ().type != EndOfToken)
            {
                tmp.push_back (
                from.current ());

                from++;
            }

            AstNode return_value;

            Get_Assignment (tmp, return_value, log);

            operation.insert (return_value);
            to.insert   (operation);

            from++;
        }

        else if (IsLexem (from.current (), Out))
        {
            AstNode operation ({ Out });

            from++;

            while (from.check () && from.current ().type != EndOfToken)
            {
                tmp.push_back (from.current ());

                from++;
            }

            AstNode out_value;

            Get_Assignment (tmp, out_value, log);

            operation.insert (out_value);
            to.insert   (operation);

            from++;
        }

        else if (IsLexem (from.current (), Break))
        {
            AstNode operation ({ Break });

            from++;

            to.insert (operation);
        }

        else
        {
            AstNode operation;

            while (from.check () && !IsLexem (from.current (), EndOfToken))
            {
                tmp.push_back (from.current ());

                from++;
            }

            Get_Assignment (tmp, operation, log);

            to.insert (operation);

            from++;
        }
    }
}

void CAP::SyntaxAnalyzer::Get_Block (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    to.key () = { Block };

    if (from.check () && IsLexem (from.current (), Begin))
    {
        from++;

        while (from.check () && from.current ().type != End)
            Get_Lexem ((from, to, log););

        from++;
    }

    else LogError (log, "Expected '{'");
}

void CAP::SyntaxAnalyzer::Get_ParamsDef (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    do
    {
        from++;

        if (IsLexem (from.current (), Int))
        {
            AstNode operation ({ DeclVar });

            operation.insert ({ Int });

            from++;

            AstNode value;
            Get_Name (from, value, log);

            operation.insert (value);
            to.insert (operation);
        }
    }
    while (IsLexem (from.current (), Comma));

    if (!IsLexem (from.current (), CloseBracket)) LogError (log, "Expected )");

    from++;
}

void CAP::SyntaxAnalyzer::Get_NewFunc (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    to.key () = { DeclFunc };

    if (IsLexem (from.current (), Int)) to.insert ({ Int });

    from++;

    AstNode value;
    Get_Name (from, value, log);
    to.insert (value);

    AstNode params ({ Params });
    Get_ParamsDef  (from, params, log);
    to.insert (params);

    if (IsLexem (from.current (), EndOfToken))
    {
        from++;

        return;
    }

    if (IsLexem (from.current (), Begin))
    {
        AstNode block;
        Get_Block (from, block, log);
        to.insert (block);
    }

    else LogError (log, "Expected ';' or '{'");
}

void CAP::SyntaxAnalyzer::Get_Code (Stream <Token>& from, AstNode& to, LogHTML& log)
{
    if (from.check ())
    {
        if (from.check_next ({ Int, Name, OpenBracket }))
            Get_NewFunc (from, to, log);

        else if (from.check_next ({ Int, Name, Assingment }))
            Get_NewVar (from, to, log);

        else if (from.check_next ({ Int, Name, EndOfToken }))
            Get_NewVar (from, to, log);

        else LogError (log, "Expected declaration of function or variable");
    }
}

#endif /* SyntaxAnalyzer_hpp */
