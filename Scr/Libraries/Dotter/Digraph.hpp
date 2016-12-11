#ifndef Digraph_hpp

#define Digraph_hpp

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdarg>

//TODO: Many setters and no getters, add ios::app with Boost streams

namespace Dotter
{
    class Digraph
    {
        private:
            FILE* dotFile_;

            const char* dotName_;
            const char* renderName_;

            size_t cluster_;
            size_t indent_;

            Digraph& operator = (const Digraph& from);

        public:
            Digraph ();
            Digraph (const char* setDotName);
            Digraph (const char* setDotName, const char* setRenderName);
            Digraph (Digraph&  from);
            Digraph (Digraph&& from);

            ~Digraph ();

            void open  ();
            void open  (const char* setDotName);
            void close ();

            void begin ();
            void end   ();

            void set (const char* comand, const char* param);

            void node (const size_t number, const char* label, ...);
            void link (const size_t from, const size_t to, const char* label, ...);

            void comment (const char* label, ...);

            void render (const char* path, const bool show = true);

            bool ok   () const;
            void dump () const;

            void setNodeShape (const char* param);
            void setNodeColor (const char* param);

            FILE*       DotFile    () const;
            const char* DotName    () const;
            const char* RenderName () const;

            const char* DotName    ();
            const char* RenderName ();
    };
}

Dotter::Digraph::Digraph ():
    dotFile_    (nullptr),
    dotName_    (nullptr),
    renderName_ (nullptr),
    cluster_    (0),
    indent_     (0)
{
}

Dotter::Digraph::Digraph (const char* setDotName):
    dotFile_    (nullptr),
    dotName_    (setDotName),
    renderName_ (nullptr),
    cluster_    (0),
    indent_     (0)
{
}

Dotter::Digraph::Digraph::Digraph (const char* setDotName, const char* setRenderName):
    dotFile_    (nullptr),
    dotName_    (setDotName),
    renderName_ (setRenderName),
    cluster_    (0),
    indent_     (0)
{
}

Dotter::Digraph::Digraph (Digraph& from):
    dotFile_    (from.dotFile_),
    dotName_    (from.dotName_),
    renderName_ (from.renderName_),
    cluster_    (from.cluster_),
    indent_     (from.indent_)
{
}

Dotter::Digraph::Digraph (Digraph&& from):
    dotFile_    (nullptr),
    dotName_    (nullptr),
    renderName_ (nullptr),
    cluster_    (0),
    indent_     (0)
{
}

Dotter::Digraph::~Digraph ()
{
    close ();
}

void Dotter::Digraph::open ()
{
    if (!dotFile_)
    {
        dotFile_ = fopen (dotName_, "w");

        fprintf (dotFile_, "digraph Hello\n");
        fprintf (dotFile_, "{\n");

        begin ();
    }
}

void Dotter::Digraph::open (const char* setDotName)
{
    if (!dotFile_)
    {
        dotFile_ = fopen (setDotName, "w");
        dotName_ = setDotName;

        fprintf (dotFile_, "digraph Hello\n");
        fprintf (dotFile_, "{\n");

        begin ();
    }
}

void Dotter::Digraph::close ()
{
    if (dotFile_)
    {
        fprintf (dotFile_, "}\n");

        end ();

        comment (" Build with Dotter ");

        fclose (dotFile_);
                dotFile_ = nullptr;
    }
}

void Dotter::Digraph::begin ()
{
    fprintf (dotFile_, "subgraph Cluster%u\n", cluster_++);
    fprintf (dotFile_, "{\n");
}

void Dotter::Digraph::end ()
{
    fprintf (dotFile_, "}\n");
}

void Dotter::Digraph::set (const char* comand, const char* param)
{
    fprintf (dotFile_, "node [%s=\"%s\"];\n", comand, param);
}

