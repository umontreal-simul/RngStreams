#include <gtest/gtest.h>

#include "RngStream.h"

namespace {

template <typename T>
bool almost_equal(T a, T b,
                  T max_rel_diff = std::numeric_limits<T>::epsilon()) {
  auto diff = std::abs(a - b);
  auto A = std::abs(a);
  auto B = std::abs(b);
  auto largest = (B > A) ? B : A;
  if (diff <= largest * max_rel_diff) return true;
  return false;
};

TEST(LEcuyerOriginalTests, FirstTest) {
  double sum;
  int i;
  RngStream g1("g1");
  RngStream g2("g2");
  RngStream g3("g3");

  sum = g2.RandU01() + g3.RandU01();

  g1.AdvanceState(5, 3);
  sum += g1.RandU01();

  g1.ResetStartStream();
  for (i = 0; i < 35; i++) g1.AdvanceState(0, 1);
  sum += g1.RandU01();

  g1.ResetStartStream();
  long sumi = 0;
  for (i = 0; i < 35; i++) sumi += g1.RandInt(1, 10);
  sum += sumi / 100.0;

  double sum3 = 0.0;
  for (i = 0; i < 100; i++) {
    sum3 += g3.RandU01();
  }
  sum += sum3 / 10.0;

  g3.ResetStartStream();
  for (i = 1; i <= 5; i++) sum += g3.RandU01();

  for (i = 0; i < 4; i++) g3.ResetNextSubstream();
  for (i = 0; i < 5; i++) sum += g3.RandU01();

  g3.ResetStartSubstream();
  for (i = 0; i < 5; i++) sum += g3.RandU01();

  g2.ResetNextSubstream();
  sum3 = 0.0;
  for (i = 1; i <= 100000; i++) sum3 += g2.RandU01();
  sum += sum3 / 10000.0;

  g3.SetAntithetic(true);
  sum3 = 0.0;
  for (i = 1; i <= 100000; i++) sum3 += g3.RandU01();
  sum += sum3 / 10000.0;

  unsigned long germe[6] = {1, 1, 1, 1, 1, 1};
  RngStream::SetPackageSeed(germe);

  RngStream gar[4] = {"Poisson", "Laplace", "Galois", "Cantor"};
  for (i = 0; i < 4; i++) sum += gar[i].RandU01();

  gar[2].AdvanceState(-127, 0);
  sum += gar[2].RandU01();

  gar[2].ResetNextSubstream();
  gar[2].IncreasedPrecis(true);
  sum3 = 0.0;
  for (i = 0; i < 100000; i++) sum3 += gar[2].RandU01();
  sum += sum3 / 10000.0;

  gar[2].SetAntithetic(true);
  sum3 = 0.0;
  for (i = 0; i < 100000; i++) sum3 += gar[2].RandU01();
  sum += sum3 / 10000.0;
  gar[2].SetAntithetic(false);

  gar[2].IncreasedPrecis(false);
  for (i = 0; i < 4; i++) sum += gar[i].RandU01();

  ASSERT_TRUE(almost_equal(sum, 39.697547445251, 1e-12));
}

TEST(LEcuyerOriginalTests, SecondTest) {
  double sum = 0.0;
  int i;
  long unsigned int initSeed[6] = {12345, 12345, 12345, 12345, 12345, 12345};
  RngStream::SetPackageSeed(initSeed);
  RngStream g1("g1");
  RngStream g2("g2");
  RngStream g3("g3");

  std::cout.precision(13);
  std::cout << "Initial states of g1, g2, and g3:\n\n";
  g1.WriteState();
  g2.WriteState();
  g3.WriteState();
  sum = g2.RandU01() + g3.RandU01();
  for (i = 0; i < 12345; i++) g2.RandU01();

  g1.AdvanceState(5, 3);
  std::cout << "State of g1 after advancing by 2^5 + 3 = 35 steps:\n";
  g1.WriteState();
  std::cout << "g1.RandU01 () = " << g1.RandU01() << "\n\n";

  g1.ResetStartStream();
  for (i = 0; i < 35; i++) g1.AdvanceState(0, 1);
  std::cout << "State of g1 after reset and advancing 35 times by 1:\n";
  g1.WriteState();
  std::cout << "g1.RandU01 () = " << g1.RandU01() << "\n\n";

  g1.ResetStartStream();
  long sumi = 0;
  for (i = 0; i < 35; i++) sumi += g1.RandInt(1, 10);
  std::cout << "State of g1 after reset and 35 calls to RandInt (1, 10):\n";
  g1.WriteState();
  std::cout << "   sum of 35 integers in [1, 10] = " << sumi << "\n\n";
  sum += sumi / 100.0;
  std::cout << "g1.RandU01 () = " << g1.RandU01() << "\n\n";

  double sum3 = 0.0;
  g1.ResetStartStream();
  g1.IncreasedPrecis(true);
  sumi = 0;
  for (i = 0; i < 17; i++) sumi += g1.RandInt(1, 10);
  std::cout << "State of g1 after reset, IncreasedPrecis (true) and 17 calls"
       << " to RandInt (1, 10):\n";
  g1.WriteState();
  g1.IncreasedPrecis(false);
  g1.RandInt(1, 10);
  std::cout << "State of g1 after IncreasedPrecis (false) and 1 call to RandInt\n";
  g1.WriteState();
  sum3 = sumi / 10.0;

  g1.ResetStartStream();
  g1.IncreasedPrecis(true);
  for (i = 0; i < 17; i++) sum3 += g1.RandU01();
  std::cout << "State of g1 after reset, IncreasedPrecis (true) and 17 calls"
       << " to RandU01:\n";
  g1.WriteState();
  g1.IncreasedPrecis(false);
  g1.RandU01();
  std::cout << "State of g1 after IncreasedPrecis (false) and 1 call to RandU01\n";
  g1.WriteState();
  sum += sum3 / 10.0;

  sum3 = 0.0;
  std::cout << "Sum of first 100 output values from stream g3:\n";
  for (i = 0; i < 100; i++) {
    sum3 += g3.RandU01();
  }
  std::cout << "   sum = " << sum3 << "\n\n";
  sum += sum3 / 10.0;

  std::cout << "\nReset stream g3 to its initial seed.\n";
  g3.ResetStartStream();
  std::cout << "First 5 output values from stream g3:\n";
  for (i = 1; i <= 5; i++) std::cout << g3.RandU01() << "\n";
  sum += g3.RandU01();

  std::cout << "\nReset stream g3 to the next SubStream, 4 times.\n";
  for (i = 1; i <= 4; i++) g3.ResetNextSubstream();
  std::cout << "First 5 output values from stream g3, fourth SubStream:\n";
  for (i = 1; i <= 5; i++) std::cout << g3.RandU01() << "\n";
  sum += g3.RandU01();

  std::cout << "\nReset stream g2 to the beginning of SubStream.\n";
  g2.ResetStartSubstream();
  std::cout << " Sum of 100000 values from stream g2 with double precision:   ";
  sum3 = 0.0;
  g2.IncreasedPrecis(true);
  for (i = 1; i <= 100000; i++) sum3 += g2.RandU01();
  std::cout << sum3 << "\n";
  sum += sum3 / 10000.0;
  g2.IncreasedPrecis(false);

  g3.SetAntithetic(true);
  std::cout << " Sum of 100000 antithetic output values from stream g3:   ";
  sum3 = 0.0;
  for (i = 1; i <= 100000; i++) sum3 += g3.RandU01();
  std::cout << sum3 << "\n";
  sum += sum3 / 10000.0;

  std::cout << "\nSetPackageSeed to seed = { 1, 1, 1, 1, 1, 1 }\n";
  unsigned long germe[6] = {1, 1, 1, 1, 1, 1};
  RngStream::SetPackageSeed(germe);

  std::cout << "\nDeclare an array of 4 named streams"
       << " and write their full state\n";
  RngStream gar[4] = {"Poisson", "Laplace", "Galois", "Cantor"};
  for (i = 0; i < 4; i++) gar[i].WriteStateFull();

  std::cout << "Jump stream Galois by 2^127 steps backward\n";
  gar[2].AdvanceState(-127, 0);
  gar[2].WriteState();
  gar[2].ResetNextSubstream();

  for (i = 0; i < 4; i++) sum += gar[i].RandU01();

  std::cout << "--------------------------------------\n";
  std::cout << "Final Sum = " << sum << "\n\n";
  ASSERT_TRUE(almost_equal(sum, 23.70532386289, 1e-11));
}

}  // namespace