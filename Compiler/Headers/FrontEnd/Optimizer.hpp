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
        case Digit:
        {
            int val = current -> key ().value;

            current -> erase ();

            return val;
        }

        case   Add:
        {
            int answer = 0;

            for (size_t i = 0; i < current -> size (); i++)
            {
                cout << "answer = " << answer << "\n";

                answer += detour (current -> children ()[i]);
            }

            cout << "answer = " << answer << "\n";

            if (current -> size () == 0)
            {
                AstNode tmp ({ Digit, answer });
                current -> parent () -> insert (tmp);

                current -> erase ();
            }

            return answer;
        }

        case   Sub:
        {
            int answer = 0;

            for (size_t i = 0; i < current -> size (); i++)
                answer -= detour (current -> children ()[i]);

            if (current -> size () == 0)
            {
                AstNode tmp ({ Digit, answer });
                current -> parent () -> insert (tmp);

                current -> erase ();
            }

            return answer;
        }

        case   Mul:
        {
            int answer = 0;

            for (size_t i = 0; i < current -> size (); i++)
                answer *= detour (current -> children ()[i]);

            if (current -> size () == 0)
            {
                AstNode tmp ({ Digit, answer });
                current -> parent () -> insert (tmp);

                current -> erase ();
            }

            return answer;
        }

        case   Div:
        {
            int answer = 0;

            for (size_t i = 0; i < current -> size (); i++)
                answer /= detour (current -> children ()[i]);

            if (current -> size () == 0)
            {
                AstNode tmp ({ Digit, answer });
                current -> parent () -> insert (tmp);

                current -> erase ();
            }

            return answer;
        }

        case   Mod:
        {
            int answer = 0;

            for (size_t i = 0; i < current -> size (); i++)
                answer %= detour (current -> children ()[i]);

            if (current -> size () == 0)
            {
                AstNode tmp ({ Digit, answer });
                current -> parent () -> insert (tmp);

                current -> erase ();
            }

            return answer;
        }

        default:
        {
            for (size_t i = 0; i < current -> size (); i++)
                detour (current -> children ()[i]);

            break;
        }
    }

    return 0;
}
