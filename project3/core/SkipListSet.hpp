// SkipListSet.hpp
//
// ICS 46 Spring 2015
// Project #3: Set the Controls for the Heart of the Sun
//
// A SkipListSet is an implementation of a Set that is a skip list, implemented
// as we discussed in lecture.  A skip list is a sequence of levels
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector), *except* that you can use
// std::vector to store your levels (e.g., pointers to the head node of each
// level) if you'd like.  Beyond that, you'll need to implement your own
// dynamically-allocated nodes with pointers connecting them.
//
// Each node should contain only two pointers: one to the node that follows it
// on the same level and another to the equivalent node on the level below it.
// Additional pointers use more memory but don't enable any techniques not
// enabled by the other two.
//
// A couple of utilities are included here: SkipListKind and SkipListKey.
// You can feel free to use these as-is and probably will not need to
// modify them.

#ifndef SKIPLISTSET_HPP
#define SKIPLISTSET_HPP

#include "Set.hpp"




// SkipListKind indicates a kind of key: a normal one, the special key
// -INF, or the special key +INF.  It's necessary for us to implement
// the notion of -INF and +INF separately, since we're building a class
// template and not all types of keys would have a reasonable notion of
// -INF and +INF.

enum class SkipListKind
{
    Normal,
    NegInf,
    PosInf
};




// A SkipListKey represents a single key in a skip list.  It is possible
// to compare these keys using < or == operators (which are overloaded here)
// and those comparisons respect the notion of whether each key is normal,
// -INF, or +INF.

template <typename T>
class SkipListKey
{
public:
    SkipListKey(SkipListKind kind, const T& key);

    bool operator==(const SkipListKey& other) const;
    bool operator<(const SkipListKey& other) const;

private:
    SkipListKind kind;
    T key;
};


template <typename T>
SkipListKey<T>::SkipListKey(SkipListKind kind, const T& key)
    : kind{kind}, key{key}
{
}


template <typename T>
bool SkipListKey<T>::operator==(const SkipListKey& other) const
{
    return kind == other.kind
        && (kind != SkipListKind::Normal || key == other.key);
}


template <typename T>
bool SkipListKey<T>::operator<(const SkipListKey& other) const
{
    switch (kind)
    {
    case SkipListKind::NegInf:
        return other.kind != SkipListKind::NegInf;

    case SkipListKind::PosInf:
        return false;

    default: // SkipListKind::Normal
        return other.kind == SkipListKind::PosInf
            || (other.kind == SkipListKind::Normal && key < other.key);
    }
}




template <typename T>
class SkipListSet : public Set<T>
{
public:
    // Initializes an SkipListSet to be empty.
    SkipListSet();

    // Cleans up the SkipListSet so that it leaks no memory.
    virtual ~SkipListSet();

    // Initializes a new SkipListSet to be a copy of an existing one.
    SkipListSet(const SkipListSet& s);

    // Assigns an existing SkipListSet into another.
    SkipListSet& operator=(const SkipListSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a SkipListSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in an expected time
    // of O(log n) (i.e., over the long run, we expect the average to be
    // O(log n)) with very high probability.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in an expected time of O(log n)
    // (i.e., over the long run, we expect the average to be O(log n))
    // with very high probability.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:

};


template <typename T>
SkipListSet<T>::SkipListSet()
{
}


template <typename T>
SkipListSet<T>::~SkipListSet()
{
}


template <typename T>
SkipListSet<T>::SkipListSet(const SkipListSet& s)
{
}


template <typename T>
SkipListSet<T>& SkipListSet<T>::operator=(const SkipListSet& s)
{
    return *this;
}


template <typename T>
bool SkipListSet<T>::isImplemented() const
{
    return false;
}


template <typename T>
void SkipListSet<T>::add(const T& element)
{
}


template <typename T>
bool SkipListSet<T>::contains(const T& element) const
{
    return false;
}


template <typename T>
unsigned int SkipListSet<T>::size() const
{
    return 0;
}



#endif // SKIPLISTSET_HPP

