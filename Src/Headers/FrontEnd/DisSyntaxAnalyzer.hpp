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
            void check (AstNode& root);

            void black (AstNode* from, Stream <char>& to);
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

void CAP::DisSyntaxAnalyzer::block (AstNode* from, Stream <char>& to)
{
    to.push_back ('{');

    for (int i = 0; i < from->size (); i++)
        check (from[i], to);

    to.push_back ('}');
}

void CAP::DisSyntaxAnalyzer::decl_var (AstNode* from, Stream <char>& to)
{
    for (int i = 0; i < from->size (); i++)
        check (from[i], to);

    to.push_back (';');
}

void CAP::DisSyntaxAnalyzer::Int (AstNode* from, Stream <char>& to)
{
    to += "int";
}

void CAP::DisSyntaxAnalyzer::name (AstNode* from, Stream <char>& to)
{
    to += std::to_string (from->key ().value);
}

void CAP::DisSyntaxAnalyzer::digit (AstNode* from, Stream <char>& to)
{
    to += std::to_string (from->key ().value);
}

#endif /* DisSyntaxAnalyzer_hpp */
