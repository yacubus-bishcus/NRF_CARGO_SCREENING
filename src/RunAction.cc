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

#include "RunAction.hh"

extern G4bool output;
extern G4bool debug;
extern G4bool WResponseFunction;
extern G4bool bremTest;

RunAction::RunAction(Analysis* histoAnalysis)
        : G4UserRunAction(), fAnalysis(histoAnalysis)
{
}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run*)
{
  if(output)
  {
    fAnalysis->Book();
  }

  if(debug)
    std::cout << "RunAction::BeginOfRunAction -> Beginning Run..." << std::endl;

  G4cout << G4endl << "Beginning Run..." << G4endl;
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
  InputFileManager *ifm = InputFileManager::Instance();
  ifm->CloseInputFile();
  G4cout << G4endl << "RunAction::EndOfRunAction -> Input File Closed." << G4endl;

  if(WResponseFunction)
  {
    DetectorResponseFunction* dResponse = DetectorResponseFunction::Instance();
    dResponse->CloseInputFile();
    G4cout << G4endl
    << "RunAction::EndOfRunAction -> DetectorResponseFunction Input File Closed."
    << G4endl;
  }

  RunInformation* rInfo = RunInformation::Instance();
  G4int fTotalSurface = rInfo->GetTotalSurface();
  G4int fNRF = rInfo->GetTotalNRF();
  G4int fCerenkovCount = rInfo->GetTotalCerenkov();
  G4int fScintCount = rInfo->GetTotalScintCount();
  G4int fStatusKilledPosition = rInfo->GetTotalKilledPosition();
  G4int fStatusKilledTime = rInfo->GetTotalKilledTime();
  G4int fStatusKilledThetaAngle = rInfo->GetTotalKilledTheta();
  G4int fStatusKilledPhiAngle = rInfo->GetTotalKilledPhi();
  G4double fCerenkovEnergy = rInfo->GetTotalCerenkovEnergy();
  G4double fScintEnergy = rInfo->GetTotalScintEnergy();
  G4int fBremBackingCount = rInfo->GetTotalBremBackingHit();
  G4int fStatusKilledProcess = rInfo->GetTotalKilledProcess();


  G4int TotNbofEvents = aRun->GetNumberOfEvent();
  std::ios::fmtflags mode = G4cout.flags();
  G4int prec = G4cout.precision(2);
  G4cout << G4endl << "Run Summary" << G4endl;
  G4cout << "----------------------------------------------------------------------"
    << G4endl;
  G4cout << "Total Number of Events:                                      "
    << TotNbofEvents << G4endl;

  if(!bremTest)
  {
    G4cout << "Total number of Surface Events:                              "
      << fTotalSurface << G4endl;
    if(!WResponseFunction)
    {
      G4cout << "Total number of Cherenkov Photons:                           "
        << fCerenkovCount << G4endl;
      G4cout << "Total number of Scintillation Photons:                       "
        << fScintCount << G4endl;
      G4cout << "Total number of Optical Photons:                             "
        << fCerenkovCount + fScintCount << G4endl;
    }
    G4cout << "Total number of NRF Photons:                                 "
      << fNRF << G4endl;
  }

  G4cout << "Total number of Tracks Cut Based on Position:                "
    << fStatusKilledPosition << G4endl;
  G4cout << "Total number of Tracks Cut Based on Process:                 "
    << fStatusKilledProcess << G4endl;
  G4cout << "Total number of Tracks Cut Based on Time:                    "
    << fStatusKilledTime << G4endl;
  G4cout << "Total number of Tracks Cut Based on Theta Emission Angle:    "
    << fStatusKilledThetaAngle << G4endl;
  G4cout << "Total number of Tracks Cut Based on Phi Emission Angle:      "
    << fStatusKilledPhiAngle << G4endl;

  if(!bremTest && !WResponseFunction)
  {
    if (fCerenkovCount > 0)
    {
      G4cout << "Average Cherenkov Photon energy emitted:                    "
             << (fCerenkovEnergy/eV)/fCerenkovCount << " eV." << G4endl;
    }

    if (fScintCount > 0)
    {
      G4cout << "Average Scintillation Photon energy emitted:                "
             << (fScintEnergy/eV)/fScintCount << " eV." << G4endl;
    }
  }

  if(bremTest)
  {
    if(fBremBackingCount > 0)
    {
      G4cout << "Total Number of Brem Backing Hits:                           " << fBremBackingCount << G4endl;
    }
  }

  G4cout << "----------------------------------------------------------------------" << G4endl;

  G4cout.setf(mode, std::ios::floatfield);

  G4cout.precision(prec);

  if(output)
  {
    fAnalysis->finish();
  }
}
