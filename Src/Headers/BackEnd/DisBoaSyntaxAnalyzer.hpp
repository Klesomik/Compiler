class DisBoaSyntaxAnalyzer
{
    public:
        void parsing (Stream <int>& from, Stream <BoaToken>& to);

    private:
        void cmd_push (Stream <int>& from, Stream <BoaToken>& to);
};

void DisBoaSyntaxAnalyzer::parsing (Stream <int>& from, Stream <BoaToken>& to)
{
    while (from.check ())
    {
        to.push_back ({ from.current (), 0 });

        #define BOA(id, params, name, word, comp, cpu) case id: { break; }

        switch (from.current ())
        {
            #include "BoaList.inl"

            default: { break; }
        }

        #undef BOA
    }
}

void DisBoaSyntaxAnalyzer::cmd_push (Stream <int>& from, Stream <BoaToken>& to)
{
    from++;

    to.back ().value = from.current ();

    from++;
}
