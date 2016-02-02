class HashTable
{
    std::vector <std::list> data_;

    HashTable ();
    HashTable (const size_t size);
};

int Hash (int         element);
int Hash (char        element);
int Hash (float       element);
int Hash (char*       element, size_t size);
int Hash (std::string element);
