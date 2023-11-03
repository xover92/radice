
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
  virtual double GetWidth() const;
  /* print dichiarato virtual altrimenti nel ciclo for che stampa la
  informazioni sulle particelle viene invocato il print della classe base anche
  per le risonanze. !Controllare definizione metodo print per resonancetypr
  */
};

#endif