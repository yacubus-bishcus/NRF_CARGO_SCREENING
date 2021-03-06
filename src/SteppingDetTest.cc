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

#include "SteppingDetTest.hh"

extern G4bool output;
extern G4long seed;
extern G4bool debug;
extern G4bool WEIGHTED;


SteppingDetTest::SteppingDetTest(EventAction* event)
: G4UserSteppingAction(), BaseSteppingAction(), kevent(event)
{
  fExpectedNextStatus = Undefined;
  if(debug)
    std::cout << "SteppingDetTest::SteppingDetTest Initialized." << std::endl;
}

SteppingDetTest::~SteppingDetTest()
{}

void SteppingDetTest::UserSteppingAction(const G4Step* aStep)
{
  if(!output)
    return;

    G4StepPoint* endPoint   = aStep->GetPostStepPoint();
    G4StepPoint* startPoint = aStep->GetPreStepPoint();
    G4Track* theTrack       = aStep->GetTrack();

    // Run Logical Checks
    if(endPoint == NULL)
    {
      return; // at the end of the world
    }
    else if(endPoint->GetPhysicalVolume()==NULL)
    {
      return;
    }

    // Grab Relevant event information including the particle weight
    EventInformation* info =
              (EventInformation*)(G4RunManager::GetRunManager()->GetCurrentEvent()->GetUserInformation());
    beamEnergy = info->GetBeamEnergy()/(MeV);

    nextStep_VolumeName = endPoint->GetPhysicalVolume()->GetName();
    previousStep_VolumeName = startPoint->GetPhysicalVolume()->GetName();

    // Run Time Cut
    if(theTrack->GetGlobalTime() > 250) // cut placed on particles time greater than 250 ns
    {
      theTrack->SetTrackStatus(fStopAndKill);
      krun->AddStatusKilledTime();
      return;
    }

    eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    trackID = theTrack->GetTrackID();
    energy = theTrack->GetKineticEnergy()/(MeV);
    gtime = theTrack->GetGlobalTime();

    CPName = "beam";
    if(theTrack->GetCreatorProcess() !=0)
      CPName = theTrack->GetCreatorProcess()->GetProcessName();

    G4ThreeVector p = startPoint->GetMomentum();
    theta = std::asin(std::sqrt(std::pow(p.x(),2)+std::pow(p.y(),2))/p.mag());
    phi = std::asin(p.y()/p.mag());
    G4ThreeVector loc = theTrack->GetPosition();

// *********************************************** Track Shielding Interactions  **************************************************** //

    // Track particles incident shielding from world

    if(nextStep_VolumeName.compare(0,5,"Atten") == 0
        && previousStep_VolumeName.compare("World") == 0)
    {
      FillShielding(0);
      return;
    }

// *********************************************** Track Plexiglass Interactions **************************************************** //

    if(nextStep_VolumeName.compare(0,4,"Plex") == 0
        && previousStep_VolumeName.compare(0,4,"Last") == 0)
    {
      if(std::cos(phi) < 0.6)
      {
        krun->AddStatusKilledPhiAngle();
        theTrack->SetTrackStatus(fStopAndKill);
        return;
      }
      if(std::cos(theta) < 0.2)
      {
        krun->AddStatusKilledThetaAngle();
        theTrack->SetTrackStatus(fStopAndKill);
        return;
      }
      FillPlexi(1);
    }

    if(nextStep_VolumeName.compare("Water") == 0
        && previousStep_VolumeName.compare("Tape") == 0)
    {
      if(trackID == 1)
        kevent->SetIncidentEnergy(energy);

      return;
    }

    // While in water keep track of cherenkov and pass number of cherenkov to EventAction
    if(startPoint->GetPhysicalVolume()->GetName().compare("Water")==0)
    {
      const std::vector<const G4Track*>* secondaries = aStep->GetSecondaryInCurrentStep();
      if(secondaries->size()>0)
      {
        for(unsigned int i=0; i<secondaries->size(); ++i)
        {
          if(secondaries->at(i)->GetParentID()>0)
          {
              if(secondaries->at(i)->GetDynamicParticle()->GetParticleDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
              {
                if(secondaries->at(i)->GetCreatorProcess()->GetProcessName() == "Scintillation")
                {
                  // for event level scintillation photon data
                  kevent->ScintillationEnergy(energy);
                  kevent->ScintillationAddSecondary();
                  krun->AddScintillationEnergy(secondaries->at(i)->GetKineticEnergy());
                  krun->AddScintillation();
                }
                if(secondaries->at(i)->GetCreatorProcess()->GetProcessName() == "Cerenkov")
                {
                  // for event level cherenkov photon data
                  kevent->CherenkovEnergy(energy);
                  kevent->CherenkovAddSecondary();
                  krun->AddCerenkovEnergy(secondaries->at(i)->GetKineticEnergy());
                  krun->AddCerenkov();
                } // end of if secondaries->at(i)->GetCreatorProcess
              } // end of if secondaries->at(i)->GetDynamicParticle()
          } // end of if secondaries->at(i)->GetParentID()
        } // end of for loop
      } // end of optical photons if statement
    } // end of if loop while inside water

// *********************************************** Track Photocathode Interactions **************************************************** //

  // Photocathode Analysis

  if(endPoint->GetStepStatus() == fGeomBoundary)
  {
    const G4DynamicParticle* theParticle = theTrack->GetDynamicParticle();
    G4OpBoundaryProcessStatus theStatus = Undefined;
    G4ProcessManager* OpManager =
            G4OpticalPhoton::OpticalPhoton()->GetProcessManager();
    G4int MAXofPostStepLoops =
            OpManager->GetPostStepProcessVector()->entries();
    G4ProcessVector* postStepDoItVector =
            OpManager->GetPostStepProcessVector(typeDoIt);
    // incident photocathode
    if(nextStep_VolumeName.compare("PC")==0
       && previousStep_VolumeName.compare("PC")!=0)
    {
      krun->AddTotalSurface();
      for (G4int i=0; i<MAXofPostStepLoops; ++i)
      {
        G4VProcess* currentProcess = (*postStepDoItVector)[i];
        G4OpBoundaryProcess* opProc = dynamic_cast<G4OpBoundaryProcess*>(currentProcess);

        if(opProc)
        {
          theStatus = opProc->GetStatus();
          if (theStatus == Detection)
          {
            G4String creatorProcess;

            if(theTrack->GetCreatorProcess() !=0)
                creatorProcess = theTrack->GetCreatorProcess()->GetProcessName();
            else
                creatorProcess = "Beam";

            kevent->AddDetected();
            if(creatorProcess == "Scintillation")
              kevent->AddDetectedScintillation();
            else if(creatorProcess == "Cerenkov")
              kevent->AddDetectedCherenkov();

          } // for if status == Detection
        } // for if opProc
      } // for for loop
    } // for if statement if first time in photocathode
  } // for if at boundary
} // end of SteppingDetTest::UserSteppingAction
