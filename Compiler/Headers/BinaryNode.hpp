
//TODO: Rewrite Danila's DOTTER!!!

#ifndef BINARYNODE_HPP_INCLUDED
    #define BINARYNODE_HPP_INCLUDED

//Include
//{==============================================================================

#include <cstdio>
#include <iostream>
#include <cassert>
#include "Dotter.h"

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

        BinaryNode <Data_T> *parent_, *left_, *right_;

        bool ok      ();
        void dump    ();

        BinaryNode (BinaryNode <Data_T>& from);
        BinaryNode <Data_T>& operator = (BinaryNode <Data_T>& from);

    public:
        BinaryNode ();
        BinaryNode (const Data_T& value);

        ~BinaryNode ();

        BinaryNode <Data_T>& operator [] (const size_t child);

        BinaryNode& insertLeft  ();
        BinaryNode& insertRight ();

        BinaryNode& insertLeft  (const Data_T& value);
        BinaryNode& insertRight (const Data_T& value);

        BinaryNode& insertLeft  (BinaryNode <Data_T>& example);
        BinaryNode& insertRight (BinaryNode <Data_T>& example);

        void erase ();

        BinaryNode <Data_T>& copy (const BinaryNode <Data_T>& from); //old
        BinaryNode <Data_T>& move (BinaryNode <Data_T>& from);

        Data_T&               key    ();
        /*const*/ BinaryNode* parent ();
        /*const*/ BinaryNode* right  ();
        /*const*/ BinaryNode* left   ();

        friend BinaryNode <Data_T>& Convert (BinaryNode <Data_T>* example);
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
        OK_BINARYNODE

        from.parent_ = nullptr;
        from.left_   = nullptr;
        from.right_  = nullptr;

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
    assert (child < 2);

    if (child == 0) return  left;
    if (child == 1) return right;
}

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T>& BinaryNode <Data_T> :: insertLeft  ()
{
    OK_BINARYNODE

    if (left_) throw "left_";

    BinaryNode from = BinaryNode ();

    OK_BINARYNODE

    return insertLeft (from);
}

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T>& BinaryNode <Data_T> :: insertRight ()
{
    OK_BINARYNODE

    if (right_) throw "right_";

    BinaryNode from = BinaryNode ();

    OK_BINARYNODE

    return insertRight (from);
}

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T>& BinaryNode <Data_T> :: insertLeft (const Data_T& value)
{
    OK_BINARYNODE

    if (left_) throw "left_";

    BinaryNode from (value);

    OK_BINARYNODE

    return insertLeft (from);
}

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T>& BinaryNode <Data_T> :: insertRight (const Data_T& value)
{
    OK_BINARYNODE

    if (right_) throw "right_";

    BinaryNode from (value);

    OK_BINARYNODE

    return insertRight (from);
}

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T>& BinaryNode <Data_T> :: insertLeft (BinaryNode <Data_T>& from)
{
    OK_BINARYNODE

    if (left_) throw "left_";

    BinaryNode* example = new BinaryNode (from);

    left_ = example;
            example -> parent_ = this;

    OK_BINARYNODE

    return (*this);
}

//===============================================================================

template <typename Data_T>
BinaryNode <Data_T>& BinaryNode <Data_T> :: insertRight (BinaryNode <Data_T>& from)
{
   OK_BINARYNODE

    if (right_) throw "right_";

    BinaryNode* example = new BinaryNode (from);

    right_ = example;
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
    from.dump ();

    OK_BINARYNODE

    delete  left_;
    delete right_;

    key_    = from.key_;

    left_   = from.left_;
              from.left_ -> parent_ = this;
              from.left_ = nullptr;

    right_  = from.right_;
              from.right_ -> parent_ = this;
              from.right_ = nullptr;

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

//===============================================================================

template <typename Data_T>
/*const*/ BinaryNode <Data_T>* BinaryNode <Data_T> :: parent ()
{
    OK_BINARYNODE

    return parent_;
}

//===============================================================================

template <typename Data_T>
/*const*/ BinaryNode <Data_T>* BinaryNode <Data_T> :: right ()
{
    OK_BINARYNODE

    return right_;
}

//===============================================================================

template <typename Data_T>
/*const*/ BinaryNode <Data_T>* BinaryNode <Data_T> :: left ()
{
    OK_BINARYNODE

    return left_;
}

#include "BinaryNodeLib.hpp"

#endif /* BINARYNODE_HPP_INCLUDED */
