#include <gtest/gtest.h>
#include "tritset.h"

class tritsetFixture : public ::testing::Test {
 protected:
  virtual void TearDown() {
    delete a;
    delete b;
  }
  virtual void SetUp() {
    b = new tritset(3);
    (*b)[0] = trit::True;
    (*b)[1] = trit::Unknown;
    (*b)[2] = trit::False;

    a = new tritset(3);
    (*a)[0] = trit::False;
    (*a)[1] = trit::True;
    (*a)[2] = trit::Unknown;
  }
  tritset *a{};
  tritset *b{};
};

TEST_F(tritsetFixture, AND) {
  EXPECT_EQ(trit::True, ((*a)[1] & (*b)[0]));
  EXPECT_EQ(trit::False, ((*a)[0] & (*a)[1]));
  EXPECT_EQ(trit::Unknown, ((*a)[1] & (*a)[2]));
  EXPECT_EQ(trit::False, ((*a)[1] & (*b)[2]));
}

TEST_F(tritsetFixture, OR){
  EXPECT_EQ(trit::True, ((*a)[1] | (*a)[2]));
  EXPECT_EQ(trit::False, ((*a)[0] | (*b)[2]));
  EXPECT_EQ(trit::Unknown, ((*a)[0] | (*a)[2]));
  EXPECT_EQ(trit::True, ((*a)[1] | (*b)[2]));
}

TEST_F(tritsetFixture, NegValue){
  EXPECT_EQ(trit::True, (~(*a)[0]));
  EXPECT_EQ(trit::False, (~(*a)[1]));
  EXPECT_EQ(trit::Unknown, (~(*a)[2]));
  EXPECT_EQ(trit::True, (~(*b)[2]));
}
