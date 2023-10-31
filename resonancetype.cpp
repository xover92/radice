#include "ResonanceType.hpp"
#include <iostream>

ResonanceType::ResonanceType(const char* fName, double fMass, int fCharge, double fWidth) 
: ParticleType(fName,fMass,fCharge),fWidth_(fWidth) {}
double ResonanceType::GetWidth() const { return fWidth_;}
void ResonanceType::print() {
    ParticleType::print();
    std::cout<< "The width is: "<< fWidth_<<'\n';
}