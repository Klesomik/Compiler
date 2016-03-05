class Optimizer
{
    public:
        Optimizer (AstNode& root);

        int detour (AstNode* current);
};

Optimizer:: Optimizer (AstNode& root)
{
    for (size_t i = 0; i < root.children ().size (); i++)
        detour (root.children ()[i]);
}

int Optimizer:: detour (AstNode* current)
{
    switch (current -> key ().type)
    {
        case  None:
        {
            for (size_t i = 0; i < current -> children ().size (); i++)
                detour (current -> children ()[i]);
        }

        case Digit: { return current -> key ().value; }

        case   Add:
        {
            int answer = 0;

            for (size_t i = 0; i < current -> children ().size (); i++)
                answer += detour (current -> children ()[i]);

            current -> parent () -> insert (answer);
            current -> erase ();

            break;
        }

        case   Sub:
        {
            int answer = 0;

            for (size_t i = 0; i < current -> children ().size (); i++)
                answer -= detour (current -> children ()[i]);

            current -> parent () -> insert (answer);
            current -> erase ();

            break;
        }

        case   Mul:
        {
            int answer = 0;

            for (size_t i = 0; i < current -> children ().size (); i++)
                answer *= detour (current -> children ()[i]);

            current -> parent () -> insert (answer);
            current -> erase ();

            break;
        }

        case   Div:
        {
            int answer = 0;

            for (size_t i = 0; i < current -> children ().size (); i++)
                answer /= detour (current -> children ()[i]);

            current -> parent () -> insert (answer);
            current -> erase ();

            break;
        }

        case   Mod:
        {
            int answer = 0;

            for (size_t i = 0; i < current -> children ().size (); i++)
                answer %= detour (current -> children ()[i]);

            current -> parent () -> insert (answer);
            current -> erase ();

            break;
        }

        default:
        {
            for (size_t i = 0; i < current -> children ().size (); i++)
                detour (current -> children ()[i]);
        }
    }
}
