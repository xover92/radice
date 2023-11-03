
#include <iostream>
#include <vector>

#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"

int main() {
  gRandom→SetSeed();

  Particle::AddParticleType("Pione+", 0.13957, 1);
  Particle::AddParticleType("Pione-", 0.13957, -1);
  Particle::AddParticleType("Kaone+", 0, 49367, 1);
  Particle::AddParticleType("Kaone-", 0, 49367, -1);
  Particle::AddParticleType("Protone+", 0.93827, 1);
  Particle::AddParticleType("Protone-", 0.93827, -1);
  Particle::AddParticleType("K*", 0.89166, 0, 0.05);

  Particle EventParticles[120];

TH1F *h1 = new TH1F("Isto1","Tipi di particelle gnerate",7,0., 6.);
TH1F *h2 = new TH1F("Isto2","Distribuzione angoli azimutali",10,0., 6.2832);
TH1F *h3 = new TH1F("Isto3","Distribuzione angoli polari",10,0., 3.1416);
TH1F *h4 = new TH1F("Isto4","Distribuzione impulso",20,0.,5.);
TH1F *h5 = new TH1F("Isto5","Impulso Trasverso",10,0.,5.);
TH1F *h6 = new TH1F("Isto6","Distribuzione Energia", 20,0., 4.);
TH1F *h7 = new TH1F("Isto7","Massa invariante gen.",20,0., 11.);
TH1F *h8 = new TH1F("Isto8","Distribuzione angoli polari",10,0., 3.1416); //mancano i 5 difficili
  for (int i{0}; i < 1E5; i++) {
    int k = 0;
    for (int j{0}; j < 100; j++) {
      double theta = gRandom->Uniform(0, TMath::Pi());
      double phi = gRandom->Uniform(0, 2 * TMath::Pi());
      double impulse = gRandom->Exp(1);
      EventParticles[j].SetP(impulse * TMath::Sin(theta) * TMath::Cos(phi),
                             impulse * TMath::Sin(theta) * TMath::sin(phi),
                             impulse * TMath::Cos(theta));
      double x = gRandom->Rndm();
      if (x < 0.4) {
        EventParticles[j].SetIndex("Pione+");
      }; else if (x < 0.8) {
        EventParticles[j].SetIndex("Pione-");
      } else if (x < 0.85) {
        EventParticles[j].SetIndex("Kaone+");
      } else if (x < 0.90) {
        EventParticles[j].SetIndex("Kaone-");
      } else if (x < 0.945) {
        EventParticles[j].SetIndex("Protone+");
      }  // ricordiamoci di cambiare negli effettivi
      else if (x < 0.99) {
        EventParticles[j].SetIndex("Protone+");
      }  // indici perchè questi sono tanti loop e pesano
      else if {
        EventParticles[j].SetIndex("K*");
      }

      if (EventParticles[j].GetParticleIndex() == FindParticle("K*")) {
        double y = gRandom->Rndm();
        if (y < 0.5) {
          EventParticles[100 + k].SetIndex("Pione+");
          EventParticles[100 + k + 1].SetIndex("Kaone-");
        } else {
          EventParticles[100 + k].SetIndex("Pione-");
          EventParticles[100 + k + 1].SetIndex("Kaone+");
        }
        EventParticles[j].Decay2Body(EventParticles[100 + k],
                                     EventParticles[100 + k + 1]) k += 2;
      }
    }
  }

  /*
  Particle::AddParticleType("Protone", 1, 2);
  Particle::AddParticleType("Neutrone", 4, 5, 6);
  Particle t{"Neutrone", 7, 8, 9};
  Particle s{"Protone", 13, 24, 17};
  Particle::PrintParticles();
  t.PrintType();
  t.TotEnergy();
  t.InvMass(s);
  ParticleType* array[2];
  array[0] = &proton;
  array[1] = &neutron;
  for (int i{0}; i < 2; i++) {
    array[i]->print();
  }
 (*array[1]).print();*/
}
