#include "TXLib.h"

class MyExeption : public std::exception
{
    private:
        const char* file_,
                    func_,
                    line_;

    public:
        MyExeption (const char* set_file, set_func, set_line);

        const char* what ();
};

MyExeption (const char* set_file, const char* set_func, const char* set_line):
    file_ (set_file),
    func_ (set_func),
    line_ (set_line)
    {}

const char* MyExeption :: what ()
{
    char message[2048] = "";

    size_t indent = 0;

    indent += sprintf (message + indent, "Message was tried at\n");

    indent += sprintf (message + indent, "  FILE: %s\n", file_try);
    indent += sprintf (message + indent, "  FUNC: %s\n", function_try);
    indent += sprintf (message + indent, "  LINE: %d\n", line_try);

    indent += sprintf (message + indent, "Message was threw at\n");

    indent += sprintf (message + indent, "  FILE: %s\n", file_throw);
    indent += sprintf (message + indent, "  FUNC: %s\n", function_throw);
    indent += sprintf (message + indent, "  LINE: %d\n", line_throw);

    indent += sprintf (message + indent, "%s\n", label);

    sprintf (message + indent, "Message was wrapped in Wrapper\n");

    return;
}

int main ()
{
    int x = 0;
    cin >> x;

    try
    {
        if (x == 5) throw MyExeption ();
    }
    catch (MyExeption& message)
    {
        cout << message.what ();
    }

    return 0;
}
