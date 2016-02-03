#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>

class FileStream
{
    private:
        FILE* stream_;

    public:
        FileStream (const char*       name, const char* type);
        FileStream (const std::string name, const char* type);

        ~FileStream ();

        void seek (const size_t example);
        bool eof ();

        void open  ();
        void close ();

        const FILE*  stream ();
        const size_t&   pos ();
        const size_t&  size ();
};

FileStream :: FileStream (const char* name, const char* type):
    stream_ (fopen (name, type)),
    pos_    (0)
    { assert (stream_); }

FileStream :: FileStream (const std::string name, const char* type):
    stream_ (fopen (name.c_str (), type)),
    pos_    (0)
    {}

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
}

bool FileStream :: eof ()
{
    return feof (stream_);
}

void FileStream :: open  ()
{
    if (!stream_)
}

void FileStream :: close ()
{
    if (stream)
}

const FILE* FileStream :: stream ()
{
    return stream_;
}

const size_t& FileStream :: pos ()
{
}

const size_t& FileStream :: size ()
{
    size_t tmp = 0;

    fseek (stream_, 0, SEEK_END);

    tmp = ftell (stream_);

    fseek (stream_, 0, SEEK_SET);

    return tmp;
}
