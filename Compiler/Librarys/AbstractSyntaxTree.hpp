
//TODO: Rewrite Danila's DOTTER!!!

#ifndef BINARYNODE_HPP_INCLUDED
    #define BINARYNODE_HPP_INCLUDED

//Include
//{==============================================================================

#include <cstdio>
#include <iostream>
#include <cassert>
#include "Dotter.h"
#include "Debug.hpp"

//}==============================================================================

//Define
//{==============================================================================

#define DEBUG_BINARYNODE

#if defined (DEBUG_BINARYNODE)

    #define DO(codeDebug, codeTest)  codeDebug
    #define OK_BINARYNODE ok ();

#elif defined (TEST_BINARYNODE)

    #define DO(codeDebug, codeTest)  codeTest
    #define OK_BINARYNODE assert (ok ());

#elif defined (RELEASE_BINARYNODE)

    #define DO(codeDebug, codeTest)
    #define OK_BINARYNODE

#else

    #error "Either DEBUG_BINARYNODE or TEST_BINARYNODE or RELEASE_BINARYNODE MUST be defined"

#endif

//}==============================================================================

//Class: BinaryNode
//{==============================================================================

template <typename Data_T>
class BinaryNode
{
    private:
        Data_T key_;

        BinaryNode <Data_T>* parent_;

        Vector <BinaryNode <Data_T>*> children_;

        BinaryNode (BinaryNode <Data_T>& from);

        BinaryNode <Data_T>& operator =  (BinaryNode <Data_T>& from);

        int position (BinaryNode <Data_T>* child); //[]

    public:
        BinaryNode ();
        BinaryNode (const Data_T& value);

        ~BinaryNode ();

        /*const*/BinaryNode <Data_T>* operator [] (const size_t child);

        BinaryNode& insert ();
        BinaryNode& insert (const Data_T& value);
        BinaryNode& insert (BinaryNode <Data_T>& example);

        void erase ();

        BinaryNode <Data_T>& copy (const BinaryNode <Data_T>& from); //old
        BinaryNode <Data_T>& move (BinaryNode <Data_T>& from);

        Data_T&                             key ();
        Vector <BinaryNode <Data_T>*>& children ();

        #if defined (DEBUG_BINARYNODE)

            public:

        #else

            private:

        #endif

        bool ok   ();
        void dump ();
};

//}==============================================================================

template <typename Data_T>
BinaryNode <Data_T> :: BinaryNode ():
    key_      (),
    parent_   (nullptr),
    children_ ()
    { OK_BINARYNODE }

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T> :: BinaryNode (const Data_T& value):
    key_      (value),
    parent_   (nullptr),
    children_ ()
    { OK_BINARYNODE }

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T> :: BinaryNode (BinaryNode <Data_T>& from):
    key_      (from.key_),
    parent_   (from.parent_),
    children_ (from.children_)
    {
        from.parent_ = nullptr;

        from.children_.clear ();

        for (size_t i = 0; i < children_.size (); i++)  children_[i] -> parent_ = this;

        OK_BINARYNODE
    }

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T> :: ~BinaryNode ()
{
    OK_BINARYNODE

    if (parent_) parent_ = nullptr;

    for (size_t i = 0; i < children_.size (); i++)
    {
        if (children_[i])
        {
            delete children_[i];
                   children_[i] = nullptr;
        }
    }
}

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T>& BinaryNode <Data_T> :: operator = (BinaryNode <Data_T>& from)
{
    OK_BINARYNODE

    key_      = from.key_;
    parent_   = from.parent_;
    children_ = from.children_;

    from.parent_ = nullptr;
    from.children_.clear ();

    for (size_t i = 0; i < children_.size (); i++)  children_[i] -> parent_ = this;

    OK_BINARYNODE

    return (*this);
}

//===============================================================================

template <typename Data_T>
/*const*/BinaryNode <Data_T>* BinaryNode <Data_T> :: operator [] (const size_t child)
{
    OK_BINARYNODE

    if (child >= children_.size ())
    {
        DO ({ throw "Not found this children"; },
            { assert (false); })
    }

    OK_BINARYNODE

    return children_[child];
}

//===============================================================================

