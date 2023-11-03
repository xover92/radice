#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

class ParticleType {
 private:
  const char* fName_;
  const double fMass_;
  const int fCharge_;

 public:
  ParticleType(const char* fName, double fMass, int fCharge);
  double GetMass() const;
  int GetCharge() const;
  const char* GetName() const;
  virtual void print();
}
  #endif