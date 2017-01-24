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
            FILE* file_;

            std::string dotter_, // Path to your directory with dotter
                        text_,   // File with information about graph
                        photo_;  // Photo which was built from 'text'

            size_t cluster_;

        public:
            Digraph ();

            ~Digraph ();

            void open  ();
            void close ();

            void begin ();
            void end   ();

            void set (const std::string& comand, const std::string& param);

            void node (const size_t number, const char* label, ...);
            void link (const size_t from, const size_t to, const char* label, ...);

            void comment (const char* label, ...);

            void render (const bool show = true);

            FILE* file ();
            std::string& dotter ();
            std::string& text ();
            std::string& photo ();
    };
}

Dotter::Digraph::Digraph ():
    file_    (nullptr),
    dotter_  (),
    text_    (),
    photo_   (),
    cluster_ (0)
{
}

Dotter::Digraph::~Digraph ()
{
    close ();
}

void Dotter::Digraph::open ()
{
    if (!file_)
    {
        file_ = fopen (text_.c_str (), "w");

        fprintf (file_, "digraph Hello\n");
        fprintf (file_, "{\n");

        begin ();
    }
}

void Dotter::Digraph::close ()
{
    if (file_)
    {
        fprintf (file_, "}\n");

        end ();

        comment (" Build with Dotter ");

        fclose (file_);
                file_ = nullptr;
    }
}

void Dotter::Digraph::begin ()
{
    fprintf (file_, "subgraph Cluster%u\n", cluster_++);
    fprintf (file_, "{\n");
}

void Dotter::Digraph::end ()
{
    fprintf (file_, "}\n");
}

void Dotter::Digraph::set (const std::string& comand, const std::string& param)
{
    fprintf (file_, "node [%s=\"%s\"];\n", comand.c_str (), param.c_str ());
}

void Dotter::Digraph::node (const size_t number, const char* label, ...)
{
    fprintf (file_, "Node%u [label=\"", number);

    va_list args;

    va_start (args, label);

    vfprintf (file_, label, args);

    va_end (args);

    fprintf (file_, "\"];\n");
}

void Dotter::Digraph::link (const size_t from, const size_t to, const char* label, ...)
{
    //const char* type = oriented? "->" : "--";

    fprintf (file_, "Node%u -> Node%u [label=\"", from, to);

    va_list args;

    va_start (args, label);

    vfprintf (file_, label, args);

    va_end (args);

    fprintf (file_, "\"];\n");
}

void Dotter::Digraph::comment (const char* label, ...)
{
    fprintf (file_, "/*");

    va_list args;

    va_start (args, label);

    vfprintf (file_, label, args);

    va_end (args);

    fprintf (file_, "*/");
}

void Dotter::Digraph::render (const bool show /* = true */)
{
    close ();

    std::string type;
    Dotter::Details::Expansion (photo_, type);

    std::string comand;

    comand += dotter_;
    comand += " -T";
    comand += type;
    comand += " ";
    comand += text_;
    comand += " -o ";
    comand += photo_;

    system (comand.c_str ());

    if (show)
    {
        std::string build;

        build += "start ";
        build += photo_;

        system (build.c_str ());
    }
}

FILE* Dotter::Digraph::file ()
{
    return file_;
}

std::string& Dotter::Digraph::dotter ()
{
    return dotter_;
}

std::string& Dotter::Digraph::text ()
{
    return text_;
}

std::string& Dotter::Digraph::photo ()
{
    return photo_;
}

#endif /* Digraph_hpp */
