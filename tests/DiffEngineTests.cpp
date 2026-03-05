#include "DiffQL/DiffEngine/DiffEngine.hpp"
#include <gtest/gtest.h>

using DiffQL::jaro_winkler;

TEST(JaroWinkler, BothEmpty)
{
  EXPECT_FLOAT_EQ(jaro_winkler("", ""), 1.0f);
}

TEST(JaroWinkler, OriginEmpty)
{
  EXPECT_FLOAT_EQ(jaro_winkler("", "abc"), 0.0f);
}

TEST(JaroWinkler, DestEmpty)
{
  EXPECT_FLOAT_EQ(jaro_winkler("abc", ""), 0.0f);
}

TEST(JaroWinkler, IdenticalStrings)
{
  EXPECT_FLOAT_EQ(jaro_winkler("hello", "hello"), 1.0f);
}

TEST(JaroWinkler, CompletelyDifferent)
{
  // No characters match within the window → score is 0
  EXPECT_FLOAT_EQ(jaro_winkler("abc", "xyz"), 0.0f);
}

TEST(JaroWinkler, Symmetry)
{
  EXPECT_FLOAT_EQ(jaro_winkler("kitten", "sitting"), jaro_winkler("sitting", "kitten"));
}

// Classic Jaro-Winkler reference: MARTHA/MARHTA → ~0.9611
TEST(JaroWinkler, ClassicMarthaMarhta)
{
  EXPECT_NEAR(jaro_winkler("MARTHA", "MARHTA"), 0.9611f, 0.001f);
}

TEST(JaroWinkler, SqlColumnNamesMissingSeparator)
{
  // user_id vs userid: one char difference, long common prefix → very high similarity
  EXPECT_GT(jaro_winkler("user_id", "userid"), 0.95f);
}

TEST(JaroWinkler, SqlColumnNamesIdentical)
{
  EXPECT_FLOAT_EQ(jaro_winkler("created_at", "created_at"), 1.0f);
}

TEST(JaroWinkler, SqlColumnNamesSimilar)
{
  // first_name vs firstname: similar structure
  EXPECT_GT(jaro_winkler("first_name", "firstname"), 0.95f);
}

TEST(JaroWinkler, SqlColumnNamesUnrelated)
{
  // completely unrelated column names → low similarity
  EXPECT_LT(jaro_winkler("user_id", "invoice_date"), 0.6f);
}
