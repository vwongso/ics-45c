// BSTSetTests.cpp

#include <gtest/gtest.h>
#include "BSTSet.hpp"

TEST(BSTSetConstructors,defaultConstructor)
{   
    BSTSet<int> x;
    
    ASSERT_EQ(x.size(),0);
}

TEST(BSTSetAdd,AddIncrementsSize)
{
    BSTSet<int> x;
    x.add(3);

    ASSERT_EQ(x.size(),1);
}

TEST(BSTSetContains,containsElement)
{
    BSTSet<int> x;
    x.add(5);
    x.add(2);

    ASSERT_EQ(x.contains(5),true);
}

TEST(BSTSetCountSize,countsSize)
{
    BSTSet<int> x;
    x.add(5);
    x.add(2);

    ASSERT_EQ(x.size(),2);
}

