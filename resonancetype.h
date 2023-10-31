
#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP

#include "ParticleType.hpp"

class ResonanceType : public ParticleType {
 private:
  const double fWidth_;

 public:
  ResonanceType(const char* fName, double fMass, int fCharge, double fWidth);
  double GetWidth() const;
  void print();
};

#endif
