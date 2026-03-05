#include "DiffQL/DiffEngine/DiffEngine.hpp"
#include <gtest/gtest.h>

// Exposes protected members for unit testing
class DiffEngineTest : public DiffEngine
{
public:
  DiffEngineTest() : DiffEngine({}, {}) {}

  using DiffEngine::jaro_winkler;
};

class JaroWinkler : public ::testing::Test
{
protected:
  DiffEngineTest engine;
};

TEST_F(JaroWinkler, BothEmpty)
{
  EXPECT_FLOAT_EQ(engine.jaro_winkler("", ""), 1.0f);
}

TEST_F(JaroWinkler, OriginEmpty)
{
  EXPECT_FLOAT_EQ(engine.jaro_winkler("", "abc"), 0.0f);
}

TEST_F(JaroWinkler, DestEmpty)
{
  EXPECT_FLOAT_EQ(engine.jaro_winkler("abc", ""), 0.0f);
}

TEST_F(JaroWinkler, IdenticalStrings)
{
  EXPECT_FLOAT_EQ(engine.jaro_winkler("hello", "hello"), 1.0f);
}

TEST_F(JaroWinkler, CompletelyDifferent)
{
  EXPECT_FLOAT_EQ(engine.jaro_winkler("abc", "xyz"), 0.0f);
}

TEST_F(JaroWinkler, Symmetry)
{
  EXPECT_FLOAT_EQ(
      engine.jaro_winkler("kitten", "sitting"),
      engine.jaro_winkler("sitting", "kitten")
  );
}

// Classic Jaro-Winkler reference: MARTHA/MARHTA -> ~0.9611
TEST_F(JaroWinkler, ClassicMarthaMarhta)
{
  EXPECT_NEAR(engine.jaro_winkler("MARTHA", "MARHTA"), 0.9611f, 0.001f);
}

TEST_F(JaroWinkler, SqlColumnNamesMissingSeparator)
{
  EXPECT_GT(engine.jaro_winkler("user_id", "userid"), 0.95f);
}

TEST_F(JaroWinkler, SqlColumnNamesIdentical)
{
  EXPECT_FLOAT_EQ(engine.jaro_winkler("created_at", "created_at"), 1.0f);
}

TEST_F(JaroWinkler, SqlColumnNamesSimilar)
{
  EXPECT_GT(engine.jaro_winkler("first_name", "firstname"), 0.95f);
}

TEST_F(JaroWinkler, SqlColumnNamesUnrelated)
{
  EXPECT_LT(engine.jaro_winkler("user_id", "invoice_date"), 0.6f);
}
