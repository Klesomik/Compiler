#ifndef Digraph_hpp

#define Digraph_hpp

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdarg>
#include "..//FormatFile.hpp"

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

            FormatFile& file ();
            std::string& dotter ();
            std::string& text ();
            std::string& photo ();
            size_t& cluster ();

        private:
            FormatFile file_;

            std::string dotter_, // Path to your directory with dotter
                        text_,   // File with information about graph
                        photo_;  // Photo which was built from 'text'

            size_t cluster_;
    };
}

Dotter::Digraph::Digraph ():
    file_    (),
    dotter_  (),
    text_    (),
    photo_   (),
    cluster_ (0),
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
        file_.open (text_.c_str ());

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

        file_.close ();
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
    //const char* type = oriented? "->" : "--";

    file_.print ("Node%u -> Node%u [label=\"", from, to);

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

FormatFile& Dotter::Digraph::file ()
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

#endif /* Digraph_hpp */
