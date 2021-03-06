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

#include "StepMessenger.hh"

StepMessenger::StepMessenger(BaseSteppingAction* stepAction)
        : stepA(stepAction)
{
  myDir = new G4UIdirectory("/output/");
  myDir->SetGuidance("Output Commands");
  Cmd = new G4UIcmdWithAString("/output/myoutput",this);
  Cmd->SetGuidance("Choose Desired Outputs");
  Cmd->SetGuidance("Choice: ChopIncData, ChopOutData, NRFData, IntObjInData, IntObjOutData, ShieldingData, PlexiData, WaterIncData, ScintillationData, ScintillationData2, CherenkovData, CherenkovData2, DetData, none (default)");
  Cmd->SetParameterName("choice",false);
  Cmd->SetDefaultValue("none");
  Cmd->SetCandidates("ChopIncData ChopOutData NRFData IntObjInData IntObjOutData ShieldingData PlexiData WaterIncData ScintillationData ScintillationData2 CherenkovData CherenkovData2 DetData none");
}

StepMessenger::~StepMessenger()
{
  delete Cmd;
}


void StepMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ // this function only works if named SetNewValue
  if(command == Cmd)
  {
    G4String theCommand = newValue;
    if(theCommand == "ChopIncData")
    {
      stepA->SetChopperIncDataFlag(1);
      G4cout << G4endl << "User Selected Chopper Incident Data." << G4endl;
    }
    else if(theCommand == "ChopOutData")
    {
      stepA->SetChopperOutDataFlag(1);
      G4cout << G4endl << "User Selected Chopper Emission Data." << G4endl;
    }
    else if(theCommand == "NRFData")
    {
      stepA->SetNRFDataFlag(1);
      G4cout << G4endl << "User Selected NRF Data." << G4endl;
    }
    else if(theCommand == "IntObjInData")
    {
      stepA->SetIntObjInDataFlag(1);
      G4cout << G4endl << "User Selected Interrogation Object Incident Data." << G4endl;
    }
    else if(theCommand == "IntObjOutData")
    {
      stepA->SetIntObjOutDataFlag(1);
      G4cout << G4endl << "User Selected Interrogation Object Emission Data." << G4endl;
    }
    else if(theCommand == "ShieldingData")
    {
      stepA->SetShieldingIncDataFlag(1);
      G4cout << G4endl << "User Selected Incident Shielding Data." << G4endl;
    }
    else if(theCommand == "PlexiData")
    {
      stepA->SetPlexiIncDataFlag(1);
      G4cout << G4endl << "User Selected Incident Plexiglass Data." << G4endl;
    }
    else if(theCommand == "WaterIncData")
    {
      stepA->SetWaterIncDataFlag(1);
      G4cout << G4endl << "User Selected Incident Water Data." <<G4endl;
    }
    else if(theCommand == "ScintillationData")
    {
      stepA->SetScintillationDataFlag(1);
      G4cout << G4endl << "User Selected Scintillation Data." << G4endl;
    }
    else if(theCommand == "ScintillationData2")
    {
      stepA->SetScintillation2DataFlag(1);
      G4cout << G4endl << "User Selected Scintillation2 Data." << G4endl;
    }
    else if(theCommand == "CherenkovData")
    {
      stepA->SetCherenkovDataFlag(1);
      G4cout << G4endl << "User Selected Cherenkov Data." <<G4endl;
    }
    else if(theCommand == "CherenkovData2")
    {
      stepA->SetCherenkov2DataFlag(1);
      G4cout << G4endl << "User Selected Cherenkov2 Data." << G4endl;
    }
    else if(theCommand == "DetData")
    {
      stepA->SetDetDataFlag(1);
      G4cout << G4endl << "User Selected Detected Data."<<G4endl;
    }
  } // end of if command == cmd
} // end of set new value function
