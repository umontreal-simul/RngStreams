#include <gtest/gtest.h>

#include "RngStream.h"

namespace {

std::vector<double> sample_uniform(const int n, RngStream& S) {
  std::vector<double> res(n);
  for (int i = 0; i != n; ++i) {
    res.push_back(S.RandU01());
  }
  return res;
}

TEST(LEcuyerAugmentationTests, CopyConstructor) {
  // Source (S1) has not advanced from inception
  RngStream S1("tom");
  RngStream S2(S1);
  ASSERT_TRUE(is_synchronized_clone(S1, S2));

  std::vector<double> u1 = sample_uniform(10, S1);
  std::vector<double> u2 = sample_uniform(10, S2);
  ASSERT_EQ(u1, u2);
  ASSERT_TRUE(is_synchronized_clone(S1, S2));

  S1.RandU01();
  ASSERT_FALSE(is_synchronized_clone(S1, S2));
  S2.RandU01();
  ASSERT_TRUE(is_synchronized_clone(S1, S2));

  // Source (S1) has advanced from inception
  RngStream S3(S1);
  ASSERT_TRUE(is_synchronized_clone(S3, S2));
  S3.ResetStartStream();
  S2.ResetStartStream();
  ASSERT_TRUE(is_synchronized_clone(S3, S2));
}

TEST(LEcuyerAugmentationTests, CopyAssingment) {
  RngStream S1("tom");
  RngStream S2 = S1;
  ASSERT_TRUE(is_synchronized_clone(S1, S2));

  std::vector<double> u1 = sample_uniform(10, S1);
  std::vector<double> u2 = sample_uniform(10, S2);
  ASSERT_EQ(u1, u2);
  ASSERT_TRUE(is_synchronized_clone(S1, S2));

  S1.RandU01();
  ASSERT_FALSE(is_synchronized_clone(S1, S2));
}

TEST(LEcuyerAugmentationTests, AdvanceState) {
  // single precision
  RngStream S1("tom");
  RngStream S2(S1);
  int u;
  for (int i = 0; i < 10; ++i) {
    u = S1.RandInt(1, 10);
  }
  S2.AdvanceState(3, 2);  // 2^3 + 2
  ASSERT_TRUE(is_synchronized_clone(S1, S2));

  // increased precision
  S1.ResetStartStream();
  S1.IncreasedPrecis(true);
  S2.ResetStartStream();
  S2.IncreasedPrecis(true);

  for (int i = 0; i < 10; ++i) {
    u = S1.RandInt(1, 10);
  }
  S2.AdvanceState(3, 2);  // 2^3 + 2 = 10
  S2.AdvanceState(3, 2);  // Increased Precision means twice the Advance States
  ASSERT_TRUE(is_synchronized_clone(S1, S2));
}

TEST(LEcuyerAugmentationTests, ConstructFromRngContents) {
  RngStream S1("tom");
  S1.AdvanceState(0, 10);

  RngContents S1_after_10 = S1.GetRngContents();
  RngStream S2(S1_after_10);
  ASSERT_TRUE(is_synchronized_clone(S1, S2));

  std::vector<double> u1 = sample_uniform(10, S1);
  std::vector<double> u2 = sample_uniform(10, S2);
  ASSERT_EQ(u1, u2);
  ASSERT_TRUE(is_synchronized_clone(S1, S2));

  S1.ResetStartStream();
  S2.ResetStartStream();
  ASSERT_TRUE(is_synchronized_clone(S1, S2));
}

TEST(LEcuyerAugmentationTests, ResetToRngContents) {
  RngStream S1("tom");
  S1.AdvanceState(0, 10);
  RngContents S1_after_10 = S1.GetRngContents();
  std::vector<double> u1 = sample_uniform(10, S1);
  
  S1.ResetToRngContents(S1_after_10);
  std::vector<double> u2 = sample_uniform(10, S1);
  ASSERT_EQ(u1, u2);
}

}  // end namespace