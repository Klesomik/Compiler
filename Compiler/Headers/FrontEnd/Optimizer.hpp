class Optimizer
{
    public:
        Optimizer (AstNode& root);

        int detour (AstNode* current);
};

Optimizer:: Optimizer (AstNode& root)
{
    try
    {
        for (size_t i = 0; i < root.children ().size (); i++)
            detour (root.children ()[i]);
    }
    catch (const char* message)
    {
        printf ("%s\n", message);
    }
    catch (char const* message)
    {
        printf ("%s\n", message);
    }
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
            int answer = current -> children ()[0] -> key ().value;

            for (size_t i = 1; i < current -> size (); i++)
                answer += detour (current -> children ()[i]);

            AstNode tmp ({ Digit, answer });
            current -> parent () -> insert (tmp);

            current -> erase ();

            break;
        }

        case   Sub:
        {
            int answer = current -> children ()[0] -> key ().value;

            for (size_t i = 1; i < current -> size (); i++)
                answer -= detour (current -> children ()[i]);

            AstNode tmp ({ Digit, answer });
            current -> parent () -> insert (tmp);

            current -> erase ();

            break;
        }

        case   Mul:
        {
            int answer = current -> children ()[0] -> key ().value;

            for (size_t i = 1; i < current -> size (); i++)
                answer *= detour (current -> children ()[i]);

            AstNode tmp ({ Digit, answer });
            current -> parent () -> insert (tmp);

            current -> erase ();

            current -> parent () -> dump ();

            break;
        }

        case   Div:
        {
            int answer = current -> children ()[0] -> key ().value;

            for (size_t i = 1; i < current -> size (); i++)
                answer /= detour (current -> children ()[i]);

            AstNode tmp ({ Digit, answer });
            current -> parent () -> insert (tmp);

            current -> erase ();

            break;
        }

        case   Mod:
        {
            int answer = current -> children ()[0] -> key ().value;

            for (size_t i = 1; i < current -> size (); i++)
                answer %= detour (current -> children ()[i]);

            AstNode tmp ({ Digit, answer });
            current -> parent () -> insert (tmp);

            current -> erase ();

            break;
        }

        default:
        {
            for (size_t i = 0; i < current -> size (); i++)
                detour (current -> children ()[i]);
        }
    }

    return 0;
}
