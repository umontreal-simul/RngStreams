#ifndef RNGSTREAM_H
#define RNGSTREAM_H

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>

struct RngContents {
  std::string name; 
  bool antithetic; 
  bool increased_precision; 
  std::vector<double> Ig; 
  std::vector<double> Bg; 
  std::vector<double> Cg; 
};

bool operator==(const RngContents & lhs, const RngContents & rhs);
bool operator!=(const RngContents & lhs, const RngContents & rhs);

class RngStream {
 public:
  /// @brief Constructor of a de novo stream
  /// @param name C character array 
  RngStream(const char *name = "");

  /// @brief Constructor 
  /// @param RngContents struct. 
  RngStream(const RngContents & rng_contents);

  /// @brief Get RngContents struct. 
  RngContents GetRngContents() const;

  static bool SetPackageSeed(const unsigned long seed[6]);

  void ResetStartStream();

  void ResetStartSubstream();

  void ResetNextSubstream();
  
  void ResetToRngContents(const RngContents & rng_contents);

  void SetAntithetic(bool a);

  void IncreasedPrecis(bool incp);

  bool SetSeed(const unsigned long seed[6]);

  void AdvanceState(long e, long c);

  void GetState(unsigned long seed[6]) const;

  void WriteState() const;

  void WriteStateFull() const;

  double RandU01();

  int RandInt(int i, int j);

 private:
  double Cg[6], Bg[6], Ig[6];

  bool anti, incPrec;

  std::string name;

  static double nextSeed[6];

  double U01();

  double U01d();
};


bool is_synchronized_clone(const RngStream& S1, const RngStream& S2);

#endif
