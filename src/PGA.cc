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

#include "PGA.hh"

extern G4bool WEIGHTED;
extern G4double chosen_energy;
extern G4bool SampleEnergyRangebool;
extern G4bool resonanceTest;
extern G4bool debug;
extern G4double uniform_width;

PGA::PGA()
: G4VUserPrimaryGeneratorAction(), BasePGA()
{
  SetupNonBremTest();
  if(chosen_energy < 0 && !resonanceTest && !SampleEnergyRangebool)
  {

    if(WEIGHTED)
    {
      ReadWeighted();
      file_check = false;
    }
    else
    {
      ReadNonWeighted();
      file_check = true;
    }
  }
  else if(chosen_energy > 0)
    SetUserEnergy();

  CallMessenger();
  StartUserMacroInputs();
}

PGA::~PGA()
{
}

void PGA::GeneratePrimaries(G4Event* anEvent)
{
  if(debug && anEvent->GetEventID() == 0)
    std::cout << "PGA::GeneratePrimaries -> First Primary Generated." << std::endl;

  G4double w = 1.;
  if(!resonanceTest && chosen_energy < 0)
  {
    // User IS USING importance sampling
    if(!file_check)
    {
      energy = h_sample->GetRandom()*MeV;
      G4double dNdE = g_input->Eval(energy);
      G4double importanceSampling = g_sample->Eval(energy);
      w = dNdE/importanceSampling;
    }
    // User IS NOT USING importance sampling
    else
    {
      double random = G4UniformRand()*N[N.size() - 1];
      for(unsigned int i=0;i<N.size();++i)
      {
        if(N[i] > random)
        {
          double f = (random - N[i - 1]) / (N[i] - N[i - 1]);
          energy = f*energies[i] + (1 - f)*energies[i - 1];
          break;
        } // end of if(N[i] > random )
      } // end of for
    } // end of else not using importance sampling !filecheck
    energy = energy*MeV;
  } // end of !resonance
  else if(chosen_energy > 0 && !SampleEnergyRangebool)
    energy = chosen_energy*MeV;
  else if(chosen_energy > 0 && SampleEnergyRangebool)
    energy = SampleEnergyRange(chosen_energy,uniform_width);
  else if(resonanceTest)
    energy = SampleUResonances();

// ************************************************************************************ //
// Input Handling Complete
// ************************************************************************************ //

  // Set the energy
  fParticleGun->SetParticleEnergy(energy);

  // Set beam position
  G4double x_r = beam_size*acos(G4UniformRand())/pi*2.*cos(360.*G4UniformRand()*CLHEP::deg);
  G4double y_r = beam_size*acos(G4UniformRand())/pi*2.*sin(360.*G4UniformRand()*CLHEP::deg);
  fParticleGun->SetParticlePosition(G4ThreeVector(x_r,y_r,beamStart)); // set the electron beam far enough back behind brem radiator

  // Set beam momentum

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1)); // along z axis

  fParticleGun->GeneratePrimaryVertex(anEvent);

// Pass the event information
  eventInformation *anInfo = new eventInformation(anEvent);
  anInfo->SetWeight(w);
  anInfo->SetBeamEnergy(energy);
  anEvent->SetUserInformation(anInfo);

  if(debug && anEvent->GetEventID() == 0)
    std::cout << "PGA::GeneratePrimaries -> First Primary Complete." << std::endl;
}
