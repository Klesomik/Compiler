#ifndef Digraph_hpp

#define Digraph_hpp

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdarg>
#include "..//FormatBuffer.hpp"
#include "..//Tools.hpp"

//TODO: Many setters and no getters, add ios::app with Boost streams

namespace Dotter
{
    class Digraph
    {
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

            FormatBuffer& file ();
            std::string& dotter ();
            std::string& text ();
            std::string& photo ();
            size_t& cluster ();
            bool& oriented ();

        private:
            FormatBuffer file_;

            std::string dotter_, // Path to your directory with dotter
                        text_,   // File with information about graph
                        photo_;  // Photo which was built from 'text'

            size_t cluster_;

            bool oriented_;
    };
}

Dotter::Digraph::Digraph ():
    file_    (),
    dotter_  (),
    text_    (),
    photo_   (),
    cluster_ (0),
    oriented_(true)
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
        file_.print ("digraph Hello\n");
        file_.print ("{\n");
        file_.increase ();

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

        file_.to_file (text_);
    }
}

void Dotter::Digraph::begin ()
{
    file_.print ("subgraph Cluster%u\n", cluster_++);
    file_.print ("{\n");

    file_.increase ();
}

void Dotter::Digraph::end ()
{
    file_.print ("}\n");

    file_.decrease ();
}

void Dotter::Digraph::set (const std::string& comand, const std::string& param)
{
    file_.print ("node [%s=\"%s\"];\n", comand.c_str (), param.c_str ());
}

void Dotter::Digraph::node (const size_t number, const char* label, ...)
{
    file_.print ("Node%u [label=\"", number);

    va_list args;

    va_start (args, label);

    vfprintf (file_, label, args);

    va_end (args);

    file_.print ("\"];\n");
}

void Dotter::Digraph::link (const size_t from, const size_t to, const char* label, ...)
{
    file_.print ("Node%u %s Node%u [label=\"", from, (oriented? "->" : "--"), to);

    va_list args;

    va_start (args, label);

    vfprintf (file_, label, args);

    va_end (args);

    file_.print ("\"];\n");
}

void Dotter::Digraph::comment (const char* label, ...)
{
    file_.print ("/*");

    va_list args;

    va_start (args, label);

    vfprintf (file_, label, args);

    va_end (args);

    file_.print ("*/");
}

void Dotter::Digraph::render (const bool show /* = true */)
{
    close ();

    std::string type;
    Dotter::Details::Expansion (photo_, type);

    Tools::System ("%s -T%s %s -o %s", dotter_, type, text_, photo_);

    if (show)
        Tools::System ("start %s", photo_);
}

FormatBuffer& Dotter::Digraph::file ()
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

bool& Dotter::Digraph::oriented ()
{
    oriented_;
}

#endif /* Digraph_hpp */