void Dotter::Digraph::node (const size_t number, const char* label, ...)
{
    fprintf (dotFile_, "Node%u ", number);

    fprintf (dotFile_, "[");

    fprintf (dotFile_, "label=\"");

    va_list args;

    va_start (args, label);

    vfprintf (dotFile_, label, args);

    va_end (args);

    fprintf (dotFile_, "\"");

    fprintf (dotFile_, "];\n");
}

void Dotter::Digraph::link (const size_t from, const size_t to, const char* label, ...)
{
    //const char* type = oriented? "->" : "--";

    fprintf (dotFile_, "Node%u -> Node%u ", from, to);

    fprintf (dotFile_, "[");

    fprintf (dotFile_, "label=\"");

    va_list args;

    va_start (args, label);

    vfprintf (dotFile_, label, args);

    va_end (args);

    fprintf (dotFile_, "\"");

    fprintf (dotFile_, "];\n");
}

void Dotter::Digraph::comment (const char* label, ...)
{
    fprintf (dotFile_, "/*");

    va_list args;

    va_start (args, label);

    vfprintf (dotFile_, label, args);

    va_end (args);

    fprintf (dotFile_, "*/");
}

void Dotter::Digraph::render (const char* path, const bool show /* = true */)
{
    close ();

    size_t dirSize = 100;
    char* dir = new char[dirSize];
    Dotter::Details::Directory (dir, dirSize);

    std::string type;
    Dotter::Details::Expansion (renderName_, type);

    const size_t cmdSize = dirSize               +
                           sizeof ("\\") - 1     +
                           strlen (path)         +
                           strlen (Dotter::Path) +
                           sizeof (" -T") - 1    +
                           type.size()           +
                           sizeof (" ") - 1      +
                           strlen (dotName_)     +
                           sizeof (" -o ") - 1   +
                           strlen (renderName_)  +
                           1;

    char* comand = new char[cmdSize] ();

    size_t counter = 0;

    Dotter::Details::StrInsert (comand,           dir, counter);
    Dotter::Details::StrInsert (comand,          "\\", counter);
    Dotter::Details::StrInsert (comand,          path, counter);
    Dotter::Details::StrInsert (comand,  Dotter::Path, counter);
    Dotter::Details::StrInsert (comand,         " -T", counter);
    Dotter::Details::StrInsert (comand, type.c_str (), counter);
    Dotter::Details::StrInsert (comand,           " ", counter);
    Dotter::Details::StrInsert (comand,      dotName_, counter);
    Dotter::Details::StrInsert (comand,        " -o ", counter);
    Dotter::Details::StrInsert (comand,   renderName_, counter);

    comand[cmdSize - 1] = '\0';

    delete[] dir;
             dir = nullptr;

    try
    {
        system (comand);
    }
    catch (...)
    {
        std::cout << "ERROR: " << comand << "\n";
    }

    delete[] comand;
             comand = nullptr;

    if (show)
    {
        const size_t buildSize = sizeof ("start ") - 1 +
                                 strlen (renderName_)  +
                                 1;

        char* build = new char[buildSize] ();

        size_t position = 0;

        Dotter::Details::StrInsert (build,    "start ", position);
        Dotter::Details::StrInsert (build, renderName_, position);

        build[buildSize - 1] = '\0';

        system (build);

        delete[] build;
                 build = nullptr;
    }
}

bool Dotter::Digraph::ok () const
{
    return true;
}

void Dotter::Digraph::dump () const
{
}

void Dotter::Digraph::setNodeShape (const char* param)
{
    fprintf (dotFile_, "node [shape=\"%s\"]\n", param);
}

void Dotter::Digraph::setNodeColor (const char* param)
{
    fprintf (dotFile_, "node [color=\"%s\"]\n", param);
}

FILE* Dotter::Digraph::DotFile () const
{
    return dotFile_;
}

const char* Dotter::Digraph::DotName () const
{
    return dotName_;
}

const char* Dotter::Digraph::RenderName () const
{
    return renderName_;
}

const char* Dotter::Digraph::DotName ()
{
    return dotName_;
}

const char* Dotter::Digraph::RenderName ()
{
    return renderName_;
}

#endif /* Digraph_hpp */
