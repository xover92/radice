

#include "Particle.hpp"

#include <iostream>

#include "ParticleType.hpp"
#include "ResonanceType.hpp"

int Particle::fNParticleType = 0;
ParticleType* Particle::Array[fMaxNumParticleType] ={};

int Particle::FindParticle(const char* ParticleName) {
  int i{0};
  for (; i < fNParticleType; i++) {
    if (Array[i]->GetName() == ParticleName) {
      return i;
    }
  }
  if (i == fNParticleType) {
    i = -1;
  }
  return i;
}

Particle::Particle(const char* fName, double Px, double Py, double Pz)
    : fPx_{Px}, fPy_{Py}, fPz_{Pz} {
  Px = 0;
  Py = 0;
  Pz = 0;
  fIndex = FindParticle(fName);
  if (fIndex == -1) {
    std::cout << "Particle not found." << '\n';
  }
}
// creo oggetto di tipo particle associando ad un tipo di particella nota gli
// impulsi

void Particle::AddParticleType(const char* name, double mass, int charge,
                               double width) {
  if (fNParticleType < fMaxNumParticleType) {
    if (FindParticle(name) == -1) {
      Array[fNParticleType] = new ResonanceType{name, mass, charge, width};
      ++fNParticleType;
    }
  } else {
    std::cout << "Maximum number of particle types reached." << '\n';
  }
}
/*
se n. particelle è minore uguale a 10 e la particella formita non è in lista
aggiungo tipo di particella all'array(controllo fatto con findparticle).
fNparticletype tiene conto del numero di tipi di particelle
*/
int Particle::GetParticleIndex() const { return fIndex; }

void Particle::SetIndex(int index) {
  if (index >= 0 && index < fNParticleType) {
    fIndex = index;
  } else {
    std::cout << "Invalid index." << std::endl;
  }
}

void Particle::SetIndex(const char* name) {
  int index = FindParticle(name);
  if (index != -1) {
    fIndex = index;
  } else {
    std::cout << "Particle type not found." << std::endl;
  }
}

void Particle::PrintParticles() {
  for (int i{0}; i < fNParticleType; i++) {
    Array[i]->print();
  }
}

void Particle::PrintType() const {
  std::cout << "Particle name: " << Array[fIndex]->GetName() << '\n';
  std::cout << "Particle index: " << fIndex << '\n';
  std::cout << "Px: " << GetPx() << '\n';
  std::cout << "Py: " << GetPy() << '\n';
  std::cout << "Pz: " << GetPz() << '\n';
}

double Particle::GetPx() const { return fPx_; }
double Particle::GetPy() const { return fPy_; }
double Particle::GetPz() const { return fPz_; }

double Particle::GetMass() const { return Array[fIndex]->GetMass(); }

double Particle::TotEnergy() const {
  double Energy = std::sqrt(std::pow(GetMass(), 2) + std::pow(GetPx(), 2) +
                            std::pow(GetPy(), 2) + std::pow(GetPz(), 2));
  return Energy;
}

double Particle::InvMass(Particle& p) {
  double MInv = std::sqrt(std::pow(TotEnergy() + p.TotEnergy(), 2) -
                          std::pow(GetPx() + p.GetPx(), 2) -
                          std::pow(GetPy() + p.GetPy(), 2) -
                          std::pow(GetPz() + p.GetPz(), 2));
  return MInv;
}

void Particle::SetP(double px, double py, double pz) {
  fPx_ = px;
  fPy_ = py;
  fPz_ = pz;
}