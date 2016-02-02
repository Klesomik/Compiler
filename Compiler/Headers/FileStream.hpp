#include <cstdio>

class FileStream
{
    private:
        FILE* stream_;

        size_t pos_;

    public:
        FileStream (const char*       name, const char* type);
        FileStream (const std::string name, const char* type);

        ~FileStream ();

        void seek (const size_t example);
        bool eof ();

        FILE*&  stream () const;
        size_t&    pos () const;
        size_t&   size () const;
};

FileStream :: FileStream (const char* name, const char* type):
    stream_ (fopen (name, type),
    pos_    (0)
    { assert (stream); }

FileStream :: FileStream (const std::string name, const char* type):
    stream_ (fopen (name.c_str (), type),
    pos_    (0)
    {}

FileStream :: ~FileStream ()
{
    fclose (stream_);
}

void FileStream :: seek (const size_t example)
{
    pos_ = example;
}

bool FileStream :: eof ()
{
    return feof (stream_);
}

FILE*& FileStream :: stream () const
{
    return stream_;
}

size_t& FileStream :: pos () const
{
    return pos_;
}

size_t& FileStream :: size () const
{
    return filelength (fileno (stream_);
}
