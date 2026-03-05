#include "DiffQL/DiffEngine/LevDistance.hpp"
#include <gtest/gtest.h>

using DiffQL::lev_distance;

TEST(LevDistance, BothEmpty)
{
  EXPECT_EQ(lev_distance("", ""), 0);
}

TEST(LevDistance, OriginEmpty)
{
  EXPECT_EQ(lev_distance("", "abc"), 3);
}

TEST(LevDistance, DestEmpty)
{
  EXPECT_EQ(lev_distance("abc", ""), 3);
}

TEST(LevDistance, IdenticalStrings)
{
  EXPECT_EQ(lev_distance("hello", "hello"), 0);
}

TEST(LevDistance, SingleSubstitution)
{
  EXPECT_EQ(lev_distance("cat", "cut"), 1);
}

TEST(LevDistance, SingleInsertion)
{
  EXPECT_EQ(lev_distance("cat", "cats"), 1);
}

TEST(LevDistance, SingleDeletion)
{
  EXPECT_EQ(lev_distance("cats", "cat"), 1);
}

TEST(LevDistance, ClassicKittenSitting)
{
  EXPECT_EQ(lev_distance("kitten", "sitting"), 3);
}

TEST(LevDistance, ClassicSundaySaturday)
{
  EXPECT_EQ(lev_distance("sunday", "saturday"), 3);
}

TEST(LevDistance, CompletelyDifferent)
{
  EXPECT_EQ(lev_distance("abc", "xyz"), 3);
}

TEST(LevDistance, Symmetry)
{
  EXPECT_EQ(lev_distance("kitten", "sitting"), lev_distance("sitting", "kitten"));
}

TEST(LevDistance, SqlColumnNames)
{
  EXPECT_EQ(lev_distance("user_id", "userid"), 1);
  EXPECT_EQ(lev_distance("created_at", "created_at"), 0);
  EXPECT_EQ(lev_distance("first_name", "firstname"), 1);
}