template <typename Data_T>
int BinaryNode <Data_T> :: position (BinaryNode <Data_T>* child)
{
    OK_BINARYNODE

    for (size_t i = 0; i < children_.size (); i++)
    {
        if (children_[i] == child) return i;
    }

    OK_BINARYNODE

    return -1;
}

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T>& BinaryNode <Data_T> :: insert  ()
{
    OK_BINARYNODE

    BinaryNode from = BinaryNode ();

    OK_BINARYNODE

    return insert (from);
}

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T>& BinaryNode <Data_T> :: insert (const Data_T& value)
{
    OK_BINARYNODE

    BinaryNode from (value);

    OK_BINARYNODE

    return insert (from);
}

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T>& BinaryNode <Data_T> :: insert (BinaryNode <Data_T>& from)
{
    OK_BINARYNODE

    BinaryNode* example = new BinaryNode (from);

    children_.push_back (example);
                         example -> parent_ = this;

    from.~BinaryNode ();

    OK_BINARYNODE

    return (*this);
}

//===============================================================================

/*template <typename Data_T>
void BinaryNode <Data_T> :: erase ()
{
    OK_BINARYNODE

    parent_ = nullptr;
    children_.clear ();

    int number = parent_[this];

    if (number != -1) parent_[number] = nullptr;

    for (size_t i = 0; i < children_.size (); i++) delete children_[i];

    OK_BINARYNODE
}*/

//===============================================================================

/*template <typename Data_T>
BinaryNode <Data_T>& BinaryNode <Data_T> :: copy (const BinaryNode <Data_T>& from)
{
    OK_BINARYNODE

    BinaryNode <Data_T> current (from.key_);

    for (size_t i = 0; i < from.children_.size (); i++) current.insert (copy (children_[i]));

    OK_BINARYNODE

    return current;
}*/

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T>& BinaryNode <Data_T> :: move (BinaryNode <Data_T>& from)
{
    OK_BINARYNODE

    for (size_t i = 0; i < children_.size (); i++) delete children_[i];

    children_.resize (from.children_.size ());

    key_ = from.key_;

    for (size_t i = 0; i < children_.size (); i++)
    {
        children_[i] = from.children_[i];
                       from.children_[i] -> parent_ = this;
                       from.children_[i] = nullptr;
    }

    from.children_.clear ();

    OK_BINARYNODE

    return (*this);
}

//===============================================================================

template <typename Data_T>
bool BinaryNode <Data_T> :: ok ()
{
    if (parent_)
    {
        int number = parent_ -> position (this);

        if (number == -1)
        {
            DO ({ throw "parent_ -> left_ != this && parent_ -> right_ != this"; },
                { return false; })
        }
    }

    for (size_t i = 0; i < children_.size (); i++)
    {
        if (children_[i] && (children_[i] -> parent_ != this))
        {
            DO ({ throw "left_ -> parent_ != this"; },
                { return false; })
        }
    }

    return true;
}

//===============================================================================

template <typename Data_T>
void BinaryNode <Data_T> :: dump ()
{
    int mode = -1;

    #if defined (DEBUG_BINARYNODE)

        #undef DEBUG_BINARYNODE

        mode = 0;

    #elif defined (RELEASE_BINARYNODE)

        #undef RELEASE_BINARYNODE

        mode = 1;

    #endif

    printf ("\n====================DUMP====================\n");

    printf ("BinaryNode (%s) [this = %p]", ok()? "ok" : "ERROR", this);
    std::cout << "[" << key_ << "];\n";

    if (parent_)
    {
        printf ("   parent = [%p]", parent_);
        std::cout << "[" << parent_ -> key_ << "];\n";
    }

    else
    {
        printf ("   parent = [%p];\n", parent_);
    }

    for (size_t i = 0; i < children_.size (); i++)
    {
        printf ("   child[%d] = [%p]", i, children_[i]);
        std::cout << "[" << children_[i] -> key_ << "];\n";
    }

    printf ("============================================\n\n");

    if (mode)
    {
        #define RELEASE_BINARYNODE
    }

    else
    {
        #define DEBUG_BINARYNODE
    }
}

//===============================================================================

template <typename Data_T>
Data_T& BinaryNode <Data_T> :: key ()
{
    OK_BINARYNODE

    return key_;
}

//===============================================================================

template <typename Data_T>
Vector <BinaryNode <Data_T>*>& BinaryNode <Data_T> :: children ()
{
    OK_BINARYNODE

    return children_;
}

#include "BinaryNodeLib.hpp"

#endif /* BINARYNODE_HPP_INCLUDED */
