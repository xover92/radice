
#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include "ParticleType.hpp"

class Particle {
 private:
  static const int fMaxNumParticleType{10};
  double fPx_;
  double fPy_;
  double fPz_;
  static ParticleType* Array[fMaxNumParticleType];
  static int fNParticleType;
  int fIndex{0};
  static int FindParticle(const char*);

 public:
  static void AddParticleType(const char*, double, int, double);
  Particle(const char* fName, double, double, double);
  int GetParticleIndex() const;
  void SetIndex(int);
  void SetIndex(const char*);
  static void PrintParticles();
  void PrintType() const;
  double GetPx() const;
  double GetPy() const;
  double GetPz() const;
  double GetMass() const;
  double TotEnergy() const;
  double InvMass(Particle& p);
  void SetP(double px,double py,double pz);
};

#endif