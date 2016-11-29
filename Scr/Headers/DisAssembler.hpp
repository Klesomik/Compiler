class DisAssembler
{
    public:
        void run (Stream <int>& in, Stream <BoaToken>& out);
};

void DisAssembler::run (Stream <int>& in, Stream <BoaToken>& out)
{
    #define BOA_1(id, params, name, word, comp, cpu) case id: { out.push_back (name); break; }
    #define BOA_2(id, params, name, word, comp, cpu) case id: { out.push_back (name); break; }
    #define BOA_3(id, params, name, word, comp, cpu) case id: { out.push_back (name); break; }
    #define BOA_4(id, params, name, word, comp, cpu) case id: { out.push_back (name); break; }

    for (int i = 0; i < in.size (); i++)
    {
        switch (in[i])
        {
            #include "BackEnd//BoaList.hpp"

            default:
            {
                in.dump ();
                out.dump ();

                throw "Error\n";
            }
        }
    }

    in.dump ();
    out.dump ();
}
