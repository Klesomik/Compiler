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

            int indent_;
            int space_;

            void print (const char* cmd, ...);

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
            size_t& cluster ();
            int& indent ();
    };
}

Dotter::Digraph::Digraph ():
    file_    (nullptr),
    dotter_  (),
    text_    (),
    photo_   (),
    cluster_ (0),
    indent_  (0),
    space_   (4)
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

        print ("digraph Hello\n");
        print ("{\n");
        indent_ += space_;

        begin ();
    }
}

void Dotter::Digraph::close ()
{
    if (file_)
    {
        end ();
        end ();

        comment (" Build with Dotter ");

        fclose (file_);
                file_ = nullptr;
    }
}

void Dotter::Digraph::begin ()
{
    print ("subgraph Cluster%u\n", cluster_++);
    print ("{\n");

    indent_ += space_;
}

void Dotter::Digraph::end ()
{
    print ("}\n");

    indent_ -= space_;
}

void Dotter::Digraph::set (const std::string& comand, const std::string& param)
{
    print ("node [%s=\"%s\"];\n", comand.c_str (), param.c_str ());
}

void Dotter::Digraph::node (const size_t number, const char* label, ...)
{
    print ("Node%u [label=\"", number);

    va_list args;

    va_start (args, label);

    vfprintf (file_, label, args);

    va_end (args);

    print ("\"];\n");
}

void Dotter::Digraph::link (const size_t from, const size_t to, const char* label, ...)
{
    //const char* type = oriented? "->" : "--";

    print ("Node%u -> Node%u [label=\"", from, to);

    va_list args;

    va_start (args, label);

    vfprintf (file_, label, args);

    va_end (args);

    fprintf (file_, "\"];\n");
}

void Dotter::Digraph::comment (const char* label, ...)
{
    print ("/*");

    va_list args;

    va_start (args, label);

    vfprintf (file_, label, args);

    va_end (args);

    print ("*/");
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

size_t& Dotter::Digraph::cluster ()
{
    return cluster_;
}

int& Dotter::Digraph::indent ()
{
    return indent_;
}

void Dotter::Digraph::print (const char* cmd, ...)
{
    std::string tmp (indent_, ' ');

    print ("%s", tmp);

    va_list args;

    va_start (args, cmd);

    vfprintf (file_, cmd, args);

    va_end (args);
}

#endif /* Digraph_hpp */
