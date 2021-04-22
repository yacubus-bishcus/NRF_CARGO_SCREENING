//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Author:
// Jacob E Bickus, 2021
// MIT, NSE
// jbickus@mit.edu
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
///////////////////////////////////////////////////////////////////////////////

#ifndef DetResponsePrimaryGenerator_h
#define DetResponsePrimaryGenerator_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "Analysis.hh"
#include "globals.hh"
#include <vector>
#include "G4ParticleGun.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4Gamma.hh"
#include "eventInformation.hh"
#include "SourceInformation.hh"
#include "DetectorInformation.hh"

#include "TFile.h"
#include "TROOT.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TRandom2.h"
#include "TSystem.h"
#include "TMath.h"

class G4Event;
class Analysis;

class DetResponsePrimaryGenerator : public G4VUserPrimaryGeneratorAction
{

public:
DetResponsePrimaryGenerator();
virtual ~DetResponsePrimaryGenerator();

public:
virtual void GeneratePrimaries(G4Event*);
G4ParticleGun* GetParticleGun()
{
  return fParticleGun;
};
void SetBeamSizeX(G4double x)
{
  beam_size_x = x;
  G4cout << "DetResponsePrimaryGenerator::BeamSizeX set to: " << beam_size_x << " cm" << G4endl;
}
void SetBeamSizeY(G4double y)
{
  beam_size_y = y;
  G4cout << "DetResponsePrimaryGenerator::BeamSizeY set to: " << beam_size_y << " cm" << G4endl;
}

void SetBeamMax(G4double maxE){beamMax = maxE;}
G4double GetBeamMax()const {return beamMax;}

void CloseInputFile(){if(fFileOpen) fin->Close();}

private:
  void CreateInputSpectrum(TGraph*);
  void CheckFile(const char*);
  G4double SampleEnergyRange(double,double);

private:
  G4ParticleGun* fParticleGun;
  G4double beamStart, beamMax;
  G4double beam_size_x, beam_size_y, energy;
  G4bool file_check, fFileOpen;
  std::vector<double> energies, N;
  // ROOT
  TRandom2 Random;
  TGraph *tBrems;
  TGraph *gSample;
  TH1D* hSample;
  TFile *fin;
};

#endif