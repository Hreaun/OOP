#include "tritset.h"
#include <gtest/gtest.h>

TEST(TritsetOp, OR){
  tritset a(5);
  a[0] = trit::True;
  tritset b(5);
  b[0] = trit::False;
  tritset c = a | b;

  EXPECT_EQ(trit::True, (trit)c[0]);
}

TEST(TritsetOp, AND){
  tritset a(5);
  a[0] = trit::True;
  tritset b(5);
  b[0] = trit::False;
  tritset c = a & b;

  EXPECT_EQ(trit::False, (trit)c[0]);
}

TEST(TritsetOp, NegTritset){
  tritset a(5);
  a[0] = trit::True;
  tritset c = ~a;

  EXPECT_EQ(trit::False, (trit)c[0]);
}


TEST(TritsetOp, TritsetResize){
  tritset a(5);
  a[100003] = trit::Unknown;
  EXPECT_EQ(5, a.getSize());

  a[15345] = trit::True;
  EXPECT_EQ(15346, a.getSize());

  tritset b(100);
  tritset c = a & b;
  EXPECT_EQ(15346, c.getSize());
}

TEST(Methods, Shrink){
  tritset a(100);

  a[79] = trit::True;
  a.shrink();
  EXPECT_EQ(80, a.getSize());

  a[79] = trit::Unknown;
  a.shrink();
  EXPECT_EQ(0, a.getSize());
}

TEST(Methods, Length) {
  tritset a(100);
  a[57] = trit::True;
  EXPECT_EQ(58, a.length());
  a[57] = trit::Unknown;
  EXPECT_EQ(0, a.length());
}

TEST(Methods, Trim) {
  tritset a(100);
  a[57] = trit::True;
  a[97] = trit::False;
  a.trim(57);
  EXPECT_EQ(trit::Unknown, (trit)a[57]);
  EXPECT_EQ(trit::Unknown, (trit)a[97]);
}

TEST(Methods, Cardinality){
  tritset a(100);

  for (size_t i = 60; i < a.getSize(); ++i){
    a[i] = trit::True;
  }
  EXPECT_EQ(40, a.cardinality(trit::True));

  a.trim(0);
  for (size_t i = 60; i < a.getSize()-20; ++i){
    if (i % 2 == 0)
      a[i] = trit::Unknown;
    else
      a[i] = trit::False;
  }
  EXPECT_EQ(10, a.cardinality(trit::False));
  EXPECT_EQ(70, a.cardinality(trit::Unknown));
}

TEST(Methods, CardinalityMap){
  std::unordered_map<trit, int> card;
  tritset a(100);

  for (size_t i = 60; i < a.getSize(); ++i){
    a[i] = trit::True;
  }
  for (size_t i = 0; i < 60; ++i){
    if (i % 2 == 0)
      a[i] = trit::Unknown;
    else
      a[i] = trit::False;
  }
  card = a.cardinality();

  EXPECT_EQ(30, card[trit::False]);
  EXPECT_EQ(30, card[trit::Unknown]);
  EXPECT_EQ(40, card[trit::True]);
}