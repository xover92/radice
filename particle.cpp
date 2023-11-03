
#include "Particle.hpp"

#include <iostream>

#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include <cmath>  // for M_PI
#include <cstdlib> //for RAND_MAX

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
int Particle::Decay2body(Particle &dau1,Particle &dau2) const {
  if(GetMass() == 0.0){
    printf("Decayment cannot be preformed if mass is zero\n");
    return 1;
  }
  
  double massMot = GetMass();
  double massDau1 = dau1.GetMass();
  double massDau2 = dau2.GetMass();

  if(fIndex > -1){ // add width effect

    // gaussian random numbers

    float x1, x2, w, y1;
    
    double invnum = 1./RAND_MAX;
    do {
      x1 = 2.0 * rand()*invnum - 1.0;
      x2 = 2.0 * rand()*invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while ( w >= 1.0 );
    
    w = sqrt( (-2.0 * log( w ) ) / w );
    y1 = x1 * w;

    massMot += Array[fIndex]->GetWidth() * y1;

  }

  if(massMot < massDau1 + massDau2){
    printf("Decayment cannot be preformed because mass is too low in this channel\n");
    return 2;
  }
  
  double pout = sqrt((massMot*massMot - (massDau1+massDau2)*(massDau1+massDau2))*(massMot*massMot - (massDau1-massDau2)*(massDau1-massDau2)))/massMot*0.5;

  double norm = 2*M_PI/RAND_MAX;

  double phi = rand()*norm;
  double theta = rand()*norm*0.5 - M_PI/2.;
  dau1.SetP(pout*sin(theta)*cos(phi),pout*sin(theta)*sin(phi),pout*cos(theta));
  dau2.SetP(-pout*sin(theta)*cos(phi),-pout*sin(theta)*sin(phi),-pout*cos(theta));

  double energy = sqrt(fPx_*fPx_ + fPy_*fPy_ + fPz_*fPz_ + massMot*massMot);

  double bx = fPx_/energy;
  double by = fPy_/energy;
  double bz = fPz_/energy;

  dau1.Boost(bx,by,bz);
  dau2.Boost(bx,by,bz);

  return 0;
}
void Particle::Boost(double bx, double by, double bz)
{

  double energy = TotEnergy();

  //Boost this Lorentz vector
  double b2 = bx*bx + by*by + bz*bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx*fPx_ + by*fPy_ + bz*fPz_;
  double gamma2 = b2 > 0 ? (gamma - 1.0)/b2 : 0.0;

  fPx_ += gamma2*bp*bx + gamma*bx*energy;
  fPy_ += gamma2*bp*by + gamma*by*energy;
  fPz_ += gamma2*bp*bz + gamma*bz*energy;
}