// AVLSet.hpp
//
// ICS 46 Spring 2015
// Project #3: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your AVL tree using your own dynamically-allocated nodes,
// with pointers connecting them, and with your own balancing algorithms
// used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include "Set.hpp"



template <typename T>
class AVLSet : public Set<T>
{
public:
    // Initializes an AVLSet to be empty.
    AVLSet();

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet();

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    struct AVLNode
    {
        T key;
        AVLNode* left;
        AVLNode* right;
        int height;

    };

    AVLNode* root;

private:
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* insert(AVLNode* node, const T& element);
    int max(int a, int b);
    int height(AVLNode* n);
    int countSize(AVLNode* node) const;
    void copyAll(const AVLSet& s);
    void destroyAll();
};


template <typename T>
AVLSet<T>::AVLSet()
    : root{nullptr}
{
}


template <typename T>
AVLSet<T>::~AVLSet()
{
    destroyAll();
}


template <typename T>
AVLSet<T>::AVLSet(const AVLSet& s)
    : root{nullptr}
{
    copyAll(s);
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s)
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
bool AVLSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void AVLSet<T>::add(const T& element)
{   
    root = insert(root,element);
    
}


template <typename T>
bool AVLSet<T>::contains(const T& element) const
{
    AVLNode* curr = root;

    while(curr != nullptr)
    {
        if(curr->key == element)
        {
            return true;
        }
        else
        {
            if(element > curr->key)
                curr = curr->right;
            else
                curr = curr->left;
        }
    }
    return false;
}

template <typename T>
int AVLSet<T>::countSize(AVLNode* node) const
{
    if(node == nullptr)
        return 0;
    else
        return (countSize(node->left) + 1 + countSize(node->right));
}

template <typename T>
unsigned int AVLSet<T>::size() const
{
    return countSize(root);
}

template <typename T>
int AVLSet<T>::max(int a, int b)
{
    return(a > b) ? a : b;
}

template <typename T>
int AVLSet<T>::height(AVLNode* n)
{
    if (n == nullptr)
        return 0;
    return n->height;
}

template <typename T>
typename AVLSet<T>::AVLNode* AVLSet<T>::rightRotate(AVLNode* y)
{
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

template <typename T>
typename AVLSet<T>::AVLNode* AVLSet<T>::leftRotate(AVLNode* x)
{
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

template <typename T>
typename AVLSet<T>::AVLNode* AVLSet<T>::insert(AVLNode* node, const T& element)
{
    AVLNode* t = new AVLNode;
    t->key = element;
    t->left = nullptr;
    t->right = nullptr;
    t->height = 1;

    if (node == nullptr)
    {   
        node = t;
    }

    if(element < node->key)
    {
        node->left = insert(node->left, element);
        if((height(node->left) - height(node->right)) > 1)
        {
            if(element < node->left->key)
                node = rightRotate(node);
            else
            {
                node->left = leftRotate(node->left);
                node = rightRotate(node);
            }
        }
    }

    if(element > node->key)
    {
        node->right = insert(node->right,element);
        if((height(node->right) - height(node->left)) > 1)
        {
            if(element > node->right->key)
                node = leftRotate(node);
            else
            {
                node->right = rightRotate(node->right);
                node = leftRotate(node);
            }
        }
    }

    
    node->height = max(height(node->left), height(node->right)) + 1;

    return node;

   /* if (element < node->key)
        node->left = insert(node->left, element);
    else
        node->right = insert(node->right, element);

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = height(node->left) - height(node->right);

    if(balance > 1 && element < node->left->key)
        return rightRotate(node);
    if(balance < -1 && element > node->right->key)
        return leftRotate(node);
    if(balance > 1 && element > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if(balance < -1 && element < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;*/
}

template <typename T>
void AVLSet<T>::copyAll(const AVLSet& s)
{
    AVLNode* r;

    if(s.root == nullptr){}

    else
    {
        r = new AVLNode;
        r->key = s.root->key;
        r->left = copyAll(s.root->left);
        r->right = copyAll(s.root->right);
        r->height = s.root->height;
    }
}

template <typename T>
void AVLSet<T>::destroyAll()
{
    delete root;
}
#endif // AVLSET_HPP

