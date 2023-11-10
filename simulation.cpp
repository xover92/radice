
#include <iostream>
#include <vector>

#include "Particle.hpp"
#include "ParticleType.hpp"
#include "ResonanceType.hpp"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TMath.h"
#include "TRandom.h"

int Sium() {
  gRandom->SetSeed();
  TString histName = "h";
  Particle::AddParticleType("Pione+", 0.13957, 1);
  Particle::AddParticleType("Pione-", 0.13957, -1);
  Particle::AddParticleType("Kaone+", 0, 49367, 1);
  Particle::AddParticleType("Kaone-", 0, 49367, -1);
  Particle::AddParticleType("Protone+", 0.93827, 1);
  Particle::AddParticleType("Protone-", 0.93827, -1);
  Particle::AddParticleType("K*", 0.89166, 0, 0.05);

  Particle EventParticles[120];

  TH1F *h1 = new TH1F("Isto1", "Tipi di particelle gnerate", 7, 0., 7.);
  TH1F *h2 =
      new TH1F("Isto2", "Distribuzione angoli azimutali", 10, 0., 6.2832);
  TH1F *h3 = new TH1F("Isto3", "Distribuzione angoli polari", 10, 0., 3.1416);
  TH1F *h4 = new TH1F("Isto4", "Distribuzione impulso", 500, 0., 5.);
  TH1F *h5 = new TH1F("Isto5", "Impulso Trasverso", 600, 0., 5.);
  TH1F *h6 = new TH1F("Isto6", "Distribuzione Energia", 600, 0., 4.);
  TH1F *h7 = new TH1F("Isto7", "Massa invariante gen.", 8000, 0., 7.);
  TH1F *h8 = new TH1F("Isto8", "Massa invariante segno discorde", 8000, 0., 7.);
  TH1F *h9 = new TH1F("Isto9", "Massa invariante segno concorde", 8000, 0., 7.);
  TH1F *h10 =
      new TH1F("Isto10", "Massa invariante  P/K segno discorde", 5000, 0., 6.);
  TH1F *h11 =
      new TH1F("Isto11", "Massa invariante P/K segno concorde", 5000, 0., 6.);
  TH1F *h12 = new TH1F("Isto12", "Istogramma di benchmark", 700, 0.5, 1.5);
  h7->Sumw2();
  h8->Sumw2();
  h9->Sumw2();
  h10->Sumw2();
  h11->Sumw2();

  // TH1F *h8 = new TH1F("Isto8","Distribuzione angoli
  // polari",10,0., 3.1416);//per dopo
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
      h3->Fill(theta);
      h2->Fill(phi);
      EventParticles[j].SetP(impulse * TMath::Sin(theta) * TMath::Cos(phi),
                             impulse * TMath::Sin(theta) * TMath::Sin(phi),
                             impulse * TMath::Cos(theta));
      h4->Fill(sqrt(EventParticles[j].GetPx() * EventParticles[j].GetPx() +
                    EventParticles[j].GetPy() * EventParticles[j].GetPy() +
                    EventParticles[j].GetPz() * EventParticles[j].GetPz()));
      h5->Fill(sqrt(EventParticles[j].GetPx() * EventParticles[j].GetPx() +
                    EventParticles[j].GetPy() * EventParticles[j].GetPy()));

      double x = gRandom->Rndm();
      if (x < 0.4) {
        EventParticles[j].SetIndex("Pione+");
      } else if (x < 0.8) {
        EventParticles[j].SetIndex("Pione-");
      } else if (x < 0.85) {
        EventParticles[j].SetIndex("Kaone+");
      } else if (x < 0.90) {
        EventParticles[j].SetIndex("Kaone-");
      } else if (x < 0.945) {
        EventParticles[j].SetIndex("Protone+");
      }  // ricordiamoci di cambiare negli effettivi
      else if (x < 0.99) {
        EventParticles[j].SetIndex("Protone-");
      }  // indici perchè questi sono tanti loop e pesano
      else {
        EventParticles[j].SetIndex("K*");
      }

      if (EventParticles[j].GetParticleIndex() == 6 /*FindParticle("K*")*/) {
        double y = gRandom->Rndm();
        if (y < 0.5) {
          EventParticles[100 + k].SetIndex("Pione+");
          EventParticles[100 + k + 1].SetIndex("Kaone-");
        } else {
          EventParticles[100 + k].SetIndex("Pione-");
          EventParticles[100 + k + 1].SetIndex("Kaone+");
        }
        EventParticles[j].Decay2body(EventParticles[100 + k],
                                     EventParticles[100 + k + 1]);

        h12->Fill(EventParticles[100 + k].InvMass(EventParticles[100 + k + 1]));
        k += 2;
      }
      h1->Fill(EventParticles[j].GetParticleIndex());
      h6->Fill(EventParticles[j].TotEnergy());
    }
    for (int n{0}; n < 120; n++) {
      for (int m{n + 1}; m < 120; m++) {
        if (EventParticles[m].GetMass() != 0.89166 &&
            EventParticles[n].GetMass() != 0.89166) {
          auto z = EventParticles[n].InvMass(EventParticles[m]);
          h7->Fill(z);
        }
        if (EventParticles[m].GetCharge() != EventParticles[n].GetCharge()) {
          auto w = EventParticles[n].InvMass(EventParticles[m]);
          h8->Fill(w);
        }
        if (EventParticles[m].GetCharge() == EventParticles[n].GetCharge()) {
          auto v = EventParticles[n].InvMass(EventParticles[m]);
          h9->Fill(v);
        }
        if ((EventParticles[m].GetParticleIndex() == 0 &&
             EventParticles[n].GetParticleIndex() == 3) ||
            (EventParticles[m].GetParticleIndex() == 1 &&
             EventParticles[n].GetParticleIndex() == 2)) {
          auto r = EventParticles[n].InvMass(EventParticles[m]);
          h10->Fill(r);
        }
        if ((EventParticles[m].GetParticleIndex() == 0 &&
             EventParticles[n].GetParticleIndex() == 2) ||
            (EventParticles[m].GetParticleIndex() == 1 &&
             EventParticles[n].GetParticleIndex() == 3)) {
          auto q = EventParticles[n].InvMass(EventParticles[m]);
          h11->Fill(q);
        }
        EventParticles[j].Decay2Body(EventParticles[100 + k],
                                     EventParticles[100 + k + 1]);
        k += 2;

       
      }
      for (int m{0}; m<100+k; m++) {
       h1->Fill( EventParticles[m].GetParticleType()) //probabilmente sbagliato
      }
      
    }
  
  }

  TCanvas *t1 = new TCanvas();
  TCanvas *t2 = new TCanvas();

  t1->Divide(2, 2);
  t2->Divide(2, 2);

  t1->cd(1);
  h1->Draw();
  t1->cd(2);
  h2->Draw();
  t1->cd(3);
  h3->Draw();
  t1->cd(4);
  h4->Draw();

  t2->cd(1);
  h5->Draw();
  t2->cd(2);
  h6->Draw();
  t2->cd(3);
  h7->Draw();

  TCanvas *t3 = new TCanvas();

  h8->Draw();
  TCanvas *t4 = new TCanvas();

  h9->Draw();

  TCanvas *t5 = new TCanvas();

  h10->Draw();
  TCanvas *t6 = new TCanvas();

  h11->Draw();
  TCanvas *t7 = new TCanvas();
  h12->Draw();

  return 0;
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
(*array[1]).print();


      h7->Fill(EventParticles[m].InvMass(
          EventParticles[m + 1]));  // chiuedere. tutte le combinazioni
                                    // possibili? non sono troppe entrate???
      if (Array[EventParticles[m].GetParticleIndex()]
              ->ParticleType::GetCharge() !=
          Array[EventParticles[m + 1].GetParticleIndex()]
              ->ParticleType::GetCharge()) {
        h8->Fill(EventParticles[m].InvMass(EventParticles[m + 1]));
      } else {
        h9->Fill(EventParticles[m].InvMass(EventParticles[m + 1]));

*/
