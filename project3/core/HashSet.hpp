// HashSet.hpp
//
// ICS 46 Spring 2015
// Project #3: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::vector, std::list, or std::array).  Instead, you'll need
// to use a dynamically-allocated array and your own linked list
// implementation; the linked list doesn't have to be its own class,
// though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include "Set.hpp"



template <typename T>
class HashSet : public Set<T>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction 
    typedef std::function<unsigned int(const T&)> HashFunction;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet();

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8.  In the case
    // where the array is resized, this function runs in linear time (with
    // respect to the number of elements, assuming a good hash function);
    // otherwise, it runs in constant time (again, assuming a good hash
    // function).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    HashFunction hashFunction;

private:
    class LN;

private:
    class LN {
        public:
        LN()                        : next(nullptr){}
        LN(const LN& ln)            : value(ln.value), next(ln.next){}
        LN(T v, LN* n = nullptr)    : value(v), next(n){}

        T value;
        LN* next;
    };
    
    LN** set = nullptr;
    double loadFactor;
    int bins = DEFAULT_CAPACITY;
    int used = 0;
    void ensure_load_factor(int new_used);
    LN* findElement(int bin, const T& element) const;
    LN* copy_list(LN* l) const;
    LN** copy_hash_table(LN** ht, int bins) const;
    void delete_hash_table(LN**& ht, int bins);
};



template <typename T>
HashSet<T>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction},loadFactor{0.8},bins{DEFAULT_CAPACITY}
{
    set = new LN*[bins];
    for (int b = 0; b < bins; ++b)
        set[b] = new LN();
}


template <typename T>
HashSet<T>::~HashSet()
{
    delete_hash_table(set,bins);
}


template <typename T>
HashSet<T>::HashSet(const HashSet& s)
    : hashFunction{s.hashFunction},loadFactor{s.loadFactor},bins{s.bins},used{s.used}
{
    set = copy_hash_table(s.set,bins);
}


template <typename T>
HashSet<T>& HashSet<T>::operator=(const HashSet& s)
{
    if (this != &s)
    {
        delete_hash_table(set,bins);
        set = copy_hash_table(s.set,s.bins);
        hashFunction = s.hashFunction;
        bins = s.bins;
        used = s.used;
    }

    return *this;
}


template <typename T>
bool HashSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void HashSet<T>::add(const T& element)
{
    int bin = hashFunction(element);
    LN* c = findElement(bin,element);
    if(c == nullptr)
    {
        ensure_load_factor(used+1);
        bin = hashFunction(element);
        set[bin] = new LN(element,set[bin]);
        ++used;
    }
}


template <typename T>
bool HashSet<T>::contains(const T& element) const
{
    return findElement(hashFunction(element),element) != nullptr;
}


template <typename T>
unsigned int HashSet<T>::size() const
{
    return used;
}

template <typename T>
void HashSet<T>::ensure_load_factor(int new_used)
{
    if(double(new_used)/double(bins) <= loadFactor)
        return;

    LN** old_set = set;
    int old_bins = bins;
    
    bins = 2*old_bins;
    set = new LN*[bins];

    for(int b=0; b<bins; ++b)
        set[b] = new LN();

    for(int b=0; b<old_bins; ++b)
    {
        LN* c = old_set[b];
        for(; c->next != nullptr; )
        {
            int bin = hashFunction(c->value);
            LN* to_move = c;
            c = c->next;
            to_move->next = set[bin];
            set[bin] = to_move;
        }
        delete c;
    }
    delete[] old_set;
}

template <typename T>
typename HashSet<T>::LN* HashSet<T>::findElement(int bin, const T& element) const
{
    for(LN* c = set[bin]; c->next != nullptr; c = c->next)
        if(element == c->value)
            return c;

    return nullptr;

}

template <typename T>
typename HashSet<T>::LN* HashSet<T>::copy_list(LN* l) const
{
    if(l == nullptr)
        return nullptr;
    else
        return new LN(l->value, copy_list(l->next));
}

template <typename T>
typename HashSet<T>::LN** HashSet<T>::copy_hash_table(LN** ht, int bins) const
{
    LN** answer = new LN*[bins];
    for(int b = 0; b < bins; ++b)
    {
        answer[b] = copy_list(ht[b]);
    }

    return answer;
}

template <typename T>
void HashSet<T>::delete_hash_table(LN**& ht, int bins)
{
    for(int b = 0; b < bins; ++b)
    {
        for(LN* c = ht[b]; c != nullptr; )
        {
            LN* to_delete = c;
            c = c->next;
            delete to_delete;
        }
    }

    delete[] ht;
    ht = nullptr;
}
#endif // HASHSET_HPP

