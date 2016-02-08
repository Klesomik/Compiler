
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

        BinaryNode <Data_T> *parent_;

        Vector <BinaryNode <Data_T>> children;

        bool ok      ();
        void dump    ();

        BinaryNode (BinaryNode <Data_T>& from);
        BinaryNode <Data_T>& operator = (BinaryNode <Data_T>& from);

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

        Data_T&  key ();
};

//}==============================================================================

template <typename Data_T>
BinaryNode <Data_T> :: BinaryNode ():
    key_    (),
    parent_ (nullptr),
    left_   (nullptr),
    right_  (nullptr)
    { OK_BINARYNODE }

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T> :: BinaryNode (const Data_T& value):
    key_    (value),
    parent_ (nullptr),
    left_   (nullptr),
    right_  (nullptr)
    { OK_BINARYNODE }

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T> :: BinaryNode (BinaryNode <Data_T>& from):
    key_    (from.key_),
    parent_ (from.parent_),
    left_   (from.left_),
    right_  (from.right_)
    {
        from.parent_ = nullptr;
        from.left_   = nullptr;
        from.right_  = nullptr;

        if (left_)  left_  -> parent_ = this;
        if (right_) right_ -> parent_ = this;

        OK_BINARYNODE
    }

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T> :: ~BinaryNode ()
{
    OK_BINARYNODE

    if (parent_) parent_ = nullptr;

    if (left_)
    {
        delete left_;
               left_ = nullptr;
    }

    if (right_)
    {
        delete right_;
               right_ = nullptr;
    }
}

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T>& BinaryNode <Data_T> :: operator = (BinaryNode <Data_T>& from)
{
    OK_BINARYNODE

    key_    = from.key_;
    parent_ = from.parent_;
    left_   = from.left_;
    right_  = from.right_;

    from.parent_ = nullptr;
    from.left_   = nullptr;
    from.right_  = nullptr;

    OK_BINARYNODE

    return (*this);
}

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T>& BinaryNode <Data_T> :: operator [] (const size_t child)
{
    OK_BINARYNODE

    if (child >= children_.size ())
    {
        DO ({ throw "Not found this children"; },
            { assert (false); })
    }

    return children_[child];
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
/*const*/BinaryNode <Data_T>* BinaryNode <Data_T> :: insert (BinaryNode <Data_T>& from)
{
    OK_BINARYNODE

    BinaryNode* example = new BinaryNode (from);

    children_.push_back (example);
                         example -> parent_ = this;

    OK_BINARYNODE

    return (*this);
}

//===============================================================================

template <typename Data_T>
void BinaryNode <Data_T> :: erase ()
{
    OK_BINARYNODE

    parent_ = nullptr;
    left_   = nullptr;
    right_  = nullptr;

    delete parent_;
    delete left_;
    delete right_;

    OK_BINARYNODE
}

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T>& BinaryNode <Data_T> :: copy (const BinaryNode <Data_T>& from)
{
    OK_BINARYNODE

    BinaryNode <Data_T> current (from.key ());

    if (from.left  ()) current.insertLeft  (copy (from.left  ()));
    if (from.rigth ()) current.insertRight (copy (from.right ()));

    OK_BINARYNODE

    return current;
}

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T>& BinaryNode <Data_T> :: move (BinaryNode <Data_T>& from)
{
    OK_BINARYNODE

    if (left_)
    {
        left_ -> parent_ = nullptr;
        left_            = nullptr;
    }

    if (right_)
    {
        right_ -> parent_ = nullptr;
        right_            = nullptr;
    }

    key_ = from.key_;

    if (from.left_)
    {
        left_ = from.left_;
                from.left_ -> parent_ = this;
                from.left_ = nullptr;
    }

    if (from.right_)
    {
        right_ = from.right_;
                 from.right_ -> parent_ = this;
                 from.right_ = nullptr;
    }

    OK_BINARYNODE

    return (*this);
}

//===============================================================================

template <typename Data_T>
bool BinaryNode <Data_T> :: ok ()
{
    if (parent_)
    {
        if (parent_ -> left_ != this && parent_ -> right_ != this)
        {
            DO ({ throw "parent_ -> left_ != this && parent_ -> right_ != this"; },
                { return false; })
        }
    }

    if (left_)
    {
        if (left_ -> parent_ != this)
        {
            DO ({ throw "left_ -> parent_ != this"; },
                { return false; })
        }
    }

    if (right_)
    {
        if (right_ -> parent_ != this)
        {
            DO ({ throw "right_ -> parent_ != this"; },
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

    printf ("\n=============DUMP=============\n");

    printf ("BinaryNode (%s) [this = %p][", ok()? "ok" : "ERROR", this);
    std::cout << "key = " << key_ << "]\n";

    printf ("    parent = %p;\n", parent_);
    printf ("      left = %p;\n",   left_);
    printf ("     right = %p;\n",  right_);

    printf ("==============================\n\n");

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

#include "BinaryNodeLib.hpp"

#endif /* BINARYNODE_HPP_INCLUDED */
