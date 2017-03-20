#ifndef DisSyntaxAnalyzer_hpp

#define DisSyntaxAnalyzer_hpp

namespace CAP
{
    class DisSyntaxAnalyzer
    {
        public:
            DisSyntaxAnalyzer ();

            void parsing (AstNode& from, Stream <char>& to);

        private:
            void check (AstNode* from, Stream <char>& to);

            void get              (AstNode* from, Stream <char>& to);
            void decl_block       (AstNode* from, Stream <char>& to);
            void decl_var         (AstNode* from, Stream <char>& to);
            void binary_operation (AstNode* from, Stream <char>& to);
            void decl_if          (AstNode* from, Stream <char>& to);
            void decl_while       (AstNode* from, Stream <char>& to);
            void decl_func        (AstNode* from, Stream <char>& to);
    };
}

void CAP::DisSyntaxAnalyzer::parsing (AstNode& from, Stream <char>& to)
{
    for (int i = 0; i < from.size (); i++)
        check (from[i], to);
}

void CAP::DisSyntaxAnalyzer::check (AstNode* from, Stream <char>& to)
{
    #define DEER(id, name, word, fontcolor, color, fillcolor, shape, style, code_generation, dis_syntax_analyzer) case id: { dis_syntax_analyzer break; }

    switch (from->key ().type)
    {
        #include "CList.inl"

        default: { std::cout << from->key ().type << "\n"; throw "default: error"; }
    }

    #undef DEER
}

void CAP::DisSyntaxAnalyzer::get (AstNode* from, Stream <char>& to)
{
    #define DEER(id, name, word, fontcolor, color, fillcolor, shape, style, code_generation, dis_syntax_analyzer) case id: { to += word; break; }

    switch (from->key ().type)
    {
        #include "CList.inl"

        default: { std::cout << from->key ().type << "\n"; throw "default: error"; }
    }

    #undef DEER
}

void CAP::DisSyntaxAnalyzer::decl_block (AstNode* from, Stream <char>& to)
{
    to.push_back ('{');

    for (int i = 0; i < from->size (); i++)
        check (from[i], to);

    to.push_back ('}');
}

void CAP::DisSyntaxAnalyzer::decl_var (AstNode* from, Stream <char>& to)
{
    check (from[0], to);
    check (from[1], to);

    to.push_back ('=');

    check (from[2], to);

    to.push_back (';');
}

void CAP::DisSyntaxAnalyzer::binary_operation (AstNode* from, Stream <char>& to)
{
    check (from[0], to);

    get (from);

    check (from[1], to);

    to.push_back (';');
}

void CAP::DisSyntaxAnalyzer::decl_if (AstNode* from, Stream <char>& to)
{
    get (from);

    to.push_back ('(');

    check (from[0], to);

    to.push_back (')');

    check (from[1], to);

    if (from->size () == 3)
    {
        to += "else";

        check (from[2], to);
    }
}

void CAP::DisSyntaxAnalyzer::decl_while (AstNode* from, Stream <char>& to)
{
    get (from);

    to.push_back ('(');

    check (from[0], to);

    to.push_back (')');

    check (from[1], to);
}

void CAP::DisSyntaxAnalyzer::decl_func (AstNode* from, Stream <char>& to)
{
    check (from[0], to);
    check (from[1], to);

    to.push_back ('(');

    for (int i = 0; i < from[2]->size (); i++)
        check (from[2][i], to);

    to.push_back (')');

    to.push_back ('{');

    check (from[3], to);

    to.push_back ('}');
}

#endif /* DisSyntaxAnalyzer_hpp */
