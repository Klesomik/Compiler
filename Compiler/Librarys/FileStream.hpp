#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>
#include "Stream.hpp"

class FileStream
{
    private:
        FILE* stream_;

        FileStream (const FileStream& from);
        FileStream& operator = (FileStream &from);

    public:
        FileStream (const char*       name, const char* mode);
        FileStream (const std::string name, const char* mode);

        ~FileStream ();

        void seek (const size_t example);
        bool eof ();

        void convert (Stream <char>& example);

        const FILE*  stream ();
        size_t size ();
};

FileStream :: FileStream (const char* name, const char* mode):
    stream_ (fopen (name, mode))
    { assert (stream_); }

FileStream :: FileStream (const std::string name, const char* mode):
    stream_ (fopen (name.c_str (), mode))
    { assert (stream_); }

FileStream :: ~FileStream ()
{
    if (stream_)
    {
        fclose (stream_);
                stream_ = nullptr;
    }
}

void FileStream :: seek (const size_t example)
{
    assert (example < SEEK_END);

    fseek (stream_, example, SEEK_SET);
}

bool FileStream :: eof ()
{
    return feof (stream_);
}

void FileStream :: convert (Stream <char>& example)
{
    for (char symbol = 0; fscanf (stream_, "%c", &symbol) != EOF;)
    {
        example.push_back (symbol);
    }
}

const FILE* FileStream :: stream ()
{
    return stream_;
}

size_t FileStream :: size ()
{
    size_t tmp = 0;

    fseek (stream_, 0, SEEK_END);

    tmp = ftell (stream_);

    fseek (stream_, 0, SEEK_SET);

    return tmp;
}
