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

#include "StackingAction.hh"
extern G4bool detTest;
extern G4bool debug;
extern G4bool bremTest;

StackingAction::StackingAction()
{
  if(debug)
    std::cout << "StackingAction::StackingAction -> Initialized." << std::endl;
}

StackingAction::~StackingAction()
{
}

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track* currentTrack)
{
  if(!detTest && !bremTest)
  {

    DetectorInformation* detInfo = DetectorInformation::Instance();
    // if a new track is created beyond interogation material kill it
    G4double EndIntObj = detInfo->getEndIntObj();
    G4double trackZ = currentTrack->GetPosition().z();
    if(trackZ/(cm) > EndIntObj/(cm))
    {
      RunInformation* runInfo = RunInformation::Instance();
      runInfo->AddStatusKilledPosition();
      return fKill;
    }
  }


  if(currentTrack->GetGlobalTime() > 10000) return fKill; // if secondary track time is greater than 10000 ns kill it

  G4ParticleDefinition *pdef = currentTrack->GetDefinition();
  // kill neutrons (probably not important)
  if(pdef == G4Neutron::Definition()) return fKill;

  return fUrgent;
}
