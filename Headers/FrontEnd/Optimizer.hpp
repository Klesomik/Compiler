typedef std::pair <bool, int> ret_t;

class Optimizer
{
    public:
        Optimizer (AstNode& root);

        ret_t check_Add (AstNode* current);
        ret_t check_Sub (AstNode* current);
        ret_t check_Mul (AstNode* current);
        ret_t check_Div (AstNode* current);
        ret_t check_Mod (AstNode* current);

        ret_t detour (AstNode* current);
};

Optimizer :: Optimizer (AstNode& root)
{
    try
    {
        for (size_t i = 0; i < root.children ().size (); i++)
            detour (root.children ()[i]);
    }
    catch (const char* message)
    {
        std::cout << message << "\n";
    }
    catch (const std::string message)
    {
        std::cout << message << "\n";
    }
    catch (const int message)
    {
        std::cout << message << "\n";
    }
}

ret_t Optimizer :: detour (AstNode* current)
{
    switch (current -> key ().type)
    {
        case Digit: { current -> erase (); return ret_t  (true, current -> key ().value); }

        case Add: { return check_Add (current); }
        case Sub: { return check_Sub (current); }
        case Mul: { return check_Mul (current); }
        case Div: { return check_Div (current); }
        case Mod: { return check_Mod (current); }

        default:
        {
            for (size_t i = 0; i < current -> size (); i++)
            {
                ret_t eps = detour (current -> children ()[i]);

                if (eps.first) current -> insert ({ Digit, eps.second });
            }

            break;
        }
    }

    return ret_t (false, current -> key ().value);
}

ret_t Optimizer :: check_Add (AstNode* current)
{
    int answer = 0;

    bool now = false;
    for (size_t i = 0; i < current -> size ();)
    {
        ret_t eps = detour (current -> children ()[i]);

        if (eps.first)
        {
            answer += eps.second;

            now = true;
        }

        else i++;
    }

    if (current -> size () == 0)
    {
        current -> erase ();

        return ret_t (true, answer);
    }

    else if (now) current -> insert ({ Digit, answer });

    return ret_t (false, answer);
}

ret_t Optimizer :: check_Sub (AstNode* current)
{
    int answer = 0;

    bool now = false;
    for (size_t i = 0; i < current -> size ();)
    {
        ret_t eps = detour (current -> children ()[i]);

        if (eps.first)
        {
            answer -= eps.second;

            now = true;
        }

        else i++;
    }

    if (current -> size () == 0)
    {
        current -> erase ();

        return ret_t (true, answer);
    }

    else if (now) current -> insert ({ Digit, answer });

    return ret_t (false, answer);
}

ret_t Optimizer :: check_Mul (AstNode* current)
{
    int answer = 1;

    bool now = false;
    for (size_t i = 0; i < current -> size ();)
    {
        ret_t eps = detour (current -> children ()[i]);

        if (eps.first)
        {
            answer *= eps.second;

            now = true;
        }

        else i++;
    }

    if (current -> size () == 0)
    {
        current -> erase ();

        return ret_t (true, answer);
    }

    else if (now) current -> insert ({ Digit, answer });

    return ret_t (false, answer);
}

ret_t Optimizer :: check_Div (AstNode* current)
{
    int answer = 0;

    bool now = false;
    for (size_t i = 0; i < current -> size ();)
    {
        ret_t eps = detour (current -> children ()[i]);

        if (eps.first)
        {
            answer /= eps.second;

            now = true;
        }

        else i++;
    }

    if (current -> size () == 0)
    {
        current -> erase ();

        return ret_t (true, answer);
    }

    else if (now) current -> insert ({ Digit, answer });

    return ret_t (false, answer);
}

ret_t Optimizer :: check_Mod (AstNode* current)
{
    int answer = 0;

    bool now = false;
    for (size_t i = 0; i < current -> size ();)
    {
        ret_t eps = detour (current -> children ()[i]);

        if (eps.first)
        {
            answer %= eps.second;

            now = true;
        }

        else i++;
    }

    if (current -> size () == 0)
    {
        current -> erase ();

        return ret_t (true, answer);
    }

    else if (now) current -> insert ({ Digit, answer });

    return ret_t (false, answer);
}
