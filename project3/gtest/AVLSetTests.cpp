// AVLSetTests.cpp

#include <gtest/gtest.h>
#include "AVLSet.hpp"

TEST(AVLSetConstructors, defaulConstructor)
{
    AVLSet<int> x;

    ASSERT_EQ(x.size(),0);
}

TEST(AVLSetAdd,AddIncrementsSize)
{
    AVLSet<int> x;
    x.add(3);
  //  x.add();
    ASSERT_EQ(x.size(),1);
}

TEST(AVLSetContains, containsElement)
{
    AVLSet<int> x;
    x.add(5);
    x.add(2);

    ASSERT_EQ(x.contains(5),true);
}


