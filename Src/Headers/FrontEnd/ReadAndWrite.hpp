void Read (Stream <char>& to, const std::string& name);

template <typename Data_T>
void Read (Stream <Data_T>& to, const std::string& name);

template <typename Data_T>
void Write (const Stream <Data_T>& from, const std::string& name);

void Read (Stream <char>& to, const std::string& name)
{
    std::ifstream in (name);

    std::string tmp;
    std::getline (in, tmp, '\0');

    to += tmp;
}

template <typename Data_T>
void Read (Stream <Data_T>& to, const std::string& name)
{
    std::ifstream in (name);

    while (!in.eof ())
    {
        Data_T value;
        in >> value;

        to.push_back (value);
    }
}

template <typename Data_T>
void Write (const Stream <Data_T>& from, const std::string& name)
{
    std::ofstream out (name);

    for (int i = 0; i < from.size (); i++)
        out << from[i];
}
