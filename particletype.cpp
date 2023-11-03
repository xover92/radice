#include "ParticleType.hpp"

#include <iostream>

ParticleType::ParticleType(const char* fName, double fMass, int fCharge)
    : fName_(fName), fMass_(fMass), fCharge_(fCharge) {}

double ParticleType::GetMass() const { return fMass_; }
int ParticleType::GetCharge() const { return fCharge_; }
const char* ParticleType::GetName() const { return fName_; }
void ParticleType::print() {
  std::cout << "The name is: " << fName_ << '\n';
  std::cout << "The mass is: " << fMass_ << '\n';
  std::cout << "The charge is: " << fCharge_ << '\n';
}