// BSTSet.hpp
//
// ICS 46 Spring 2015
// Project #3: Set the Controls for the Heart of the Sun
//
// A BSTSet is an implementation of a Set that is a binary search tree,
// albeit one that makes no attempt to remain balanced.  (You explicitly
// should not do any balancing here; do that in AVLSet instead, if you
// choose to work on that one.)
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your binary search tree using your own dynamically-allocated
// nodes, with pointers connecting them.

#ifndef BSTSET_HPP
#define BSTSET_HPP

#include "Set.hpp"



template <typename T>
class BSTSet : public Set<T>
{
public:
    // Initializes a BSTSet to be empty.
    BSTSet();

    // Cleans up the BSTSet so that it leaks no memory.
    virtual ~BSTSet();

    // Initializes a new BSTSet to be a copy of an existing one.
    BSTSet(const BSTSet& s);

    // Assigns an existing BSTSet into another.
    BSTSet& operator=(const BSTSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a BSTSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    struct treeNode
    {
        T key;
        treeNode* left;
        treeNode* right;
    };

    treeNode* root;

private:
    int countSize(struct treeNode* node) const;
    void copyAll(const BSTSet& s);
    void destroyAll();
};

template <typename T>
BSTSet<T>::BSTSet()
    : root{nullptr}
{
}


template <typename T>
BSTSet<T>::~BSTSet()
{
    destroyAll();
}


template <typename T>
BSTSet<T>::BSTSet(const BSTSet& s)
    : root{nullptr}
{
    copyAll(s);
}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(const BSTSet& s)
{
    if(this != &s)
    {
        destroyAll();
        root = nullptr;
        copyAll(s);
    }
    return *this;
}


template <typename T>
bool BSTSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void BSTSet<T>::add(const T& element)
{
    treeNode* t = new treeNode;
    treeNode* parent;
    t->key = element;
    t->left = nullptr;
    t->right = nullptr;
    parent = nullptr;
    
    if(root == nullptr)
    {
        root = t;
        return;
    }

    treeNode* curr;
    curr = root;

    while (curr != nullptr)
    {
        if(curr->key == element)
            return;
        else
        {
            parent = curr;
            if (t->key > curr->key)
                curr = curr->right;
            else
                curr = curr->left;
        }
    }

    if (t->key < parent->key)
        parent->left = t;
    else
        parent->right = t;
}


template <typename T>
bool BSTSet<T>::contains(const T& element) const
{
    treeNode* curr = root;

    while (curr != nullptr)
    {
        if (curr->key == element)
        {
            return true;
        }
        else
        {
            
            if (element > curr->key)
                curr = curr->right;
            else
                curr = curr->left;
        }
    }
    return false;
}


template <typename T>
unsigned int BSTSet<T>::size() const
{
    treeNode* curr = root;

    return countSize(curr);
}

template <typename T>
int BSTSet<T>::countSize(treeNode* node) const
{
    if(node == nullptr)
        return 0;
    else
        return (countSize(node->left) + 1 + countSize(node->right));
}

template <typename T>
void BSTSet<T>::copyAll(const BSTSet& s)
{
    treeNode* r;

    if(s.root == nullptr){}

    else
    {
        r = new treeNode;
        r->key = s.root->key;
        r->left = copyAll(s.root->left);
        r->right = copyAll(s.root->right);
    }
}

template <typename T>
void BSTSet<T>::destroyAll()
{
    delete root;
}
#endif // BSTSET_HPP

